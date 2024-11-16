//
// Created by fumosoftware on 11/15/2024.
//

#ifndef AARD_H
#define AARD_H

#include <expected>
#include <memory>
#include "SDL.h"

namespace aard {
using WindowHandle = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using RendererHandle = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

enum struct AppError {
  SDLAlreadyInitialized,
  SDLInitializationFailed,
  WindowOrRendererCreationFailed,
};

class Aard {
public:
  // named constructor, just in case SDL Initialization fails.
  //  this will:
  //    1. check if SDL is already initialized. if it is, returns AppError::SDLAlreadyInitialized.
  //    2. attempt to initialize SDL. if initialization fails, returns AppError::SDLInitializationFailed.
  //    3. creates the window and renderering context. if that fails, calls SDL_Quit() and returns AppError::WindowOrRendererCreationFailed.
  //    4. creates an instance of aard::Aard and returns it (should be created in place, as aard::Aard will call SDL_Quit() in its destructor.)
  static auto create_app() -> std::expected<Aard, AppError>;
  ~Aard() noexcept;

  Aard(const Aard&) = delete;
  Aard& operator=(const Aard&) = delete;

  // runs application loop.
  int run() noexcept;
private:
  // actual constructor. asserts if either window or renderer are nullptr.
  Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept;

  aard::WindowHandle m_window { nullptr, SDL_DestroyWindow };
  aard::RendererHandle m_renderer { nullptr, SDL_DestroyRenderer };

};

} // aard

#endif //AARD_H
