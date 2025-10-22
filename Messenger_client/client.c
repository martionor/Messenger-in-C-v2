#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <arpa/inet.h>
#include "client.h"
#include "../Messenger_server/server.h"

static char server_ip[64] = "127.0.0.1";

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
    while((read_bytes = read(sock, buffer, sizeof(buffer)-1))>0){
        buffer[read_bytes]='\0';
        printf("%s\n", buffer);
    }

    close(sock);


}

void setup_server_address(struct sockaddr_in *serv_addr){
    serv_addr ->sin_family = AF_INET;
    serv_addr ->sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, get_server_ip(), &serv_addr->sin_addr);
}

const char* get_server_ip(void){
    return server_ip;
}

void change_new_ip(void){
    char new_ip[64];
    printf("Enter new server IP: ");
    fgets(new_ip,sizeof(new_ip),  stdin);
    new_ip[strcspn(new_ip, "\r\n")] = 0;

    if(strlen(new_ip)==0){
        printf("IP adress not changed.\n");
        return;
    }

    strncpy(server_ip, new_ip, sizeof(server_ip));
    printf("Server IP changed to: %s\n", server_ip);
}