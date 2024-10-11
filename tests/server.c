#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int configurar_puerto_serial(int fd) {
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    tcsetattr(fd, TCSANOW, &options);
    return fd;
}

int main() {
    int fd;
    char *puerto = "/dev/ttyACM0";
    char mensaje[] = "5";  

    fd = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("No se pudo abrir el puerto serial");
        return -1;
    }

    configurar_puerto_serial(fd);

    printf("Enviando mensaje al Arduino...\n");

    int bytes_enviados = write(fd, mensaje, strlen(mensaje));
    if (bytes_enviados < 0) {
        perror("Error al enviar el mensaje");
        close(fd);
        return -1;
    }

    printf("Mensaje enviado: %s\n", mensaje);

    close(fd);
    return 0;
}
