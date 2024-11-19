//
// Created by fumosoftware on 11/15/2024.
//

#ifndef AARD_H
#define AARD_H

#include <expected>
#include "SDL.h"
#include "entt/entt.hpp"

namespace aard {

enum struct ErrorCode {
  SDLAlreadyInitialized,
  SDLInitializationFailure,
  WindowOrRendererCreationFailure,
};

class Aard {
public:
  [[nodiscard]] static std::expected<Aard, ErrorCode> create_app() noexcept;
  ~Aard() noexcept;

  Aard(Aard const&) = delete;
  Aard& operator=(Aard const&) = delete;

  // Move constructor flips was_moved to true
  // Destructor checks was_moved, and if false then it deletes SDL_Window and SDL_Renderer
  // then calls SDL_Quit()
  Aard(Aard&&) noexcept;
  [[nodiscard]] Aard& operator=(Aard&&) noexcept;

  [[nodiscard]] int run() noexcept;
private:
  Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept;

  void draw() const noexcept;

  bool was_moved{false};
  SDL_Window* m_window{ nullptr };
  SDL_Renderer* m_renderer{ nullptr };

  // TODO: Move these into some kind of resource manager
  SDL_Texture* m_ball_texture{ nullptr };
  SDL_Texture* m_paddle_texture{ nullptr };
  SDL_Texture* m_brick_texture{ nullptr };

  // ECS registry
  entt::registry m_registry;
};

} // aard

#endif //AARD_H
