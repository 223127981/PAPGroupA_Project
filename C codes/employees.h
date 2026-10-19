/*
 * employees.h - Employee Management module
 * Municipal Financial Management System (MFMS) - PAP521S Project A, Group 5
 * Author: Alfeus Rosalia (224009893)
 */

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

extern int employeeID[MAX_EMPLOYEES];
extern char employeeName[MAX_EMPLOYEES][50];
extern char department[MAX_EMPLOYEES][50];
extern float basicSalary[MAX_EMPLOYEES];
extern float housingAllowance[MAX_EMPLOYEES];
extern float transportAllowance[MAX_EMPLOYEES];
extern int employeeCount;

/* Sub-menu: main.c calls this when the user picks "Employee Management" */
void employeeMenu(void);

void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
float calculateSalary(float basicSalary, float housingAllowance, float transportAllowance);

#endif
