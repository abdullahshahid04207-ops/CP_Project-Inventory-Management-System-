
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inventory.h"

/* A SEPERATE MODULE TO TEST WHETHER A NEW ADDED ID ALREADLY EXIST OR NOT CALLED IN ADD MODULE LATER*/
/* This function checks if a product ID is already saved in the file.
   It returns 1 if the ID is found, and 0 if it is not found. */
int id_exists(int id) {
    /* Open the file "inventory.txt" in read mode ("r") */
    FILE *fp = fopen("inventory.txt", "r");

    /* If the file could not be opened (fp is NULL), the file does not exist yet */
    if (fp == NULL) return 0;   /* no file yet, so no duplicates */

    /* Make a temporary variable to hold one product's data at a time */
    Items temp;

    /* Read the file line by line.
       fscanf reads the 4 values: id, name, quantity and price.
       It returns 4 when all 4 values were read properly.
       When the file ends (or the line is wrong), it returns something else and the loop stops. */
    while (fscanf(fp, "%d | %s | %d | %f",
                  &temp.id, temp.name, &temp.quantity, &temp.price) == 4) {

        /* Compare the ID from the file with the ID we are searching for */
        if (temp.id == id) {
            fclose(fp);   /* close the file before leaving the function */
            return 1;     /* ID found, so it already exists */
        }
    }

    /* We checked every line and found no match, so close the file */
    fclose(fp);
    return 0;   /* ID not found, so it does not exist */
}
/* TO ADD PRODUCTS INTO OR MANAGEMENT SYSTEM */
    /* EACH INPUT PRODUCT IS ADDED TO FILE TO PRESERVE DATA*/
/* This function takes product details from the user and saves them in the file. */
void Add_items(void) {
    int cont;      /* stores the user's answer: 1 = add more, 0 = stop */
    Items item;    /* a variable to hold one product's details */
    FILE *fp;      /* a pointer used to work with the file */

    /* This loop keeps running so the user can add many products one after another */
    while(1){
    /* Ask the user for the product ID and store it in item.id */
    printf("Enter Product ID: \n");
    scanf("%d", &item.id);

    /* If the ID is already in the file, keep asking until the user enters a new one */
    while (id_exists(item.id)) {   /* Called module to test id */
        printf("ID %d already exists. Enter a different ID: \n", item.id);
        scanf("%d", &item.id);
    }
    
    /* Ask for the product name (the space before %s skips any leftover Enter key) */
    printf("Enter Product Name: \n");
    scanf(" %s", item.name);

    /* Ask for how many pieces of the product we have */
    printf("Enter Product Quantity: \n");
    scanf("%d", &item.quantity);

    /* Ask for the price of one piece */
    printf("Enter Product Price(IN PKR): \n");
    scanf("%f", &item.price);

    /* Open the file in append mode ("a"), which adds new data at the end
       and does not delete the old data */
    fp = fopen("inventory.txt", "a");

    /* Write the product in the file as one line, with | between the values */
    fprintf(fp, "%d | %s | %d | %f\n", item.id, item.name, item.quantity, item.price);

    /* CHANGED: close the file now, after every product.
       This saves the data properly, so id_exists can find this ID next time. */
    fclose(fp);

    printf("\n");
    
    /* A FUCTION TO KEEP ASKING OPERATOR TO WHETHER HE WANT TO ADD ANOTHER PRODUCT OR NOT BASED ON HIS RESPONSE */
    printf("DO YOU WANT TO ADD MORE PRODUCTS?(1 FOR YES AND 0 FOR NO): ");
        scanf("%d",&cont);

        /* If the user typed 1, go back to the start of the loop and add another product */
        if(cont == 1)
        continue;

        /* If the user typed 0, leave the loop because we are finished */
        if(cont == 0)
        break;

        /* If the user typed anything else, show a message and ask again */
        else if (cont != 0 && cont != 1){
        printf("\n<------Input Correct Option------>\n\n");
        continue;
        }
    
    }
    printf("\n");
    /* The old fclose(fp) was removed from here, because the file is already closed inside the loop */

}
/* A MODULE TO SEARCH ANY INPUT ID IN FILES WHETHER EXIST OR NOT AND IF EXIST THEN DEATILS OF THE PRODUCT UNDER THAT ID*/

