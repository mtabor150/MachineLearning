#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include "charVector.h"
#include "tweet.h"

using namespace std;

int main(int argc, char **argv) {
  
  if (argc < 2) {
    printf("Error:  please give the name of the file to read from.\n");
    return 0;
  }

  printf("Reading from file %s\n", argv[1]);

  int fd = open(argv[1], O_RDONLY, 0);  // Open in read only mode
  if (fd >= 0) {
    close(fd);
    vector<map<string, int> > vectors;
  }
  else {
    perror("File not opened.\n");
    exit(errno);
  }

  return 0;
}
