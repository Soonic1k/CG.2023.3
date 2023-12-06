# CG.2023.3

Projeto para a disciplina de Computação Gráfica utilizando a biblioteca ABCg.

## Integrantes:

- Matheus Silvério Oliveira - 11201720810
- Sonny Yassuaki R. Ganiko - 21050913

## Atividade 03:
As funções descritas abaixo foram criadas para a Atividade 3 ou foram alteradas em relação a Atividade 2, as demais funções não listadas neste capítulo permaneceram inalteradas ou sofreram correções mínimas.

### Classe Window

#### Carregamento do Modelo da Nave

A função `Window::createSpaceship()` é responsável por carregar e configurar o modelo 3D da nave espacial (spaceship) no ambiente do jogo. Ela carrega as texturas difusa e normal, o modelo 3D em si e configura os parâmetros de material necessários para a renderização.

##### Carregamento do Modelo da Nave Espacial
- **Carregamento do Modelo**:
  - Utiliza a classe `Model` para carregar o modelo 3D da nave espacial a partir de um arquivo obj.
  - Configura o Vertex Array Object (VAO) associado ao modelo.

##### Carregamento das Texturas
- **Carregamento das Texturas**:
  - Carrega a textura difusa da nave espacial a partir de um arquivo de imagem (jpg).
  - Carrega a textura normal da nave espacial a partir de um arquivo de mapa normal (png).

##### Configuração dos Materiais
- **Configuração dos Materiais**:
  - Obtém os coeficientes de reflectância (Ka, Kd, Ks) e a intensidade especular (shininess) associados ao modelo no arquivo mtl correspondente.

##### Posicionamento Inicial da Nave Espacial
- **Posicionamento Inicial**:
  - Define a posição inicial da nave espacial no ambiente.

#### Carregamento do Modelo de Asteróides

A função `Window::createAsteroid()` é responsável por carregar e configurar o modelo 3D de um asteroide no ambiente do jogo. Ela carrega a textura do céu (skybox), a textura difusa do asteroide, o modelo 3D em si e configura os parâmetros necessários para a renderização.

##### Carregamento do Modelo do Asteroide
- **Carregamento do Modelo**:
  - Utiliza a classe `Model` para carregar o modelo 3D do asteroide a partir de um arquivo obj.
  - Configura o Vertex Array Object (VAO) associado ao modelo.

##### Carregamento das Texturas
- **Carregamento da Textura do Céu (Skybox)**:
  - Carrega a textura do céu (skybox) a partir de um diretório contendo as imagens correspondentes aos seis lados.

- **Carregamento da Textura Difusa do Asteroide**:
  - Carrega a textura difusa (albedo) do asteroide a partir de um arquivo de imagem (jpg).

#### Carregamento do Skybox

A função `Window::createSkybox()` é responsável por criar e configurar o céu (skybox) no ambiente do jogo. Ela compila e vincula os shaders específicos para o céu, gera um Vertex Buffer Object (VBO) contendo as posições dos vértices do skybox e configura o Vertex Array Object (VAO) associado ao skybox.

##### Compilação e Vinculação dos Shaders
- **Programa do Skybox**:
  - Compila e vincula shaders vertex e fragment específicos para o skybox.
  - Usa a classe `abcg::createOpenGLProgram` para gerar o programa do skybox.

##### Configuração do VBO e VAO
- **Geração do VBO**:
  - Gera um VBO para armazenar as posições dos vértices do skybox.
  - Preenche o VBO com as posições predefinidas do skybox.

- **Vinculação do VAO**:
  - Gera um VAO para armazenar o estado de configuração do VBO.
  - Vincula o VAO atual.
  - Vincula o VBO ao VAO.
  - Configura o atributo de posição do shader.

#### Função Window::onCreate()

A função `Window::onCreate()` é chamada durante a inicialização da janela do OpenGL. Ela configura o ambiente gráfico, compila shaders, cria modelos e configura a câmera. Além disso, a função chama outras funções especializadas para criar elementos específicos do jogo, como a espaçonave, asteroides, estrelas e o céu (skybox).

##### Configuração Inicial do OpenGL
- **Limpeza de Buffer**:
  - Define a cor de limpeza do buffer de cor para preto.
  - Ativa o teste de profundidade.

- **Compilação e Vinculação de Shaders**:
  - Compila e vincula shaders vertex e fragment para normal mapping.
  - Utiliza a classe `abcg::createOpenGLProgram` para gerar o programa.

##### Criação de Objetos 3D
- **Espaçonave (Spaceship)**:
  - Chama a função `createSpaceship()` para carregar e configurar a modelagem 3D da espaçonave.
  - Configura materiais (Ka, Kd, Ks, brilho) da espaçonave.

