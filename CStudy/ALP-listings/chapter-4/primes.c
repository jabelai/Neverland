/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <pthread.h>
#include <stdio.h>

/* Compute successive prime numbers (very inefficiently).  Return the
   Nth prime number, where N is the value pointed to by *ARG.  */

void* compute_prime (void* arg)
{
  // Print the current thread id
  pthread_t currentThreadId = pthread_self();
  printf("work thread id : %lu\n", currentThreadId);
  printf("print the arg from the main thread : %d\n", *((int*) arg));
  int candidate = 2;
  int n = *((int*) arg);

  while (1) {
    int factor;
    int is_prime = 1;

    /* Test primality by successive division.  */
    for (factor = 2; factor < candidate; ++factor)
      if (candidate % factor == 0) {
        is_prime = 0;
        printf("print the arg from the main thread : %d\n", *((int*) arg));
        break;
      }
    /* Is this the prime number we're looking for?  */
    if (is_prime) {
      if (--n == 0) {
        /* Return the desired prime number as the thread return value.  */
        printf("print the arg from the main thread : %d\n", *((int*) arg));
        return (void*) candidate;
      }
    }
    ++candidate;
  }
  printf("print the arg from the main thread : %d\n", *((int*) arg));
  return NULL;
}

int main ()
{
  pthread_t thread;
  int which_prime = 5000;
  int prime;
  /* Start the computing thread, up to the 5000th prime number.  */
  pthread_create (&thread, NULL, &compute_prime, &which_prime);
  /* Do some other work here...  */
  /* Wait for the prime number thread to complete, and get the result.  */
  if (!pthread_equal (pthread_self(), thread)) {
    pthread_join (thread, (void*) &prime);
  }
  // Print the current thread id
  pthread_t currentThreadId = pthread_self();
  printf("main thread id : %lu\n", currentThreadId);
  /* Print the largest prime it computed.  */
  printf("Hello, The %dth prime number is %d.\n", which_prime, prime);
  return 0;
}