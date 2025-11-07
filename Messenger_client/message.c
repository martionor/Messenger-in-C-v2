#include <stdio.h>
#include <string.h>
#include "message.h"

void create_message (write_message_t  *msg){
    printf("Enter your name: ");
    safe_fgets(msg->name, sizeof(msg->name));
   
    
    printf("To who: ");
    safe_fgets(msg->to_who, sizeof(msg->to_who));
  
    
    
    printf ("Message subject: ");
    safe_fgets(msg->subject, sizeof(msg->subject));
    // Remove newline character from the subject
    msg->subject[strcspn(msg->subject, "\n")] = 0;
    
}

// Display the message content
void display_message(write_message_t  *msg){
    printf("\nMessage from %s to %s \nSubject: %s\n", msg->name, msg->to_who, msg->subject);
}


void safe_fgets(char *dst, size_t size) {
    if (fgets(dst, size, stdin)) {
        // If newline is missing, flush remaining input
        if (!strchr(dst, '\n')) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}