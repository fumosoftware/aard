//
// Created by fumosoftware on 10/28/2024.
//

#ifndef sdl_template_SDL_VIDEO_H
#define sdl_template_SDL_VIDEO_H

#include "SDL.h"
#include "graphics_context.h"

namespace sdl {
struct Video {
  SDL_Window*     window{nullptr};
  GraphicsContext graphics_context{};
};
}

void render(sdl::Video const& video) noexcept;
#endif //sdl_template_SDL_VIDEO_H
