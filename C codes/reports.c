#include <stdio.h>
#include "reports.h"
#include "assets.h"
#include "suppliers.h"
#include "budget_management.h"
#include "employees.h"
void displayReports(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("              REPORTS MENU\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Return to Main Menu\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            employeeReport();
            break;

        case 2:
            budgetReport();
            break;

        case 3:
            supplierReport();
            break;

        case 4:
            assetReport();
            break;

        case 5:
            printf("Returning to Main Menu...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}

void assetReport(void)
{
    printf("\n========================================\n");
    printf("              ASSET REPORT\n");
    printf("========================================\n");

    displayAssets();

    printf("\nTotal Assets: %d\n", getAssetCount());
    printf("Total Asset Value: N$%.2f\n", getTotalAssetValue());

    printf("========================================\n");
}

void employeeReport(void)
{
    int i;
    float salary;
    float totalSalary = 0;
    float highestSalary;
    float lowestSalary;

    printf("\n========================================\n");
    printf("            EMPLOYEE REPORT\n");
    printf("========================================\n");

    if (employeeCount == 0)
    {
        printf("No employees registered yet.\n");
    }
    else
    {
        highestSalary = calculateSalary(
            basicSalary[0],
            housingAllowance[0],
            transportAllowance[0]);

        lowestSalary = highestSalary;

        for (i = 0; i < employeeCount; i++)
        {
            salary = calculateSalary(
                basicSalary[i],
                housingAllowance[i],
                transportAllowance[i]);

            totalSalary += salary;

            if (salary > highestSalary)
                highestSalary = salary;

            if (salary < lowestSalary)
                lowestSalary = salary;
        }

        printf("Total Employees: %d\n", employeeCount);
        printf("Average Salary: N$%.2f\n", totalSalary / employeeCount);
        printf("Highest Salary: N$%.2f\n", highestSalary);
        printf("Lowest Salary: N$%.2f\n", lowestSalary);
    }

    printf("========================================\n");
}

void budgetReport(void)
{
    int i;
    double totalAllocated = 0;
    double totalExpenditure = 0;

    printf("\n========================================\n");
    printf("             BUDGET REPORT\n");
    printf("========================================\n");

    if (deptCount == 0)
    {
        printf("No budget information available yet.\n");
    }
    else
    {
        for (i = 0; i < deptCount; i++)
        {
            totalAllocated += budgets[i].allocated;
            totalExpenditure += budgets[i].expenditure;
        }

        printf("Total Allocated Budget: N$%.2f\n", totalAllocated);
        printf("Total Expenditure: N$%.2f\n", totalExpenditure);
        printf("Remaining Budget: N$%.2f\n",
               totalAllocated - totalExpenditure);

        displayExceeded();
    }

    printf("========================================\n");
}

void supplierReport(void)
{
    printf("\n========================================\n");
    printf("            SUPPLIER REPORT\n");
    printf("========================================\n");

    displayAllSuppliers();

    printf("========================================\n");
}