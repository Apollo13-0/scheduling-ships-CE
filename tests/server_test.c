#include "server_test.h"

int serverTest() {
    int fd = configureSerialPort();
    if (fd < 0) {
        return 1; // Termina si hay un error al abrir el puerto
    }

    int number = 0; // Comienza en 4
    char write_buffer[20]; // Buffer para el mensaje

    while (number < 10) { // Cambia la condición según sea necesario
        // Formatear el mensaje con el número incrementado
        sprintf(write_buffer, "%dN-NNAP-1-7P\n", number);
        
        // Enviar el mensaje al Arduino
        writeSerialPort(fd, write_buffer);
        
        number++; // Incrementar el número
        sleep(1); // Esperar 1 segundo entre envíos
    }

    close(fd); // Cerrar el puerto
    return 0; // Terminar exitosamente
}
