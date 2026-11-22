# Engine Gráfica 3D Interativa
Este repositório contém a implementação de um motor gráfico 3D renderizado por software, construído do zero utilizando **C++** e o framework **Qt**. O sistema renderiza primitivas geométricas e modelos 3D poligonais (formato `.obj`), orquestrando um pipeline de visualização completo — desde o Sistema de Coordenadas do Mundo (WC) até o mapeamento em pixels no Espaço de Tela (Viewport).

## Funcionalidades Principais

* **Leitura de Modelos 3D:** Parser nativo para malhas de arquivos `.obj`.
* **Manipulação Espacial:** Translação, Rotação (Eixos X, Y e Z) e Escala, com suporte a pivô no centroide.
* **Clipping:** Algoritmos de recorte para estabilidade geométrica e otimização de renderização.
* **Sistema de Câmera Virtual:** Navegação pelo ambiente com ajustes de ângulo, zoom e distância focal.

---

## Arquitetura do Pipeline e Conceitos Teóricos

O motor baseia-se nos princípios fundamentais de álgebra linear aplicada à computação gráfica. O processamento de um vértice percorre as seguintes etapas matemáticas:

### 1. Transformações por Matrizes Homogêneas

Todas as manipulações de geometria são realizadas através de matrizes $4 \times 4$ operando sobre coordenadas homogêneas $(x, y, z, w)$. A quarta dimensão ($w$) unifica as operações, permitindo que a translação — que na geometria euclidiana é uma adição de vetores — seja computada como uma simples multiplicação de matrizes.
Para rotacionar ou escalonar um objeto em torno de seu próprio centro (e não da origem global), o motor compõe transformações em três etapas:
$M_{composta} = M_{retorno} \cdot M_{escala\_ou\_rotacao} \cdot M_{origem}$

### 2. Câmera Virtual (View Space)

A classe `Camera` atua como o observador do universo. Em vez de mover fisicamente a câmera pelo espaço, o sistema aplica a relatividade do movimento: a matriz de visualização (`mView`) move o mundo inteiro na direção inversa.

* A `mView` é gerada aplicando a translação negativa das coordenadas da câmera, seguida pela rotação inversa do seu ângulo de visada.
* Ao multiplicar o mundo pela `mView`, o observador é cravado na coordenada $(0,0,0)$, facilitando os cálculos ópticos subsequentes.

### 3. Projeção Perspectiva

É a etapa responsável por deformar o espaço 3D para criar a ilusão de profundidade na tela plana.

* Baseia-se em uma matriz de projeção (`mProj`) construída a partir da distância focal $d$ do observador até o plano de visualização.
* A projeção injeta o valor da profundidade ($z$) no componente $W$ da coordenada homogênea. A distorção ocorre na **divisão homogênea**: as coordenadas $x$ e $y$ são divididas por esse novo $W$. Como resultado matemático, objetos com um $z$ maior colapsam em direção à origem, parecendo menores.

### 4. Recorte de Geometria (Clipping)

Garante que a GPU não desenhe vértices inválidos ou fora da tela.

* **Z-Clipping (Near Plane):** Ocorre logo após a transformação da câmera. Intersecciona equações paramétricas de reta para cortar a geometria que está fisicamente atrás das lentes do observador ($z < z_{near}$). Ignorar esta etapa causaria divisão por zero ou inversão de coordenadas na matriz perspectiva.
* **Clipping Normalizado (SCN):** Ocorre após a projeção. Todo o volume visível da câmera é esmagado em um cubo perfeito cujos eixos variam de $[-1, 1]$. O motor aplica o algoritmo de **Cohen-Sutherland** (para retas) e **Sutherland-Hodgman** (para faces) contra os limites deste cubo, descartando ou esculpindo precisamente os polígonos que cruzam as bordas da tela.

### 5. Transformada de Viewport

A etapa final do pipeline. Mapeia os vértices que sobreviveram ao recorte (agora limitados entre $-1$ e $1$) para a resolução física e localização em pixels do componente de tela do Qt (`QFrame`), invertendo o eixo Y para o padrão de monitores e rasterizando o resultado visual.

---

## Estrutura do Código

* `Matriz.cpp/h`: Núcleo algébrico. Constrói matrizes de translação, rotação, escala, perspectiva e manipula sobrecarga de operadores para composição.
* `camera.cpp/h`: Entidade herdeira de `Forma` que dita os parâmetros ópticos do pipeline.
* `MeuFrame.cpp/h`: Canvas de renderização. Orquestra a execução da lista de objetos (`displayFile`) a cada `paintEvent`.
* `Forma.cpp/h`: Superclasse polimórfica que detém as lógicas de Bounding Box, Interseção Paramétrica e Clipping de polígonos.
* `modelo3d.cpp/h`: Estrutura de parsing encarregada de interpretar a sintaxe de arquivos `.obj` e renderizar malhas trianguladas.

---

## Como Compilar e Executar

Este projeto utiliza o sistema de build `qmake`. A compilação é gerenciada nativamente pela IDE do Qt.

### Pré-requisitos

* **Qt Creator** instalado juntamente com as bibliotecas core do **Qt Framework** (versão 5 ou superior).
* Um compilador `C++` devidamente configurado nos *Kits* do Qt Creator (GCC para ambientes Linux ou MSVC/MinGW para Windows).

### Passos para Build

1. Clone ou extraia os arquivos do repositório em um diretório local.
2. Abra o **Qt Creator**.
3. Acesse `File > Open File or Project...` e selecione o arquivo de configuração principal do projeto: `trabalhoCG.pro`.


4. Na aba **Configure Project**, selecione o *Kit* de desenvolvimento correspondente ao seu sistema operacional e arquitetura (ex: *Desktop Qt 6.x.x GCC 64bit*). Clique em **Configure Project**.
5. Compile o código e inicie o motor gráfico pressionando `Ctrl + R` (Run).
