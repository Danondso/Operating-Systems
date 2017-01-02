/* A simple TCP client */
#include <stdio.h>
#include <stdlib.h> /*get rid of exit warnings*/
#include <string.h> /*get rid of bzero warnings*/
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_TCP_PORT		3555
#define BUFLEN			256	/* buffer length */


int main(int argc, char **argv)
{
	int 	n, bytes_to_read;
	int 	sd, port;
	struct 	hostent 	*hp;
	struct 	sockaddr_in 	server;

        //host pointer,    , return buffer?, send buffer?
	char 	*host, *bp, rbuf[BUFLEN], sbuf[BUFLEN];

	switch(argc) {
	case 2:
		host = argv[1];
		port = SERVER_TCP_PORT;
		break;
	case 3:
		host = argv[1];
		port = atoi(argv[2]);
		break;
	default:
		fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
		exit(1);
	}

	/* Create a stream socket */
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't create a socket\n");
		exit(1);
	}

	/* copy zeros into socket structure */
	bzero((char *)&server, sizeof(struct sockaddr_in));
	/* set protocol family to AF_INET, which is TCP/IP */
	server.sin_family = AF_INET;
        /* set port number, convert from host byte order to network byte order */
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL) {
		fprintf(stderr, "Can't get server's address\n");
		exit(1);
	}
	/* copy host address to socket */
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	/* Connecting to the server */
	if (connect(sd, (struct sockaddr *)&server, 
	sizeof(server)) == -1) {
		fprintf(stderr, "Can't connect\n");
		exit(1);
	}
	printf("Connected: server's address is %s\n", hp->h_name);
	
	printf("Transmit:\n");
        /* gets() is not safe and we should use fgets() in real code */
	/* gets(sbuf); */
        fgets(sbuf, BUFLEN, stdin);     /* get user's text */
	write(sd, sbuf, BUFLEN);	/* send it out */

	printf("Receive:\n");
	bp = rbuf;
	bytes_to_read = BUFLEN;
	while ((n = read(sd, bp, bytes_to_read)) > 0) {
		bp += n;
		bytes_to_read -= n;
	}
	printf("%s\n", rbuf);

	close(sd); /* close connection */
	return(0);
}

