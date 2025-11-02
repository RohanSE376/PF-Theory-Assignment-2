#include <stdio.h>

void readString(char buffer[], int size) {
    int i = 0;
    char c;
    while (i < size - 1) {
        c = getchar();
        if (c == '\n') {
            break;
        }
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';
}

int getStringLength(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

void reverseString(char s[]) {
    int start = 0;
    int end = getStringLength(s) - 1;
    char temp;

    while (start < end) {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

void toggleMessageBits(char s[]) {
    int i = 0;
    int mask = (1 << 1) | (1 << 4); 

    while (s[i] != '\0') {
        s[i] = s[i] ^ mask;
        i++;
    }
}

void encodeMessage(char message[]) {
    reverseString(message);
    toggleMessageBits(message);
}

void decodeMessage(char message[]) {
    toggleMessageBits(message);
    reverseString(message);
}

int main() {
    char message[256];
    int choice;

    do {
        printf("\n--- TCS Secure Message System ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("---------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while(getchar() != '\n'); 
            continue;
        }
        
        while(getchar() != '\n');

        switch (choice) {
            case 1:
                printf("Enter message to encode: ");
                readString(message, 256);
                encodeMessage(message);
                printf("Encoded message: %s\n", message);
                break;
            case 2:
                printf("Enter message to decode: ");
                readString(message, 256);
                decodeMessage(message);
                printf("Decoded message: %s\n", message);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }

    } while (choice != 3);

    return 0;
}

