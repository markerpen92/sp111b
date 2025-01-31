//遠端編譯
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define MUL 3
#define NOT 4

int get_next_space(char* str, int start)
{
    int i;
    for(i = start; str[i] != ' ' && i < strlen(str); i++);
    return i == strlen(str) ? -1 : i;
}

int get_int(char* str, int start){
    int i, res = 0;
    for(i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++){
        res *= 10;
        res += (str[i] - '0');
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello\n";
    char *del;
  
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
  
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
  
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address  ))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
  
    while(1)
    {
        if(recv(new_socket , buffer , sizeof(buffer) , 0) == 0) break;
        else
        {
            buffer[sizeof(buffer)] = '\0';
            char command[1024];
    
            sscanf(buffer , "%s[^ ]" , command);
    
            if(strcmp(command , "add") == 0)
            {
                int num1 , num2;
                sscanf(buffer , "%s %d %d" , command , &num1 , &num2);
                buffer[0]  = '\0';
                sprintf(buffer , "%d" , num1+num2);
            }
            else if(strcmp(command , "abs") == 0)
            {
                int num;
                sscanf(buffer , "%s %d" , command , &num);
                buffer[0] = '\0';
                if(num<0) num *= -1;
                sprintf(buffer , "%d" , num);
            }
            else if(strcmp(command , "mul") == 0)
            {
                int num1 , num2;
                sscanf(buffer , "%s %d %d" , command , &num1 , &num2);
                buffer[0] = '\0';
                sprintf(buffer , "%d" , num1*num2);
            }
            else if(strcmp(command , "kill") == 0)
            {
                break;
            }
            else
            {
                buffer[0] = '\0';
                sprintf(buffer , "%s" , "Wrong Cmd");
            }
        }
        send(new_socket , buffer , sizeof(buffer) , 0);
    }
    close(new_socket);
    shutdown(server_fd , SHUT_RDWR);
  
    return 0;
}