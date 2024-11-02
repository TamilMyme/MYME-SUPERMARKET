#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

void addItem(Item *inventory, int *count) {
    printf("Enter item ID: ");
    scanf("%d", &inventory[*count].id);
    printf("Enter item name: ");
    scanf("%s", inventory[*count].name);
    printf("Enter quantity: ");
    scanf("%d", &inventory[*count].quantity);
    printf("Enter price: ");
    scanf("%f", &inventory[*count].price);
    (*count)++;
    printf("Item added successfully!\n");
}

void viewInventory(Item *inventory, int count) {
    printf("\n--- Inventory ---\n");
    printf("ID\tName\tQuantity\tPrice\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%d\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
}

void updateItem(Item *inventory, int count) {
    int id;
    printf("Enter ID of item to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("Enter new quantity: ");
            scanf("%d", &inventory[i].quantity);
            printf("Enter new price: ");
            scanf("%f", &inventory[i].price);
            printf("Item updated successfully!\n");
            return;
        }
    }
    printf("Item not found.\n");
}

void deleteItem(Item *inventory, int *count) {
    int id;
    printf("Enter ID of item to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            (*count)--;
            printf("Item deleted successfully!\n");
            return;
        }
    }
    printf("Item not found.\n");
}

void processSale(Item *inventory, int count) {
    int id, quantity;
    printf("Enter item ID to sell: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (inventory[i].id == id) {
            printf("Enter quantity to sell: ");
            scanf("%d", &quantity);

            if (quantity <= inventory[i].quantity) {
                inventory[i].quantity -= quantity;
                printf("Sale processed! Total price: %.2f\n", inventory[i].price * quantity);
            } else {
                printf("Insufficient stock.\n");
            }
            return;
        }
    }
    printf("Item not found.\n");
}

void generateInventoryReport(Item *inventory, int count) {
    FILE *file = fopen("inventory_report.txt", "w");
    if (file == NULL) {
        printf("Error creating report file.\n");
        return;
    }
    fprintf(file, "ID\tName\tQuantity\tPrice\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\t%s\t%d\t%.2f\n", inventory[i].id, inventory[i].name, inventory[i].quantity, inventory[i].price);
    }
    fclose(file);
    printf("Inventory report generated as 'inventory_report.txt'!\n");
}

int main() {
    Item inventory[MAX_ITEMS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n--- MYME Supermarket Stock Management ---\n");
        printf("1. Add Item\n");
        printf("2. View Inventory\n");
        printf("3. Update Item\n");
        printf("4. Delete Item\n");
        printf("5. Process Sale\n");
        printf("6. Generate Inventory Report\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem(inventory, &count);
                break;
            case 2:
                viewInventory(inventory, count);
                break;
            case 3:
                updateItem(inventory, count);
                break;
            case 4:
                deleteItem(inventory, &count);
                break;
            case 5:
                processSale(inventory, count);
                break;
            case 6:
                generateInventoryReport(inventory, count);
                break;
            case 7:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
