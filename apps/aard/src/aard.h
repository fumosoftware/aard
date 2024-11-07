//
// Created by fumosoftware on 11/6/2024.
//

#ifndef AARD_H
#define AARD_H

#include "SDL.h"

namespace fumo {

class Aard {
public:
  Aard(SDL_Window* window, SDL_Renderer* renderer) noexcept;
  ~Aard() noexcept;

  Aard(const Aard&) = delete;
  Aard& operator=(const Aard&) noexcept = delete;
  Aard(Aard&&) = delete;
  Aard& operator=(Aard&&) noexcept = delete;

  [[nodiscard]] auto run() noexcept -> int;
private:
  SDL_Window* m_window {nullptr};
  SDL_Renderer* m_renderer {nullptr};
};

}

#endif //AARD_H
