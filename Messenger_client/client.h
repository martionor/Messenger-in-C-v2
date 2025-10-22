#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include "message.h"

#define SERVER_PORT 8080


void send_message_to_ip(struct write_message *msg);
void request_messages(const char *password);
void setup_server_address(struct sockaddr_in *serv_addr);
void change_new_ip(void);
const char * get_server_ip(void);
#endif