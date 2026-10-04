#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets.h"

/* ---------- Sizes and limits ---------- */
#define ID_LENGTH 10   /* max 9 characters, e.g. "AST001"   */
#define NAME_LENGTH 26 /* max 25 characters                 */
#define TYPE_LENGTH 20
#define DEPT_LENGTH 21 /* max 20 characters                 */
#define CONDITION_LENGTH 12
#define INPUT_LENGTH 100 /* size of the temporary input buffer */
#define TYPE_COUNT 6
#define CONDITION_COUNT 4
#define MAX_ASSET_VALUE 1000000000.0 /* N$1 billion upper limit   */
#define TABLE_WIDTH 99

/* ---------- The asset register (parallel arrays) ----------
 * Asset number i is stored at position i of EVERY array:
 * assetIds[i], assetNames[i], assetTypes[i] ... all describe one asset. */
static char assetIds[MAX_ASSETS][ID_LENGTH];
static char assetNames[MAX_ASSETS][NAME_LENGTH];
static char assetTypes[MAX_ASSETS][TYPE_LENGTH];
static double assetValues[MAX_ASSETS];
static char assetDepartments[MAX_ASSETS][DEPT_LENGTH];
static char assetConditions[MAX_ASSETS][CONDITION_LENGTH];
static int assetCount = 0;

/* Fixed lists the user chooses from */
static char typeList[TYPE_COUNT][TYPE_LENGTH] = {
    "Vehicle", "Computer", "Building", "Equipment", "Office Furniture", "Other"};
static char conditionList[CONDITION_COUNT][CONDITION_LENGTH] = {
    "Excellent", "Good", "Fair", "Poor"};

/* =====================================================================
 *  HELPER FUNCTIONS (only used inside this file)
 * ===================================================================== */

/* Reads one whole line typed by the user and removes the Enter key ('\n'). */
static void readLine(char input[])
{
    int length;
    int ch;

    if (fgets(input, INPUT_LENGTH, stdin) == NULL)
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
        /* The line was longer than the buffer: throw away the rest of it */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
}

/* Returns 1 if the text is empty or only spaces, otherwise 0. */
static int isBlank(char text[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] != ' ' && text[i] != '\t')
        {
            return 0;
        }
    }
    return 1;
}

/* Changes every small letter in text to a capital letter. */
static void toUpperCase(char text[])
{
    int i;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = text[i] - 'a' + 'A';
        }
    }
}

/* Returns 1 if the two texts are the same, ignoring capital/small letters. */
static int sameText(char first[], char second[])
{
    char a[INPUT_LENGTH];
    char b[INPUT_LENGTH];

    strcpy(a, first);
    strcpy(b, second);
    toUpperCase(a);
    toUpperCase(b);

    return strcmp(a, b) == 0;
}

/* Keeps asking until the user types text that is not empty and fits. */
static void readText(char prompt[], char text[], int size)
{
    char input[INPUT_LENGTH];
    int length;

    while (1)
    {
        printf("%s", prompt);
        readLine(input);
        length = strlen(input);

        if (isBlank(input))
        {
            printf("  Error: this field cannot be empty.\n");
        }
        else if (length >= size)
        {
            printf("  Error: too long - maximum %d characters.\n", size - 1);
        }
        else
        {
            strcpy(text, input);
            return;
        }
    }
}

/* Keeps asking until the user types a valid positive amount of money. */
static double readAmount(char prompt[])
{
    char input[INPUT_LENGTH];
    double value;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        readLine(input);

        if (sscanf(input, "%lf %c", &value, &extra) != 1)
        {
            printf("  Error: enter numbers only, without N$ or commas.\n");
        }
        else if (value > 0 && value <= MAX_ASSET_VALUE)
        {
            return value;
        }
        else
        {
            printf("  Error: value must be more than 0 and at most N$%.2f\n",
                   MAX_ASSET_VALUE);
        }
    }
}

/* Keeps asking until the user types a whole number from min to max. */
static int readChoice(char prompt[], int min, int max)
{
    char input[INPUT_LENGTH];
    int choice;
    char extra;

    while (1)
    {
        printf("%s", prompt);
        readLine(input);

        if (sscanf(input, "%d %c", &choice, &extra) == 1 && choice >= min && choice <= max)
        {
            return choice;
        }
        printf("  Error: enter a number from %d to %d.\n", min, max);
    }
}

/* Returns the position of the asset with this ID, or -1 if not found. */
static int findAssetById(char id[])
{
    int i;

    for (i = 0; i < assetCount; i++)
    {
        if (strcmp(assetIds[i], id) == 0)
        {
            return i;
        }
    }
    return -1;
}

/* Copies one asset's details into the next free position of every array. */
static void storeAsset(char id[], char name[], char type[], double value,
                       char department[], char condition[])
{
    strcpy(assetIds[assetCount], id);
    strcpy(assetNames[assetCount], name);
    strcpy(assetTypes[assetCount], type);
    assetValues[assetCount] = value;
    strcpy(assetDepartments[assetCount], department);
    strcpy(assetConditions[assetCount], condition);
    assetCount++;
}

