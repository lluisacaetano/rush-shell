# Rush - Shell Simples em C

Um interpretador de comandos (shell) minimalista desenvolvido em C, com suporte a pipes e redirecionamento de entrada/saída.

## Funcionalidades

- Execução de comandos do sistema
- Suporte a **pipes** (`|`) para encadeamento de comandos
- **Redirecionamento de saída** (`>`) para arquivos
- **Redirecionamento de entrada** (`<`) de arquivos
- Comando `exit` para encerrar o shell

## Compilação

```bash
make
```

Para limpar os arquivos compilados:

```bash
make clean
```

## Uso

```bash
./rush
```

### Exemplos

```bash
# Comando simples
Digite o comando: ls -la

# Usando pipes
Digite o comando: ls | grep .c

# Redirecionamento de saída
Digite o comando: ls > arquivos.txt

# Redirecionamento de entrada
Digite o comando: cat < arquivo.txt

# Sair do shell
Digite o comando: exit
```

## Estrutura do Projeto

| Arquivo | Descrição |
|---------|-----------|
| `rush.c` | Código fonte principal |
| `rush.h` | Header com definições e protótipos |
| `makefile` | Script de compilação |

## Requisitos

- GCC (GNU Compiler Collection)
- Sistema operacional Unix-like (Linux, macOS)

## Autor

Luisa Caetano

