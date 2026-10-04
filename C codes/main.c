#include <stdio.h>
#include "reports.h"
#include "employees.h"
#include "budget_management.h"
#include "suppliers.h"
#include "assets.h"

int main(void)
{
    int choice;

    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Welcome to Windhoek Municipality\n");

    do
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
        printf("Enter your choice: ");

        scanf("%d", &choice);

        if (choice == 5)
        {
            displayReports();
        }

        else if (choice == 1)
        {
            addEmployee();
        }

        else if (choice == 2)
        {
            budgetMenu();
        }

        else if (choice == 3)
        {
            handleSupplierMenu();
        }

        else if (choice == 4)
        {
            assetMenu();
        }

    } while (choice != 6);

    return 0;
}