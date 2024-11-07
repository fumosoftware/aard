//
// Created by fumosoftware 10/23/2024.
//


#include "SDL.h"
#include "aard.h"

int main(int, char**) {
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("Error: Could not initialize SDL. Reason: %s", SDL_GetError());
    return 1;
  }

  SDL_Window* window{nullptr};
  SDL_Renderer* renderer{nullptr};
  if(SDL_CreateWindowAndRenderer(600, 380, SDL_WINDOW_SHOWN, &window, &renderer) != 0) {
    SDL_Log("Error: Could not create window and renderer. Reason: %s", SDL_GetError());
    return 1;
  }

  fumo::Aard aard{window, renderer};

  return aard.run();
}