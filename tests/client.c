// gcc -Wall cliente.c sock-lib.c -o cliente

#include "../sock-lib.h"

#define BUFFER_SIZE 4096

int main()
{
    int sock;
    char buf[BUFFER_SIZE];
    int bytes_recibidos;

    // conectarse
    sock = conectar("localhost", 8000, 1);

    // read / write (bloqueante!)
    bytes_recibidos = read(sock, buf, BUFFER_SIZE);
    if (bytes_recibidos == -1)
    {
        fprintf(stderr, "read():: error en la lectura");
    }

    // do....
    buf[bytes_recibidos] = 0;
    fprintf(stderr, "debug:: recibido=%s\n", buf);

    // descomentar para verificar los sockets desde la linea de comandos
    // pause();

    // cerrar el socket
    close(sock);

    return 0;
}