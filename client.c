#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LEN 1024
#define SOCKETS 5

int main(int argc, char **argv)
{
    int sockfd[SOCKETS];
    struct sockaddr_in servaddr;
    char buffer[SOCKETS][MAX_LEN];
    int n;
    int i;

    if (argc < 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }

    /* Connect to the server */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(atoi(argv[1]));

    /*Entry screen*/

    puts("WELCOME TO ACCOUNTABILITY APP\n");
    puts("To Query The Database, enter a command:\n");
    puts("<set> - To add a debt listing.\nFormat: set <first name=?> , <last name=?> , <id=?> , <phone number=?> , <date=dd/mm/yyyy> , <debt=?>\n");
    puts("<select> - To search for a customer balance.\nselect <=/</>/!=> <first name/last name...>\n");
    puts("<print> - To print customenrs and their current debt balance.\n");
    puts("<send> - To send queries\n");
    puts("<quit> - To quit the app\n");

    /* Send data to the server */
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        puts("\nEnter up to 5 messages:");
        int i = 0;
        while (i < SOCKETS)
        {
            fgets(buffer[i], MAX_LEN, stdin);

            if(strcmp(buffer[i], "send\n") == 0)
                break;
                //get out of current loop
                
            if (strcmp(buffer[i], "\n") == 0)
            {
                strcpy(buffer[i], "send\n");
                break;
            }
            

            if (strcmp(buffer[i], "quit\n") == 0)
                break;
                //get out of client loop
            
            i++;
        }
        if (strcmp(buffer[i], "quit\n") == 0)
            break;
        
        /* Create sockets */
        i=0;
        while (strcmp(buffer[i], "send\n") != 0 && i < SOCKETS)
        {
            sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd[i] < 0)
            {
                perror("Error creating socket");
                return 1;
            }
            if (connect(sockfd[i], (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
            {
                perror("Error connecting");
                return 1;
            }
            i++;
        }
        i=0;
        while (strcmp(buffer[i], "send\n") != 0 && i < SOCKETS)
        {
            n = send(sockfd[i], buffer[i], strlen(buffer[i]) - 1, 0);
            if (n < 0)
            {
                perror("Client error sending data");
                return 1;
            }
            i++;
        }
        i=0;
        while (strcmp(buffer[i], "send\n") != 0 && i < SOCKETS)
        {
            printf("\nReply to request No. %d:\n", i+1);
            do
            {
                n = recv(sockfd[i], buffer[i], MAX_LEN, 0);
                if (n < 0)
                {
                    perror("Client error recieving data");
                    return 1;
                }
                buffer[i][n] = '\0';
                printf("%s", buffer[i]);
            } while (n);

            close(sockfd[i]);
            i++;
        }
    }
    return 0;
}
