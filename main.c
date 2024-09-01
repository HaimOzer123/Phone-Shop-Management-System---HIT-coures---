// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#include <stdio.h>
#include <stdlib.h>
#include "logs.h"
#include "employee.h"
#include "employeePrompts.h"
#include "item.h"
#include "itemsPrompts.h"
#include "customer.h"
#include "customersPrompts.h"
#include "customerItemPrompots.h"
#include "customerItem.h"
#include "shopPrompts.h"

void prompts(nodeItem** items, nodeCustomer** customers, employee** employees, int* employeeSize, customerItem** customerItems, int* customerItemsSize, int accessLevel) {
	system("cls");
	int choice;
	do {
		printf("Choose the option you want to work on:\n");
		printf("1. Employees\n");
		printf("2. Items\n");
		printf("3. Customers\n");
		printf("4. Shop\n");
		printf("0. Exit\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			employeePrompts(employees, employeeSize, accessLevel);
			break;
		case 2:
			itemPrompts(items, accessLevel);
			break;
		case 3:
			customerPrompts(customers, accessLevel);
			break;
		case 4:
			shopPrompts(customers, items, customerItems, customerItemsSize);
			break;
		case 0:
			exit(0);
			break;
		default:
			printf("Wrong choice\n");
			break;
		}
	} while (choice != 0);
}

int main(int argc, char* argv[]) {
	initializeLogs();
	employee* employees;
	int employeeSize = initializeEmployees(&employees);
	employee* loggedEmployee = loginPrompt(employeeSize, employees, 0);
	nodeItem* items = initializeItems();
	nodeCustomer* customers;
	initializeCustomers(&customers);
	customerItem* customerItems;
	saveCustomers(customers);
	int customerItemsSize = initializeCustomerItems(&customerItems);
	prompts(&items, &customers, &employees, &employeeSize, &customerItems, &customerItemsSize, loggedEmployee->accessLevel);

	free(employees);
	free(customerItems);
	freeTreeItems(items);
	freeCustomers(customers);
	
	return 0;
}