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
}

namespace aard {

std::expected<Aard, AppError> Aard::create_app() noexcept{
  if(SDL_WasInit(0) != 0) {
    return std::unexpected{
      AppError{
        "SDL was already initialized."s,
        AppError::Error::SDLAlreadyInitialized
      }
    };
  }

  if(SDL_Init(SDL_INIT_FLAGS) != 0) {
    SDL_Log("Error: %s", SDL_GetError());
    return std::unexpected{
      AppError{
        fmt::format("SDL failed to initialize: {}", SDL_GetError()),
        AppError::Error::SDLInitializationFailure
      }
    };
  }

  SDL_Window* window{ nullptr };
  SDL_Renderer* renderer{ nullptr };
  if(SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer) != 0) {
    SDL_Quit();
    return std::unexpected{
      AppError{
        fmt::format("Failed to create window or renderer: {}", SDL_GetError()),
        AppError::Error::WindowOrRendererCreationFailure
      }
    };
  }

  return Aard{window, renderer};
}

Aard::~Aard() noexcept {
  if(!was_moved) {
    std::cout << "Not moved, quitting SDL.\n";
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