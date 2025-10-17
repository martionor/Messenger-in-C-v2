#ifndef MESSAGE_H
#define MESSAGE_H

struct write_message {
    char name[24];
    char to_who[24];
    char subject[255];
};

void create_message(struct write_message *msg);
void display_message(struct write_message *msg);


#endif