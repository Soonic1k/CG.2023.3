#include "window.hpp"

#include <glm/gtc/random.hpp>
#include <glm/gtx/fast_trigonometry.hpp>



// Mouse and Keyboard Events
void Window::onEvent(SDL_Event const &event) {
  // Keyboard events
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w){
      if(m_angle_calculated > 0.1f || rotation_x > 0.1f){
        m_angle_calculated -= 0.4f;
        rotation_x -= 0.04f;
        rotation_y -= 0.04f;
        m_angle_calculated = glm::clamp(m_angle_calculated, 0.1f, 20.0f);
        rotation_x = glm::clamp(rotation_x, 0.1f, 3.0f);
        rotation_y = glm::clamp(rotation_y, 0.1f, 3.0f);
        m_angle_ship = glm::wrapAngle(glm::radians(m_angle_calculated));
        starship_rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
        m_gameData.m_input.set(gsl::narrow<size_t>(Input::Up));
      }

      if(m_angle_calculated < 0.1f || rotation_x < 0.1f) {
        m_angle_calculated += 0.4f;
        rotation_x += 0.04f;
        rotation_y -= 0.04f;
        m_angle_calculated = glm::clamp(m_angle_calculated, -20.0f, 0.0f);
        rotation_x = glm::clamp(rotation_x, -3.0f, 0.1f);
        rotation_y = glm::clamp(rotation_y, 0.1f, 3.0f);
        m_angle_ship = glm::wrapAngle(glm::radians(m_angle_calculated));
        starship_rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
        m_gameData.m_input.set(gsl::narrow<size_t>(Input::Up));
      }
    }
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s){
      if(m_angle_calculated > 0.1f || rotation_x > 0.1f){
        m_angle_calculated -= 0.4f;
        rotation_x -= 0.04f;
        rotation_y -= 0.04f;
        m_angle_calculated = glm::clamp(m_angle_calculated, 0.1f, 20.0f);
        rotation_x = glm::clamp(rotation_x, 0.1f, 3.0f);
        rotation_y = glm::clamp(rotation_y, 0.1f, 3.0f);
        m_angle_ship = glm::wrapAngle(glm::radians(m_angle_calculated));
        starship_rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
        m_gameData.m_input.set(gsl::narrow<size_t>(Input::Down));
      }
      if(m_angle_calculated < 0.1f || rotation_x < 0.1f) {
        m_angle_calculated += 0.4f;
        rotation_x += 0.04f;
        rotation_y -= 0.04f;
        m_angle_calculated = glm::clamp(m_angle_calculated, -20.0f, 0.1f);
        rotation_x = glm::clamp(rotation_x, -3.0f, 0.1f);
        rotation_y = glm::clamp(rotation_y, 0.1f, 3.0f);
        m_angle_ship = glm::wrapAngle(glm::radians(m_angle_calculated));
        starship_rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
        m_gameData.m_input.set(gsl::narrow<size_t>(Input::Down));
      }
    }
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a){
      m_angle_calculated += 0.4f;
      m_angle_calculated = glm::clamp(m_angle_calculated, -20.0f, 20.0f);
      m_angle_ship = glm::wrapAngle(glm::radians(m_angle_calculated));
      rotation_x += 0.04f;
      rotation_y += 0.04f;
      rotation_x = glm::clamp(rotation_x, -3.0f, 3.0f);
      rotation_y = glm::clamp(rotation_y, 0.1f, 3.0f);
      starship_rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Left));
    }
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d){
      m_angle_calculated -= 0.4f;
      m_angle_calculated = glm::clamp(m_angle_calculated, -20.0f, 20.0f);
      m_angle_ship = glm::wrapAngle(glm::radians(m_angle_calculated));
      rotation_x -= 0.04f;
      rotation_y += 0.04f;
      rotation_x = glm::clamp(rotation_x, -3.0f, 3.0f);
      rotation_y = glm::clamp(rotation_y, 0.1f, 3.0f);
      starship_rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
      m_gameData.m_input.set(gsl::narrow<size_t>(Input::Right));
    }
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Up));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Down));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.reset(gsl::narrow<size_t>(Input::Right));
  }

  //Mouse events
  glm::ivec2 mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

  if (event.type == SDL_MOUSEWHEEL) {
    m_zoom += (event.wheel.y > 0 ? -1.00f : 1.00f) * 2.0f / 5.0f;
    m_zoom = glm::clamp(m_zoom, 0.00f, 3.0f);
  }
}

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  //abcg::glClearColor(0, 0, 0, 1);
  abcg::glEnable(GL_DEPTH_TEST);

  createSpaceship();
  createAsteroid();

  // Camera at (0,0,0) and looking towards the negative z
  glm::vec3 const eye{0.0f, 0.0f, 2.0f}; //0.0f, 0.035f, 0.01f
  glm::vec3 const at{0.0f, 0.0f, 0.0f}; //{0.0f, -0.1f, -1.0f};
  glm::vec3 const up{0.0f, 1.0f, 0.0f}; //{0.0f, 1.0f, 0.0f}
  m_viewMatrix = glm::lookAt(eye, at, up);

  //rotação inicial da nave
  m_angle_ship = glm::wrapAngle(glm::radians(0.0f));
  starship_rotation = glm::vec3(1.0f, 1.0f, 1.0f);

  // Setup stars
  for (auto &star : m_stars) {
    randomizeStar(star);
  }

  createSkybox();
}

