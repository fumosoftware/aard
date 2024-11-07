//
// Created by fumosoftware on 11/6/2024.
//

#include "aard.h"

#include "fmt/core.h"

namespace fumo {

auto initialize_app()-> std::expected<AppContext, std::string>{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    return std::unexpected{fmt::format("Error: Could not initialize SDL. Reason: {}", SDL_GetError())};
  }

  AppContext context{};
  if(SDL_CreateWindowAndRenderer(600, 380, 0, &context.window, &context.renderer) != 0) {
    return std::unexpected{fmt::format("Error: Could not create Window/Renderer. Reason: {}", SDL_GetError())};
  }

  return context;
}

Aard::Aard(AppContext context) noexcept :
  m_window{context.window}, m_renderer{context.renderer} {
  SDL_assert(m_window != nullptr);
  SDL_assert(m_renderer != nullptr);
}


Aard::~Aard() noexcept {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);

  SDL_Quit();
}

auto Aard::run() noexcept-> int {
  if(!m_window) {
    SDL_Log("Window is null");
    return 1;
  }

  if(!m_renderer) {
    SDL_Log("Renderer is null");
    return 1;
  }

  bool is_running{true};
  while(is_running) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) { is_running = false; }
    }

    if(!is_running) { break;}

    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
  }

  return 0;
}

}