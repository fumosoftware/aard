//
// Created by fumosoftware on 11/15/2024.
//

#include "aard.h"
#include <iostream>

namespace {
}

namespace aard {

auto Aard::create_app()-> std::expected<Aard, AppError> {
  constexpr auto SDL_INIT_FLAGS = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
  auto const initialize_sdl = []->std::expected<void, AppError> {
    [[unlikely]] if(SDL_WasInit(0) != 0) {
      SDL_Log("SDL was already initialized.");
      return std::unexpected{ aard::AppError::SDLAlreadyInitialized };
    }

    [[unlikely]] if(SDL_Init(SDL_INIT_FLAGS) != 0) {
      SDL_Log("SDL_Init: %s", SDL_GetError());
      return std::unexpected{ aard::AppError::SDLInitializationFailed };
    }
    return {};
  };

  struct SDL_Context {
    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
  };
  auto const create_context = []->std::expected<SDL_Context, AppError> {
    SDL_Context context{};
    [[unlikely]] if(SDL_CreateWindowAndRenderer(600, 400, 0, &context.window, &context.renderer) != 0) {
      SDL_Log("Error: %s", SDL_GetError());
      SDL_Quit();
      return std::unexpected{ aard::AppError::WindowOrRendererCreationFailed };
    }

    return std::expected<SDL_Context, aard::AppError>{context};
  };

  auto const create_app = [](SDL_Context ctx) {
            return Aard{ctx.window, ctx.renderer};
          };

  return initialize_sdl()
          .and_then(create_context)
          .transform(create_app);
}

Aard::Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept :
  m_window(window, SDL_DestroyWindow),
  m_renderer(renderer, SDL_DestroyRenderer)
{
  SDL_assert(window != nullptr);
  SDL_assert(renderer != nullptr);
}

Aard::~Aard() noexcept{
  SDL_Quit();
}

int Aard::run() noexcept{
  while(1) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) return 0;

      SDL_RenderClear(m_renderer.get());
      SDL_RenderPresent(m_renderer.get());
    }
  }

  return 0;
}


} // aard