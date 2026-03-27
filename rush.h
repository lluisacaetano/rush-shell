#ifndef RUSH_H
#define RUSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// Definindo o número máximo de argumentos que um comando pode ter
#define MAX_ARGS 100

// Função para dividir a linha de comando em argumentos
void parse_command(char *cmd, char **args);

// Função para dividir a linha de comando em comandos separados por pipes
void parse_command_with_pipes(char *cmd, char **cmds);

// Função para manipular redirecionamento de entrada e saída
void handle_redirection(char **args);

// Função para executar um comando específico
void execute_command(char *cmd);

#endif