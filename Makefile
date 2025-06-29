# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g  # Ativa warnings, padrão C11 e debug symbols
LDFLAGS = -lm  # Linkagem com math.h (se necessário)

# Nome do executável final
TARGET = programa

# Arquivos fonte (.c) e objetos (.o)
SRCS = main.c bd_paciente.c paciente.c interface.c
OBJS = $(SRCS:.c=.o)

# Regra padrão: compila tudo
all: $(TARGET)

# Gera o executável ligando os objetos
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "\n--- Compilação concluída. Execute com: ./$(TARGET) ---\n"

# Regras para cada arquivo objeto
main.o: main.c bd_paciente.h paciente.h interface.h
	$(CC) $(CFLAGS) -c $<

bd_paciente.o: bd_paciente.c bd_paciente.h paciente.h
	$(CC) $(CFLAGS) -c $<

paciente.o: paciente.c paciente.h
	$(CC) $(CFLAGS) -c $<

interface.o: interface.c interface.h paciente.h bd_paciente.h # Correção aqui
	$(CC) $(CFLAGS) -c $<

# Limpa objetos e executável
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Arquivos de build removidos."

# Executa o programa (após compilar)
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run