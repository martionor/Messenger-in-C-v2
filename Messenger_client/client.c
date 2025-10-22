#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
#include <arpa/inet.h>
#include "client.h"
#include "../Messenger_server/server.h"

// Store the current server IP address as a global variable
static char server_ip[64] = "127.0.0.1";

void send_message_to_ip(struct write_message *msg){
    int sock = 0; // Socket file descriptor
    struct sockaddr_in serv_addr; // Server address structure
    char message [512]; // Buffer to hold formatted message
    
    //Format message to a string
    snprintf(message, sizeof(message), "From %s\nTo: %s\nMessage: %s", msg->name, msg->to_who, msg->subject);
    
    //Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0){
        perror("Socket creation error");
        return;
    }
    // Fill server address structure
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
    char buffer[MSG_SIZE] = {0}; // Buffer to receive server response
    char command[]= "READ_MESSAGES"; // Command string sent to server
    
     // Create TCP socket
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

    // Send request to server in format "READ_MESSAGES:password"
    snprintf(buffer, sizeof(buffer), "%s:%s", command, password);
    send(sock, buffer, strlen(buffer),0);

    //Receive messages from server one by one
    int read_bytes;
    while((read_bytes = read(sock, buffer, sizeof(buffer)-1))>0){
        buffer[read_bytes]='\0'; // Null-terminate the received data
        printf("%s\n", buffer);
    }

    close(sock);


}

void setup_server_address(struct sockaddr_in *serv_addr){
    serv_addr ->sin_family = AF_INET;  // IPv4
    serv_addr ->sin_port = htons(SERVER_PORT); // Server port (network byte order)
    inet_pton(AF_INET, get_server_ip(), &serv_addr->sin_addr); // Convert IP string to binary
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

    // Copy new IP into global variable
    strncpy(server_ip, new_ip, sizeof(server_ip));
    printf("Server IP changed to: %s\n", server_ip);
}