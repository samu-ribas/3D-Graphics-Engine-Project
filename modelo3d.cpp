#include "modelo3d.h"
#include <QFile>
#include <QTextStream>
#include <sstream>
#include <string>
#include <QMessageBox>

Modelo3D::Modelo3D(QString n, std::list<Coordenada> vertices, const std::vector<std::vector<int>>& facesObj) : Forma(n, TipoForma::MODELO3D){
    this->p = vertices;
    this->faces = facesObj;
}

Modelo3D* Modelo3D::carregarOBJ(const QString& nome, const QString& caminho)
{
    QFile file(caminho);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){ // digo que é texto pra reconhecer \n
        QMessageBox::critical(nullptr, "Erro", "Não foi possível abrir o arquivo OBJ: " + caminho);
        return nullptr;
    }

    std::list<Coordenada> vertices;
    std::vector<std::vector<int>> faces; //cada face é um vetor de índices
    QString line;

    QTextStream stream(&file);
    while(!stream.atEnd())
    {   //retorna verdadeiro se não houver mais dados para serem lidos do QTextStream;
        line = stream.readLine().trimmed();

        if(line.isEmpty() || line.startsWith('#')){//pula se for vazia ou comentario
            continue;
        }

        // converte a linha para std::string para usar std::istringstream
        std::string linhaStd = line.toStdString();
        std::istringstream iss(linhaStd);
        std::string tipo;
        iss >> tipo;

        if(tipo == "v"){
            // Vértice: v x y z
            double x, y, z;
            if(iss >> x >> y >> z){
                vertices.push_back(Coordenada(x, y, z));
            }
        }else if (tipo == "f"){
            // Face: f v1[/vt1][/vn1] v2[/vt2][/vn2] ...
            std::vector<int> faceIndices;
            std::string token;
            while(iss >> token)
            {
                //extrai apenas o primeiro número (índice do vértice)
                size_t slashPos = token.find('/');
                std::string idxStr = (slashPos == std::string::npos) ? token : token.substr(0, slashPos);

                //converte para inteiro
                char* end;
                long idx = std::strtol(idxStr.c_str(), &end, 10);

                if (*end != '\0') {
                    continue;
                }
                //OBJ é 1‑based
                if(idx == 0){
                    continue;
                }

                if(idx < 0){
                    idx = static_cast<long>(vertices.size()) + idx; // -1 vira size-1
                }else{
                    idx--; //converte para 0‑based
                }

                if(idx >= 0 && idx < static_cast<long>(vertices.size())){
                    faceIndices.push_back(static_cast<int>(idx));
                }
            }
            //triangula a face (se tiver mais de 3 vértices)
            if(faceIndices.size() >= 3){
                for(size_t i = 1; i + 1 < faceIndices.size(); ++i){
                    faces.push_back({ faceIndices[0], faceIndices[i], faceIndices[i + 1] });
                }
            }
        }
        //ignorar vt, vn, g, o
    }

    if(vertices.empty() || faces.empty()){
        QMessageBox::warning(nullptr, "Erro", "Arquivo OBJ sem vértices ou faces válidas.");
        return nullptr;
    }

    double minX=1e9, maxX=-1e9, minY=1e9, maxY=-1e9;

    for (auto& v : vertices) {
        minX = std::min(minX, v.x_wc);
        maxX = std::max(maxX, v.x_wc);
        minY = std::min(minY, v.y_wc);
        maxY = std::max(maxY, v.y_wc);
    }
    double sx = 200.0 / (maxX - minX);
    double sy = 200.0 / (maxY - minY);
    double tx = -(minX + maxX) / 2.0;
    double ty = -(minY + maxY) / 2.0;

    for(auto& v : vertices){
        v.x_wc = (v.x_wc + tx) * sx;
        v.y_wc = (v.y_wc + ty) * sy;
        v.z_wc *= sx;
    }

    return new Modelo3D(nome, vertices, faces);
}

void Modelo3D:: desenhar(QPainter &painter, const Matriz& mView, const Matriz& mProj, const Viewport& win, double zoom){
    std::vector<Coordenada> vertices_vector(this->p.begin(), this->p.end());
    double z_near = 1.0;
    double sx = (2.0 / win.getLargura()) * zoom;
    double sy = (2.0 / win.getAltura())  * zoom;

    for(const auto& face : faces){
        if(face.size() < 3){
            continue;
        }
        Coordenada v[3];
        for(int i = 0; i < 3; ++i){
            int idx = face[i];
            if (idx < 0 || idx >= (int)vertices_vector.size()){
                continue;
            }
            v[i] = mView * vertices_vector[idx];
        }

        for(int i = 0; i < 3; ++i){
            Coordenada p1 = v[i];
            Coordenada p2 = v[(i + 1) % 3];

            if(!clipNearPlane(p1, p2, z_near)){
                continue;
            }

            p1 = mProj * p1;
            p2 = mProj * p2;

            p1.x_wc *= sx;
            p1.y_wc *= sy;
            p2.x_wc *= sx;
            p2.y_wc *= sy;

            p1.x_scn = p1.x_wc;
            p1.y_scn = p1.y_wc;
            p2.x_scn = p2.x_wc;
            p2.y_scn = p2.y_wc;

            LimitesSCN limites = Viewport::getLimitesSCN();
            if(!cohenSutherland(p1, p2, limites)){
                continue;
            }

            double x1_vp = (p1.x_wc + 1.0) * (win.getLargura() / 2.0);
            double y1_vp = (1.0 - p1.y_wc) * (win.getAltura()  / 2.0);
            double x2_vp = (p2.x_wc + 1.0) * (win.getLargura() / 2.0);
            double y2_vp = (1.0 - p2.y_wc) * (win.getAltura()  / 2.0);

            painter.drawLine(x1_vp, y1_vp, x2_vp, y2_vp);
        }
    }
}

