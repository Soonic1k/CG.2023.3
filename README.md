# CG.2023.3

Projeto para a disciplina de Computação Gráfica utilizando a biblioteca ABCg.

## Integrantes:

- Matheus Silvério Oliveira - 11201720810
- Sonny Yassuaki R. Ganiko - 21050913

## Atividade 02:

O projeto, desenvolvido utilizando a estrutura leve em C++ chamada ABCg, é um simulador espacial em 3D. Nele, uma nave espacial navega pelo espaço sideral evitando asteroides que se aproximam. A nave tem a capacidade de se mover para a direita, esquerda, acelerar, dar ré e ajustar seu zoom (Setas, WASD e scroll do mouse), oferecendo uma experiência interativa e imersiva. Desenvolvido para a disciplina de Computação Gráfica da UFABC, o projeto utiliza as capacidades do OpenGL para criar uma aplicação em WebAssembly.

### Classe Window

#### Tratamento de Eventos do Teclado e Mouse

A função `Window::onEvent` é responsável por lidar com eventos do teclado e do mouse e direciona para a rotação e movimentação da nave espacial.

##### Funcionamento Principal

- **Teclas de Direção (Setas e 'W', 'A', 'S', 'D')**:
  - O código trata as teclas de seta (cima, baixo, esquerda, direita) e as teclas 'W', 'A', 'S' e 'D' como comandos de entrada do jogador.
  - Dependendo da tecla pressionada, a função ajusta a rotação, a inclinação da nave espacial e outros parâmetros, controlando sua direção e movimento.
- **Mouse**:
  - A função monitora a posição do mouse e a rolagem da roda do mouse.
  - A rolagem da roda do mouse é usada para controlar o nível de zoom da visualização.
  - A posição do mouse é capturada para fins de interação do jogador.

##### Atualizações e Limites
- A função atualiza várias variáveis, como ângulo de rotação, rotação e zoom, com base nos eventos do teclado e do mouse.
- Os valores são limitados dentro de faixas específicas para garantir que permaneçam dentro de limites aceitáveis durante o jogo.
- O zoom é feito através da manipulação dos eixos da câmera LookAt.

#### Configuração Inicial da Janela

A função `Window::onCreate()` é responsável por inicializar e configurar diversos elementos essenciais ao iniciar a janela de renderização. Isso inclui a definição da cor de fundo, configurações de profundidade, carregamento de modelos 3D, configuração da câmera e preparação dos elementos do jogo.

##### Carregamento de Modelos 3D
- **Asteroides**:
  - Carrega o modelo de asteroides (asteroid.obj) para a visualização no jogo.
  - Prepara o Vertex Array Object (VAO) associado ao programa OpenGL.
- **Nave Espacial (Starship)**:
  - Carrega o modelo da nave espacial (starship.obj) para a visualização no jogo.
  - Configura o Vertex Array Object (VAO) associado ao programa OpenGL.
  - Define a posição inicial da nave espacial.

##### Configuração da Câmera
- **Posição e Orientação da Câmera**:
  - Configura a câmera para posicionar-se em (0, 0.035, 0.01) e apontar na direção negativa do eixo Z.
  - Define o vetor "up" para garantir a orientação correta da câmera.

##### Rotação Inicial da Nave
- **Inicialização da Rotação da Nave Espacial**:
  - Define a rotação inicial da nave espacial como 0 graus, armazenada em radianos.
  - Configura a rotação para a direção (1.0, 1.0, 1.0) nos eixos x, y e z.

##### Configuração das Estrelas
- **Configuração Inicial das Estrelas**:
  - Para cada estrela na coleção de estrelas (m_stars), a função randomizeStar() é chamada para inicializar suas propriedades.

#### Randomização das Estrelas

A função `Window::randomizeStar(Star &star)` é responsável por gerar posições e eixos de rotação aleatórios para as estrelas no jogo. Ela utiliza distribuições uniformes para criar uma variedade de posições e eixos de rotação a fim de aumentar a diversidade visual das estrelas no espaço.

