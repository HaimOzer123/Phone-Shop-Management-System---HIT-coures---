// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customerItem.h"
#include "item.h"

#ifndef _CUSTOMER_ITEM_PROMPTS_H_
#define _CUSTOMER_ITEM_PROMPTS_H_

#pragma warning(disable:4996)

void addCustomerItemPrompt(customerItem** customerItems, int* size) {
	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);
	printf("Enter item id: ");
	scanf("%d", &itemId);
	addCustomerItem(customerItems, size, customerId, itemId);
	
	char log[100];
	snprintf(log, sizeof(log), "%d Added item for sale successfully", itemId);
	logMessage(&log);
}

void deleteCustomerItemPrompt(customerItem** customerItems, int* size) {
	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);
	printf("Enter item id: ");
	scanf("%d", &itemId);
	removeCustomerItem(customerItems, size, customerId, itemId);
	
	char log[100];
	snprintf(log, sizeof(log), "%d Remove item for sale successfully", itemId);
	logMessage(&log);
}

void viewAllCustomerItemsPrompt(customerItem* customerItems, int size, item* root, customer* customers) {
	system("cls");
	
	viewAllCustomerItems(customerItems, size, root, customers);
}
#endif