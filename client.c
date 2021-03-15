#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MSGLEN 80
#define PORT 8080

void chat_client(int sockfd)
{
	char msg[MSGLEN];
	int n; 

	while (1) {
		bzero(msg, sizeof(msg));
		printf("To Server : ");
		n = 0;
		while ((msg[n++] = getchar()) != '\n');
		write(sockfd, msg, sizeof(msg));
		bzero(msg, sizeof(msg));
		read(sockfd, msg, sizeof(msg));
		printf("From Server : %s", msg);
		if ((strncmp(msg, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed..\n");
		return 1;
	}
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORT);
	seraddr.sin_addr.s_addr = inet_addr("10.138.129.231");

	if (connect(sockfd, (struct sockaddr *) &seraddr, sizeof(seraddr)) != 0) {
		printf("connection with the server failed...\n");
		return 1;
	}	
	
	chat_client(sockfd);

	close(sockfd);
	return 0;
}
