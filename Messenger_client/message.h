#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct write_message {
    char name[24];
    char to_who[24];
    char subject[255];
} write_message_t;

void create_message(write_message_t *msg);
void display_message(write_message_t *msg);


#endif