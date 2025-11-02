#include <stdio.h>


#define MAX_BOOKS 100
#define MAX_TITLE_LEN 50




void readString(char buffer[], int length);


int findBook(int isbnToFind, int isbns[], int count);


void addBook(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int *count);


void processSale(int isbns[], int quantities[], int count);


void generateReport(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int count);



int main() {
   
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][MAX_TITLE_LEN];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    
   
    int bookCount = 0; 
    
    int choice;

    
    do {
        printf("\n--- Liberty Books Inventory System ---\n");
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice: ");
        
       
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            
            while(getchar() != '\n'); 
            choice = 0; 
            continue;   
        }

        
        while(getchar() != '\n'); 

        
        switch (choice) {
            case 1:
                
                addBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, quantities, bookCount);
                break;
            case 3:
                generateReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }

    } while (choice != 4);

    return 0;
}



void readString(char buffer[], int length) {
    int i = 0;
    char ch;
    
    
    while (i < length - 1) {
        ch = getchar();
        
        if (ch == '\n') {
            break;
        }
        buffer[i] = ch;
        i++;
    }
   
    buffer[i] = '\0';
}


int findBook(int isbnToFind, int isbns[], int count) {
    for (int i = 0; i < count; i++) {
        if (isbns[i] == isbnToFind) {
            return i; // Found it
        }
    }
    return -1; 
}


void addBook(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int *count) {
    int newIsbn;
    
    
    if (*count >= MAX_BOOKS) {
        printf("Error: Inventory is full. Cannot add more books.\n");
        return;
    }

    printf("Enter new ISBN: ");
    scanf("%d", &newIsbn);

    
    if (findBook(newIsbn, isbns, *count) != -1) {
        printf("Error: A book with this ISBN already exists.\n");
       
        while(getchar() != '\n');
        return;
    }
    
   
    isbns[*count] = newIsbn;

    while(getchar() != '\n'); 

    printf("Enter Title: ");
    
    readString(titles[*count], MAX_TITLE_LEN);

    printf("Enter Price: ");
    scanf("%f", &prices[*count]);

    printf("Enter Quantity: ");
    scanf("%d", &quantities[*count]);

    printf("Book added successfully!\n");
    
    
    (*count)++;
}


void processSale(int isbns[], int quantities[], int count) {
    int isbnToFind;
    int quantityToSell;

    printf("Enter ISBN of book to sell: ");
    scanf("%d", &isbnToFind);

    int index = findBook(isbnToFind, isbns, count);

   
    if (index == -1) {
        printf("Error: Book with ISBN %d not found.\n", isbnToFind);
        return;
    }

    
    printf("Enter number of copies sold: ");
    scanf("%d", &quantityToSell);

    if (quantityToSell <= 0) {
        printf("Error: Invalid quantity. Must be greater than 0.\n");
    }
   
    else if (quantityToSell > quantities[index]) {
        printf("Error: Not enough stock. Only %d copies available.\n", quantities[index]);
    }
    
    else {
        quantities[index] -= quantityToSell; // Update the quantity
        printf("Sale successful. Remaining stock: %d\n", quantities[index]);
    }
}


void generateReport(int isbns[], char titles[][MAX_TITLE_LEN], float prices[], int quantities[], int count) {
    int foundLowStock = 0; // Flag to check if any books are low

    printf("\nLow-Stock Report (Quantity < 5)\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        
        if (quantities[i] < 5) {
            printf("ISBN: %d\n", isbns[i]);
            printf("Title: %s\n", titles[i]);
            printf("Price: $%.2f\n", prices[i]);
            printf("Qty:   %d\n", quantities[i]);
            
            foundLowStock = 1; 
        }
    }

    
    if (foundLowStock == 0) {
        printf("No books are currently low on stock.\n");
    }
}

           
