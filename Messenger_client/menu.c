#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "message.h"

char password[64];

void open_menu(){
    char menu_choice[10] = {0};
    struct write_message msg;

    while(menu_choice[0] !=0){
        printf("\n Menu \n");
        printf("1 - Send message \n");
        printf("2 - Read messages \n");
        printf("0 - Exit\n");

        fgets(menu_choice, sizeof(menu_choice), stdin);

        switch(menu_choice[0]){
        case '1':
            create_message(&msg);
            display_message(&msg);
            send_message_to_ip(&msg);
            break;
        case '2':
            printf("Enter password to get messages");
            get_password(password, sizeof(password));
            request_messages(password);
            break;
        case '0':
            printf("Goodbye\n");
            return;
        default:
            printf("Invalid option. Choose 1,2,0. \n");
            break;
        }
    }
}


void get_password(char *password, int size){
    printf("Enter password: ");
    fgets(password, size, stdin);
    password[strcspn(password, "\r\n")] = 0;
}
