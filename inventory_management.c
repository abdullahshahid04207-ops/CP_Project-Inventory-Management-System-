#include <stdio.h>
#include "inventory.h"


/* Also declared prototype here as well as in another file to know what the program actually does*/
void Add_items(void);
void Search_items(void);
void Update_items(void);
void Delete_items(void);
void Display_items(void);


/* MAIN ONLY RESERVED FOR FUNCTION CALLING AND MENU*/
int main() {
    int choice;

    do{
                                            /* ********** INVENTORY MENU  ********** */

        printf("\n<================================= INVENTORY MANAGEMENT SYSTEM =================================>\n");
        printf("\n||                                   Choice #1  Add PRODUCT                                    ||\n");
        printf("\n||                                   Choice #2  Search PRODUCT                                 ||\n");
        printf("\n||                                   Choice #3  UPDATE PRODUCT                                 ||\n");
        printf("\n||                                   Choice #4  DELETE PRODUCT                                 ||\n");
        printf("\n||                                   Choice #5  DISPLAY PRODUCT                                ||\n");
        printf("\n||                                   Choice #6  EXIT                                           ||\n");
        printf("\n<================================= XXXXXXXXX XXXXXXXXXX XXXXXX =================================>\n");
        // Geeting choice of user
        printf("\n Which Option Do You Want to Select (Enter Number)?:  ");

        if(scanf("%d",&choice) != 1){
            int c;
            while((c = getchar()) != '\n' && c != EOF);
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            Add_items();
            break;
        case 2:
            Search_items();
            break;
        case 3:
           Update_items();
           break;
        case 4:
           Delete_items();
           break;
        case 5:
            Display_items();
            break;
        case 6:
            printf("\nExiting From Program.......\n");
            break;    
        default:
            printf("\nInvalid Input (choose Option 1-6)\n");
            break;
        }
        
    
        
    }while (choice != 6);

    


    return 0;
}

