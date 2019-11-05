#ifndef Q1_H
#define Q1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#define INITIAL_SIZE 10
#define INCREMENT 5
#define ANSWER_LEN 101
#define USER_LEN 51
#define RANDOMNUM_LEN 50
#define PASSWORD_LEN 32
#define SIZE_PASSWORD 8
#define STATUS_LEN 513


typedef struct user {
	char username[51];
	char password[33];
	int randomNum;
	char securityAnswer[101];
	struct user *next;
} User;

User *searchUser(User *head, char* username);
User *addUser(User *head, User *new_user);
int *turnPasswordStringIntoIntArray(char* password);

int validateUsername(char * username, int len);

int validateAnswer(char * securityAnswer, int len);

int convertPassword(int * password, int randomNum);

char * intToBinary(int password);

int matchPassword(int * passarr, User * user);

int usernameInList(char * username, User * head);

User * fill_user(char * username, char * password, int randomNum, char * securityAnswer);

void printUser(User * user);

void printUserList(User * head);

char ** split(char * line, char * delimiter, int loop, int delim_len);

User * createUserList(FILE * fptr, char * string, int max);

char * create_password(int * randomNum, char username[51]);

User * create_account(User * head);

void exitFunc(FILE * fptr, User * head);

int logIn(int * var, int * input, User * head);

#endif
