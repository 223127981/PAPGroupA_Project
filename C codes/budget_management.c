#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "budget_management.h"

Department budgets[MAX_DEPTS];
int deptCount = 0;

void readLine(const char *prompt, char *buffer, int size)
{
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL)
    {
        printf("\nInput ended. Exiting.\n");
        exit(0);
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

double calculateRemaining(double allocated, double expenditure)
{
    return allocated - expenditure;
}

const char *getStatus(double allocated, double expenditure)
{
    if (expenditure <= allocated)
        return "WITHIN BUDGET";
    else
        return "EXCEEDED BUDGET";
}

void readName(const char *prompt, char *name)
{
    while (1)
    {
        readLine(prompt, name, NAME_LEN);
        if (strlen(name) > 0)
            return;
        printf("  Error: Name cannot be empty.\n");
    }
}

double readAmount(const char *prompt)
{
    char text[100];
    char *end;
    double amount;

    while (1)
    {
        readLine(prompt, text, sizeof(text));
        amount = strtod(text, &end);

        if (end == text || *end != '\0')
            printf("  Error: Enter a valid number.\n");
        else if (amount <= 0)
            printf("  Error: Amount must be greater than zero.\n");
        else
            return amount;
    }
}

int findDepartment(const char *name)
{
    int i;

    for (i = 0; i < deptCount; i++)
    {
        if (strcmp(budgets[i].name, name) == 0)
            return i;
    }

    return -1;
}

void addBudget(void)
{
    char name[NAME_LEN];

    if (deptCount == MAX_DEPTS)
    {
        printf("  Error: Maximum number of departments reached.\n");
        return;
    }

    readName("Department name: ", name);

    if (findDepartment(name) != -1)
    {
        printf("  Error: %s already has a budget.\n", name);
        return;
    }

    strcpy(budgets[deptCount].name, name);
    budgets[deptCount].allocated = readAmount("Allocated budget (N$): ");
    budgets[deptCount].expenditure = 0.0;
    deptCount++;

    printf("  Budget saved for %s.\n", name);
}

void addExpenditure(void)
{
    char name[NAME_LEN];
    int index;
    double amount, remaining;

    readName("Department name: ", name);
    index = findDepartment(name);

    if (index == -1)
    {
        printf("  Error: Department not found.\n");
        return;
    }

    amount = readAmount("Expenditure (N$): ");
    budgets[index].expenditure += amount;

    remaining = calculateRemaining(
        budgets[index].allocated,
        budgets[index].expenditure);

    printf("  Remaining budget: N$%.2f\n", remaining);

    if (remaining < 0)
        printf("  WARNING: %s has EXCEEDED its budget!\n", name);
}

void displayDepartment(Department d)
{
    printf("\nDepartment: %s\n", d.name);
    printf("Allocated Budget: N$%.2f\n", d.allocated);
    printf("Expenditure: N$%.2f\n", d.expenditure);
    printf("Remaining Budget: N$%.2f\n",
           calculateRemaining(d.allocated, d.expenditure));
    printf("Status: %s\n",
           getStatus(d.allocated, d.expenditure));
}

void displayAll(void)
{
    int i;

    if (deptCount == 0)
    {
        printf("  No budgets entered yet.\n");
        return;
    }

    for (i = 0; i < deptCount; i++)
        displayDepartment(budgets[i]);
}

void displayExceeded(void)
{
    int i, found = 0;

    printf("\nDepartments over budget:\n");

    for (i = 0; i < deptCount; i++)
    {
        if (budgets[i].expenditure > budgets[i].allocated)
        {
            printf("  %s - over by N$%.2f\n",
                   budgets[i].name,
                   budgets[i].expenditure - budgets[i].allocated);
            found = 1;
        }
    }

    if (!found)
        printf("  None. All departments are within budget.\n");
}

void budgetMenu(void)
{
    char choice[10];

    do
    {
        printf("\n===== BUDGET MANAGEMENT =====\n");
        printf("1. Enter departmental budget\n");
        printf("2. Enter expenditure\n");
        printf("3. Display budget information\n");
        printf("4. Show departments over budget\n");
        printf("0. Exit\n");

        readLine("Choose: ", choice, sizeof(choice));

        if (strcmp(choice, "1") == 0)
            addBudget();
        else if (strcmp(choice, "2") == 0)
            addExpenditure();
        else if (strcmp(choice, "3") == 0)
            displayAll();
        else if (strcmp(choice, "4") == 0)
            displayExceeded();
        else if (strcmp(choice, "0") == 0)
            printf("Goodbye.\n");
        else
            printf("  Invalid option.\n");

    } while (strcmp(choice, "0") != 0);
}
