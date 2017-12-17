/**
 * Implementation of tee using syscalls.
 */

#include "tlpi_hdr.h"

int main(int argc, char* args[]) {
  int max_read = 128;
  char buf[max_read];
  int read_res;

  while ((read_res = read(STDIN_FILENO, buf, max_read)) > 0) {
    write(STDOUT_FILENO, buf, read_res);
  }

  if (read_res < 0) {
    errExit("reading from stdin");
  }
}
