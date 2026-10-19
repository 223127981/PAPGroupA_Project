/*
 * suppliers.c - Supplier Management module
 * Municipal Financial Management System (MFMS) - PAP521S Project A, Group 5
 * Author: Nangolo Drothea (223039985)
 *
 * Registers suppliers, lists them, and searches them by name or by the
 * service/goods they provide.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "suppliers.h"

#define INPUT_SIZE 200   /* bigger than any field, so long input can be detected */

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;


/* ---------- Input helpers (only used inside this file) ---------- */

/* Reads one whole line and removes the Enter key ('\n'). */
static void supReadLine(char input[])
{
    int length;
    int ch;

    if (fgets(input, INPUT_SIZE, stdin) == NULL)
    {
        printf("\nNo more input. Closing the program.\n");
        exit(0);
    }

    length = strlen(input);
    if (length > 0 && input[length - 1] == '\n')
    {
        input[length - 1] = '\0';
    }
    else
    {
        /* The line was too long: throw away the rest of it */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
}

/* Keeps asking until the user types text that is not empty and fits
 * in an array of 'size' characters. */
static void supReadText(char prompt[], char text[], int size)
{
    char input[INPUT_SIZE];
    char first;

    while (1)
    {
        printf("%s", prompt);
        supReadLine(input);

        if (sscanf(input, " %c", &first) != 1)
        {
            printf("  This field cannot be empty. Please try again.\n");
        }
        else if ((int)strlen(input) >= size)
        {
            printf("  Too long - maximum %d characters. Please try again.\n", size - 1);
        }
        else
        {
            strcpy(text, input);
            return;
        }
    }
}

/* Keeps asking until the user types a whole number from min to max. */
static int supReadChoice(char prompt[], int min, int max)
{
    char input[INPUT_SIZE];
    int choice;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        supReadLine(input);

        if (sscanf(input, "%d %c", &choice, &extra) == 1 && choice >= min && choice <= max)
        {
            return choice;
        }
        printf("Invalid choice. Please enter a number from %d to %d.\n", min, max);
    }
}

/* Copies source into destination with every capital letter made small. */
static void toLowerCopy(char destination[], char source[])
{
    int i;

    for (i = 0; source[i] != '\0'; i++)
    {
        if (source[i] >= 'A' && source[i] <= 'Z')
        {
            destination[i] = source[i] - 'A' + 'a';
        }
        else
        {
            destination[i] = source[i];
        }
    }
    destination[i] = '\0';
}

/* Returns 1 if keyword appears anywhere in text, ignoring capital letters. */
static int containsIgnoreCase(char text[], char keyword[])
{
    char lowerText[INPUT_SIZE];
    char lowerKeyword[INPUT_SIZE];

    toLowerCopy(lowerText, text);
    toLowerCopy(lowerKeyword, keyword);

    return strstr(lowerText, lowerKeyword) != NULL;
}

/* Prints the details of the supplier at position i. */
static void printSupplier(int i)
{
    printf("  Name:    %s\n", suppliers[i].name);
    printf("  Contact: %s\n", suppliers[i].contact);
    printf("  Service: %s\n", suppliers[i].service);
}


/* ---------- Public functions (declared in suppliers.h) ---------- */

/* Asks for a new supplier's details, validates them and stores them. */
void addSupplier(void)
{
    Supplier s;

    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("\n Supplier list is full!\n");
        return;
    }

    s.isActive = 1;

    printf("\n--- Register New Supplier ---\n");

    supReadText("Supplier Name: ", s.name, MAX_NAME);
    supReadText("Contact Person / Phone: ", s.contact, MAX_CONTACT);
    supReadText("Service / Goods Provided: ", s.service, MAX_NAME);

    suppliers[supplierCount++] = s;
    printf("\n Supplier registered successfully! Total: %d\n", supplierCount);
}

/* Lists every registered supplier. */
void displayAllSuppliers(void)
{
    int i;

    if (supplierCount == 0)
    {
        printf("\n No suppliers registered yet.\n");
        return;
    }

    printf("\n=== All Registered Suppliers (%d) ===\n", supplierCount);
    for (i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier #%d\n", i + 1);
        printSupplier(i);
    }
}

/* Finds suppliers whose name or service contains the keyword. */
void searchSupplier(void)
{
    char keyword[MAX_NAME];
    int found = 0;
    int i;

    printf("\n--- Search Supplier ---\n");
    supReadText("Enter name or keyword to search: ", keyword, MAX_NAME);

    printf("\n--- Search Results ---\n");
    for (i = 0; i < supplierCount; i++)
    {
        if (containsIgnoreCase(suppliers[i].name, keyword) ||
            containsIgnoreCase(suppliers[i].service, keyword))
        {
            printf("\n Found Supplier #%d\n", i + 1);
            printSupplier(i);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\n No supplier matching '%s' found.\n", keyword);
    }
}

/* The Supplier Management sub-menu. Loops until the user chooses 4. */
void handleSupplierMenu(void)
{
    int choice;

    while (1)
    {
        printf("\n\n=== SUPPLIER MANAGEMENT - Nangolo Drothea (223039985) ===\n");
        printf("1. Register New Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");

        choice = supReadChoice("Enter your choice: ", 1, 4);

        switch (choice)
        {
        case 1:
            addSupplier();
            break;
        case 2:
            displayAllSuppliers();
            break;
        case 3:
            searchSupplier();
            break;
        case 4:
            return;
        }
    }
}
