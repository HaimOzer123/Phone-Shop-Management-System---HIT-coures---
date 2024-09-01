// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"
#include "logs.h"

#ifndef _EMPLOYEES_PROMPTS_H_
#define _EMPLOYEES_PROMPTS_H_

#pragma warning(disable:4996)

void createEmployeePrompt(employee** employees, int* numEmployees) {
	system("cls");
	employee* newEmployee = malloc(sizeof(employee));
	printf("Enter username: ");
	scanf("%s", newEmployee->username);
	printf("Enter password: ");
	scanf("%s", newEmployee->password);
	printf("Enter full name: ");
	scanf("%s", newEmployee->fullName);
	printf("Enter access level: ");
	scanf("%d", &newEmployee->accessLevel);
	addEmployee(employees, numEmployees, newEmployee);
	
	char log[100];
	snprintf(log, sizeof(log), "%s created employee successfully", newEmployee->username);
	logMessage(&log);
	saveEmployees(*employees, *numEmployees);
}

void removeEmployeePrompt(employee** employees, int* numEmployees) {
	system("cls");
	char username[32];
	printf("Enter username: ");
	char log[100];
	scanf("%s", username);
	int isSuccessRemove = removeEmployee(employees, numEmployees, username);
	if (isSuccessRemove == 1) {
		snprintf(log, sizeof(log), "%s removed employee successfully", username);
		logMessage(&log);
		saveEmployees(*employees, *numEmployees);
	}
	else {
		printf("Employee not found\n");
	}

}

void searchEmployeeByFullNamePrompt(employee* employees, int numEmployees) {
	system("cls");
	char fullName[32];
	printf("Enter full name: ");
	scanf("%s", fullName);
	employee* foundEmployee = searchEmployeeByFullName(fullName, numEmployees, employees);
	if (foundEmployee == NULL) {
		printf("Employee not found\n");
	}
	else {
		printf("Employee found\n");
		printEmployee(foundEmployee);
	}
}

void searchEmployeeByUsernamePrompt(employee* employees, int numEmployees) {
	system("cls");
	char username[32];
	printf("Enter username: ");
	scanf("%s", username);
	employee* foundEmployee = searchEmployeeByUsername(username, numEmployees, employees);
	if (foundEmployee == NULL) {
		printf("Employee not found\n");
	}
	else {
		printf("Employee found\n");
		printEmployee(foundEmployee);
	}
}

void viewAllEmployeesPrompt(const employee* employees, int employeesSize) {
	system("cls");
	printf("All employees:\n");
	for (int i = 0; i < employeesSize; i++) {
		printEmployee(&employees[i]);
	}
}

void employeePrompts(const employee** employees, int* employeesSize, int accessLevel) {
	system("cls");
	int choice;
	do {
		printf("-----------------\n\n\n\n");
		printf("1. View all employees\n");
		printf("2. Search employee by full name\n");
		printf("3. Search employee by username\n");
		if (accessLevel == 2 || accessLevel == 3) {
			printf("4. Create employee\n");
		}
		if (accessLevel == 3) {
			printf("5. Remove employee\n");
		}
		printf("0. Back\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			break;
		case 1:
			viewAllEmployeesPrompt(*employees, *employeesSize);
			break;
		case 2:
			searchEmployeeByFullNamePrompt(*employees, *employeesSize);
			break;
		case 3:
			searchEmployeeByUsernamePrompt(*employees, *employeesSize);
			break;
		case 4:
			if (accessLevel == 2 || accessLevel == 3) {
				createEmployeePrompt(employees, employeesSize);
			}
			else {
				printf("Invalid choice\n");
			}
			break;
		case 5:
			if (accessLevel == 3) {
				removeEmployeePrompt(employees, employeesSize);
			}
			else {
				printf("Invalid choice\n");
			}
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice != 0);

}
#endif