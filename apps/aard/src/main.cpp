//
// Created by fumosoftware on 11/15/2024.
//

#include "aard.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  if(auto aard_game = aard::Aard::create_app()) {
    return aard_game->run();
  }

  return 1;
}