#include <stdio.h>
#include <string.h>
#include "message.h"

void create_message (write_message_t  *msg){
    printf("Enter your name: ");
    fgets(msg->name, sizeof(msg->name), stdin);
    flush_stdin();
    
    printf("To who: ");
    fgets(msg->to_who, sizeof(msg->to_who), stdin);
    flush_stdin();
    
    
    printf ("Message subject: ");
    fgets(msg->subject, sizeof(msg->subject), stdin);
    // Remove newline character from the subject
    msg->subject[strcspn(msg->subject, "\n")] = 0;
    flush_stdin();
}

// Display the message content
void display_message(write_message_t  *msg){
    printf("\nMessage from %s to %s \nSubject: %s\n", msg->name, msg->to_who, msg->subject);
}

void flush_stdin(void){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}