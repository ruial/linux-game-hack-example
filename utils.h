#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <sys/types.h>

bool read_addr(pid_t pid, unsigned long addr, void *buffer, size_t size);

bool write_addr(pid_t pid, unsigned long addr, void *buffer, size_t size);

pid_t find_pid(char *name);

unsigned long module_addr(pid_t pid, char *name);

void sleep_ms(int ms);

void mouse_click();

#endif
