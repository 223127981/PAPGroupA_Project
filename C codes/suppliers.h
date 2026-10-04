#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define MAX_NAME 100
#define MAX_CONTACT 100

typedef struct
{
    char name[MAX_NAME];
    char contact[MAX_CONTACT];
    char service[MAX_NAME];
    int isActive;
} Supplier;

extern Supplier suppliers[MAX_SUPPLIERS];
extern int supplierCount;

void addSupplier(void);
void displayAllSuppliers(void);
void searchSupplier(void);
void handleSupplierMenu(void);

#endif