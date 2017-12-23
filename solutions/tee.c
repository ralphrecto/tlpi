/**
 * Implementation of tee using syscalls.
 */
#include "tlpi_hdr.h"
#include "fcntl.h"

void usage(char* argv0) {
  usageErr("%s [-a] [FILE]...\n -a append to given files, do not overwrite\n", argv0);
}

int main(int argc, char* argv[]) {
  // Parse command line arguments.
  if (argc < 2) {
    usage(argv[0]);
  }

  int append_mode = strcmp(argv[1], "-a") == 0;

  if (append_mode && (argc < 3)) {
    usage(argv[0]);
  }

  // Open all files given as input.
  int file_count = argc - (append_mode ? 2 : 1);

  int open_flags = O_WRONLY | O_CREAT | (append_mode ? O_APPEND : 0);
  int fds[file_count];
  for (int i = 0; i < file_count; i++) {
    fds[i] = open(argv[argc - file_count + i], open_flags);
  }

  // Allocate buffer to place stdin data into.
  int max_read = 128;
  char buf[max_read];

  int read_res;
  while ((read_res = read(STDIN_FILENO, buf, max_read)) > 0) {
    write(STDOUT_FILENO, buf, read_res);

    for (int i = 0; i < file_count; i++) {
      write(fds[i], buf, read_res);
    }
  }

  if (read_res < 0) {
    errExit("reading from stdin");
  }

  // Clean up opened files.
  for (int i = 0; i < file_count; i++) {
    if (close(fds[i]) < 0) {
      errExit("error on closing file.");
    }
  }
}
