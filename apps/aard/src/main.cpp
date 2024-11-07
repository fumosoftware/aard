//
// Created by fumosoftware 10/23/2024.
//


#include "SDL.h"
#include "aard.h"

int main(int, char**) {
  auto app_context = fumo::initialize_app();
  if(!app_context) {
    SDL_Log("%s", app_context.error().c_str());
    return 1;
  }

  fumo::Aard aard{*app_context};

  return aard.run();
}