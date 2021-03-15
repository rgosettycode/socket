#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define MSGLEN 80
#define PORT 8080

void chat_server(int sockfd)
{
	char msg[MSGLEN];
	int n;

	while(1) {
		bzero(msg, sizeof(msg));
		read(sockfd, msg, sizeof(msg));
		printf("From client: %s\t To client : ", msg);
		bzero(msg, sizeof(msg));
		n = 0; 
        	while ((msg[n++] = getchar()) != '\n');
		write(sockfd, msg, sizeof(msg));
		if (strncmp("exit", msg, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

int main()
{
	int sockfd, clifd, len;
	struct sockaddr_in seraddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		return 1;
	}
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(PORT);
	seraddr.sin_addr.s_addr = inet_addr("10.138.129.231");

	if (bind(sockfd, (struct sockaddr *) &seraddr, sizeof(seraddr)) != 0) {
		printf("socket bind failed...\n");
		return 1;
	}
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		return 1;
	}
	len = sizeof(cliaddr);
	clifd = accept(sockfd, (struct sockaddr *) &cliaddr, &len);
	if (clifd < 0) {
		printf("server accept failed ...\n");
		return 1;
	}
	chat_server(clifd);

	close(sockfd);
	return 0;
}
