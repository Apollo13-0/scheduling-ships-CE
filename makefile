# Variables para el compilador y flags
CC = gcc
CFLAGS = -Wall -g   # Mostrar todas las advertencias y habilitar debug (-g)
LDFLAGS = -lcjson         # Flags adicionales de linkeo si son necesarios

# Archivos fuente y objetos
SRCS = main.c ship.c CEthreads.c config-file/config.c tests/ship_test.c tests/thread_test.c tests/mutex_test.c tests/config_test.c canal.c tests/canal_test.c  linkedList.c tests/schedulers_test.c ocean.c schedulers.c
#SRCS = main_test.c ship.c CEthreads.c config-file/config.c tests/ship_test.c tests/thread_test.c tests/mutex_test.c tests/config_test.c canal.c tests/canal_test.c  linkedList.c tests/schedulers_test.c ocean.c schedulers.c
OBJS = $(SRCS:.c=.o)  # Cambia .c por .o para generar los archivos objeto

# Nombre del ejecutable
TARGET = scheduling_ships

# Regla principal para generar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regla para compilar los archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpieza de archivos intermedios y ejecutables
clean:
	rm -f $(OBJS) $(TARGET)
