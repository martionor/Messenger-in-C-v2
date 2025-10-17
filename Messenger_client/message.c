#include <stdio.h>
#include <string.h>
#include "message.h"

void create_message (struct write_message *msg){
    printf("Enter your name: ");
    fgets(msg->name, sizeof(msg->name), stdin);

    printf("To who: ");
    fgets(msg->to_who, sizeof(msg->to_who), stdin);

    printf ("Message subject: ");
    fgets(msg->subject, sizeof(msg->subject), stdin);

    msg->subject[strcspn(msg->subject, "\n")] = 0;
}

void display_message(struct write_message *msg){
    printf("\nMessage from %s to %s \nSubject: %s\n", msg->name, msg->to_who, msg->subject);
}