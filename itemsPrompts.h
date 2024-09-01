// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"
#include "item.h"

#ifndef _ITEMS_PROMPTS_H
#define _ITEMS_PROMPTS_H
#pragma warning(disable:4996)

void createItemPrompt(nodeItem** items) {
	system("cls");
	item* data = malloc(sizeof(item));
	printf("Enter item id: ");
	scanf("%d", &data->id);
	printf("Enter item name: ");
	scanf("%s", data->phoneName);
	printf("Enter item brand: ");
	scanf("%s", data->brand);
	printf("Enter item price: ");
	scanf("%f", &data->price);
	printf("Enter item is new (0 for new , 1 for used): ");
	scanf("%d", &data->isNew);
	data->date = time(NULL);


	addItem(items, data);

	char log[100];
	snprintf(log, sizeof(log), "%s created item successfully", data->phoneName);
	logMessage(&log);
	saveItems(*items);
}

void deleteItemPrompt(nodeItem** items) {
	system("cls");
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	removeItem(items, id);

	char log[100];
	snprintf(log, sizeof(log), "%d removed item successfully", id);
	logMessage(&log);
	saveItems(*items);
}

void viewAllItemsPrompt(nodeItem* items) {
	system("cls");
	printTreeItems(items);
}

void searchItemByIdPrompt(nodeItem* items) {
	system("cls");
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	nodeItem* result = searchByIdItem(items, id);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printItem(&result->data);
	}
}

void searchItemByPhoneNamePrompt(nodeItem* items) {
	system("cls");
	char phoneName[32];
	printf("Enter phone name: ");
	scanf("%s", phoneName);
	nodeItem* result = searchByPhoneNameItem(items, phoneName);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printItem(&result->data);
	}
}

void searchItemByBrandPrompt(nodeItem* items) {
	system("cls");
	char brand[32];
	printf("Enter brand: ");
	scanf("%s", brand);
	listItem* result = searchByBrandItems(items, brand);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		while (result != NULL) {
			printItem(&result->data);
			result = result->next;
		}
	}
}

void searchItemByIsNewPrompt(nodeItem* items) {
	system("cls");
	int isNew;
	printf("Enter isNew: ");
	scanf("%d", &isNew);
	listItem* result = searchByIsNewItem(items, isNew);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		while (result != NULL) {
			printItem(&result->data);
			result = result->next;
		}
	}
}

void updateItemPrompt(nodeItem** items) {
	system("cls");
	int id;
	printf("Enter id: ");
	scanf("%d", &id);
	nodeItem* result = searchByIdItem(*items, id);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		printf("Item found: %d, %s, %s, %f, %d, %ld\n", result->data.id, result->data.phoneName, result->data.brand, result->data.price, result->data.isNew, result->data.date);
		printf("Enter new item name: ");
		scanf("%s", result->data.phoneName);
		printf("Enter new item brand: ");
		scanf("%s", result->data.brand);
		printf("Enter new item price: ");
		scanf("%f", &result->data.price);
		printf("Enter item is new (0 for new , 1 for used): ");
		scanf("%d", &result->data.isNew);

		char log[100];
		snprintf(log, sizeof(log), "%s updated item successfully", result->data.phoneName);
		logMessage(&log);
		saveItems(*items);
	}
}

void searchItemByDatePrompt(nodeItem* items) {
	system("cls");
	int day, month, year;
	printf("Enter day: ");
	scanf("%d", &day);
	printf("Enter month: ");
	scanf("%d", &month);
	printf("Enter year: ");
	scanf("%d", &year);
	int isAbove;
	printf("Enter isAbove: ");
	scanf("%d", &isAbove);

	struct tm tm;
	memset(&tm, 0, sizeof(struct tm));
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;

	time_t date = mktime(&tm);
	listItem* result = searchByDateItems(items, date, isAbove);
	if (result == NULL) {
		printf("Item not found\n");
	}
	else {
		while (result != NULL) {
			printItem(&result->data);
			result = result->next;
		}
	}
}

void itemPrompts(nodeItem** root, int accessLevel) {
	system("cls");
	int choice;
	do {
		printf("-----------------\n\n\n\n");
		printf("1. View all items\n");
		printf("2. Create item\n");
		printf("3. Search item by id\n");
		printf("4. Search item by phone name\n");
		printf("5. Search item by brand\n");
		printf("6. Search item by isNew\n");
		printf("7. Search item by created date\n");
		if (accessLevel == 2 || accessLevel == 3) {
			printf("8. Update item\n");
		}
		if (accessLevel == 3) {
			printf("9. Delete item\n");
		}
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			viewAllItemsPrompt(*root);
			break;
		case 2:
			createItemPrompt(root);
			break;
		case 3:
			searchItemByIdPrompt(*root);
			break;
		case 4:
			searchItemByPhoneNamePrompt(*root);
			break;
		case 5:
			searchItemByBrandPrompt(*root);
			break;
		case 6:
			searchItemByIsNewPrompt(*root);
			break;
		case 7:
			searchItemByDatePrompt(*root);
			break;
		case 8:
			if (accessLevel == 2 || accessLevel == 3) {
				updateItemPrompt(root);
			}
			else {
				printf("Invalid choice\n");
			}
			break;
		case 9:
			if (accessLevel == 3) {
				deleteItemPrompt(root);
			}
			else {
				printf("Invalid choice\n");
			}
			break;
		case 0:
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);
}

#endif