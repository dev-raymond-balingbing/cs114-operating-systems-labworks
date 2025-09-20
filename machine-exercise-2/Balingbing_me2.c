#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void cpu_sched_A();
void wait_exec_funcs_B();

int main() {
    // cpu_sched_A();
    wait_exec_funcs_B();

    return 0;
}

void cpu_sched_A() {
  pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return;
    }

    if (pid == 0) {
        while (1) {
            printf("[CHILD]: PID %d, PPID %d\n", getpid(), getppid());
            usleep(500000); // sleep for 0.5 seconds to slow down output
        }
    } else {
        while (1) {
            printf("[PARENT]: PID %d, PPID %d\n", getpid(), getppid());
            usleep(500000); // sleep for 0.5 seconds to slow down output
        }
    }
}

void wait_exec_funcs_B() {
  pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // CHILD PROCESS - Replace its code with child_program
        execl("./hello", "./hello", (char *)NULL);

        // If exec fails:
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        // PARENT PROCESS
        printf("[PARENT]: PID %d, waits for child with PID %d\n", getpid(), pid);

        int status;
        waitpid(pid, &status, 0); // wait until child finishes (blocking)

        printf("[PARENT]: Child with PID %d finished and unloaded.\n", pid);
    }
}