##### Geração de Posição Aleatória
- **Posição Aleatória no Espaço Tridimensional**:
  - Gera aleatoriamente as coordenadas (x, y, z) dentro dos intervalos específicos:
    - x e y no intervalo [-20, 20)
    - z no intervalo [-100, 0)
  - Define a posição da estrela com base nas coordenadas geradas.

##### Geração de Eixo de Rotação Aleatório
- **Eixo de Rotação Aleatório**:
  - Utiliza a função `glm::sphericalRand(1.0f)` para gerar um vetor de rotação aleatório.
  - Define o eixo de rotação da estrela para o vetor resultante, permitindo uma variedade de orientações no espaço.

#### Atualização do Ambiente e Estrelas

A função `Window::onUpdate()` é responsável por atualizar o estado do ambiente e o movimento das estrelas no jogo. Esta função executa a lógica para a nave espacial, a movimentação das estrelas, e as verificações para reposicionamento e realocação das estrelas no espaço tridimensional.

##### Orientação da Nave Espacial
- **Definição da Orientação da Nave**:
  - Define o eixo de rotação da nave espacial com base nas variáveis de rotação (starship_rotation).

##### Atualização da Câmera
- **Configuração da Matriz de Visualização (View Matrix)**:
  - Atualiza a matriz de visualização para a câmera com base em variáveis de zoom e posição.

##### Atualização das Estrelas
- **Movimentação e Verificações das Estrelas**:
  - Itera sobre cada estrela e atualiza sua posição ao longo do eixo z com base no tempo.
  - Responde aos inputs do jogador, ajustando a posição das estrelas de acordo com a direção desejada.
  - Verifica se as estrelas ultrapassam certos limites no espaço (eixo z e x), realocando-as para garantir que permaneçam visíveis.

##### Controle de Movimento das Estrelas
- **Gerenciamento de Posicionamento das Estrelas**:
  - Se uma estrela ultrapassa a posição da câmera, é reposicionada aleatoriamente e movida de volta para a posição inicial.
  - Se uma estrela ultrapassa os limites laterais do espaço, é reposicionada aleatoriamente e movida para a extremidade oposta.

#### Renderização do Ambiente e Objetos

A função `Window::onPaint()` é responsável por renderizar os elementos do ambiente, incluindo a nave espacial e as estrelas. Esta função configura as variáveis uniformes dos shaders, aplica transformações nos modelos e efetua o processo de renderização dos objetos 3D.

##### Configuração Inicial
- **Limpeza do Buffer Gráfico**:
  - Limpa o buffer de cor e o buffer de profundidade para preparar o contexto gráfico para o desenho dos objetos.

##### Configuração do Shader
- **Ativação do Programa do Shader**:
  - Habilita o uso do programa de shader para realizar as renderizações.

##### Configuração das Matrizes Uniformes
- **Definição das Matrizes de Visualização e Projeção**:
  - Define as matrizes de visualização (viewMatrix) e projeção (projMatrix) no programa de shader para definir a câmera e a perspectiva.

##### Renderização do Modelo da Nave Espacial
- **Renderização do Modelo da Nave**:
  - Aplica as transformações necessárias (escala, translação, rotação) no modelo da nave espacial e o renderiza.

##### Renderização das Estrelas
- **Renderização das Estrelas**:
  - Itera sobre cada estrela, aplica transformações individuais (escala, translação, rotação) e renderiza cada uma no ambiente.

##### Finalização da Renderização
- **Desativação do Programa do Shader**:
  - Finaliza o uso do programa de shader após a renderização dos objetos.

#### Função Window::onPaintUI()

A função `Window::onPaintUI()` é responsável por renderizar a interface do usuário (UI) e gerenciar as configurações gráficas relacionadas à projeção do ambiente do jogo.

##### Seleção do Tipo de Projeção
- **Seleção da Projeção (Perspectiva ou Ortográfica)**:
  - Cria um combo box para selecionar entre projeção perspectiva e ortográfica.
  - Atualiza a matriz de projeção com base na escolha do usuário.
  - Exibe um slider para ajustar o campo de visão (FOV) no caso da projeção perspectiva.

