#define API_BUILD

#include "hello.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern int initialize_lisp(int argc, char **argv);

int (*hello_world)(char *);

void (*start_slynk)(int);


int init_hello() {
  static int initialized = 0;
  char *init_args[] = {"", "--core", "libhello.core", "--noinform", };
  if (initialized) return 1;
  if (initialize_lisp(4, init_args) != 0) return -1;
  initialized = 1;
  return 0;
}

