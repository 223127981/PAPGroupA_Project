#ifndef ASSETS_H
#define ASSETS_H

#define MAX_ASSETS 100 /* the register can hold up to 100 assets */

/* Sub-menu: main.c calls this when the user picks "Asset Management" */
void assetMenu(void);

/* Asset operations */
void addAsset(void);
void displayAssets(void);
void searchAssetById(void);
void searchAssetsByDepartment(void);
void searchAssetsByType(void);
void assetSummary(void);

/* Functions the Reports module can call */
int getAssetCount(void);
double getTotalAssetValue(void);

/* Puts a few example assets in the register (for testing and the demo) */
void loadSampleAssets(void);

#endif
