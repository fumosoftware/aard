//
// Created by fumosoftware on 11/15/2024.
//

#ifndef AARD_H
#define AARD_H

#include <expected>
#include <memory>
#include "SDL.h"

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

  // Move constructor flips should_quit_sdl to false
  // Destructor checks should_quit_sdl, and if true then it deletes SDL_Window and SDL_Renderer
  // then calls SDL_Quit()
  Aard(Aard&&) noexcept;
  [[nodiscard]] Aard& operator=(Aard&&) noexcept;

  [[nodiscard]] int run() noexcept;
private:
  Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept;

  bool was_moved{false};
  SDL_Window* m_window{ nullptr };
  SDL_Renderer* m_renderer{ nullptr };
};

} // aard

#endif //AARD_H
