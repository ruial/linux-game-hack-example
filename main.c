#include "game.h"
#include "keyboard.h"
#include "utils.h"
#include <stdio.h>

void printPlayer(MyPlayer player) {
  printf("Health: %.2f | Ammo: %d\n", player.health, (int)(player.ammo));
}

int main() {
  printf("waiting for xonotic...\n");
  Game game;
  open_game(&game);
  printf("pid: %d\n", game.pid);
  printf("xonotic-linux64-sdl module: %lx\n", game.module);

  MyPlayer myPlayer;

  while (true) {
    if (readMyPlayer(game, &myPlayer)) {
      manage_input(&game);
      if (game.options.health) {
        writeHealth(game, myPlayer, 150);
      }
      if (game.options.ammo) {
        writeAmmo(game, myPlayer, 20);
      }
      printPlayer(myPlayer);
    } else {
      printf("not in arena\n");
      sleep_ms(1000);
    }
    sleep_ms(50);
  }

  printf("end\n");
  return 0;
}
