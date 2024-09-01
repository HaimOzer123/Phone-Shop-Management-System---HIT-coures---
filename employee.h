// Shon Pazarker - 208426890
// Haim Ozer - 316063569

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _EMPLOYEES_H_
#define _EMPLOYEES_H_

#pragma warning(disable:4996)

typedef struct employee {
	char username[32];
	char password[32];
	int accessLevel;
	char fullName[32];
}employee;

void saveEmployees(const employee* employees, int numEmployees) {
	FILE* fp = fopen("employees.bin", "wb");
	if (fp == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	fwrite(&numEmployees, sizeof(int), 1, fp);
	for (int i = 0; i < numEmployees; i++) {
		fwrite(&employees[i], sizeof(employee), 1, fp);
	}

	fclose(fp);
}

int initializeEmployees(employee** employees) {
	FILE* infile = fopen("employees.bin", "rb");
	int i;
	int array_size;
	employee* d_array;
	// Check if the input file exists
	if (!infile) {
		printf("Initialize new file employees\n");
		// If the input file does not exist, create an empty array of structs
		array_size = 1;
		d_array = malloc(array_size * sizeof(employee));
		d_array[0] = (employee){ .username = "Admin", .password = "Admin", .fullName = "Manager_System", .accessLevel = 3 };
		saveEmployees(d_array, array_size);
	}
	else {
		// If the input file exists, read the data from the file and store it in an array of structs
		printf("Loading existing employees file\n");
		fread(&array_size, sizeof(int), 1, infile);
		d_array = malloc(array_size * sizeof(employee));
		for (i = 0; i < array_size; i++) {
			fread(&d_array[i], sizeof(employee), 1, infile);
		}
		fclose(infile);
	}
	*employees = d_array;
	return array_size;
}



void addEmployee(employee** employees, int* numEmployees, employee* newEmployee) {
	int i = 0;
	// Allocate memory for the new employee
	employee* newEmployees = (employee*)malloc(sizeof(employee) * (*numEmployees + 1));
	if (newEmployees == NULL) {
		perror("Error allocating memory");
		exit(0);
	}

	// Check if the employee already exists
	for (i = 0; i < *numEmployees; i++) {
		if (strcmp((*employees)[i].username, newEmployee->username) == 0) {
			printf("employee already exist");
			exit(0);
		}
	}

	// Copy the old employees to the new array
	for (i = 0; i < *numEmployees; i++) {
		newEmployees[i] = (*employees)[i];
	}

	// Add the new employee to the array
	newEmployees[*numEmployees] = *newEmployee;

	// Free the old array
	free(*employees);

	// Update the pointer to the array
	*employees = newEmployees;

	// Update the number of employees
	(*numEmployees)++;
}

int removeEmployee(employee** employees, int* numEmployees, const char* username) {
	// Allocate memory for the new employee
	employee* newEmployees = (employee*)malloc(sizeof(employee) * (*numEmployees - 1));
	if (newEmployees == NULL) {
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	// Check if the employee exists
	int found = 0;
	for (int i = 0; i < *numEmployees; i++) {
		if (strcmp((*employees)[i].username, username) == 0) {
			found = 1;
			break;
		}
	}

	// If the employee doesn't exist, return failure
	if (!found) {
		return 0;
	}

	// Copy the old employees to the new array
	int j = 0;
	for (int i = 0; i < *numEmployees; i++) {
		if (strcmp((*employees)[i].username, username) != 0) {
			newEmployees[j] = (*employees)[i];
			j++;
		}
	}

	// Free the old array
	free(*employees);

	// Update the pointer to the array
	*employees = newEmployees;

	// Update the number of employees
	(*numEmployees)--;

	// Return success
	return 1;
}


employee* tryLogin(const char* username, const char* password, int employeesSize, const employee* employees) {
	for (int i = 0; i < employeesSize; i++) {
		if (strcmp(username, employees[i].username) == 0 && strcmp(password, employees[i].password) == 0) {
			return &employees[i];
		}
	}
	return NULL;
}

employee* loginPrompt(int employeesSize, const employee* employees, int isSkip) {
	int tries = 0;
	char username[32] = "Admin";
	char password[32] = "Admin";
	employee* loggedInEmployee = NULL;
	while (tries < 3 && loggedInEmployee == NULL) {
		if (isSkip == 0) {
			// Prompt the user for a username and password
			printf("Enter username: ");
			scanf("%s", username);
			printf("Enter password: ");
			scanf("%s", password);
		}

		// Try to login with the provided username and password
		loggedInEmployee = tryLogin(username, password, employeesSize, employees);
		if (loggedInEmployee == NULL) {
			printf("Login failed.\n");
		}
		tries++;
	}
	if (loggedInEmployee == NULL) {
		printf("You have exceeded the maximum number of tries.\n");
		exit(0);
	}

	//clear console
	system("cls");
	char log[100];
	snprintf(log, sizeof(log), "%s logged in successfully", username);
	logMessage(&log);

	printf("Login successful!\n");
	printf("Access level: %d\n", loggedInEmployee->accessLevel);
	printf("Full name: %s\n\n\n", loggedInEmployee->fullName);

	return loggedInEmployee;
}

employee* searchEmployeeByFullName(const char* fullName, int employeesSize, const employee* employees) {
	for (int i = 0; i < employeesSize; i++) {
		if (strcmp(fullName, employees[i].fullName) == 0) {
			return &employees[i];
		}
	}
	return NULL;
}

employee* searchEmployeeByUsername(const char* username, int employeesSize, const employee* employees) {
	for (int i = 0; i < employeesSize; i++) {
		if (strcmp(username, employees[i].username) == 0) {
			return &employees[i];
		}
	}
	return NULL;
}

void printEmployee(const employee* employee) {
	printf("----------------\n");
	printf("Username: %s\n", employee->username);
	printf("Full name: %s\n", employee->fullName);
	printf("Access level: %d\n", employee->accessLevel);
	printf("Password: %s\n", employee->password);
}


#endif