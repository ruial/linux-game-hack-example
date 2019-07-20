#include "game.h"
#include "keyboard.h"
#include "utils.h"
#include <stdio.h>

void open_game(Game *game) {
  open_keyboard();
  while ((game->pid = find_pid("xonotic-linux64-sdl")) == 0) {
    sleep_ms(1000);
  }
  while ((game->module = module_addr(game->pid, "xonotic-linux64-sdl")) == 0) {
    sleep_ms(1000);
  }
}

bool readMyPlayer(Game game, MyPlayer *myPlayer) {
  unsigned long ptr;
  if (read_addr(game.pid, game.module + PLAYER_OFFSET_1, &ptr, sizeof(ptr))) {
    // printf("%lx\n", ptr);
    if (read_addr(game.pid, ptr + PLAYER_OFFSET_2, &ptr, sizeof(ptr))) {
      // printf("%lx\n", ptr);
      // float health;
      // read_addr(game.pid, ptr + 0xC0, &health, sizeof(health));
      // printf("%d\n", (int)health);
      myPlayer->address = ptr;
      return read_addr(game.pid, ptr, myPlayer,
                       sizeof(MyPlayer) - sizeof(myPlayer->address));
    }
  }
  return false;
}

void writeHealth(Game game, MyPlayer myPlayer, float value) {
  write_addr(game.pid, myPlayer.address + HEALTH_OFFSET, &value, sizeof(value));
}

void writeAmmo(Game game, MyPlayer myPlayer, float value) {
  write_addr(game.pid, myPlayer.address + AMMO_OFFSET, &value, sizeof(value));
}
