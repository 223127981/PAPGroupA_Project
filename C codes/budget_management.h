#ifndef BUDGET_MANAGEMENT_H
#define BUDGET_MANAGEMENT_H

#define MAX_DEPTS 50
#define NAME_LEN 50

typedef struct
{
    char name[NAME_LEN];
    double allocated;
    double expenditure;
} Department;

extern Department budgets[MAX_DEPTS];
extern int deptCount;

double calculateRemaining(double allocated, double expenditure);
void displayAll(void);
void displayExceeded(void);
void budgetMenu(void);

#endif