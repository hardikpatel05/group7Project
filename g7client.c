#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char *argv[])
{
	char message[500];
	int server, portNumber;
	socklen_t len;
	struct sockaddr_in servAdd;

	if(argc != 3)
	{
		printf("Call model:%s <IP> <Port#>\n",argv[0]);
		exit(0);
	}

	if((server = socket(AF_INET, SOCK_STREAM, 0))<0)
	{
		fprintf(stderr, "Cannot create socket\n");
		exit(1);
	}

	servAdd.sin_family = AF_INET;
	sscanf(argv[2], "%d", &portNumber);
	servAdd.sin_port = htons((uint16_t)portNumber);

	if(inet_pton(AF_INET,argv[1],&servAdd.sin_addr)<0)
	{
		fprintf(stderr, " inet_pton() has failed\n");
		exit(2);
	}

	if(connect(server,(struct sockaddr *)&servAdd,sizeof(servAdd))<0)
	{
		fprintf(stderr, "connect() has failed, exiting\n");
		exit(3);
	}
	else
	{
		fprintf(stderr,"\t\t________________________________________\n");
	        fprintf(stderr,"\n\t\t\t\t WELCOME ");
       	        fprintf(stderr,"\n\t\t\t\t    to ");
	        fprintf(stderr,"\n\t\t\t\t THE GAME ");
		fprintf(stderr,"\n\t\t________________________________________");
		fprintf(stderr,"\n\t\t________________________________________\n");
 	        fprintf(stderr,"\n\t\t > Press S to Start the game");
      		fprintf(stderr,"\n\t\t > Rules: \n\t\t1. For each right answer you get 1 point.\n\t\t2. At the end of the quiz you will get the \n\t\t   relative score out of 10");
	        fprintf(stderr,"\n\t\t > Press Q to Quit ");
      		fprintf(stderr,"\n\t\t________________________________________\n\n");
		
		
	}
	while(1)
	{
		if(read(server, message, 255)<=0)
		{
			fprintf(stderr, "read() error\n");
			exit(3);
		}
		printf("\n");
		fprintf(stderr, "%s",message);
		//fprintf(stderr, "Enter the $ sign to quit or a message for the server\n");
		
		fgets(message, 254, stdin);
		if(message[0] == 'n' || message[0] == 'N' || message[0]=='q' || message[0]=='Q')
		{
			close(server);
			exit(0);
		}

		write(server, message, strlen(message)+1);
		
	}
}

