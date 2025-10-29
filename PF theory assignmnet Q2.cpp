#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_CART 50


int productCodes[] = {1, 2, 3, 4};
int stock[] = {50, 10, 20, 8};
int price[] = {100, 200, 300, 150};
int totalProducts = 4;
int cartCodes[MAX_CART];
int cartQty[MAX_CART];
int cartCount = 0;


char customerName[50];
char customerCNIC[20];

void getCustomerInfo();
void displayInventory();
void updateInventory(int code, int quantity);
void addToCart();
float displayTotalBill();
void showInvoice(float total, float discountedTotal);

int main() {
    int choice;
    float total = 0.0, discountedTotal = 0.0;

    do {
        
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getCustomerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                addToCart();
                break;
            case 4:
                total = displayTotalBill();
                printf("\nTotal Bill (without discount): %.2f\n", total);

                char promo[10];
                printf("Do you have a promo code? (Enter code or 'no'): ");
                scanf("%s", promo);
                if (strcmp(promo, "Eid2025") == 0) {
                    discountedTotal = total * 0.75;
                    printf("Promo code applied! 25%% discount.\n");
                    printf("Discounted Total: %.2f\n", discountedTotal);
                } else {
                    discountedTotal = total;
                    printf("No valid promo code applied.\n");
                }
                break;
            case 5:
                showInvoice(total, discountedTotal);
                break;
            case 6:
                printf("Exiting system. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}


void getCustomerInfo() {
    printf("\nEnter customer name: ");
    getchar(); 
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';

    printf("Enter CNIC number: ");
    fgets(customerCNIC, sizeof(customerCNIC), stdin);
    customerCNIC[strcspn(customerCNIC, "\n")] = '\0';

    printf("Customer information saved successfully.\n");
}


void displayInventory() {
    printf("\n=== Inventory ===\n");
    printf("Code\tStock\tPrice\n");
    for (int i = 0; i < totalProducts; i++) {
        printf("%03d\t%d\t%d\n", productCodes[i], stock[i], price[i]);
    }
}


void updateInventory(int code, int quantity) {
    for (int i = 0; i < totalProducts; i++) {
        if (productCodes[i] == code) {
            if (stock[i] >= quantity)
                stock[i] -= quantity;
            else
                printf("Not enough stock for product %03d\n", code);
            return;
        }
    }
}


void addToCart() {
    int code, qty, found = 0;
    displayInventory();

    printf("Enter product code to add to cart: ");
    scanf("%d", &code);
    printf("Enter quantity: ");
    scanf("%d", &qty);

    for (int i = 0; i < totalProducts; i++) {
        if (productCodes[i] == code) {
            found = 1;
            if (qty > stock[i]) {
                printf("Not enough stock available!\n");
                return;
            }
            cartCodes[cartCount] = code;
            cartQty[cartCount] = qty;
            cartCount++;
            updateInventory(code, qty);
            printf("Item added to cart successfully.\n");
            return;
        }
    }

    if (!found)
        printf("Invalid product code!\n");
}


float displayTotalBill() {
    float total = 0;
    printf("\n=== Cart Details ===\n");
    printf("Code\tQty\tPrice\tSubtotal\n");
    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < totalProducts; j++) {
            if (cartCodes[i] == productCodes[j]) {
                float subtotal = cartQty[i] * price[j];
                printf("%03d\t%d\t%d\t%.2f\n", productCodes[j], cartQty[i], price[j], subtotal);
                total += subtotal;
            }
        }
    }
    return total;
}


void showInvoice(float total, float discountedTotal) {
    printf("\nINVOICE \n");
    printf("Customer Name: %s\n", customerName);
    printf("CNIC: %s\n", customerCNIC);
    
    printf("Code\tQty\tPrice\tSubtotal\n");
    float subtotal = 0;
    for (int i = 0; i < cartCount; i++) {
        for (int j = 0; j < totalProducts; j++) {
            if (cartCodes[i] == productCodes[j]) {
                float line = cartQty[i] * price[j];
                printf("%03d\t%d\t%d\t%.2f\n", productCodes[j], cartQty[i], price[j], line);
                subtotal += line;
            }
        }
    }
    
    printf("Total (no discount): %.2f\n", total);
    printf("Total (with discount): %.2f\n", discountedTotal);
   
}

