//
// Created by fumosoftware on 11/15/2024.
//

#include "aard.h"

#include "fmt/format.h"

#include <iostream>
#include <utility>

using namespace std::string_literals;

namespace {
constexpr auto SDL_INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_EVENTS;

struct SDL_Context {
  SDL_Window* window{ nullptr };
  SDL_Renderer* renderer{ nullptr };
};

struct AppError {

  std::string message{};
  aard::ErrorCode error{};
};
}

namespace aard {
std::expected<Aard, ErrorCode> Aard::create_app() noexcept {
  auto const initialize_sdl = []() -> std::expected<SDL_Context, AppError> {
    [[unlikely]] if(SDL_WasInit(0) != 0) {
      return std::unexpected {
        AppError {
          "SDL has already been initialized."s,
          ErrorCode::SDLAlreadyInitialized
        }
      };
    }

    [[unlikely]] if(SDL_Init(SDL_INIT_FLAGS) != 0) {
      return std::unexpected {
        AppError {
          fmt::format("SDL could not be initialized: {}", SDL_GetError()),
          ErrorCode::SDLInitializationFailure
        }
      };
    }

    return SDL_Context{};
  };


  auto const create_window_and_renderer = [](SDL_Context ctx) -> std::expected<SDL_Context, AppError> {
    [[unlikely]] if(SDL_CreateWindowAndRenderer(600, 400, 0, &ctx.window, &ctx.renderer) != 0) {
      return std::unexpected {
        AppError {
          fmt::format("Could not create window or renderer: {}", SDL_GetError()),
          ErrorCode::WindowOrRendererCreationFailure
        }
      };
    }

    return ctx;
  };

  auto const cleanup_and_cry = [](AppError const& err) -> std::expected<SDL_Context, ErrorCode> {
    SDL_Log("Error: %s", err.message.c_str());
    SDL_Quit();
    return std::unexpected{err.error};
  };

  auto ctx = initialize_sdl()
        .and_then(create_window_and_renderer)
        .or_else(cleanup_and_cry);

  [[unlikely]] if(!ctx) return std::unexpected{ ctx.error() };

  return Aard{ ctx->window, ctx->renderer };
}

Aard::~Aard() noexcept {
  if(!was_moved) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }
}

Aard::Aard(Aard&& rhs) noexcept :
  was_moved{std::exchange(rhs.was_moved, true) },
  m_window{ std::exchange(rhs.m_window, nullptr) },
  m_renderer{ std::exchange(rhs.m_renderer, nullptr) }
{
  SDL_assert(m_window != nullptr);
  SDL_assert(m_renderer != nullptr);
}

Aard& Aard::operator=(Aard&& rhs) noexcept {
  was_moved = std::exchange(rhs.was_moved, true);
  m_window = std::exchange(rhs.m_window, nullptr);
  m_renderer = std::exchange(rhs.m_renderer, nullptr);

  SDL_assert(m_window != nullptr);
  SDL_assert(m_renderer != nullptr);
  return *this;
}

int Aard::run() noexcept{
  SDL_assert(m_window != nullptr);
  SDL_assert(m_renderer != nullptr);

  while(1) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) return 0;
    }

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
  }

  return 0;
}

Aard::Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept :
  m_window { window },
  m_renderer { renderer }
{
  SDL_assert(m_window != nullptr);
  SDL_assert(m_renderer != nullptr);
}
} // aard