/* This function asks for an ID, looks for it in the file, and shows the product if it is found. */
void Search_items(void){
    int s_id, found = 0;   /* s_id = the ID to search, found = 0 means "not found yet", 1 means "found" */
    Items item;            /* a variable to hold one product's data at a time */

    /* Open the file in read mode ("r") */
    FILE *fp = fopen("inventory.txt", "r");

    if (fp == NULL) {   /* TO GRACEFULLY ENCOUNTER THE SITUATION IF THERE IS NO DATA IN FILE */
        printf("No products found.\n");
        return;   /* stop the function here because there is nothing to search */
    }

    /* Ask the user which ID they want to search */
    printf("Enter ID to search: ");
    scanf("%d", &s_id);

    /* Read the file one line at a time.
       The loop continues while fscanf successfully reads all 4 values. */
    while (fscanf(fp, "%d | %s | %d | %f",
        &item.id, item.name, &item.quantity, &item.price) == 4) {

        /* Check if the ID from the file matches the ID the user typed */
        if (item.id == s_id)
        {
            /* Print the heading of the table.
               %-8s means: print the text and leave 8 spaces of width, aligned to the left */
            printf("\n%-8s %-20s %-12s %-10s\n\n", "ID", "Name", "Quantity", "Price");

            /* Print the product's details under the heading.
               %-10.2f means: show the price with 2 digits after the decimal point */
            printf("%-8d %-20s %-12d Rs. %-10.2f\n",
                   item.id, item.name, item.quantity, item.price);

            found = 1;   /* remember that we found the product */
            break;       /* stop the loop, no need to read the remaining lines */
        }
        
    }

    /* If found is still 0, it means no line matched the ID */
    if (!found){   /* TO GRACEFULLY ENCOUNTER THE SINARIO IN CASE ID DONT EXIST*/
        printf("The id you have entered does not exist!\n");
    }

    fclose(fp);   /* close the file because we are done reading it */

    /* This takes the leftover Enter key from the input, so the program does not skip the next input */
    getchar();
}

 /* TO UPDATE A DETAILS OF A PRODUCT IN CASE THERE IS ANY CHANGE IN A PRODUCT*/
/* This function changes the details of one product.
   Idea: copy every product into a new temporary file, and for the product being updated, write the new details instead.
   At the end, the new file replaces the old one. */
void Update_items(void){
    int s_id, found = 0;   /* s_id = the ID to update, found = 1 when we find that ID */
    Items item;            /* a variable to hold one product's data at a time */

    /* Open the main file for reading */
    FILE *fp = fopen("inventory.txt", "r");
    FILE *temp;   /* this pointer will be used for the temporary file */

    /* If the main file does not exist, there is nothing to update */
    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    /* Create a new temporary file in write mode ("w") */
    temp = fopen("temp.txt", "w");

    /* If the temporary file could not be created, close the main file and stop */
    if (temp == NULL) {
        printf("Could not create temp file.\n");
        fclose(fp);
        return;
    }

    /* Ask the user which product ID they want to update */
    printf("Enter ID to update: ");
    scanf("%d", &s_id);

    /* Read the main file line by line */
    while (fscanf(fp, "%d | %s | %d | %f",
                  &item.id, item.name, &item.quantity, &item.price) == 4) {

        /* If this is the product we want to update, take the new details from the user.
           These new values replace the old ones stored in item. */
        if (item.id == s_id) {
            found = 1;   /* remember that we found the ID */
            printf("Enter new name: ");
            scanf("%s", item.name);
            printf("Enter new quantity: ");
            scanf("%d", &item.quantity);
            printf("Enter new price(IN PKR): ");
            scanf("%f", &item.price);
        }

        /* Write the product into the temporary file.
           If it was updated, the new details are written. If not, the old details are written as they were. */
        fprintf(temp, "%d | %s | %d | %.2f\n",
                item.id, item.name, item.quantity, item.price);
    }

    /* Close both files because we finished reading and writing */
    fclose(fp);
    fclose(temp);

    if (found) {
        remove("inventory.txt");              /* delete the old file */
        rename("temp.txt", "inventory.txt");  /* give the new file the old file's name */
        printf("Item updated successfully!\n");
    } else {
        /* The ID was not found, so nothing changed. Delete the temporary file. */
        remove("temp.txt");
        printf("The id you have entered does not exist!\n");
    }

    /* These two getchar() calls take the leftover Enter keys from the input,
       so the program does not skip the next input */
    getchar();
    getchar();
}

