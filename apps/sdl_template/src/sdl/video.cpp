//
// Created by fumosoftware on 10/28/2024.
//

#include "video.h"

#include "SDL.h"

void render(sdl::Video const& video) noexcept {
  auto& [renderer, _] = video.graphics_context;
  SDL_assert(renderer != nullptr);

  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, video.graphics_context.textures[0],nullptr, nullptr);
  SDL_RenderPresent(renderer);
}