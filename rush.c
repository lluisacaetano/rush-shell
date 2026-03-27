#include "rush.h"

// Função para analisar um comando e separar seus argumentos
void parse_command(char *cmd, char **args) {
    int i = 0;
    char *token = strtok(cmd, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

// Função para analisar um comando e separar os comandos com pipes
void parse_command_with_pipes(char *cmd, char **cmds) {
    int i = 0;
    char *token = strtok(cmd, "|");
    while (token != NULL && i < MAX_ARGS - 1) {
        cmds[i++] = token;
        token = strtok(NULL, "|");
    }
    cmds[i] = NULL;
}

// Função para tratar redirecionamentos de entrada e saída
void handle_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            break;
        } else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
            break;
        }
    }
}

// Função para executar um comando
void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    parse_command(cmd, args);
    handle_redirection(args);

    if (execvp(args[0], args) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char command[1024]; // Buffer para armazenar o comando digitado
    char *cmds[MAX_ARGS]; // Array para armazenar comandos separados por pipes
    int i, status;
    pid_t pid;
    int pipefd[2];
    int fd_in = 0;

    while (1) {
        // Exibe o prompt e lê o comando digitado
        printf("Digite o comando: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Se o comando for "exit", termina o programa
        if (strncmp(command, "exit", 4) == 0) {
            break;
        }

        // Analisa o comando e separa os comandos com pipes
        parse_command_with_pipes(command, cmds);

        // Executa cada comando separado por pipes
        for (i = 0; cmds[i] != NULL; i++) {
            pipe(pipefd);
            if ((pid = fork()) == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                dup2(fd_in, 0); // Redireciona a entrada do processo atual
                if (cmds[i + 1] != NULL) {
                    dup2(pipefd[1], 1); // Redireciona a saída para o próximo comando
                }
                close(pipefd[0]);
                execute_command(cmds[i]);
            } else {
                waitpid(pid, &status, 0); // Espera o processo filho terminar
                close(pipefd[1]);
                fd_in = pipefd[0]; // Salva a leitura do pipe para o próximo comando
            }
        }
    }

    return 0;
}
