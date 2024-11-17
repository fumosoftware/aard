//
// Created by fumosoftware on 11/15/2024.
//

#include "aard.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  if(auto aard_game = aard::Aard::create_app()) {
    return aard_game->run();
  } else {
    SDL_Log("Error: %s", aard_game.error().message.c_str());
    return 1;
  }
}