//
// Created by fumosoftware on 10/28/2024.
//

#ifndef sdl_template_SDL_GRAPHICS_CONTEXT_H
#define sdl_template_SDL_GRAPHICS_CONTEXT_H

#include <vector>
#include "SDL.h"

namespace sdl {
struct GraphicsContext {
  SDL_Renderer*             renderer{nullptr};
  std::vector<SDL_Texture*> textures{};
};
}

#endif //sdl_template_SDL_GRAPHICS_CONTEXT_H
