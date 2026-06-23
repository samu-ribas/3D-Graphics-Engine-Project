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
    while(!stream.atEnd()){ //retorna verdadeiro se não houver mais dados para serem lidos do QTextStream;
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
            }else{
                qDebug() << "Linha de vértice mal formatada:" << line;
            }
        }else if (tipo == "f"){
            // Face: f v1[/vt1][/vn1] v2[/vt2][/vn2] ...
            std::vector<int> faceIndices;
            std::string token;
            while(iss >> token){
                //extrai apenas o primeiro número (índice do vértice)
                size_t slashPos = token.find('/');
                std::string idxStr = (slashPos == std::string::npos) ? token : token.substr(0, slashPos);
                //converte para inteiro
                char* end;
                long idx = std::strtol(idxStr.c_str(), &end, 10);
                if (*end != '\0') {
                    qDebug() << "Índice inválido na face:" << token.c_str();
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
                }else{
                    qDebug() << "Índice fora dos limites:" << idx;
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

void Modelo3D::desenhar(QPainter &painter, const Matriz& mCam, const Window& win) {
    if(p.empty() || this->faces.empty()){
        return;
    }
    // Converte a lista de vértices para vetor para acesso por índice
    std::vector<Coordenada> vertices(p.begin(), p.end());

    QPen caneta(Qt::white, 1);
    painter.setPen(caneta);

    LimitesWindow limitesSCN = Window::getLimitesSCN();

    for(const auto& face : faces){
        if(face.size() < 3) continue;

        std::vector<Coordenada> faceSCN;
        for(int aux : face){
            if(aux < 0 || aux >= (int)vertices.size()){
                continue;
            }
            faceSCN.push_back(mCam * vertices[aux]);
        }

        for(size_t i = 0; i < faceSCN.size(); ++i){
            Coordenada p1 = faceSCN[i];
            Coordenada p2 = faceSCN[(i + 1) % faceSCN.size()];

            double x0 = p1.x_wc;
            double y0 = p1.y_wc;
            double x1 = p2.x_wc;
            double y1 = p2.y_wc;

            std::bitset<4> outcode0 = this->getOutcode(x0, y0, limitesSCN);
            std::bitset<4> outcode1 = this->getOutcode(x1, y1, limitesSCN);
            bool accept = false;

            while(true){
                if((outcode0 | outcode1).none()){
                    accept = true;
                    break;
                }
                if((outcode0 & outcode1).any())
                    break;

                std::bitset<4> out_fora = outcode0.any() ? outcode0 : outcode1;
                double x = 0.0, y = 0.0;

                if(out_fora.test(3)){
                    x = x0 + (x1 - x0) * (1.0 - y0) / (y1 - y0);
                    y = 1.0;
                }else if(out_fora.test(2)){
                    x = x0 + (x1 - x0) * (-1.0 - y0) / (y1 - y0);
                    y = -1.0;
                }else if(out_fora.test(1)){
                    y = y0 + (y1 - y0) * (1.0 - x0) / (x1 - x0);
                    x = 1.0;
                }else if(out_fora.test(0)){
                    y = y0 + (y1 - y0) * (-1.0 - x0) / (x1 - x0);
                    x = -1.0;
                }

                if(out_fora == outcode0){
                    x0 = x; y0 = y;
                    outcode0 = this->getOutcode(x0, y0, limitesSCN);
                }else{
                    x1 = x; y1 = y;
                    outcode1 = this->getOutcode(x1, y1, limitesSCN);
                }
            }

            if(accept){
                double x_vp0 = (x0 + 1.0) * (win.getLargura() / 2.0);
                double y_vp0 = (1.0 - y0) * (win.getAltura() / 2.0);

                double x_vp1 = (x1 + 1.0) * (win.getLargura() / 2.0);
                double y_vp1 = (1.0 - y1) * (win.getAltura() / 2.0);

                painter.drawLine(QPointF(x_vp0, y_vp0), QPointF(x_vp1, y_vp1));
            }
        }
    }
}

