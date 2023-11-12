#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"
#include "model.hpp"
#include "gamedata.hpp"
#include "trackball.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;


private:
  std::default_random_engine m_randomEngine;

  glm::ivec2 m_viewportSize{};
  glm::vec3 m_additionalModelPosition;

  Model m_model;
  Model m_additionalModel;
  GameData m_gameData;
  TrackBall m_trackBall;

  struct Star {
    glm::vec3 m_position{};
    glm::vec3 m_rotationAxis{};
  };

  struct Starship {
    glm::vec3 m_rotationAxis{};
  };

  std::array<Star, 500> m_stars;
  Starship starship;

  float m_angle{};
  float starship_angle{};
  float m_zoom{};

  glm::mat4 m_modelMatrix{1.0f};
  glm::mat4 additionalModelMatrix{1.0f};
  glm::mat4 m_viewMatrix{1.0f};
  glm::mat4 m_projMatrix{1.0f};

  float m_FOV{75.0f};

  GLuint m_program{};


  void randomizeStar(Star &star);
};

#endif