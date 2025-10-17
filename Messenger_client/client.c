#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"
#include "../Messenger_server/server.h"


void send_message_to_ip(struct write_message *msg){
    int sock = 0;
    struct sockaddr_in serv_addr;
    char message [512];
    
    snprintf(message, sizeof(message), "From %s\nTo: %s\nMessage: %s", msg->name, msg->to_who, msg->subject);
    
    //Create socket
    sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0){
        perror("Socket creation error");
        return;
    }
    
    setup_server_address(&serv_addr);

    //Connect to server
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0){
        perror("Connection failed");
        close(sock);
        return;
    }

    //Send message
    send(sock, message, strlen(message), 0);
    printf("Message sent to server \n");

    close(sock);

}

//Get messages from server
void request_messages(const char *password){
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MSG_SIZE] = {0};
    char command[]= "READ_MESSAGES";
    
    sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock < 0){
        perror("Socket creation failed");
        return;
    }
    
    setup_server_address(&serv_addr);
 
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        perror("Connection failed");
        close(sock);
        return;
    }

    //Send request for messages
    snprintf(buffer, sizeof(buffer), "%s:%s", command, password);
    send(sock, buffer, strlen(buffer),0);

    //Receive messages from server one by one
    int read_bytes;
    while((read_bytes = read(sock, buffer, sizerof(buffer)-1))>0){
        buffer[read_bytes]='\0';
        printf("%s\n", buffer);
    }

    close(sock);


}

void setup_server_address(struct sockaddr_in *serv_addr){
    serv_addr ->sin_family = AF_INET;
    serv_addr ->sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &serv_addr->sin_addr);
}