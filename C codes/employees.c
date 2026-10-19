/*
 * employees.c - Employee Management module
 * Municipal Financial Management System (MFMS) - PAP521S Project A, Group 5
 * Author: Alfeus Rosalia (224009893)
 *
 * Adds, displays and searches employees, and calculates each employee's
 * total salary (basic salary + housing allowance + transport allowance).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employees.h"

#define INPUT_SIZE 100            /* size of the temporary input buffer */
#define TEXT_SIZE 50              /* name/department arrays hold 49 characters */
#define MAX_AMOUNT 10000000.0f    /* N$10 million upper limit for any amount */

int employeeID[MAX_EMPLOYEES];
char employeeName[MAX_EMPLOYEES][50];
char department[MAX_EMPLOYEES][50];
float basicSalary[MAX_EMPLOYEES];
float housingAllowance[MAX_EMPLOYEES];
float transportAllowance[MAX_EMPLOYEES];

int employeeCount = 0;


/* ---------- Input helpers (only used inside this file) ---------- */

/* Reads one whole line and removes the Enter key ('\n'). */
static void empReadLine(char input[])
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

/* Keeps asking until the user types text that is not empty and fits. */
static void empReadText(char prompt[], char text[])
{
    char input[INPUT_SIZE];
    char first;

    while (1)
    {
        printf("%s", prompt);
        empReadLine(input);

        if (sscanf(input, " %c", &first) != 1)
        {
            printf("This field cannot be empty. Please try again.\n");
        }
        else if (strlen(input) >= TEXT_SIZE)
        {
            printf("Too long - maximum %d characters. Please try again.\n", TEXT_SIZE - 1);
        }
        else
        {
            strcpy(text, input);
            return;
        }
    }
}

/* Keeps asking until the user types a whole number greater than 0. */
static int empReadId(char prompt[])
{
    char input[INPUT_SIZE];
    int id;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        empReadLine(input);

        if (sscanf(input, "%d %c", &id, &extra) != 1)
        {
            printf("Employee ID must be a whole number. Please try again.\n");
        }
        else if (id <= 0)
        {
            printf("Employee ID must be greater than 0. Please try again.\n");
        }
        else
        {
            return id;
        }
    }
}

/* Keeps asking until the user types a valid amount of money.
 * allowZero = 1 accepts 0 (allowances); allowZero = 0 needs more than 0. */
static float empReadAmount(char prompt[], int allowZero)
{
    char input[INPUT_SIZE];
    float value;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        empReadLine(input);

        if (sscanf(input, "%f %c", &value, &extra) != 1)
        {
            printf("Enter numbers only, without N$ or commas. Please try again.\n");
        }
        else if (value < 0)
        {
            printf("Amount cannot be negative. Please try again.\n");
        }
        else if (value == 0 && !allowZero)
        {
            printf("Amount must be more than 0. Please try again.\n");
        }
        else if (value > MAX_AMOUNT)
        {
            printf("Amount is too large (maximum N$%.2f). Please try again.\n", MAX_AMOUNT);
        }
        else
        {
            return value;
        }
    }
}

/* Keeps asking until the user types a whole number from min to max. */
static int empReadChoice(char prompt[], int min, int max)
{
    char input[INPUT_SIZE];
    int choice;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        empReadLine(input);

        if (sscanf(input, "%d %c", &choice, &extra) == 1 && choice >= min && choice <= max)
        {
            return choice;
        }
        printf("Invalid choice. Please enter a number from %d to %d.\n", min, max);
    }
}

/* Returns the position of the employee with this ID, or -1 if not found. */
static int findEmployeeById(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employeeID[i] == id)
        {
            return i;
        }
    }
    return -1;
}

/* Prints all the details of the employee at position i. */
static void printEmployee(int i)
{
    printf("Employee ID: %d\n", employeeID[i]);
    printf("Name: %s\n", employeeName[i]);
    printf("Department: %s\n", department[i]);
    printf("Basic Salary: N$%.2f\n", basicSalary[i]);
    printf("Housing Allowance: N$%.2f\n", housingAllowance[i]);
    printf("Transport Allowance: N$%.2f\n", transportAllowance[i]);
    printf("Total Salary: N$%.2f\n",
           calculateSalary(basicSalary[i], housingAllowance[i], transportAllowance[i]));
}


/* ---------- Public functions (declared in employees.h) ---------- */

/* The Employee Management sub-menu. Loops until the user chooses 4. */
void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          EMPLOYEE MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Search employee by name\n");
        printf("4. Back to main menu\n");

        choice = empReadChoice("Enter your choice: ", 1, 4);

        switch (choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            displayEmployees();
            break;
        case 3:
            searchEmployee();
            break;
        case 4:
            printf("Returning to main menu...\n");
            break;
        }
    } while (choice != 4);
}

/* Asks for every detail of a new employee, validates it and stores it. */
void addEmployee(void)
{
    int id;

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Employee limit reached.\n");
        return;
    }

    printf("\n--- Add Employee ---\n");

    /* The ID must be a positive whole number that is not already used */
    while (1)
    {
        id = empReadId("Enter Employee ID: ");
        if (findEmployeeById(id) == -1)
        {
            break;
        }
        printf("Employee ID %d already exists. Please try again.\n", id);
    }
    employeeID[employeeCount] = id;

    empReadText("Enter Employee Name: ", employeeName[employeeCount]);
    empReadText("Enter Department: ", department[employeeCount]);

    basicSalary[employeeCount] = empReadAmount("Enter Basic Salary: ", 0);
    housingAllowance[employeeCount] = empReadAmount("Enter Housing Allowance: ", 1);
    transportAllowance[employeeCount] = empReadAmount("Enter Transport Allowance: ", 1);

    employeeCount++;

    printf("Employee added successfully!\n");
}

/* Shows every employee with their total salary. */
void displayEmployees(void)
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
        printf("\n");
        printEmployee(i);
    }
}

/* Returns the total salary: basic salary + housing + transport allowance. */
float calculateSalary(float basicSalary,
                      float housingAllowance,
                      float transportAllowance)
{
    return basicSalary + housingAllowance + transportAllowance;
}

/* Finds an employee by their full name and shows their details. */
void searchEmployee(void)
{
    char searchName[TEXT_SIZE];
    int found = 0;
    int i;

    printf("\n--- Search Employee ---\n");

    empReadText("Enter the employee's full name (exact spelling): ", searchName);

    for (i = 0; i < employeeCount; i++)
    {
        if (strcmp(employeeName[i], searchName) == 0)
        {
            printf("\nEmployee found!\n");
            printEmployee(i);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("Employee not found.\n");
    }
}