- **Asteroides**:
  - Chama a função `createAsteroid()` para carregar e configurar a modelagem 3D de asteroides.
  - Configura texturas e materiais dos asteroides.

- **Skybox**:
  - Chama a função `createSkybox()` para criar e configurar o céu (skybox).

##### Configuração da Câmera
- **Matriz de Visualização (View Matrix)**:
  - Configura a matriz de visualização usando a função `glm::lookAt` para definir a posição da câmera (eye), o ponto de visão (at) e a direção "para cima" (up).

##### Configuração Inicial do Jogo
- **Rotação Inicial da Espaçonave**:
  - Configura a rotação inicial da espaçonave.

- **Configuração Inicial das Estrelas**:
  - Chama a função `randomizeStar` para inicializar as posições e orientações iniciais das estrelas.

#### Renderização do Skybox

A função `Window::renderSkybox()` é responsável por renderizar o céu (skybox) na cena. Ela configura e utiliza shaders específicos para renderização do skybox, aplicando uma textura de mapa de cubo para criar um ambiente imersivo ao redor da cena principal.

##### Renderização do Skybox
- **Uso do Programa do Skybox**:
  - Ativa o programa do skybox usando `abcg::glUseProgram(m_skyProgram)`.

- **Localização de Uniformes**:
  - Obtém as localizações das variáveis uniformes no programa do skybox, incluindo as matrizes `viewMatrix`, `projMatrix` e a textura do mapa de cubo (`skyTex`).
  - `viewMatrixLoc`: Localização da matriz de visualização.
  - `projMatrixLoc`: Localização da matriz de projeção.
  - `skyTexLoc`: Localização da textura do mapa de cubo.

- **Configuração das Matrizes de Visualização e Projeção**:
  - Configura uma matriz `projView` (100.0f) para a matriz de visualização.
  - Atualiza as variáveis uniformes `viewMatrix` e `projMatrix` com as matrizes de visualização e projeção.

- **Vinculação e Ativação de Texturas**:
  - Ativa a textura do mapa de cubo, que foi carregada previamente durante a inicialização.
  - A textura é vinculada à unidade de textura GL_TEXTURE0.

- **Renderização do Skybox**:
  - Habilita o teste de profundidade e a face traseira do skybox.
  - Configura a função de teste de profundidade para `GL_LEQUAL`.
  - Desenha os triângulos do skybox usando `abcg::glDrawArrays(GL_TRIANGLES, 0, m_skyPositions.size())`.
  - Restaura a função de teste de profundidade para `GL_LESS` após a renderização.

- **Desativação de Atributos e Programa**:
  - Desabilita a matriz de atributos do VAO do skybox.
  - Desativa o programa do skybox usando `abcg::glUseProgram(0)`.

#### Função Window::onPaint()

A função `Window::onPaint()` é chamada para realizar a renderização principal da cena. Nesta função, objetos 3D, como a nave espacial, asteroides e o skybox, são renderizados usando shaders e técnicas de iluminação.

##### Configuração Inicial
- **Limpeza de Buffers**:
  - Limpa os buffers de cor e profundidade usando `abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`.

- **Configuração do Viewport**:
  - Configura a visualização usando `abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y)`.

- **Uso do Programa Principal**:
  - Ativa o programa principal da aplicação usando `abcg::glUseProgram(m_program)`.

##### Uniformes e Localizações
- **Obtenção de Localizações Uniformes**:
  - Obtém as localizações das variáveis uniformes necessárias para a renderização do modelo 3D.
  - Localizações incluem matrizes de visão (`viewMatrix`), projeção (`projMatrix`), modelo (`modelMatrix`) e normal (`normalMatrix`).
  - Localizações de texturas e modos de mapeamento também são obtidas.

##### Iluminação e Materiais
- **Configuração de Iluminação e Materiais**:
  - Configura as propriedades de iluminação e materiais, incluindo a direção da luz (`lightDirWorldSpace`), intensidades de luz ambiente (`Ia`), difusa (`Id`) e especular (`Is`), e coeficientes de material (`Ka`, `Kd`, `Ks`).
  - Define a rugosidade do material (`shininess`).

##### Renderização da Nave Espacial
- **Renderização da Nave Espacial**:
  - Configura a matriz de modelo para a nave espacial.
  - Aplica as transformações de translação, escala e rotação.
  - Renderiza a nave espacial usando `m_additionalModel.render()`.

##### Renderização dos Asteroides
- **Renderização dos Asteroides**:
  - Para cada asteroide na lista, calcula a matriz de modelo e renderiza o asteroide usando `m_model.render()`.

