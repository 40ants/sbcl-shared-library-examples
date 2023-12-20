#include "hello.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern int init_hello();


int main(int argc, char **argv) {
  printf("Initializing\n");
  init_hello();
  printf("Initialized\n");

  printf("Calling Lisp function from DLL.\n");
  hello_world("Bob");

  printf("Calling start-slynk function from DLL.\n");
  start_slynk(4005);

  printf("Exiting.\n");
  return 0;
}
