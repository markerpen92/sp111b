#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;  // sin_family-IPV4 or IPV6 & sin_port & sin_addr & sin_zero
	char *hello = "Hello from client"; 
	char buffer[1024] = {0};

    usleep(500000);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

    while(1)
    {
        //	printf("Input : ");
        fgets(buffer , sizeof(buffer)-1 , stdin);
        if(buffer == NULL) continue;
        else
        {
            send(sock , buffer , sizeof(buffer) , 0);
            if(recv(sock , buffer , sizeof(buffer) , 0) == 0) break;
            else
            {
                buffer[sizeof(buffer)] = '\0';
                printf("%s \n" , buffer);
            }
        }
    }
    close(sock);
	return 0;
}