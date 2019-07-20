#define _GNU_SOURCE
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

// http://manpages.ubuntu.com/manpages/trusty/man2/process_vm_readv.2.html
bool read_addr(pid_t pid, unsigned long addr, void *buffer, size_t size) {
  struct iovec local[1];
  struct iovec remote[1];

  local[0].iov_base = buffer;
  local[0].iov_len = size;
  remote[0].iov_base = (void *)addr;
  remote[0].iov_len = size;

  // pid, local struct, local size, remote struct, remote size, flags
  return process_vm_readv(pid, local, 1, remote, 1, 0) == size;
}

bool write_addr(pid_t pid, unsigned long addr, void *buffer, size_t size) {
  struct iovec local[1];
  struct iovec remote[1];

  local[0].iov_base = buffer;
  local[0].iov_len = size;
  remote[0].iov_base = (void *)addr;
  remote[0].iov_len = size;

  return process_vm_writev(pid, local, 1, remote, 1, 0) == size;
}

pid_t find_pid(char *name) {
  char cmd[100] = "pidof ";
  strcat(cmd, name);
  FILE *f = popen(cmd, "r");
  char line[20];
  fgets(line, 20, f);
  pclose(f);
  return strtoul(line, NULL, 10);
}

unsigned long module_addr(pid_t pid, char *name) {
  char cmd[200];
  sprintf(cmd, "cat /proc/%d/maps | grep %s -m1 | cut -d '-' -f1", pid, name);
  FILE *f = popen(cmd, "r");
  char line[20];
  fgets(line, 20, f);
  pclose(f);
  return strtoul(line, NULL, 16);
}

void sleep_ms(int ms) { usleep(ms * 1000); }

void mouse_click() { system("xdotool click 1 && sleep 0.2"); }
