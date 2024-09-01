// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "customerItem.h"
#include "customer.h"

#ifndef _SHOP_H_
#define _SHOP_H_

#pragma warning(disable:4996)


void buyPrompt(nodeCustomer** customers, nodeItem** items, customerItem** customerItems, int* size) {
	system("cls");
	printf("All items:\n");
	viewAllItemsPrompt(*items);
	printf("All customers:\n");
	viewAllCustomersPrompt(*customers);

	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);
	int numberOfItemsBought = getNumberOfItemsOfCustomer(*customerItems, *size, customerId);
	if (numberOfItemsBought >= 3) {
		printf("Customer has already bought 3 items\n");
		return;
	}

	nodeCustomer* customer = searchCustomerById(*customers, customerId);
	if (customer == NULL) {
		printf("Wrong customer id");
		return;
	}
	printf("Enter item id: ");
	scanf("%d", &itemId);

	nodeItem* item = searchByIdItem(*items, itemId);
	if (item == NULL) {
		printf("Wrong item id");
		return;
	}
	addCustomerItem(customerItems, size, customerId, itemId);
	saveCustomerItems(*customerItems, *size);
}

void refundPrompt(nodeCustomer** customers, nodeItem** items, customerItem** customerItems, int* size) {
	system("cls");

	viewAllCustomerItemsPrompt(*customerItems, *size, *items, *customers);
	int customerId;
	int itemId;
	printf("Enter customer id: ");
	scanf("%d", &customerId);

	nodeCustomer* customer = searchCustomerById(*customers, customerId);
	if (customer == NULL) {
		printf("Wrong customer id");
		return;
	}
	printf("Enter item id: ");
	scanf("%d", &itemId);
	
	nodeItem* item = searchByIdItem(*items, itemId);
	if (item == NULL) {
		printf("Wrong item id");
		return;
	}
	
	customerItem* customerItem = searchCustomerItemByCustomerIdAndItemId(*customerItems, *size, customerId, itemId);
	if (customerItem == NULL) {
		printf("Customer didn't buy this item");
		return;
	}
	
	if (isPurchaseDateInLast14Days(*customerItems, *size, customerId)) {
		removeCustomerItem(customerItems, size, customerId, itemId);
		saveCustomerItems(*customerItems, *size);
		printf("Refund successfully!\n");
	}
	else {
		printf("Can't refund because purchase date is not in last 14 days\n");
	}
}

void shopPrompts(nodeCustomer** customers, nodeItem** items, customerItem** customerItems, int* customerItemsSize) {
	system("cls");
	int choice;
	do {
		printf("-----------------\n\n\n\n");
		printf("1. View all sales\n");
		printf("2. Sell an item\n");
		printf("3. Refund an item\n");
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			viewAllCustomerItemsPrompt(*customerItems, *customerItemsSize, *items, *customers);
			break;
		case 2:
			buyPrompt(customers, items, customerItems, customerItemsSize);
			break;
		case 3:
			refundPrompt(customers, items, customerItems, customerItemsSize);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}
#endif