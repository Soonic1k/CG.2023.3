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
    m_zoom += (event.wheel.y > 0 ? -0.001f : 0.001f) * 2.0f / 5.0f;
    m_zoom = glm::clamp(m_zoom, 0.00f, 0.02f);
  }
}

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  abcg::glClearColor(0, 0, 0, 1);
  abcg::glEnable(GL_DEPTH_TEST);

  m_program =
      abcg::createOpenGLProgram({{.source = assetsPath + "depth.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                  {.source = assetsPath + "depth.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  m_model.loadObj(assetsPath + "asteroid.obj"); //Change Stars image loaded on screen
  m_model.setupVAO(m_program);


  //STARSHIP MODEL
  m_additionalModel.loadObj(assetsPath + "starship.obj");
  m_additionalModel.setupVAO(m_program);
  m_additionalModelPosition = glm::vec3(0.0f, 0.0f, 0.0f);


  // Camera at (0,0,0) and looking towards the negative z
  glm::vec3 const eye{0.0f, 0.035f, 0.01f};
  glm::vec3 const at{0.0f, -0.1f, -1.0f};
  glm::vec3 const up{0.0f, 1.0f, 0.0f};
  m_viewMatrix = glm::lookAt(eye, at, up);

  //rotação inicial da nave
  m_angle_ship = glm::wrapAngle(glm::radians(0.0f));
  starship_rotation = glm::vec3(1.0f, 1.0f, 1.0f);

  // Setup stars
  for (auto &star : m_stars) {
    randomizeStar(star);
  }

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
      glm::lookAt(glm::vec3(0.0f, 0.005f + m_zoom, 0.035f + m_zoom),
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
    if (star.m_position.z > 0.1f) {
      randomizeStar(star);
      star.m_position.z = -100.0f; // Back to -100
    }
    if (star.m_position.z < -100.0f) {
      randomizeStar(star);
      star.m_position.z = 0.1f; // Back to -100
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
  auto const colorLoc{abcg::glGetUniformLocation(m_program, "color")};


  // Set uniform variables that have the same value for every model
  abcg::glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  abcg::glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);
  abcg::glUniform4f(colorLoc, 0.7f, 0.7f, 0.7f, 0.7f); // White

  //STARSHIP MODEL RENDER
  glm::mat4 additionalModelMatrix{1.0f};
  additionalModelMatrix = glm::translate(additionalModelMatrix, m_additionalModelPosition);
  additionalModelMatrix = glm::scale(additionalModelMatrix, glm::vec3(0.014f, 0.014f, 0.014f));
  additionalModelMatrix = glm::rotate(additionalModelMatrix, m_angle_ship, starship.m_rotationAxis);
  abcg::glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &additionalModelMatrix[0][0]);
  m_additionalModel.render();

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

  abcg::glUseProgram(0);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

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

void Window::onResize(glm::ivec2 const &size) { 
  m_viewportSize = size; 
}

void Window::onDestroy() {
  m_model.destroy();
  m_additionalModel.destroy();
  abcg::glDeleteProgram(m_program);
}