#include <stdio.h>

#define ROWS 3
#define COLS 3


#define POWER_ON 1        
#define OVERLOAD 2        
#define MAINTENANCE 4     


void updateSector(int grid[ROWS][COLS]);
void querySector(int grid[ROWS][COLS]);
void runDiagnostic(int grid[ROWS][COLS]);
void displayStatus(int status);

int main() {
    int grid[ROWS][COLS] = {0}; 
    int choice;

    do {
        printf("\n===== IESCO Power Grid Monitoring System =====\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSector(grid);
                break;
            case 2:
                querySector(grid);
                break;
            case 3:
                runDiagnostic(grid);
                break;
            case 4:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}


void updateSector(int grid[ROWS][COLS]) {
    int row, col, option, flag;

    printf("Enter sector coordinates (row and column): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nSelect the status to modify:\n");
    printf("1. Power Status\n");
    printf("2. Overload Warning\n");
    printf("3. Maintenance Required\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option) {
        case 1: flag = POWER_ON; break;
        case 2: flag = OVERLOAD; break;
        case 3: flag = MAINTENANCE; break;
        default: printf("Invalid option!\n"); return;
    }

    int action;
    printf("Enter 1 to SET or 0 to CLEAR this flag: ");
    scanf("%d", &action);

    if (action == 1)
        grid[row][col] |= flag;   
    else
        grid[row][col] &= ~flag;  

    printf("Sector (%d, %d) updated successfully.\n", row, col);
}


void querySector(int grid[ROWS][COLS]) {
    int row, col;

    printf("Enter sector coordinates to query (row and column): ");
    scanf("%d %d", &row, &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\n=== Sector (%d, %d) Status Report ===\n", row, col);
    displayStatus(grid[row][col]);
}


void displayStatus(int status) {
    printf("Power Status: %s\n", (status & POWER_ON) ? "ON" : "OFF");
    printf("Overload Warning: %s\n", (status & OVERLOAD) ? "YES" : "NO");
    printf("Maintenance Required: %s\n", (status & MAINTENANCE) ? "YES" : "NO");
}


void runDiagnostic(int grid[ROWS][COLS]) {
    int overloadCount = 0, maintenanceCount = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] & OVERLOAD)
                overloadCount++;
            if (grid[i][j] & MAINTENANCE)
                maintenanceCount++;
        }
    }

    printf("\n=== System Diagnostic Report ===\n");
    printf("Total Overloaded Sectors: %d\n", overloadCount);
    printf("Total Sectors Requiring Maintenance: %d\n", maintenanceCount);
}

