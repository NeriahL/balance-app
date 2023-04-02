#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "helper_functions.h"
#include "generate_list.h"
#include "handle_commands.h"

#define MAX_LEN 1024

typedef struct socket_info
{
    int new_sock;
    char *database;
} Socket_Info;

Customer *head = NULL;
pthread_mutex_t mutex;

void send_cust(Customer *cust, int socket)
{
    char buffer[MAX_LEN];
    int n;
    sprintf(buffer, "First Name: %s. \nLast Name: %s. \nID: %s. \nPhone Number: %s. \nDate: %d/%d/%d. \nDebt: %d.\n\n",
        cust->first_name, 
        cust->last_name,
        cust->id,
        cust->phone_number,
        cust->date.month,
        cust->date.day,
        cust->date.year,
        cust->debt);
    n = send(socket, buffer, strlen(buffer), 0);
    if (n < 0)
    {
        perror("Server error sending data print ");
        close(socket);
        return;
    }
}

void send_error(char str[], int socket)
{
    char buffer[MAX_LEN];
    int n;
    strcpy(buffer, str);
    
	n = send(socket, str, strlen(buffer), 0);
    if (n < 0)
    {
        perror("Server error sending data output error ");
        close(socket);
        return;
    }
}

void *conn_handler(void *args)
{
    pthread_mutex_lock(&mutex);
    char buffer[MAX_LEN] = {0};
    int n;
    Socket_Info *sock = (Socket_Info *)args;

    n = recv(sock->new_sock, buffer, MAX_LEN, 0);
    if (n < 0)
    {
        perror("Server error recieving data");
        goto exit;
    }
    buffer[n] = '\0';

    FILE *ptr = fopen(sock->database, "r");

    handle_options(ptr, head, buffer, sock->new_sock, send_cust, send_error);

    fclose(ptr);
    exit:
    close(sock->new_sock);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    if (argc < 3)
    {
        printf("Usage: %s <port> <database>\n", argv[0]);
        return 1;
    }

    /* Create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    /* Bind the socket to a specific port */
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error binding socket");
        return 1;
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Error listening");
        return 1;
    }
	
    Socket_Info *sock = malloc(sizeof(Socket_Info));
    sock->database = argv[2];
    FILE *ptr = fopen(sock->database, "r");
    char *output;
    char buf[265];

    list_init(ptr, &head, buf, -1, send_cust, send_error);

    if (pthread_mutex_init(&mutex, NULL) != 0) 
    {
        perror("mutex init has failed");
        return 1;
    }

    while (1)
    {
        pthread_t tid;
        sock->new_sock = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t*)&len);

        if (sock->new_sock < 0)
        {
            perror("accept failed");
            return 1;
        }

        pthread_create(&tid, NULL, conn_handler, (void *)sock);
        pthread_join(tid, NULL);
    }
    free_list(&head);
    fclose(ptr);
    pthread_mutex_destroy(&mutex);

    return 0;
}
