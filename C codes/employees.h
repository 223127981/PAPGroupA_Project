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

void addEmployee();
void displayEmployees();
void searchEmployee();
float calculateSalary(float basicSalary, float housingAllowance, float transportAllowance);

#endif