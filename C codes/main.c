/*
 * main.c - Main menu of the Municipal Financial Management System (MFMS)
 * PAP521S Project A - Group 5
 *
 * main.c only shows the main menu and sends the user to the module they
 * choose. The work of each module is done in its own .c file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"
#include "employees.h"
#include "budget_management.h"
#include "suppliers.h"
#include "assets.h"

#define MENU_INPUT_LENGTH 100
#define EXIT_CHOICE 6

static void displayMainMenu(void);
static int getMainMenuChoice(void);

int main(void)
{
    int choice;

    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Welcome to Windhoek Municipality\n");

    do
    {
        displayMainMenu();
        choice = getMainMenuChoice();

        switch (choice)
        {
        case 1:
            employeeMenu();
            break;
        case 2:
            budgetMenu();
            break;
        case 3:
            handleSupplierMenu();
            break;
        case 4:
            assetMenu();
            break;
        case 5:
            displayReports();
            break;
        case 6:
            printf("\nThank you for using MFMS. Goodbye!\n");
            break;
        }
    } while (choice != EXIT_CHOICE);

    return 0;
}

/* Prints the main menu. */
static void displayMainMenu(void)
{
    printf("\n========================================\n");
    printf("               MAIN MENU\n");
    printf("========================================\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

/* Keeps asking until the user types a whole number from 1 to 6,
 * then returns it. Letters, empty lines and other numbers are rejected. */
static int getMainMenuChoice(void)
{
    char input[MENU_INPUT_LENGTH];
    int choice;
    char extra;
    int length;
    int ch;

    while (1)
    {
        printf("Enter your choice: ");

        if (fgets(input, MENU_INPUT_LENGTH, stdin) == NULL)
        {
            printf("\nNo more input. Closing the program.\n");
            exit(0);
        }

        /* If the line was too long, throw away the rest of it */
        length = strlen(input);
        if (length > 0 && input[length - 1] != '\n')
        {
            while ((ch = getchar()) != '\n' && ch != EOF)
            {
            }
        }

        if (sscanf(input, "%d %c", &choice, &extra) == 1 && choice >= 1 && choice <= EXIT_CHOICE)
        {
            return choice;
        }

        printf("Invalid choice. Please enter a number from 1 to %d.\n", EXIT_CHOICE);
    }
}
