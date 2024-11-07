//
// Created by fumosoftware on 11/6/2024.
//

#include "aard.h"

namespace fumo {

Aard::Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept :
  m_window{window}, m_renderer{renderer} {
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