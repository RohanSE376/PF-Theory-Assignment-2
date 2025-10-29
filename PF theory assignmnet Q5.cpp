#include <stdio.h>
#include <string.h>


void encodeMessage(char message[]);
void decodeMessage(char message[]);
void toggleBits(char *ch);

int main() {
    char message[200];
    int choice;

    while (1) {
        
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("\nEnter message to encode: ");
                gets(message);
                encodeMessage(message);
                printf("\nEncoded Message: %s\n", message);
                break;

            case 2:
                printf("\nEnter message to decode: ");
                gets(message);
                decodeMessage(message);
                printf("\nDecoded Message: %s\n", message);
                break;

            case 3:
                printf("\nExiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}


void toggleBits(char *ch) {
    *ch = *ch ^ (1 << 1); 
    *ch = *ch ^ (1 << 4); 
}


void encodeMessage(char message[]) {
    int len = strlen(message);
    char temp;

    
    for (int i = 0; i < len / 2; i++) {
        temp = message[i];
        message[i] = message[len - i - 1];
        message[len - i - 1] = temp;
    }

    
    for (int i = 0; i < len; i++) {
        toggleBits(&message[i]);
    }
}


void decodeMessage(char message[]) {
    int len = strlen(message);
    char temp;

   
    for (int i = 0; i < len; i++) {
        toggleBits(&message[i]);
    }

    
    for (int i = 0; i < len / 2; i++) {
        temp = message[i];
        message[i] = message[len - i - 1];
        message[len - i - 1] = temp;
    }
}
