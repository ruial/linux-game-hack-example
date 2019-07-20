#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <sys/types.h>

#define PLAYER_OFFSET_1 0x1AC6E00
#define PLAYER_OFFSET_2 0x18
#define HEALTH_OFFSET 0xC0
#define AMMO_OFFSET 0xD8

typedef struct {
  bool health;
  bool ammo;
} Options;

typedef struct {
  pid_t pid;
  unsigned long module;
  Options options;
} Game;

typedef struct {
  char _1[0xC0];
  float health;  // 0xC0
  char _2[0x14]; // 0xD8 - 0xC0 - 0x4(sizeof float)
  float ammo;    // 0xD8
  unsigned long address;
} MyPlayer;

void open_game(Game *game);

bool readMyPlayer(Game game, MyPlayer *myPlayer);

void writeHealth(Game game, MyPlayer myPlayer, float value);

void writeAmmo(Game game, MyPlayer myPlayer, float value);

#endif
