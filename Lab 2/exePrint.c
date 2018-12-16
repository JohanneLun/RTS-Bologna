#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
  execlp("/afs/numi.ing.unibo.it/users/stud/9/2/5/s1900071925/Documents/Lab 2/print5", "./print5", (char*)NULL);
}

// https://stackoverflow.com/questions/21558937/i-do-not-understand-how-execlp-works-in-linux
