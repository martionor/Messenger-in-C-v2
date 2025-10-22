#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include "message.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

// char server_address= SERVER_IP;

void send_message_to_ip(struct write_message *msg);
void request_messages(const char *password);
void setup_server_address(struct sockaddr_in *serv_addr);
// void get_new_ip(char *server_address);
#endif