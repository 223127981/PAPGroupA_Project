#include <stdio.h>
#include <string.h>
#include "suppliers.h"

Supplier suppliers[MAX_SUPPLIERS];
int supplierCount = 0;

void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS)
    {
        printf("\n Supplier list is full!\n");
        return;
    }

    Supplier s;
    s.isActive = 1;

    printf("\n--- Register New Supplier ---\n");

    printf("Supplier Name: ");
    getchar();
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Contact Person / Phone: ");
    fgets(s.contact, MAX_CONTACT, stdin);
    s.contact[strcspn(s.contact, "\n")] = '\0';

    printf("Service / Goods Provided: ");
    fgets(s.service, MAX_NAME, stdin);
    s.service[strcspn(s.service, "\n")] = '\0';

    suppliers[supplierCount++] = s;
    printf("\n Supplier registered successfully! Total: %d\n", supplierCount);
}

void displayAllSuppliers(void)
{
    if (supplierCount == 0)
    {
        printf("\n No suppliers registered yet.\n");
        return;
    }

    printf("\n=== All Registered Suppliers (%d) ===\n", supplierCount);
    for (int i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier #%d\n", i + 1);
        printf("  Name:    %s\n", suppliers[i].name);
        printf("  Contact: %s\n", suppliers[i].contact);
        printf("  Service: %s\n", suppliers[i].service);
    }
}

void searchSupplier(void)
{
    char keyword[MAX_NAME];
    int found = 0;

    printf("\n--- Search Supplier ---\n");
    printf("Enter name or keyword to search: ");
    getchar();
    fgets(keyword, MAX_NAME, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    printf("\n--- Search Results ---\n");
    for (int i = 0; i < supplierCount; i++)
    {
        if (strstr(suppliers[i].name, keyword) != NULL ||
            strstr(suppliers[i].service, keyword) != NULL)
        {
            printf("\n Found Supplier #%d\n", i + 1);
            printf("  Name:    %s\n", suppliers[i].name);
            printf("  Contact: %s\n", suppliers[i].contact);
            printf("  Service: %s\n", suppliers[i].service);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\n No supplier matching '%s' found.\n", keyword);
    }
}

void handleSupplierMenu(void)
{
    int choice;
    while (1)
    {
        printf("\n\n=== SUPPLIER MANAGEMENT — Nangolo Drothea (223039985) ===\n");
        printf("1. Register New Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("Please enter a valid number.\n");
            continue;
        }

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
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
}