/* Prints a line of dashes. */
static void printLine(int length)
{
    int i;

    for (i = 0; i < length; i++)
    {
        printf("-");
    }
    printf("\n");
}

/* Prints the column headings of the asset table. */
static void printTableHeader(void)
{
    printf("\n%-9s %-25s %-16s %-20s %-9s %15s\n",
           "ID", "Name", "Type", "Department", "Condition", "Value (N$)");
    printLine(TABLE_WIDTH);
}

/* Prints one asset as one row of the table. */
static void printAssetRow(int index)
{
    printf("%-9s %-25s %-16s %-20s %-9s %15.2f\n",
           assetIds[index], assetNames[index], assetTypes[index],
           assetDepartments[index], assetConditions[index], assetValues[index]);
}

/* Shows the asset types as a numbered list; returns the position chosen. */
static int chooseType(void)
{
    int i;

    printf("Asset type:\n");
    for (i = 0; i < TYPE_COUNT; i++)
    {
        printf("  %d. %s\n", i + 1, typeList[i]);
    }
    return readChoice("Choose type: ", 1, TYPE_COUNT) - 1;
}

/* Shows the conditions as a numbered list; returns the position chosen. */
static int chooseCondition(void)
{
    int i;

    printf("Condition:\n");
    for (i = 0; i < CONDITION_COUNT; i++)
    {
        printf("  %d. %s\n", i + 1, conditionList[i]);
    }
    return readChoice("Choose condition: ", 1, CONDITION_COUNT) - 1;
}

/* =====================================================================
 *  PUBLIC FUNCTIONS (declared in assets.h)
 * ===================================================================== */

/* The Asset Management sub-menu. Loops until the user chooses 7. */
void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("            ASSET MANAGEMENT\n");
        printf("========================================\n");
        printf("1. Add a new asset\n");
        printf("2. Display all assets\n");
        printf("3. Search asset by ID\n");
        printf("4. Search assets by department\n");
        printf("5. Search assets by type\n");
        printf("6. Asset value summary\n");
        printf("7. Back to main menu\n");

        choice = readChoice("Enter your choice: ", 1, 7);

        switch (choice)
        {
        case 1:
            addAsset();
            break;
        case 2:
            displayAssets();
            break;
        case 3:
            searchAssetById();
            break;
        case 4:
            searchAssetsByDepartment();
            break;
        case 5:
            searchAssetsByType();
            break;
        case 6:
            assetSummary();
            break;
        case 7:
            printf("Returning to main menu...\n");
            break;
        }
    } while (choice != 7);
}

/* Asks for every detail of a new asset, validates it and stores it. */
void addAsset(void)
{
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
    char department[DEPT_LENGTH];
    double value;
    int typeIndex;
    int conditionIndex;

    if (assetCount >= MAX_ASSETS)
    {
        printf("\nThe register is full (%d assets). Cannot add more.\n", MAX_ASSETS);
        return;
    }

    printf("\n--- Add a New Asset ---\n");

    /* The ID must not already exist */
    while (1)
    {
        readText("Asset ID (e.g. AST007): ", id, ID_LENGTH);
        toUpperCase(id);

        if (findAssetById(id) == -1)
        {
            break;
        }
        printf("  Error: asset ID %s already exists.\n", id);
    }

    readText("Asset name: ", name, NAME_LENGTH);
    typeIndex = chooseType();
    value = readAmount("Purchase value in N$ (e.g. 250000): ");
    readText("Department (e.g. Finance): ", department, DEPT_LENGTH);
    conditionIndex = chooseCondition();

    storeAsset(id, name, typeList[typeIndex], value, department,
               conditionList[conditionIndex]);

    printf("\nAsset %s (%s) added. Total assets: %d\n", id, name, assetCount);
}

/* Shows every asset in a table, with the total value at the bottom. */
void displayAssets(void)
{
    int i;

    if (assetCount == 0)
    {
        printf("\nNo assets have been registered yet.\n");
        return;
    }

    printf("\n--- MUNICIPAL ASSET REGISTER ---\n");
    printTableHeader();

    for (i = 0; i < assetCount; i++)
    {
        printAssetRow(i);
    }

    printLine(TABLE_WIDTH);
    printf("Total assets: %d     Total value: N$%.2f\n",
           assetCount, getTotalAssetValue());
}

/* Finds one asset by its ID and shows all its details. */
void searchAssetById(void)
{
    char id[ID_LENGTH];
    int index;

    readText("\nEnter the asset ID to search for: ", id, ID_LENGTH);
    toUpperCase(id);
    index = findAssetById(id);

    if (index == -1)
    {
        printf("No asset found with ID %s.\n", id);
    }
    else
    {
        printf("\n--- ASSET FOUND ---\n");
        printf("Asset ID       : %s\n", assetIds[index]);
        printf("Name           : %s\n", assetNames[index]);
        printf("Type           : %s\n", assetTypes[index]);
        printf("Department     : %s\n", assetDepartments[index]);
        printf("Condition      : %s\n", assetConditions[index]);
        printf("Purchase value : N$%.2f\n", assetValues[index]);
    }
}

