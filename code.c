#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string>
#include<windows.h>
#pragma warning(disable:4996)
struct manager
{
	char organ[50];
	int access_manager;
	int people_manager;
	long double reward_manager;
};
struct header
{
	char part[50];
	int access_header;
	int people_header;
	long double reward_header;
};
struct employee
{
	char emp_num[50];
	long double punish;
	int member;
};
typedef struct members
{
	int group;
	std::string name;
	std::string family;
	char num[11];
	char birthday[12];
	long double salary;
	long double money;
	int hour;
	int hardship;
	struct manager manager;
	struct header header;
	struct employee employee;
	struct members *ptr;
};
members *temp = NULL, *push = NULL, *top = NULL;
std::string name, family;
char num[11], birthday[12], organ[50], part[50], emp_num[50];
int group, hour, hardship, access_manager, people_manager, access_header, people_header, member;
long double salary, reward_manager, reward_header, punish, money;
void push_member() {
	temp = new members;
	temp->group = group;
	temp->name = name.c_str();
	temp->family = family.c_str();
	strcpy(temp->num, num);
	strcpy(temp->birthday, birthday);
	temp->salary = salary;
	temp->hour = hour;
	temp->money = money;
	temp->hardship = hardship;
	strcpy(temp->manager.organ, organ);
	temp->manager.access_manager = access_manager;
	temp->manager.people_manager = people_manager;
	temp->manager.reward_manager = reward_manager;
	strcpy(temp->header.part, part);
	temp->header.access_header = access_header;
	temp->header.people_header = people_header;
	temp->header.reward_header = reward_header;
	strcpy(temp->employee.emp_num, emp_num);
	temp->employee.member = member;
	temp->employee.punish = punish;
	temp->ptr = NULL;
	if (top == NULL)
		top = temp;
	else {
		for (push = top; push->ptr != NULL; push = push->ptr);
		push->ptr = temp;
	}
}
int search(char num[]) {
	for (temp = top; temp != NULL&&strcmp(temp->num, num) != 0; temp = temp->ptr);
	if (temp == NULL)
		return -1;
	else
		return 1;
}
void delete_member(char num[]) {
	for (temp = top, push = NULL; temp != NULL&&strcmp(temp->num, num) != 0; push = temp, temp = temp->ptr);
	if (temp == NULL)
		printf("Not exist.\n");
	else if (temp == top) {
		top = temp->ptr;
		free(temp);
	}
	else {
		push->ptr = temp->ptr;
		free(temp);
	}
}
void print(char num[]) {
	for (temp = top; temp != NULL&&strcmp(temp->num, num) != 0; temp = temp->ptr);
	if (temp == NULL)
		printf("Not exist.\n");
	else {
		printf("name: %s\n", temp->name.c_str());
		printf("last name: %s\n", temp->family.c_str());
		printf("national number: %s\n", temp->num);
		printf("bithday: %s\n", temp->birthday);
		printf("salary: %llf\n", temp->salary);
		printf("working hours per month: %d\n", temp->hour);
		printf("cost of work per hour: %llf\n", temp->money);
		printf("hardship: %d\n", temp->hardship);
		if (temp->group == 1) {
			printf("name of organ: %s\n", temp->manager.organ);
			printf("access: %d\n", temp->manager.access_manager);
			printf("number of people in organ: %d\n", temp->manager.people_manager);
			printf("reward: %llf\n", temp->manager.reward_manager);
		}
		else if (temp->group == 2) {
			printf("name of part: %s\n", temp->header.part);
			printf("access: %d\n", temp->header.access_header);
			printf("number of people in part: %d\n", temp->header.people_header);
			printf("reward: %llf\n", temp->header.reward_header);
		}
		else if (temp->group == 3) {
			printf("employee number: %s\n", temp->employee.emp_num);
			printf("punish: %llf\n", temp->employee.punish);
			printf("number of familei's member: %d\n", temp->employee.member);
		}
	}
}
long double salary_mambers(char num[]) {
	for (temp = top; temp != NULL&&strcmp(temp->num, num) != 0; temp = temp->ptr);
	if (temp == NULL)
		return -1;
	else {
		if (temp->group == 1)
			return (temp->manager.reward_manager * 2) + (temp->hardship*temp->money*temp->hour);
		if (temp->group == 2)
			return temp->header.reward_header + (temp->hardship*temp->money*temp->hour);
		if (temp->group == 3)
			return (temp->hardship*temp->money*temp->hour) - temp->employee.punish;
	}
}
void write(void) {
	FILE *pointer;
	pointer = fopen("members.txt", "w");
	for (temp = top; temp != NULL; temp = temp->ptr) {
		fprintf(pointer, "%d,%s,%s,%s,%s,%llf,%d,%llf,%d,", temp->group,temp->name.c_str(),temp->family.c_str(),temp->num,temp->birthday,temp->salary,temp->hour,temp->money,temp->hardship);
		if (temp->group == 1)
			fprintf(pointer, "%s,%d,%d,%llf", temp->manager.organ, temp->manager.access_manager, temp->manager.people_manager, temp->manager.reward_manager);
		else if (temp->group == 2)
			fprintf(pointer, "%s,%d,%d,%llf", temp->header.part, temp->header.access_header, temp->header.people_header, temp->header.reward_header);
		else if (temp->group == 3)
			fprintf(pointer, "%s,%llf,%d", temp->employee.emp_num, temp->employee.punish, temp->employee.member);
		fprintf(pointer, "\n");
	}
	fclose(pointer);
}
int main() {
	char ch, edit[20];
	int x;
	FILE *pointer;
	char temp1[300] = "";
	pointer = fopen("members.txt", "r");
	while (1) {
		fgets(temp1, 300, pointer);
		if (strcmp(temp1,"")==0)
			break;
		group = atoi(strtok(temp1, ","));
		name = strtok(NULL, ",");
		family = strtok(NULL, ",");
		strcpy(num, strtok(NULL, ","));
		strcpy(birthday, strtok(NULL, ","));
		salary = atof(strtok(NULL, ","));
		hour = atoi(strtok(NULL, ","));
		money = atof(strtok(NULL, ","));
		hardship = atoi(strtok(NULL, ","));
		memset(organ, NULL, sizeof(organ));
		access_manager = -1;
		people_manager = -1;
		reward_manager = -1;
		memset(part, NULL, sizeof(part));
		access_header = -1;
		people_header = -1;
		reward_header = -1;
		memset(emp_num, NULL, sizeof(emp_num));
		punish = -1;
		member = -1;
		if (group == 1) {
			strcpy(organ, strtok(NULL, ","));
			access_manager = atoi(strtok(NULL, ","));
			people_manager = atoi(strtok(NULL, ","));
			reward_manager = atof(strtok(NULL, ","));
		}
		if (group == 2) {
			strcpy(part, strtok(NULL, ","));
			access_header = atoi(strtok(NULL, ","));
			people_header = atoi(strtok(NULL, ","));
			reward_header = atof(strtok(NULL, ","));
		}
		if (group == 3) {
			strcpy(emp_num, strtok(NULL, ","));
			punish = atoi(strtok(NULL, ","));
			member = atoi(strtok(NULL, ","));
		}
		memset(temp1, NULL, sizeof(temp1));
		push_member();
	}
	fclose(pointer);
	printf("                                       *** welcome to this programm ***\n");
	system("start.mp3");
	Sleep(18000);
	while (1) {
		printf("Enter a number: ");
		ch = getchar();
		getchar();
		switch (ch)
		{
		case 49:
			printf("Enter new member group(1 for manager, 2 for headwe, 3 for employee): ");
			scanf("%d", &group);
			getchar();
			printf("Enter new member's name: ");
			scanf("%s",name.c_str());
			getchar();
			printf("Enter new member's family: ");
			scanf("%s", family.c_str());
			getchar();
			printf("Enter new member's national number: ");
			gets_s(num);
			if (search(num) == 1) {
				printf("This member exist.\n");
				break;
			}
			printf("Enter new member's birthday: ");
			gets_s(birthday);
			printf("Enter new member's salary: ");
			scanf("%LG", &salary);
			getchar();
			printf("Enter new member's working hours per month: ");
			scanf("%d", &hour);
			getchar();
			printf("Enter new member's cost of work per hour: ");
			scanf("%LG", &money);
			getchar();
			printf("Enter new member's working hardship: ");
			scanf("%d", &hardship);
			getchar();
			memset(organ, NULL, sizeof(organ));
			access_manager = -1;
			people_manager = -1;
			reward_manager = -1;
			memset(part, NULL, sizeof(part));
			access_header = -1;
			people_header = -1;
			reward_header = -1;
			memset(emp_num, NULL, sizeof(emp_num));
			punish = -1;
			member = -1;
			if (group == 1) {
				printf("Enter the name of organ: ");
				gets_s(organ);
				printf("Enter new member's access: ");
				scanf("%d", &access_manager);
				getchar();
				printf("Enter number of people in organ: ");
				scanf("%d", &people_manager);
				getchar();
				printf("Enter new members's reward: ");
				scanf("%LG", &reward_manager);
				getchar();
			}
			else if (group == 2) {
				printf("Enter the name of part: ");
				gets_s(part);
				printf("Enter new member's access: ");
				scanf_s("%d", access_header);
				getchar();
				printf("Enter number of people in part: ");
				scanf("%d", &people_header);
				getchar();
				printf("Enter new members's reward: ");
				scanf("%LG", &reward_header);
				getchar();
			}
			else if (group == 3) {
				printf("Enter new member's employee number: ");
				gets_s(emp_num);
				printf("Enter new member's punishment: ");
				scanf("%LG", &punish);
				getchar();
				printf("Enter the number of peoples in new member's family: ");
				scanf("%d", &member);
				getchar();
			}
			push_member();
			write();
			break;
		case 50:
			printf("Enter member's national number: ");
			gets_s(num);
			if (search(num) == -1) {
				printf("This member doesn't exist.\n");
				break;
			}
			system("edit1.mp3");
			Sleep(27000);
			if (temp->group == 1) {
				system("edit2.mp3");
				Sleep(15000);
			}
			if (temp->group == 2) {
				system("edit3.mp3");
				Sleep(14000);
			}
			if (temp->group == 3) {
				system("edit4.mp3");
				Sleep(11000);
			}
			printf("Enter a number (for editing): ");
			scanf("%d", &x);
			getchar();
			switch (x) {
			case 0:
				printf("Enter new group: ");
				scanf("%d", &temp->group);
				getchar();
				break;
			case 1:
				printf("Enter new name: ");
				scanf("%s", temp->name.c_str());
				getchar();
				break;
			case 2:
				printf("Enter new family: ");
				scanf("%s",temp->family.c_str());
				break;
			case 3:
				printf("Enter new national number: ");
				gets_s(temp->num);
				break;
			case 4:
				printf("Enter new birthday date: ");
				gets_s(temp->birthday);
				break;
			case 5:
				printf("Enter new salary: ");
				scanf("%LG", &temp->salary);
				getchar();
				break;
			case 6:
				printf("Enter new working hours per month: ");
				scanf("%d", &temp->hour);
				getchar();
				break;
			case 7:
				printf("Enter new cost of working per hour: ");
				scanf("%LG", &temp->money);
				getchar();
				break;
			case 8:
				printf("Enter new working hardship: ");
				scanf("%d", &temp->hardship);
				getchar();
				break;
			case 9:
				if (temp->group == 1) {
					printf("Enter new name of organ: ");
					gets_s(temp->manager.organ);
				}
				else if (temp->group == 2) {
					printf("Enter new name of organ: ");
					gets_s(temp->header.part);
				}
				else if (temp->group == 3) {
					printf("Enter new employee number: ");
					gets_s(temp->employee.emp_num);
				}
				break;
			case 10:
				if (temp->group == 1) {
					printf("Enter new access: ");
					scanf("%d", &temp->manager.access_manager);
					getchar();
				}
				else if (temp->group == 2) {
					printf("Enter new access: ");
					scanf("%d", &temp->header.access_header);
					getchar();
				}
				else if (temp->group == 3) {
					printf("Enter new punishment: ");
					scanf("%LG", &temp->employee.punish);
					getchar();
				}
				break;
			case 11:
				if (temp->group == 1) {
					printf("Enter new number of people in organ: ");
					scanf("%d", &temp->manager.people_manager);
					getchar();
				}
				else if (temp->group == 2) {
					printf("Enter the number of people in part: ");
					scanf("%d", temp->header.people_header);
					getchar();
				}
				else if (temp->group == 3) {
					printf("Enter new number of people in family: ");
					scanf("%d", &temp->employee.member);
					getchar();
				}
				break;
			case 12:
				if (temp->group == 1) {
					printf("Enter new reward: ");
					scanf("%LG", &temp->manager.reward_manager);
					getchar();
				}
				else if (temp->group == 2) {
					printf("Enter new reward: ");
					scanf("%LG", &temp->header.reward_header);
					getchar();
				}
				break;
			}
			write();
			break;
		case 51:
			printf("Enter a national number: ");
			gets_s(num);
			if (search(num) == -1) {
				printf("Not exist.\n");
				break;
			}
			delete_member(num);
			printf("Member deleted successfully\n");
			write();
			break;
		case 52:
			printf("Enter a national number: ");
			gets_s(num);
			if (search(num) == -1) {
				printf("Not exist.\n");
				break;
			}
			print(num);
			break;
		case 53:
			printf("Enter a national number: ");
			gets_s(num);
			if (search(num) == -1) {
				printf("Not exist.\n");
				break;
			}
			printf("The salary is: %llf\n", salary_mambers(num));
			break;
		case 54:
			printf("Good bye...\n");
			return 0;
			break;
		}
	}
}