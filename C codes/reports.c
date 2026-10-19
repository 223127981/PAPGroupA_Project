/*
 * reports.c - Reports module
 * Municipal Financial Management System (MFMS) - PAP521S Project A, Group 5
 * Author: Allan Lunga (225061333)
 *
 * Produces the Employee, Budget, Supplier and Asset reports by using the
 * data and functions of the other modules.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reports.h"
#include "assets.h"
#include "suppliers.h"
#include "budget_management.h"
#include "employees.h"

#define REPORT_INPUT_SIZE 100

/* Keeps asking until the user types a whole number from min to max.
 * (Only used inside this file.) */
static int reportReadChoice(int min, int max)
{
    char input[REPORT_INPUT_SIZE];
    int choice;
    char extra;
    int length;
    int ch;

    while (1)
    {
        printf("Enter your choice: ");

        if (fgets(input, REPORT_INPUT_SIZE, stdin) == NULL)
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

        if (sscanf(input, "%d %c", &choice, &extra) == 1 && choice >= min && choice <= max)
        {
            return choice;
        }
        printf("Invalid choice. Please enter a number from %d to %d.\n", min, max);
    }
}

/* The Reports menu. Loops until the user chooses 5. */
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

        choice = reportReadChoice(1, 5);

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
        }

    } while (choice != 5);
}

/* Asset Report: the asset register plus the number and total value of assets. */
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

/* Employee Report: total employees, average, highest and lowest salary. */
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

/* Budget Report: total allocated, total spent, remaining, and over-budget departments. */
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

/* Supplier Report: every registered supplier. */
void supplierReport(void)
{
    printf("\n========================================\n");
    printf("            SUPPLIER REPORT\n");
    printf("========================================\n");

    displayAllSuppliers();

    printf("========================================\n");
}
