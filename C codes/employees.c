#include <stdio.h>
#include <string.h>
#include "employees.h"

int employeeID[MAX_EMPLOYEES];
char employeeName[MAX_EMPLOYEES][50];
char department[MAX_EMPLOYEES][50];
float basicSalary[MAX_EMPLOYEES];
float housingAllowance[MAX_EMPLOYEES];
float transportAllowance[MAX_EMPLOYEES];

int employeeCount = 0;

void addEmployee()
{
    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Employee limit reached.\n");
        return;
    }

    printf("\n--- Add Employee ---\n");

    do
    {
        printf("Enter Employee ID: ");
        scanf("%d", &employeeID[employeeCount]);

        if (employeeID[employeeCount] <= 0)
        {
            printf("Employee ID must be greater than 0. Please try again.\n");
        }

    } while (employeeID[employeeCount] <= 0);

    printf("Enter Employee Name: ");
    scanf(" %[^\n]", employeeName[employeeCount]);

    printf("Enter Department: ");
    scanf(" %[^\n]", department[employeeCount]);

    do
    {
        printf("Enter Basic Salary: ");
        scanf("%f", &basicSalary[employeeCount]);

        if (basicSalary[employeeCount] < 0)
        {
            printf("Salary cannot be negative. Please try again.\n");
        }

    } while (basicSalary[employeeCount] < 0);

    do
    {
        printf("Enter Housing Allowance: ");
        scanf("%f", &housingAllowance[employeeCount]);

        if (housingAllowance[employeeCount] < 0)
        {
            printf("Housing allowance cannot be negative. Please try again.\n");
        }

    } while (housingAllowance[employeeCount] < 0);

    do
    {
        printf("Enter Transport Allowance: ");
        scanf("%f", &transportAllowance[employeeCount]);

        if (transportAllowance[employeeCount] < 0)
        {
            printf("Transport allowance cannot be negative. Please try again.\n");
        }

    } while (transportAllowance[employeeCount] < 0);

    employeeCount++;

    printf("Employee added successfully!\n");
}

void displayEmployees()
{
    int i;

    if (employeeCount == 0)
    {
        printf("\nNo employees registered.\n");
        return;
    }

    printf("\n--- Employee List ---\n");

    for (i = 0; i < employeeCount; i++)
    {
        printf("\nEmployee ID: %d\n", employeeID[i]);
        printf("Name: %s\n", employeeName[i]);
        printf("Department: %s\n", department[i]);
        printf("Basic Salary: N$%.2f\n", basicSalary[i]);
        printf("Housing Allowance: N$%.2f\n", housingAllowance[i]);
        printf("Transport Allowance: N$%.2f\n", transportAllowance[i]);

        printf("Total Salary: N$%.2f\n",
               calculateSalary(
                   basicSalary[i],
                   housingAllowance[i],
                   transportAllowance[i]));
    }
}

float calculateSalary(float basicSalary,
                      float housingAllowance,
                      float transportAllowance)
{
    return basicSalary + housingAllowance + transportAllowance;
}

void searchEmployee()
{
    char searchName[50];
    int found = 0;
    int i;

    printf("\n--- Search Employee ---\n");

    printf("Enter employee name: ");
    scanf(" %[^\n]", searchName);

    for (i = 0; i < employeeCount; i++)
    {
        if (strcmp(employeeName[i], searchName) == 0)
        {
            printf("\nEmployee found!\n");
            printf("Employee ID: %d\n", employeeID[i]);
            printf("Name: %s\n", employeeName[i]);
            printf("Department: %s\n", department[i]);
            printf("Basic Salary: N$%.2f\n", basicSalary[i]);
            printf("Housing Allowance: N$%.2f\n", housingAllowance[i]);
            printf("Transport Allowance: N$%.2f\n",
                   transportAllowance[i]);

            printf("Total Salary: N$%.2f\n",
                   calculateSalary(
                       basicSalary[i],
                       housingAllowance[i],
                       transportAllowance[i]));

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Employee not found.\n");
    }
}