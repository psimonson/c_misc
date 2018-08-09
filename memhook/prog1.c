#include <stdio.h>
#include <sys/socket.h>
#include "debug.h"

int main()
{
	int sockfd;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return error_print("Could not create socket.");
	else
		debug_print("Socket created successfully.");
	close(sockfd);
	return 0;
}
