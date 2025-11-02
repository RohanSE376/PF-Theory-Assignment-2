#include <stdio.h>

#define MAX_PRODUCTS 4
#define MAX_NAME 100
#define MAX_CNIC 20
#define PROMO_CODE "Eid2025"
#define DISCOUNT_RATE 0.25

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

int stringCompare(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

int findProduct(int code, int codes[], int count) {
    for (int i = 0; i < count; i++) {
        if (codes[i] == code) {
            return i;
        }
    }
    return -1;
}

void getCustomerInfo(char name[], char cnic[]) {
    printf("Enter Customer Name: ");
    readString(name, MAX_NAME);
    printf("Enter Customer CNIC: ");
    readString(cnic, MAX_CNIC);
    printf("Customer information saved.\n");
}

void displayInventory(int codes[], int quantities[], float prices[], int count) {
    printf("\n--- Current Inventory ---\n");
    printf("Product code\tQuantity in stock\tPrice per product\n");
    printf("---------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%03d\t\t%d\t\t\t%.2f\n", codes[i], quantities[i], prices[i]);
    }
}

float addItemToCart(int codes[], int quantities[], float prices[], int count) {
    int code, qty, index;
    float cost = 0.0;

    printf("Enter Product Code: ");
    scanf("%d", &code);

    index = findProduct(code, codes, count);

    if (index == -1) {
        printf("Error: Product code not found.\n");
    } else {
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        if (qty <= 0) {
            printf("Error: Invalid quantity.\n");
        } else if (qty > quantities[index]) {
            printf("Error: Not enough stock. Only %d available.\n", quantities[index]);
        } else {
            quantities[index] -= qty;
            cost = prices[index] * qty;
            printf("Added to cart. Cost: %.2f\n", cost);
        }
    }
    
    while(getchar() != '\n');
    return cost;
}

void calculateFinalBill(float total, float *discount, float *finalBill) {
    char promo[50];
    char choice[10];
    *discount = 0.0;

    printf("\n--- Checkout ---\n");
    printf("Total Bill before discount: %.2f\n", total);

    printf("Do you have a promocode? (yes/no): ");
    readString(choice, 10);

    if (stringCompare(choice, "yes") == 0) {
        printf("Enter promocode: ");
        readString(promo, 50);
        if (stringCompare(promo, PROMO_CODE) == 0) {
            *discount = total * DISCOUNT_RATE;
            printf("Promocode 'Eid2025' applied! 25%% discount.\n");
        } else {
            printf("Invalid promocode.\n");
        }
    }

    *finalBill = total - *discount;
    printf("Discount: -%.2f\n", *discount);
    printf("Final Bill: %.2f\n", *finalBill);
}

void showInvoice(char name[], char cnic[], float total, float discount, float finalBill) {
    printf("\n--- FINAL INVOICE ---\n");
    printf("Customer Name: %s\n", name);
    printf("Customer CNIC: %s\n", cnic);
    printf("-----------------------\n");
    printf("Total Bill:     %.2f\n", total);
    printf("Discount:       -%.2f\n", discount);
    printf("Final Payable:  %.2f\n", finalBill);
    printf("-----------------------\n");
    printf("Thank you for shopping!\n");
}

int main() {
    int productCodes[MAX_PRODUCTS] = {1, 2, 3, 4};
    int quantities[MAX_PRODUCTS] = {50, 10, 20, 8};
    float prices[MAX_PRODUCTS] = {100.0, 200.0, 300.0, 150.0};

    char customerName[MAX_NAME];
    char customerCNIC[MAX_CNIC];
    float totalBill = 0.0;
    float discount = 0.0;
    float finalBill = 0.0;

    int customerInfoEntered = 0;
    int billCalculated = 0;
    int choice;

    do {
        printf("\n--- Supermarket Menu ---\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Proceed to Checkout (Calculate Bill)\n");
        printf("5. Show Final Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n'); 

        switch (choice) {
            case 1:
                getCustomerInfo(customerName, customerCNIC);
                customerInfoEntered = 1;
                break;
            case 2:
                displayInventory(productCodes, quantities, prices, MAX_PRODUCTS);
                break;
            case 3:
                totalBill += addItemToCart(productCodes, quantities, prices, MAX_PRODUCTS);
                billCalculated = 0; 
                break;
            case 4:
                calculateFinalBill(totalBill, &discount, &finalBill);
                billCalculated = 1;
                break;
            case 5:
                if (customerInfoEntered == 0) {
                    printf("Please enter customer information first (Option 1).\n");
                } else if (billCalculated == 0) {
                    printf("Please calculate the bill first (Option 4).\n");
                } else {
                    showInvoice(customerName, customerCNIC, totalBill, discount, finalBill);
                }
                break;
            case 6:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}


