#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int received_number = 0;

void sig_handler(int signum, siginfo_t *info, void *context) {
    if (signum == SIGUSR1) {
        received_number = info->si_value.sival_int;
    }
}

int main(void) {
    // Register signal handler with sigaction
    struct sigaction sa;
    sa.sa_sigaction = sig_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    printf("Receiver: Waiting for number from sender...\n");

    // Wait for signal from sender
    while (received_number == 0) {
        sleep(1);
    }

    printf("Receiver: Received number: %d\n", received_number);

    return EXIT_SUCCESS;
}
