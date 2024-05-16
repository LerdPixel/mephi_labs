#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
        union sigval value;
        value.sival_int = 123;
        sigqueue(0,SIGUSR1, value);
}