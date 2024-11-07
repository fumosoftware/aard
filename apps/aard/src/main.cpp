//
// Created by fumosoftware 10/23/2024.
//

#include "SDL.h"
#include "SDL_image.h"
#include "sdl/context.h"

sdl::Context unwrap_or_panic(std::expected<sdl::Context, std::string>&& maybe) {
  // Something really really bad has happened!
  // SDL_Quit will have already been called, and SDL_Window*/SDL_Renderer* would have
  // already been destroyed/uninitialized right here.
  SDL_assert(maybe.has_value() == true);
  if(!maybe) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Error: %s",maybe.error().c_str());
    std::exit(1);
  }

  return *maybe;
}

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv) {
  //TODO: Create settings from a config file or command line arguments
  auto context = unwrap_or_panic(setup_sdl());


  auto tex = IMG_LoadTexture(context.video.graphics_context.renderer, "data/smiley.png");
  if(tex == nullptr) {
    return 2;
  }

  context.video.graphics_context.textures.push_back(tex);

  bool is_running{true};
  while(is_running) {
    SDL_Event event{};
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        is_running = false;
      }
    }

    if(!is_running) { break; }

    render(context.video);
  }

  teardown_sdl(context);
  return 0;
}