void Window::randomizeStar(Star &star) {
  // Random position: x and y in [-20, 20), z in [-100, 0)
  std::uniform_real_distribution<float> distPosXY(-20.0f, 20.0f);
  std::uniform_real_distribution<float> distPosZ(-100.0f, 0.0f);
  star.m_position =
      glm::vec3(distPosXY(m_randomEngine), distPosXY(m_randomEngine),
                distPosZ(m_randomEngine));

  // Random rotation axis
  star.m_rotationAxis = glm::sphericalRand(1.0f);
}

void Window::onUpdate() {

  starship.m_rotationAxis = starship_rotation;

  m_viewMatrix =
      glm::lookAt(glm::vec3(0.0f, 0.5f + m_zoom, 2.0f + m_zoom),
                  glm::vec3(0.0f, -0.1f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));


  // Increase angle by 90 degrees per second
  auto const deltaTime{gsl::narrow_cast<float>(getDeltaTime())};
  m_angle = glm::wrapAngle(m_angle + glm::radians(90.0f) * deltaTime);

  // Update stars
  for (auto &star : m_stars) {
    // Increase z by 10 units per second
    star.m_position.z += deltaTime * 10.0f;

    if (m_gameData.m_input[static_cast<size_t>(Input::Up)]) {
      star.m_position.z += deltaTime * 30.0f;
    }

    if (m_gameData.m_input[static_cast<size_t>(Input::Down)]) {
      star.m_position.z -= deltaTime * 30.0f;
    }

    if (m_gameData.m_input[static_cast<size_t>(Input::Left)]) {
      star.m_position.x += deltaTime * 30.0f;
    }

    if (m_gameData.m_input[static_cast<size_t>(Input::Right)]) {
      star.m_position.x -= deltaTime * 30.0f;
    }

    // If this star is behind the camera, select a new random position &
    // orientation and move it back to -100
    if (star.m_position.z > 10.0f) {
      randomizeStar(star);
      star.m_position.z = -100.0f; // Back to -100
    }
    if (star.m_position.z < -100.0f) {
      randomizeStar(star);
      star.m_position.z = 10.0f; // Back to -100
    }

    if (star.m_position.x > 20.0f) {
      randomizeStar(star);
      star.m_position.x = -20.0f; // Back to -100
    }

    if (star.m_position.x < -20.0f) {
      randomizeStar(star);
      star.m_position.x = 20.0f; // Back to -100
    }
  }

    
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  abcg::glUseProgram(m_program);

  // Get location of uniform variables
  auto const viewMatrixLoc{abcg::glGetUniformLocation(m_program, "viewMatrix")};
  auto const projMatrixLoc{abcg::glGetUniformLocation(m_program, "projMatrix")};
  auto const modelMatrixLoc{
      abcg::glGetUniformLocation(m_program, "modelMatrix")};
  //auto const colorLoc{abcg::glGetUniformLocation(m_program, "color")};
  auto const normalMatrixLoc{
      abcg::glGetUniformLocation(m_program, "normalMatrix")};
  auto const lightDirLoc{
      abcg::glGetUniformLocation(m_program, "lightDirWorldSpace")};
  auto const shininessLoc{abcg::glGetUniformLocation(m_program, "shininess")};
  auto const IaLoc{abcg::glGetUniformLocation(m_program, "Ia")};
  auto const IdLoc{abcg::glGetUniformLocation(m_program, "Id")};
  auto const IsLoc{abcg::glGetUniformLocation(m_program, "Is")};
  auto const KaLoc{abcg::glGetUniformLocation(m_program, "Ka")};
  auto const KdLoc{abcg::glGetUniformLocation(m_program, "Kd")};
  auto const KsLoc{abcg::glGetUniformLocation(m_program, "Ks")};
  
  auto const diffuseTexLoc{abcg::glGetUniformLocation(m_program, "diffuseTex")};
  auto const mappingModeLoc{abcg::glGetUniformLocation(m_program, "mappingMode")};
  auto const normalTexLoc{abcg::glGetUniformLocation(m_program, "normalTex")};
  auto const cubeTexLoc{abcg::glGetUniformLocation(m_skyProgram, "cubeTex")};
 
  //Iluminação
  auto const lightDirRotated{m_lightDir};
  abcg::glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
  abcg::glUniform4fv(IaLoc, 1, &m_Ia.x);
  abcg::glUniform4fv(IdLoc, 1, &m_Id.x);
  abcg::glUniform4fv(IsLoc, 1, &m_Is.x);
  abcg::glUniform4fv(KaLoc, 1, &m_Ka.x);
  abcg::glUniform4fv(KdLoc, 1, &m_Kd.x);
  abcg::glUniform4fv(KsLoc, 1, &m_Ks.x);
  abcg::glUniform1f(shininessLoc, m_shininess);


  // Set uniform variables that have the same value for every model
  abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);
  abcg::glUniform1i(diffuseTexLoc, 0);
  abcg::glUniform1i(mappingModeLoc, m_mappingMode);
  abcg::glUniform1i(normalTexLoc, 1);
  abcg::glUniform1i(cubeTexLoc, 2);
  abcg::glUniform1i(mappingModeLoc, m_mappingMode);


  //STARSHIP MODEL RENDER
  glm::mat4 additionalModelMatrix{1.0f};
  additionalModelMatrix = glm::translate(additionalModelMatrix, m_additionalModelPosition);
  additionalModelMatrix = glm::scale(additionalModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f)); //0.014
  additionalModelMatrix = glm::rotate(additionalModelMatrix, m_angle_ship, starship.m_rotationAxis);
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &additionalModelMatrix[0][0]);

  m_additionalModel.render();

  auto const modelViewMatrix{glm::mat3(m_viewMatrix * m_modelMatrix)};
  auto const normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  abcg::glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);

  // Render each star
  for (auto &star : m_stars) {
    // Compute model matrix of the current star
    glm::mat4 modelMatrix{1.0f};
    modelMatrix = glm::translate(modelMatrix, star.m_position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
    modelMatrix = glm::rotate(modelMatrix, m_angle, star.m_rotationAxis);

    // Set uniform variable
    abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &modelMatrix[0][0]);

    m_model.render();

  }

  //Render Skybox
  renderSkybox();

  abcg::glUseProgram(0);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();


  auto const widgetSize{ImVec2(222, 244)};
  ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x - widgetSize.x - 5,
                                  m_viewportSize.y - widgetSize.y - 5));
  ImGui::SetNextWindowSize(widgetSize);
  ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoDecoration);

  ImGui::Text("Light properties");

  // Slider to control light properties
  ImGui::PushItemWidth(widgetSize.x - 36);
  ImGui::ColorEdit3("Ia", &m_Ia.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Id", &m_Id.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Is", &m_Is.x, ImGuiColorEditFlags_Float);
  ImGui::PopItemWidth();
  
  ImGui::Spacing();
  
  ImGui::Text("Material properties");

  // Slider to control material properties
  ImGui::PushItemWidth(widgetSize.x - 36);
  ImGui::ColorEdit3("Ka", &m_Ka.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Kd", &m_Kd.x, ImGuiColorEditFlags_Float);
  ImGui::ColorEdit3("Ks", &m_Ks.x, ImGuiColorEditFlags_Float);
  ImGui::PopItemWidth();
  
  // Slider to control the specular shininess
  ImGui::PushItemWidth(widgetSize.x - 16);
  ImGui::SliderFloat(" ", &m_shininess, 0.0f, 500.0f, "shininess: %.1f");
  ImGui::PopItemWidth();
  
  ImGui::End();



  {
    auto const widgetSize{ImVec2(218, 62)};
    ImGui::SetNextWindowPos(ImVec2(m_viewportSize.x - widgetSize.x - 5, 5));
    ImGui::SetNextWindowSize(widgetSize);
    ImGui::Begin("Widget window", nullptr, ImGuiWindowFlags_NoDecoration);

    {
      ImGui::PushItemWidth(120);
      static std::size_t currentIndex{};
      std::vector<std::string> const comboItems{"Perspective", "Orthographic"};

      if (ImGui::BeginCombo("Projection",
                            comboItems.at(currentIndex).c_str())) {
        for (auto const index : iter::range(comboItems.size())) {
          auto const isSelected{currentIndex == index};
          if (ImGui::Selectable(comboItems.at(index).c_str(), isSelected))
            currentIndex = index;
          if (isSelected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }
      ImGui::PopItemWidth();

      ImGui::PushItemWidth(170);
      auto const aspect{gsl::narrow<float>(m_viewportSize.x) /
                        gsl::narrow<float>(m_viewportSize.y)};
      if (currentIndex == 0) {
        m_projMatrix =
            glm::perspective(glm::radians(m_FOV), aspect, 0.01f, 100.0f);

        ImGui::SliderFloat("Vel.", &m_FOV, 55.0f, 160.0f, "%.0f Light Years");
      } else {
        m_projMatrix = glm::ortho(-20.0f * aspect, 20.0f * aspect, -20.0f,
                                  20.0f, 0.01f, 100.0f);
      }
      ImGui::PopItemWidth();
    }
    ImGui::End();
  }
}

void Window::createAsteroid() {

  auto const assetsPath{abcg::Application::getAssetsPath()};

  m_model.loadDiffuseTexture(assetsPath + "maps/Rock-Texture-Surface.jpg");
  m_model.loadCubeTexture(assetsPath + "maps/");
  m_model.loadObj(assetsPath + "asteroid.obj"); //Change Stars image loaded on screen
  m_model.setupVAO(m_program);
}

void Window::createSpaceship() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  m_program =
      abcg::createOpenGLProgram({{.source = assetsPath + "normalmapping.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                  {.source = assetsPath + "normalmapping.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  //STARSHIP MODEL
  //m_additionalModel.loadDiffuseTexture(assetsPath + "maps/SciFi_Fighter_AK5-diffuse.jpg");
  //m_additionalModel.loadNormalTexture(assetsPath + "maps/pattern_normal.png");
  //m_additionalModel.loadCubeTexture(assetsPath + "maps/");
  //m_model.loadCubeTexture(assetsPath + "maps/");
  m_additionalModel.loadObj(assetsPath + "SciFi_Fighter_AK5.obj");
  m_additionalModel.setupVAO(m_program);
  m_additionalModelPosition = glm::vec3(0.0f, 0.0f, 0.0f);

  m_Ka = m_additionalModel.getKa();
  m_Kd = m_additionalModel.getKd();
  m_Ks = m_additionalModel.getKs();
  m_shininess = m_additionalModel.getShininess();


}

void Window::createSkybox() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  // Create skybox program
  auto const path{assetsPath + "skybox"};
  m_skyProgram = abcg::createOpenGLProgram(
      {{.source = path + ".vert", .stage = abcg::ShaderStage::Vertex},
       {.source = path + ".frag", .stage = abcg::ShaderStage::Fragment}});

  // Generate VBO
  abcg::glGenBuffers(1, &m_skyVBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_skyVBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(m_skyPositions),
                     m_skyPositions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_skyProgram, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &m_skyVAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_skyVAO);

  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_skyVBO);
  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Window::renderSkybox() {
  abcg::glUseProgram(m_skyProgram);

  auto const viewMatrixLoc{
      abcg::glGetUniformLocation(m_skyProgram, "viewMatrix")};
  auto const projMatrixLoc{
      abcg::glGetUniformLocation(m_skyProgram, "projMatrix")};
  auto const skyTexLoc{abcg::glGetUniformLocation(m_skyProgram, "skyTex")};


  // Matriz de projeção
  glm::mat4 projView = glm::mat4(100.0f);

  abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &projView[0][0]);
  abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  abcg::glUniform1i(skyTexLoc, 0);

  abcg::glBindVertexArray(m_skyVAO);

  abcg::glActiveTexture(GL_TEXTURE0);
  abcg::glBindTexture(GL_TEXTURE_CUBE_MAP, m_model.getCubeTexture());

  abcg::glEnable(GL_CULL_FACE);
  abcg::glFrontFace(GL_CW);
  abcg::glDepthFunc(GL_LEQUAL);
  abcg::glDrawArrays(GL_TRIANGLES, 0, m_skyPositions.size());
  abcg::glDepthFunc(GL_LESS);
  abcg::glFrontFace(GL_CCW);

  abcg::glBindVertexArray(0);
  abcg::glUseProgram(0);
}

void Window::onResize(glm::ivec2 const &size) { 
  m_viewportSize = size; 
}

void Window::onDestroy() {
  m_model.destroy();
  m_additionalModel.destroy();
  destroySkybox();
  abcg::glDeleteProgram(m_program);
}

void Window::destroySkybox() const {
  abcg::glDeleteProgram(m_skyProgram);
  abcg::glDeleteBuffers(1, &m_skyVBO);
  abcg::glDeleteVertexArrays(1, &m_skyVAO);
}