#### Função Window::onResize()

A função `Window::onResize()` é chamada quando a janela do aplicativo é redimensionada. Ela atualiza o tamanho do viewport, que é essencial para garantir que a cena seja renderizada corretamente após a mudança de tamanho da janela.

#### Função Window::onDestroy()

A função `Window::onDestroy()` é chamada quando o aplicativo está sendo encerrado. Ela é responsável por liberar recursos, como os programas de shader e os modelos 3D.

### Classe Gamedata

A classe `GameData` representa a estrutura de dados para controlar e armazenar informações de movimentação da nave.

#### Componentes da Classe

- **m_input**: Um objeto `std::bitset` que armazena as informações de entrada do jogo. Especificamente, são registrados os comandos de direcionais (esquerda, direita, cima, baixo) juntamente com um comando adicional não especificado.

#### Elementos da Classe

- **enum class Input { Right, Left, Down, Up }**: Uma enumeração que representa os diferentes tipos de comandos de entrada. Esses comandos incluem movimento para a direita, esquerda, para baixo e para cima.

#### Fluxo de Dados

- A classe GameData é utilizada para manter um registro dos comandos de entrada recebidos durante a execução do jogo.
- O std::bitset é usado para armazenar informações booleanas de forma compacta, permitindo o registro de diferentes tipos de entrada.

### Classe Model

A classe é utilizada para a renderização de objetos 3D.

#### Funcionalidades

- **createBuffers()**: Esta função cria e configura os buffers de vértices e índices para armazenar e renderizar modelos 3D.
- **loadObj(std::string_view path, bool standardize)**: Carrega um modelo 3D a partir de um arquivo no formato .obj, convertendo suas informações em vértices e índices. O parâmetro `standardize` normaliza o modelo para caber dentro do intervalo [-1, 1].
- **render(int numTriangles)**: Renderiza o modelo 3D. O parâmetro `numTriangles` define a quantidade de triângulos a serem desenhados.
- **setupVAO(GLuint program)**: Configura o Vertex Array Object (VAO) para o modelo, especificando os atributos dos vértices.
- **standardize()**: Normaliza o modelo para caber dentro do intervalo [-1, 1] em todas as dimensões.
- **destroy()**: Limpa os buffers e o VAO alocados para o modelo, realizando a limpeza de memória e recursos utilizados.

#### Principais Funcionalidades

- A leitura de arquivos .obj é feita utilizando a biblioteca `tinyobj` para obter as informações do modelo.
- Os vértices e índices são armazenados em buffers apropriados utilizando funções de baixo nível do OpenGL (GL_ELEMENT_ARRAY_BUFFER e GL_ARRAY_BUFFER).
- As funções `setupVAO` e `render` são usadas para configurar a renderização dos modelos dentro de um contexto OpenGL.
- A função `standardize` garante que os modelos renderizados se ajustem a um espaço padronizado para facilitar a renderização e manipulação.

### Classe Main

O código apresentado inicializa e gerencia a janela de visualização.

#### Funcionalidades

- **abcg::Application**: Inicializa a aplicação e gere o ciclo de vida do programa.
- **Window**: Classe responsável por configurar e controlar as definições da janela de visualização.

#### Fluxo Principal

1. **Inicialização da Aplicação**: Inicia a aplicação e cria a janela de visualização por meio da classe `Window`.
2. **Configurações da Janela**: Define as configurações da janela, como largura, altura, título e configurações específicas do OpenGL, como o número de amostras.
3. **Execução do Aplicativo**: Inicia a execução do aplicativo gráfico por meio do método `run()` da classe `abcg::Application`.

#### Assets
1. Nave espacial: https://www.cgtrader.com/free-3d-models/space/spaceship/free-scifi-fighter
2. Asteroide: https://free3d.com/3d-model/low-poly-rock-4631.html