# Define o compilador a ser utilizado
CC = gcc

# Define as flags de compilação:
# -Wall: ativa todos os avisos do compilador.
# -g: inclui informações de depuração no executável.
CFLAGS = -Wall -g

# Alvo padrão do make. Ao rodar 'make' sem argumentos, ele tenta construir 'rush'.
all: rush

# Regra para construir o executável 'rush'
# 'rush' depende de 'rush.o'
rush: rush.o
	# Comando para compilar e criar o executável 'rush' a partir do objeto 'rush.o'
	$(CC) $(CFLAGS) -o rush rush.o

# Regra para construir o objeto 'rush.o'
# 'rush.o' depende dos arquivos 'rush.c' e 'rush.h'
rush.o: rush.c rush.h
	# Comando para compilar 'rush.c' e gerar o objeto 'rush.o'
	$(CC) $(CFLAGS) -c rush.c

# Regra para limpar os arquivos de objeto e o executável
clean:
	# Comando para remover 'rush.o' e 'rush'
	rm -f rush.o rush
