/**
 * Implementation of cp that preserves file holes.
 */
#include "tlpi_hdr.h"
#include "fcntl.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    usageErr("%s SOURCE DEST\n", argv[0]);
  }

  int source_fd = open(argv[1], O_RDONLY);
  if (source_fd < 0) {
    errExit("Could not open source file.");
  }

  int dest_fd = open(argv[2], O_WRONLY | O_CREAT);
  if (dest_fd < 0) {
    errExit("Could not open dest file.");
  }

  char buf = 0;
  int bufsize = sizeof(char);
  int read_res;
  while ((read_res = read(source_fd, &buf, bufsize)) > 0) {
    if ((buf ^ 0) == 0) {
      // If the word read is null, seek ahead in dest instead of writing
      // to preserve file holes.
      lseek(dest_fd, bufsize, SEEK_CUR);
    } else {
      write(dest_fd, &buf, read_res);
    }

    // Clear out the buffer for the next iteration, in case less than bufsize
    // bytes are read.
    buf = 0;
  }

  // Clean up all used files.
  if (close(source_fd) < 0 || close(dest_fd) < 0) {
    errExit("Could not close all files.");
  }
}