/* Lists all assets that belong to the department the user types. */
void searchAssetsByDepartment(void)
{
    char department[DEPT_LENGTH];
    int i;
    int found = 0;
    double totalValue = 0;

    readText("\nEnter the department to search for: ", department, DEPT_LENGTH);

    for (i = 0; i < assetCount; i++)
    {
        if (sameText(assetDepartments[i], department))
        {
            if (found == 0)
            {
                printTableHeader();
            }
            printAssetRow(i);
            found++;
            totalValue += assetValues[i];
        }
    }

    if (found == 0)
    {
        printf("No assets found for department \"%s\".\n", department);
    }
    else
    {
        printf("%d asset(s) found. Total value: N$%.2f\n", found, totalValue);
    }
}

/* Lists all assets of the type the user picks from the list. */
void searchAssetsByType(void)
{
    int typeIndex;
    int i;
    int found = 0;
    double totalValue = 0;

    printf("\n");
    typeIndex = chooseType();

    for (i = 0; i < assetCount; i++)
    {
        if (strcmp(assetTypes[i], typeList[typeIndex]) == 0)
        {
            if (found == 0)
            {
                printTableHeader();
            }
            printAssetRow(i);
            found++;
            totalValue += assetValues[i];
        }
    }

    if (found == 0)
    {
        printf("No assets of type \"%s\" are registered.\n", typeList[typeIndex]);
    }
    else
    {
        printf("%d asset(s) found. Total value: N$%.2f\n", found, totalValue);
    }
}

/* Calculates totals, average, highest, lowest and condition counts. */
void assetSummary(void)
{
    int i;
    int j;
    int highest = 0;
    int lowest = 0;
    int poorFound = 0;
    int conditionCounts[CONDITION_COUNT] = {0};
    double total;

    if (assetCount == 0)
    {
        printf("\nNo assets have been registered yet.\n");
        return;
    }

    total = getTotalAssetValue();

    for (i = 0; i < assetCount; i++)
    {
        if (assetValues[i] > assetValues[highest])
        {
            highest = i;
        }
        if (assetValues[i] < assetValues[lowest])
        {
            lowest = i;
        }

        for (j = 0; j < CONDITION_COUNT; j++)
        {
            if (strcmp(assetConditions[i], conditionList[j]) == 0)
            {
                conditionCounts[j]++;
            }
        }
    }

    printf("\n--- ASSET VALUE SUMMARY ---\n");
    printf("Total assets         : %d\n", assetCount);
    printf("Total value          : N$%.2f\n", total);
    printf("Average value        : N$%.2f\n", total / assetCount);
    printf("Most valuable asset  : %s (N$%.2f)\n",
           assetNames[highest], assetValues[highest]);
    printf("Least valuable asset : %s (N$%.2f)\n",
           assetNames[lowest], assetValues[lowest]);

    printf("\nAssets by condition:\n");
    for (j = 0; j < CONDITION_COUNT; j++)
    {
        printf("  %-10s: %d\n", conditionList[j], conditionCounts[j]);
    }

    printf("\nAssets in POOR condition (need repair or replacement):\n");
    for (i = 0; i < assetCount; i++)
    {
        if (strcmp(assetConditions[i], "Poor") == 0)
        {
            printf("  %s - %s (%s)\n",
                   assetIds[i], assetNames[i], assetDepartments[i]);
            poorFound++;
        }
    }
    if (poorFound == 0)
    {
        printf("  None\n");
    }
}

/* Returns how many assets are registered (for the Reports module). */
int getAssetCount(void)
{
    return assetCount;
}

/* Adds up the purchase values of all assets and returns the total. */
double getTotalAssetValue(void)
{
    int i;
    double total = 0;

    for (i = 0; i < assetCount; i++)
    {
        total += assetValues[i];
    }
    return total;
}

/* Loads example assets so the system has data to show straight away. */
void loadSampleAssets(void)
{
    if (assetCount > 0)
    {
        return;
    }

    storeAsset("AST001", "Toyota Hilux 2.4 GD-6", "Vehicle", 685000.00,
               "Technical Services", "Good");
    storeAsset("AST002", "Dell OptiPlex Desktop", "Computer", 18500.00,
               "Finance", "Excellent");
    storeAsset("AST003", "Municipal Office Block A", "Building", 12500000.00,
               "Administration", "Fair");
    storeAsset("AST004", "Caterpillar Grader", "Equipment", 3200000.00,
               "Technical Services", "Poor");
    storeAsset("AST005", "Boardroom Table Set", "Office Furniture", 42000.00,
               "Administration", "Good");
    storeAsset("AST006", "HP LaserJet Printer", "Computer", 9800.00,
               "Finance", "Poor");
}
