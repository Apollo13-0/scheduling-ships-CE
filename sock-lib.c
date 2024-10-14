/**
 * \file sock-lib.c
 * \brief contiene las funciones simplificadas de manejo de sockets para usar en Informática I
 * \author Alejandro Furfaro
 * \date 2018.09.10
 * \author Oscar Paniagua
 * \date 2022.12.12
 */

#include "sock-lib.h"

/**
 * \fn int conectar (char *hostname, int port)
 * \brief Única función del lado cliente, que crea un socket y conecta a un server que le llega como argumento.
 * \details Se crea un socket y luego se invoca a la función connect para iniciar conexión con el nodo remoto en el
 * cual debe estar ejecutando un programa servidor escuchando conexiones por el mismo port al que inicia la conexión.
 * El port si es 0 se utiliza el valor por default.
 * \return Devuelve un entero con el file descriptor de socket.
 * \author Alejandro Furfaro
 * \date 2018.09.10
 * \author Oscar Paniagua
 * \date 2022.12.12
 */
int conectar(char *hostname, int port, int debug)
{
	int sockfd;
	struct hostent *he;			   /* Se utiliza para convertir el nombre del host a su dirección IP */
	struct sockaddr_in their_addr; /* dirección del server donde se conectará */

	// convertimos el nombre del host a su dirección IP
	if ((he = gethostbyname(hostname)) == NULL)
	{
		herror("Error en Nombre de Host");
		exit(1);
	}

	/* Creamos el socket */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Error en creación de socket");
		exit(1);
	}
	if (debug)
		fprintf(stderr, "debug:: conectar() socket()=%d\t\t..........OK\n", sockfd);

	if (debug)
		fprintf(stderr, "debug:: conectar() dst port()=%d\t..........OK\n", port);

	port = (port == 0) ? htons(PORT) : htons(port);

	/* Establecemos their_addr con la direccion del server */
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = port;
	their_addr.sin_addr = *((struct in_addr *)he->h_addr_list[0]); /* Usar h_addr_list[0] */
	bzero(&(their_addr.sin_zero), 8);

	/* Intentamos conectarnos con el servidor */
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("conectar():: error tratando de conectar al server");
		exit(1);
	}
	if (debug)
		fprintf(stderr, "debug:: conectar() connect()\t\t..........OK\n");

	return sockfd;
}

/**
 * \fn int abrir_conexion (int port, int backlog, int debug)
 * \brief Función del lado server que crea un socket, lo enlaza con un port definido y pasa a escuchar conexiones.
 * \details Se crea un socket y se enlaza a un port utilizando bind. Luego, el socket queda a la espera de conexiones mediante listen().
 * \return Devuelve un entero con el file descriptor de socket.
 * \author Alejandro Furfaro
 * \date 2018.09.10
 */

int abrir_conexion(int port, int backlog, int debug)
{
	int sockaux; /*socket auxiliar*/
	int aux;	 /*variable auxiliar*/
	struct sockaddr_in my_addr;

	/*Crea un socket y verifica si hubo algún error*/
	if ((sockaux = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "Error en función socket(). Código de error %s\n", strerror(sockaux));
		return -1;
	}
	if (debug)
		fprintf(stderr, "debug:: abrir_conexion() socket()=%d\t..........OK\n", sockaux);

	// reuso por timeout inmediato
	int optval = 1;
	if (setsockopt(sockaux, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
	{
		fprintf(stderr, "Error en función setsockopt()\n");
		return -1;
	}
	if (debug)
		fprintf(stderr, "debug:: abrir_conexion() setsockopt()\t..........OK\n");

	/* Asignamos valores a la estructura my_addr */
	if (port == 0)
		port = PORT;

	my_addr.sin_family = AF_INET;		  /* familia de sockets INET para UNIX*/
	my_addr.sin_port = htons(port);		  /* convierte el entero formato PC a entero formato network*/
	my_addr.sin_addr.s_addr = INADDR_ANY; /* automaticamente usa la IP local */
	bzero(&(my_addr.sin_zero), 8);		  /* rellena con ceros el resto de la estructura */

	/* Con la estructura sockaddr_in completa, se declara en el Sistema que este proceso escuchará pedidos por la IP y el port definidos*/
	if ((aux = bind(sockaux, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))) == -1)
	{
		fprintf(stderr, "Error en función bind. Código de error %s\n", strerror(aux));
		return -1;
	}
	if (debug)
		fprintf(stderr, "debug:: abrir_conexion() bind()\t\t..........OK\n");

	/* Habilitamos el socket para recibir conexiones, con una cola de conexiones en espera que tendrá como máximo el tamaño especificado en BACKLOG*/
	if (backlog == 0)
		backlog = BACKLOG;

	if ((aux = listen(sockaux, backlog)) == -1)
	{
		fprintf(stderr, "Error en función listen. Código de error %s\n", strerror(aux));
		return -1;
	}
	if (debug)
		fprintf(stderr, "debug:: abrir_conexion() listen()\t..........OK\n");

	return sockaux;
}

/**
 * \fn int aceptar_pedidos (int sockfd, int debug)
 * \brief Función que acepta pedidos de conexión del lado servidor.
 * \details Se utiliza el socket creado para aceptar conexiones entrantes y devolver un nuevo socket para transacciones con el cliente.
 * \return Devuelve un entero con el file descriptor de socket duplicado para intercambio de datos.
 * \author Alejandro Furfaro
 * \date 2018.09.10
 */
int aceptar_pedidos(int sockfd, int debug)
{
	int newfd;					   /* Por este socket duplicado del inicial se transaccionará */
	struct sockaddr_in their_addr; /* Contendrá la dirección IP y número de puerto del cliente */
	unsigned int sin_size = sizeof(struct sockaddr_in);

	/* Se espera por conexiones */
	if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1)
	{
		fprintf(stderr, "Error en función accept. Código de error %s\n", strerror(newfd));
		return -1;
	}
	else
	{
		if (debug)
			fprintf(stderr, "debug:: aceptar_pedidos() conexión desde: %s\n", inet_ntoa(their_addr.sin_addr));

		return newfd;
	}
}
