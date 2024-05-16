#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid of receiver> <number to send>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid_t receiver_pid = atoi(argv[1]);
    int number = atoi(argv[2]);

    if (receiver_pid <= 0 || number <= 0) {
        fprintf(stderr, "Invalid PID or number\n");
        return EXIT_FAILURE;
    }

    // Send the number to the receiver using SIGUSR1
    printf("Sender: Sending number %d to receiver\n", number);
    union sigval sv;
    sv.sival_int = number;
    sigqueue(receiver_pid, SIGUSR1, sv);

    return EXIT_SUCCESS;
}