##### Renderização do Skybox
- **Renderização do Skybox**:
  - Chama a função `renderSkybox()` para renderizar o skybox.

##### Limpeza e Desativação
- **Limpeza e Desativação**:
  - Desativa o programa principal usando `abcg::glUseProgram(0)`.

#### Função Window::onPaintUI()

A função `Window::onPaintUI()` é responsável por renderizar a interface gráfica do usuário (GUI) durante o processo de pintura. Ela utiliza a biblioteca ImGui para criar elementos interativos, como sliders e janelas de configuração, que permitem ao usuário ajustar parâmetros em tempo real.

##### Janela de Propriedades de Luz
- **Controles de Luz**:
  - Utiliza sliders de cores para ajustar as propriedades de luz ambiente (`Ia`), difusa (`Id`), e especular (`Is`).
  - Os controles permitem ao usuário interagir diretamente com as propriedades de luz.

##### Janela de Configuração Geral
- **Seleção de Projeção**:
  - Oferece uma caixa de combinação para escolher entre projeção perspectiva e ortográfica (`Perspective` e `Orthographic`).
  - Atualiza a matriz de projeção com base na escolha do usuário.

- **Ajuste do Campo de Visão (FOV)**:
  - Se a projeção perspectiva estiver selecionada, exibe um slider para ajustar o campo de visão (`FOV`) em graus.
  - Atualiza a matriz de projeção conforme o usuário ajusta o slider.

#### Função Window::onDestroy()

A função `Window::onDestroy()` é responsável por liberar os recursos alocados durante a execução do programa, garantindo uma limpeza adequada e prevenindo vazamentos de memória.

##### Liberação de Modelos e Texturas
- `m_model.destroy()`: Libera os recursos associados ao modelo principal (asteroide). Isso inclui buffers, texturas e objetos de array de vértices (VAO).
- `m_additionalModel.destroy()`: Libera os recursos associados ao modelo adicional (espaçonave). Semelhante ao modelo principal, isso inclui buffers, texturas e VAO.

### Liberação do Programa da Skybox
- `abcg::glDeleteProgram(m_skyProgram)`: Deleta o programa OpenGL associado à renderização da Skybox. Isso inclui os shaders de vértice e fragmento.
- `abcg::glDeleteBuffers(1, &m_skyVBO)`: Deleta o buffer de vértices (VBO) usado para armazenar as posições da Skybox.
- `abcg::glDeleteVertexArrays(1, &m_skyVAO)`: Deleta o objeto de array de vértices (VAO) associado à Skybox.

### Liberação do Programa Principal
- `abcg::glDeleteProgram(m_program)`: Deleta o programa OpenGL associado à renderização principal. Isso inclui os shaders de vértice e fragmento.

### Classe Model

Somente as funções que sofreram alterações ou foram adicionadas para a atividade atual serão documentadas, as demais funções seguem a documentação da Atividade 02.

#### Função Model::computeNormals()

A função `Model::computeNormals()` é responsável por calcular as normais dos vértices do modelo com base nas normais das faces.

##### Limpeza das Normais Anteriores
- `for (auto &vertex : m_vertices)`: Itera sobre todos os vértices do modelo.
  - `vertex.normal = glm::vec3(0.0f);`: Inicializa as normais dos vértices com vetores nulos.

##### Cálculo das Normais das Faces
- `for (auto const offset : iter::range(0UL, m_indices.size(), 3UL))`: Itera sobre os índices do modelo em incrementos de 3, representando triângulos.
  - `auto &a{m_vertices.at(m_indices.at(offset + 0))};`: Obtém o primeiro vértice do triângulo.
  - `auto &b{m_vertices.at(m_indices.at(offset + 1))};`: Obtém o segundo vértice do triângulo.
  - `auto &c{m_vertices.at(m_indices.at(offset + 2))};`: Obtém o terceiro vértice do triângulo.
  - `auto const edge1{b.position - a.position};`: Calcula o vetor da aresta 1.
  - `auto const edge2{c.position - b.position};`: Calcula o vetor da aresta 2.
  - `auto const normal{glm::cross(edge1, edge2)};`: Calcula a normal da face usando o produto vetorial das arestas.
  - `a.normal += normal;`, `b.normal += normal;`, `c.normal += normal;`: Acumula as normais nas estruturas de vértices correspondentes.

##### Normalização das Normais dos Vértices
- `for (auto &vertex : m_vertices)`: Itera sobre todos os vértices do modelo.
  - `vertex.normal = glm::normalize(vertex.normal);`: Normaliza as normais dos vértices.

##### Atualização do Estado das Normais
- `m_hasNormals = true;`: Atualiza a flag `m_hasNormals` para indicar que o modelo agora possui informações de normais.

