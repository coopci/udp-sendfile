/*
        demo-udp-03: udp-send: a simple udp client
	send udp messages
	sends a sequence of messages (the # of messages is defined in MSGS)
	The messages are sent to a port defined in SERVICE_PORT

        usage:  udp-send

        Paul Krzyzanowski
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#define SERVICE_PORT    1153 
#define BUFLEN 2048
#define MSGS 5	/* number of messages to send */

int main(void)
{
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen=sizeof(remaddr);
	char *server = "127.0.0.1";	/* change this to use a different server */
	char buf[BUFLEN];

	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		printf("socket created\n");

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}       

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	/* now let's send the messages */

	int localfile_fd = open("data.txt", O_RDWR);
        printf("localfile_fd: %d\n", localfile_fd);
	for (i=0; i < MSGS; i++) {
		/*
                printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		sprintf(buf, "This is packet %d", i);
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1)
			perror("sendto");

                */
               int sendfile_fd;
               if ((sendfile_fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
                    printf("socket creating failed.\n");
                
               if (-1 == connect(sendfile_fd, (struct sockaddr *)&remaddr, slen)) {


                    printf("errno: %d\n", errno);
               }
               off_t offset = 0;
	       size_t bytes_sent = sendfile(sendfile_fd, localfile_fd, &offset , 7 );
               printf("bytes_sent: %d\n", bytes_sent);


	}
	close(fd);
	return 0;
}

