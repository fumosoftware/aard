//
// Created by fumosoftware on 10/28/2024.
//

#include "context.h"

#include <fmt/format.h>


using namespace std::string_literals;
namespace {
std::expected<sdl::Video, std::string> setup_sdl_video() {
  SDL_Window* window{nullptr};
  SDL_Renderer* renderer{nullptr};
  if(SDL_CreateWindowAndRenderer(600, 380, 0, &window, &renderer) != 0) {
    return std::unexpected{fmt::format("Failed to setup video: {}", SDL_GetError())};
  }

  return sdl::Video{
    .window{window},
    .graphics_context{renderer}
  };
}

void teardown_sdl_video(sdl::Video& video) {
  for(auto const texture : video.graphics_context.textures) {
    SDL_DestroyTexture(texture);
  }

  SDL_DestroyRenderer(video.graphics_context.renderer);
  SDL_DestroyWindow(video.window);
}
}

std::expected<sdl::Context, std::string> setup_sdl() noexcept {
  if(auto const was_init = SDL_WasInit(0); was_init != 0) {
    SDL_assert(was_init == 0);
    return std::unexpected{"SDL is already initialized!"s};
  }

  //SDL_INIT_VIDEO implies also initializing SDL_INIT_EVENTS
  if(auto const did_init = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS); did_init != 0) {
    SDL_assert(!did_init);
    return std::unexpected{fmt::format("SDL could not be initialized: {}", SDL_GetError())};
  }

  auto video = setup_sdl_video();
  if(!video) {
    SDL_assert(!video);
    return std::unexpected{video.error()};
  }

  return sdl::Context{
    .video{*video}
  };
}

void teardown_sdl(sdl::Context& ctx) noexcept {
  auto& [video] = ctx;

  teardown_sdl_video(video);
  SDL_Quit();
}