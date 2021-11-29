#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

char *filename = "test.txt";

void readFromFile();

void child_handler(int sig) {
    readFromFile();
}

char *get_input() {
    char input[LINE_MAX];
    printf("Please enter your input: ");
    fgets(input, LINE_MAX, stdin);
    return input;
}

void writeToFile(char *input) {
    FILE *file = fopen(filename, "w");
    printf("%s", input);
    fputs(input, file);
    fclose(file);
}

void readFromFile() {
    FILE *file = fopen(filename, "r");
    char fileContent[LINE_MAX];
    fgets(fileContent, LINE_MAX, file);
    fclose(file);

    printf("Child process : %s", fileContent);
}

int main() {
    writeToFile(get_input());

    pid_t pid;
    if ((pid = fork()) == 0) {
        signal(SIGUSR1, child_handler);
        kill(pid, SIGUSR1);
    }
    while (1);
}