/* TO DELETE AN ALREADY EXISTING PRODUCT USING ITS ID */
/* This function removes one product from the file.
   Idea: copy every line into a new temporary file, except the line of the product we want to delete.
   At the end, the new file replaces the old one. */
void Delete_items(void) {
    FILE *fp, *temp;   /* fp = the main file, temp = the temporary file */
    char line[256];    /* a box to hold one full line of text from the file */
    int d_id, id, found = 0;   /* d_id = ID to delete, id = ID read from a line, found = 1 when we find the ID */

    /* Open the main file for reading */
    fp = fopen("inventory.txt", "r");

    /* If the file does not exist, there is nothing to delete */
    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    /* Ask the user which product ID they want to delete */
    printf("Enter ID to delete: ");

    /* scanf returns 1 when it reads one number properly.
       If it does not return 1, the user typed something wrong (like a letter). */
    if (scanf("%d", &d_id) != 1) {
        printf("Invalid input!\n");
        fclose(fp);   /* close the file before leaving */
        return;
    }

    /* Create a new temporary file in write mode ("w") */
    temp = fopen("temp.txt", "w");

    /* If the temporary file could not be created, close the main file and stop */
    if (temp == NULL) {
        printf("Could not create temporary file.\n");
        fclose(fp);
        return;
    }

    /* Read the main file one full line at a time.
       fgets reads a whole line and stores it in "line". It returns NULL when the file ends. */
    while (fgets(line, sizeof(line), fp) != NULL) {

        /* sscanf reads from the text in "line" (not from the keyboard or file).
           Here it takes only the first number, which is the product ID.
           If it read the ID properly and it matches the ID to delete... */
        if (sscanf(line, "%d", &id) == 1 && id == d_id) {
            found = 1; // skip matching item
            /* We do nothing else here, so this line is not copied to the temporary file */
        } else {
            fputs(line, temp); // keep all other lines
            /* fputs writes the line as it is into the temporary file */
        }
    }

    /* Close both files because we finished reading and writing */
    fclose(fp);
    fclose(temp);

    if (found) {
        remove("inventory.txt");              /* delete the old file */
        rename("temp.txt", "inventory.txt");  /* give the new file the old file's name */
        printf("Product deleted successfully!\n");
    } else {
        /* The ID was not found, so nothing was deleted. Remove the temporary file. */
        remove("temp.txt");
        printf("ID not found!\n");
    }

    /* This takes the leftover Enter key from the input, so the program does not skip the next input */
    getchar();
}
/* TO DISPLAY THE ENTIRE PRODUCT LIST WITH ALL DETAILS*/
void Display_items(void) {
    Items item;
    FILE *fp = fopen("inventory.txt", "r");

    if (fp == NULL) {
        printf("No products found.\n");
        return;
    }

    printf("\n%-8s %-20s %-12s %-10s\n\n", "ID", "Name", "Quantity", "Price");
    while (fscanf(fp, "%d | %s | %d | %f",
                  &item.id, item.name, &item.quantity, &item.price) == 4) {
        printf("%-8d %-20s %-12d Rs. %-10.2f\n",
               item.id, item.name, item.quantity, item.price);
    }

    fclose(fp);
    getchar();
}



