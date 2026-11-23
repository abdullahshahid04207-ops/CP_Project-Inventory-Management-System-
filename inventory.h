/* invi.h - Inventory management module: item structure and function declarations */

// Include guard: prevents multiple inclusion of this header
#ifndef INVI_H
#define INVI_H

// Represents a single product in the inventory
typedef struct Items {
    int id;                    // Unique item identifier
    char name[50];             // Item name (max 49 characters + null terminator)
    int quantity;              // Units in stock
    float price;               // Price per unit
} Items;

int id_exists(int id);    // Returns nonzero if an item with this ID already exists (used to avoid duplicates)
void Add_items(void);     // Prompts for item details and adds a new item to the inventory
void Search_items(void);  // Searches for an item and displays it if found
void Update_items(void);  // Modifies the details of an existing item
void Delete_items(void);  // Removes an item from the inventory
void Display_items(void); // Prints all items in the inventory

#endif    // INVI_H
