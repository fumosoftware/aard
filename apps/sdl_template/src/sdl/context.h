//
// Created by fumosoftware on 10/28/2024.
//

#ifndef sdl_template_SDL_CONTEXT_H
#define sdl_template_SDL_CONTEXT_H

#include <expected>
#include <string>
#include "video.h"

namespace sdl {
struct Context {
  Video video{};
};
}

std::expected<sdl::Context, std::string> setup_sdl() noexcept;
void teardown_sdl(sdl::Context& ctx) noexcept;

#endif //CONTEXT_H
