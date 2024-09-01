// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

#ifndef _CUSTOMER_ITEM_H_
#define _CUSTOMER_ITEM_H_

#pragma warning(disable:4996)

typedef struct customerItem {
	int generatedId;
	int customerId;
	int itemId;
	time_t purchasedDate;
} customerItem;

typedef struct listCustomerItem {
	customerItem data;
	struct listCustomerItem* next;
} listCustomerItem;

void viewAllCustomerItems(customerItem* customerItems, int size, nodeItem* root, nodeCustomer* customers) {
	for (int i = 0; i < size; i++) {
		nodeItem* item = searchByIdItem(root, customerItems[i].itemId);
		printItem(&item->data);
		customer* customer = searchCustomerById(customers, customerItems[i].customerId);
		printCustomer(customer);
		printf("Purchased Date: %s\n", ctime(&customerItems[i].purchasedDate));
		printf("-------------------------------------------------\n");

	}
}

void addCustomerItem(customerItem** customerItems, int* size, int customerId, int itemId) {
	customerItem* newCustomerItem = (customerItem*)malloc(sizeof(customerItem));
	newCustomerItem->generatedId = *size + 1;
	newCustomerItem->customerId = customerId;
	newCustomerItem->itemId = itemId;
	newCustomerItem->purchasedDate = time(NULL);

	(*size)++;
	*customerItems = (customerItem*)realloc(*customerItems, *size * sizeof(customerItem));
	(*customerItems)[*size - 1] = *newCustomerItem;
}

void removeCustomerItem(customerItem** customerItems, int* size, int customerId, int itemId) {
	for (int i = 0; i < *size; i++) {
		if ((*customerItems)[i].customerId == customerId && (*customerItems)[i].itemId == itemId) {
			for (int j = i; j < *size - 1; j++) {
				(*customerItems)[j] = (*customerItems)[j + 1];
			}
			(*size)--;
			*customerItems = (customerItem*)realloc(*customerItems, *size * sizeof(customerItem));
			return;
		}
	}
}

void saveCustomerItems(const customerItem* customerItems, int numCustomerItems) {
	FILE* fp = fopen("customerItem.bin", "wb");
	if (fp == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	fwrite(&numCustomerItems, sizeof(int), 1, fp);
	for (int i = 0; i < numCustomerItems; i++) {
		fwrite(&customerItems[i], sizeof(customerItem), 1, fp);
	}

	fclose(fp);
}

customerItem* searchCustomerItemByCustomerIdAndItemId(customerItem* customerItems, int size, int customerId, int itemId) {
	for (int i = 0; i < size; i++) {
		if (customerItems[i].customerId == customerId && customerItems[i].itemId == itemId) {
			return &customerItems[i];
		}
	}
	return NULL;
}

int initializeCustomerItems(customerItem** customerItems) {
	FILE* infile = fopen("customerItem.bin", "rb");
	int i;
	int array_size;
	customerItem* d_array;
	if (!infile) {
		printf("Initialize new file customerItem\n");
		array_size = 0;
		d_array = malloc(array_size * sizeof(customerItem));
	}
	else {
		printf("Loading existing customerItem file\n");
		fread(&array_size, sizeof(int), 1, infile);
		d_array = malloc(array_size * sizeof(customerItem));
		for (i = 0; i < array_size; i++) {
			fread(&d_array[i], sizeof(customerItem), 1, infile);
		}
		fclose(infile);
	}
	*customerItems = d_array;
	return array_size;
}

int isPurchaseDateInLast14Days(customerItem* customerItems, int size, int customerId) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (customerItems[i].customerId == customerId) {
			if (customerItems[i].purchasedDate > time(NULL) - 14 * 24 * 60 * 60) {
				count++;
			}
		}
	}
	return count;
}

int getNumberOfItemsOfCustomer(customerItem* customerItems, int size, int customerId) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (customerItems[i].customerId == customerId) {
			count++;
		}
	}
	return count;
}
#endif