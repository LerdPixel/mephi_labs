#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t status = 0;

static void catch_function(int signo) {
    status = signo;
    printf("signal received: %d\n", signo);
}

int main(void) {
    // Set above function as signal handler for the SIGINT signal:
    if (signal(SIGINT, catch_function) == SIG_ERR) {
        fputs("An error occurred while setting a signal handler.\n", stderr);
        return EXIT_FAILURE;
    }
    puts("Raising the interactive attention signal.");
    if (raise(SIGINT)) {
        fputs("Error raising the signal.\n", stderr);
        return EXIT_FAILURE;
    }
    if (status == SIGINT) puts("Interactive attention signal caught.");
    puts("Exiting.");
    return EXIT_SUCCESS;
    // exiting after raising signal
}