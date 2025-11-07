#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h> //For multiple clients at once
#include "server.h"

#define PORT 8080

char messages[MAX_MESSAGES][MSG_SIZE];
int message_count = 0;
pthread_mutex_t messages_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    start_server();
    return 0;
}


//Setting up the socket
int setup_server(){
    int server_fd;
    struct sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM,0);
    if (server_fd <0){
        perror("Socked failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,5)<0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d \n", PORT);
    return server_fd;
}


//Thread function to handle each client
void *handle_client(void *arg){
    int new_socket = *(int *)arg;
    free(arg);//Free memory for socket
    char buffer[512];

    read(new_socket, buffer, sizeof(buffer));

    if (strncmp(buffer, "READ_MESSAGES", 13)==0){
        send_stored_messages(new_socket);}
    else {
        pthread_mutex_lock(&messages_mutex);
        store_message(buffer);
        pthread_mutex_unlock(&messages_mutex);
    }
    close(new_socket);
    return NULL;
}

//Start server and accept multiple connections
void start_server(){
    int server_fd = setup_server();

    while (1){
        struct sockaddr_in address;
        int addrlen = sizeof(address);
        int *new_socket = malloc(sizeof(int));
        if (!new_socket){
            perror("Malloc failed.");
            continue;
        }

        *new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if(*new_socket <0){
            perror("Accept failed.");
            free(new_socket);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, new_socket);
        pthread_detach(tid); //Thread clean up after itself
    }
    close(server_fd);
}


//Storage messages with wrap_around
void store_message(const char *buffer){
    strncpy(messages[message_count % MAX_MESSAGES], buffer, MSG_SIZE);
    printf("Message number: %d\n", (message_count % MAX_MESSAGES)+1);
    printf("Received message: %s\n", buffer);
    message_count ++;
}

//Send stored messages to client
void send_stored_messages(int new_socket){
    char all_messages[MSG_SIZE * MAX_MESSAGES] = "";
    int start = (message_count > MAX_MESSAGES) ? (message_count - MAX_MESSAGES) :0;

    if (message_count == 0){
        strcpy(all_messages, "No messages stored yet. \n");
    }else{
        for(int i = start; i<message_count; i++){
            strcat(all_messages, messages[i%MAX_MESSAGES]);
            strcat(all_messages, "\n--------------\n");
        }
    }

    send(new_socket, all_messages, strlen(all_messages),0);
}


//Check password
// int check_password(const char *received_pass){
//     const char *password = "password";
//     char clean_pass[64];

//     strncpy(clean_pass, received_pass, sizeof(clean_pass));
//     clean_pass[strcspn(clean_pass, "\r\n")]=0;

//     return strcmp(clean_pass, password) ==0;
// }