#### Função Model::loadCubeTexture(std::string const &path)

A função `Model::loadCubeTexture` é responsável por carregar uma textura de cubemap no modelo.

##### Funcionamento
- `m_cubeTexture = abcg::loadOpenGLCubemap({.paths = {path + "posx.jpg", path + "negx.jpg", path + "posy.jpg", path + "negy.jpg", path + "posz.jpg", path + "negz.jpg"}});`: Carrega uma nova textura de cubemap usando a função `abcg::loadOpenGLCubemap`. Os caminhos das seis imagens são construídos com base no caminho fornecido, e os identificadores da textura resultantes são armazenados em `m_cubeTexture`.

##### Observações Adicionais
- A função presume que as imagens do cubemap estão nomeadas seguindo a convenção de nomenclatura padrão, com sufixos indicando as direções dos eixos: "posx" (positivo x), "negx" (negativo x), "posy" (positivo y), "negy" (negativo y), "posz" (positivo z) e "negz" (negativo z).
- A função é projetada para ser utilizada em conjunto com modelos que requerem um cubemap para efeitos visuais ou de iluminação específicos.

#### Função Model::loadDiffuseTexture(std::string_view path)

A função `Model::loadDiffuseTexture` é responsável por carregar uma textura difusa (textura de cor) para o modelo.

##### Funcionamento
- `m_diffuseTexture = abcg::loadOpenGLTexture({.path = path});`: Carrega uma nova textura difusa usando a função `abcg::loadOpenGLTexture`. O identificador da textura resultante é armazenado em `m_diffuseTexture`.

#### Função Model::loadNormalTexture(std::string_view path)

A função `Model::loadNormalTexture` é responsável por carregar uma textura normal para o modelo.

##### Funcionamento
- `m_normalTexture = abcg::loadOpenGLTexture({.path = path});`: Carrega uma nova textura normal usando a função `abcg::loadOpenGLTexture`. O identificador da textura resultante é armazenado em `m_normalTexture`.

#### Função Model::loadObj(std::string_view path, bool standardize)

A função `Model::loadObj` é responsável por carregar um modelo 3D no formato OBJ, incluindo suas informações de vértices, índices, normais, coordenadas de textura e materiais associados.

##### Funcionamento
- `auto const basePath{std::filesystem::path{path}.parent_path().string() + "/"};`: Calcula o caminho base para o arquivo do modelo, que será usado como o caminho para os arquivos de materiais (MTL).

- `tinyobj::ObjReaderConfig readerConfig;`: Configuração do leitor de arquivo OBJ.
  - `readerConfig.mtl_search_path = basePath;`: Define o caminho de pesquisa para arquivos de materiais.

- `tinyobj::ObjReader reader;`: Objeto de leitura do arquivo OBJ.

- `if (!reader.ParseFromFile(path.data(), readerConfig)) { ... }`: Analisa o arquivo OBJ especificado usando o leitor configurado. Lança uma exceção se a análise falhar.

- `auto const &attrib{reader.GetAttrib()};`: Obtém os atributos do modelo (vértices, normais, coordenadas de textura).
- `auto const &shapes{reader.GetShapes()};`: Obtém as formas do modelo.
- `auto const &materials{reader.GetMaterials()};`: Obtém os materiais do modelo.

- Limpa as listas de vértices e índices do modelo (`m_vertices` e `m_indices`).
- Inicializa o indicador de presença de normais e coordenadas de textura como falso (`m_hasNormals` e `m_hasTexCoords`).

- Um loop sobre as formas e índices é realizado para extrair as informações do modelo.

- Um mapa `hash` é utilizado para armazenar vértices únicos e seus índices correspondentes.

- As propriedades do primeiro material, se disponíveis, são usadas para definir propriedades do modelo, como coeficientes de reflexão e textura difusa.

- Se o modelo deve ser padronizado (`standardize` é verdadeiro), a função `Model::standardize` é chamada para ajustar a escala e centralizar o modelo na origem.

- Se o modelo não possui informações de normais, a função `Model::computeNormals` é chamada para calcular as normais dos vértices.

- Finalmente, a função `Model::createBuffers` é chamada para criar os buffers de vértices e índices utilizados para renderizar o modelo.

##### Observações Adicionais
- Essa função utiliza a biblioteca TinyObjLoader para analisar arquivos OBJ e extrair informações sobre o modelo.
- As informações de material do primeiro material são usadas para definir as propriedades do modelo, se disponíveis.
- A função também suporta o carregamento de texturas difusas associadas aos materiais do modelo.

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
3. Imagem de fundo: https://unblast.com/10-free-space-background-images-jpg/
4. Imagem para Cubemap: https://jaxry.github.io/panorama-to-cubemap/