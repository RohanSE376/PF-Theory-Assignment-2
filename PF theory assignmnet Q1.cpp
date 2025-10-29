#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100


void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount);
void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);
void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount);


int main() {
    int isbns[MAX_BOOKS];
    char titles[MAX_BOOKS][50];
    float prices[MAX_BOOKS];
    int quantities[MAX_BOOKS];
    int bookCount = 0;
    int choice;

    do {
        
        printf("1. Add New Book\n");
        printf("2. Process a Sale\n");
        printf("3. Generate Low-Stock Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(isbns, titles, prices, quantities, &bookCount);
                break;
            case 2:
                processSale(isbns, titles, prices, quantities, bookCount);
                break;
            case 3:
                generateLowStockReport(isbns, titles, prices, quantities, bookCount);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}


void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount) {
    if (*bookCount >= MAX_BOOKS) {
        printf("Inventory full Cannot add more books.\n");
        return;
    }

    int isbn, i;
    char title[50];
    float price;
    int quantity;

    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    
    for (i = 0; i < *bookCount; i++) {
        if (isbns[i] == isbn) {
            printf("Book with ISBN %d already exists\n", isbn);
            return;
        }
    }

    printf("Enter title: ");
    getchar(); 
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0'; 

    printf("Enter price: ");
    scanf("%f", &price);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    
    isbns[*bookCount] = isbn;
    strcpy(titles[*bookCount], title);
    prices[*bookCount] = price;
    quantities[*bookCount] = quantity;

    (*bookCount)++;

    printf("Book added successfully!\n");
}


void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    if (bookCount == 0) {
        printf("No books available in inventory!\n");
        return;
    }

    int isbn, copies, i, found = 0;
    printf("Enter ISBN of the book to sell: ");
    scanf("%d", &isbn);

    for (i = 0; i < bookCount; i++) {
        if (isbns[i] == isbn) {
            found = 1;
            printf("Book Found: %s (Stock: %d)\n", titles[i], quantities[i]);
            printf("Enter number of copies sold: ");
            scanf("%d", &copies);

            if (copies > quantities[i]) {
                printf("Error: Only %d copies in stock!\n", quantities[i]);
            } else {
                quantities[i] -= copies;
                printf("Sale processed successfully!\n");
                printf("Remaining stock: %d\n", quantities[i]);
            }
            break;
        }
    }

    if (!found)
        printf("Book with ISBN %d not found!\n", isbn);
}

void generateLowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int bookCount) {
    if (bookCount == 0) {
        printf("No books in inventory!\n");
        return;
    }

    int i, found = 0;
    printf("\n=== Low-Stock Report (Quantity < 5) ===\n");
    for (i = 0; i < bookCount; i++) {
        if (quantities[i] < 5) {
            printf("ISBN: %d | Title: %s | Price: %.2f | Quantity: %d\n",
                   isbns[i], titles[i], prices[i], quantities[i]);
            found = 1;
        }
    }

    if (!found)
        printf("All books are sufficiently stocked.\n");
}

