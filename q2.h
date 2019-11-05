#ifndef Q2_H
#define Q2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#define INITIAL_SIZE 10
#define INCREMENT 5
#define ANSWER_LEN 101
#define USER_LEN 51
#define RANDOMNUM_LEN 50
#define PASSWORD_LEN 32
#define SIZE_PASSWORD 8
#define STATUS_LEN 513

typedef struct profileStruct {
	char username[51];
	char status[513];
	char friends[100000];
	struct profileStruct *requestHead;//רשימה מקושרת
} profile;

typedef struct profile_list_t {
	profile *user_data;
	struct profile_list_t *next;
} profiles_lst;


void replaceNewline(char * line);

int num_of_friends(char * line);

int num_of_friends1(char * friends_string);

void print_pending(profile * requesthead);

void print_lst(profiles_lst * head);
int num_of_friends2(char *friends_string);
char *increasePointer(char* pline);
char **split(char *line, char *delimiter, int loop, int delim_len);
char **split2(char *line, char *delimiter, int loop, int delim_len);
void printFriendsOption(profile *prof);
void printProfileList(profiles_lst *head);
profiles_lst *returnProfile(profiles_lst *head, char *username);
profiles_lst *returnProfile2(profiles_lst *head, char *username);
profile *returnPending(profile *pendingHead, char*username);
void searchOption(profiles_lst* list, char* query, char *my_username);
profile* add_last(profile* new_profile, profile* requestHead);
profile* createProfile(char* name, char* status, char* friends);
void printPendingList(profile *head);
void requestOption(char *reqFriend, profiles_lst *head, char *my_username);
int space(char *string);
void profOption(profiles_lst* list, char* my_username);
void unfriendOption(char *unfriend, profiles_lst *head, char* my_username);
void free_pending(profile* requestHead);
profiles_lst *createProfiles_lst();
void printProfilesLst(profiles_lst *head);
profile *createPendingList(char *pendingLine);
profiles_lst *readProfileList(profiles_lst *head, char* my_username, FILE *fptr);
int inFriendList(char**friendList, int friendNum, char* secFriend);
int inSecondCircle(char **secondCircle, char*maybe, int secondLen);
void printNetworkOption(profiles_lst *head, char* my_username);
void remove_from_pending(profiles_lst* head, char* username, char* pend_name);
int how_many_pending(profile *requesthead);
void update_statusOption(profiles_lst *head, char* username);
void check_friends_statusOption(profiles_lst *head, char *username, char *friend_name);
void add_friend(profiles_lst* head, char* username, char* app_friend);
void check_requestsOption(profiles_lst* head, char*username);
void print_to_file(FILE *fptr, profiles_lst *head);
int profileMenu(char *username,int var2);
 

#endif