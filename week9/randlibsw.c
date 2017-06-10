/* Contains the software implementation of the random number generator. Should
   include randlib.h and implement the interface described by it. */
#include "randlib.h"
#include <stdlib.h>
#include <stdio.h>
//Input stream containing random bytes
static FILE *urandstream;

extern void software_rand64_init (void) __attribute__((constructor));
extern void software_rand64_fini (void) __attribute__((destructor));

//Initialize the software rand64 implementation
extern void software_rand64_init(void) {
  urandstream = fopen ("/dev/urandom", "r");
  if(!urandstream)
    abort();
}

//Return a random value, using software operations
extern unsigned long long software_rand64(void) {
  unsigned long long int x;
  if(fread(&x, sizeof x, 1, urandstream) != 1)
    abort();
  return x;
}

//Finalize the software rand64 implementation
extern void software_rand64_fini(void) {
  fclose(urandstream);
}
