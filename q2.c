#include "q2.h"

void replaceNewline(char *line) {
	char *newline = NULL;
	/*if (line == NULL);
	return;*/
	newline = strchr(line, '\n');
	if (newline != NULL)
		*newline = '\0';
	return;
}
int num_of_friends1(char *friends_string) {

	int counter = 0, i;
	if (*friends_string == '\n') {
		
		return 0;
	}
	if (*friends_string != '\0') {
		for (i = 0; friends_string[i] != '\n'; i++) {
			if (friends_string[i] == '$')
				counter++;
		}
		counter++;
		return counter;
	}
	else
		return 0;


}
void print_pending(profile* requesthead) {

	profile *iter = requesthead;

	while (iter != NULL) {
		printf("%s", iter->requestHead->username);
		iter = iter->requestHead;
	}
}
void print_lst(profiles_lst* head) {

	profiles_lst *iter = head;

	while (iter != NULL) {
		printf("%s\n", iter->user_data->username);
		printf("%s\n", iter->user_data->status);
		printf("%s\n", iter->user_data->friends);
		print_pending(iter->user_data->requestHead);
		iter = iter->next;
	}
}
int num_of_friends2(char *friends_string) {

	int counter = 0, i;
	if (*friends_string == '\n') {

		return 0;
	}
	if (friends_string != NULL) {
		for (i = 0; friends_string[i] != '\0'; i++) {
			if (friends_string[i] == '$')
				counter++;
		}
		counter++;
		return counter;
	}
	else
		return 0;


}
char *increasePointer(char* pline) {
	pline = strchr(pline, '_');
	pline++;
	return pline;
}
char **split2(char *line, char *delimiter, int loop, int delim_len)  //split string and put it into a list that points to substrings
{
	int k = 0, len=0;
	char *p = line, *i, *is_newline = NULL, **list = NULL;
	list = (char**)malloc(loop * sizeof(char*)); //I NEED TO FREE THIS
	if (NULL == list)
	{
		printf("Error in **split");
		exit(1);
	}
	while (*p != '\0') {
		i = strstr(p, delimiter);
		if (i == NULL) //we're in the last iteration
		{
			is_newline = strstr(p, "\n"); // is there a newline?
			if (is_newline != NULL)
				*is_newline = '\0';
			/*else {
				len = strlen(p);
				*(p + len - 1) = '\0';
			}*/
			*(list + k) = p;
			break;
		}
		*i = '\0';
		*(list + k) = p;
		k++;
		p = i + delim_len;
		//printf("%s", p);
	}
	/*for (int i = 0; i < size;i++) {
	printf("%s\n", list[i]);
	}*/
	return list;
}
void printFriendsOption(profile *prof) {
	char **arr = NULL, *tmp=NULL, friendscopy[1000000];
	int i=0, j=0;
	int friendNum = num_of_friends2(prof->friends);
	printf("\n\n========================================================================\n\n\n");
	if (*(prof->friends) == '\n')
	{
		printf("\nDear %s, you don't have any friends yet.\n", prof->username);
		return;
	}
	else
		printf("Dear %s, here are your friends:\n");
	strcpy(friendscopy, prof->friends);
	arr = split2(friendscopy, "_$_", friendNum, 3);
	for (i = friendNum - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (strcmp(*(arr+j),*(arr+j + 1)) >0 ) {
				// swap
				tmp = *(arr + j);
				*(arr + j) = *(arr + j + 1);
				*(arr + j+1) = tmp;
			}
		}
	}
	for (i = 0; i < friendNum;i++) {
		printf("%s\n", arr[i]);
	}
	printf("\n");
}
void printProfileList(profiles_lst *head) {
	while (head != NULL) {
		if (head!=NULL)
			printf("Profile Name: %s\n", head->user_data->username);
		head = head->next;
	}
}
profiles_lst *returnProfile(profiles_lst *head,char *username) {
	profiles_lst *it = head;
	while (it != NULL) {
		if (strcmp(it->user_data->username, username) == 0) {
			return it;
		}
		it = it->next;
		}	
	
	printf("\nDid not find %s, returned end of list \n", username);
	return head;
} // returns head if there isn't one
profiles_lst *returnProfile2(profiles_lst *head, char *username) { // returns null if there isn't one
	profiles_lst *it = head;
	while (it != NULL) {
		if (strcmp(it->user_data->username, username) == 0) {
			return it;
		}
		it = it->next;
	}
	printf("\nDid not find %s, returned end of list \n", username);
	return NULL;
}
profile *returnPending(profile *pendingHead, char*username) {
	profile *it = pendingHead;
	while (it != NULL)
	{
		if (strcmp(it->username, username) == 0)
			return it;
		it = it->requestHead;
	}
	return NULL; // could not find

		
}
void searchOption(profiles_lst* list, char* query, char *my_username) {
	int proflen = 0,i=0, found=0;
	char username[USER_LEN];
	profiles_lst *it = list;
	printf("\n\n========================================================================\n\n\n");
	printf("The search for \"%s\" has found the following users within the SocioPath network:\n", query);
	while (it != NULL)
	{
		strcpy(username, it->user_data->username);
		proflen = strlen(username);
		for (i = 0; i < proflen;i++) {
			if (isupper(username[i]) != 0) {
				username[i] += 'a' - 'A';
			}
		}
		if (strstr(username, query) != NULL){
			found = 1;
			printf(" * %s\n", it->user_data->username);
		}
		it = it->next;
	}
	if (found ==0)
		printf("Dear %s, no results have been found.\n", my_username);
	


}
profile* add_last(profile* new_profile, profile* requestHead) {

	profile *requestTail = requestHead;

	if (requestHead == NULL) {
		requestHead = new_profile;
		return new_profile;
	}

	while (requestTail->requestHead != NULL) {
		requestTail->requestHead = requestTail;
	}
	if (requestTail->requestHead == NULL) {
		requestTail->requestHead = new_profile;
		return requestHead;
	}
	return requestHead;
}
profile* createProfile(char* name, char* status, char* friends)
{
	profile *ppro = NULL;
	ppro = (profile*)malloc(sizeof(profile));
	if (ppro == NULL)
	{
		printf("Error in createProfile\n");
		exit(1);
	}
	else
	{
		strcpy(ppro->username, name);
		if (status == NULL)
			strcpy(ppro->status, "");
		else
			strcpy(ppro->status, status);
		if (friends == NULL)
			strcpy(ppro->friends, "");
		else
			strcpy(ppro->friends, friends);
		ppro->requestHead = NULL;
	}
	return ppro;
}
void printPendingList(profile *head) {
	profile *it = head;
	printf("Printing pending friends' list\n");
	while (it != NULL) {
		printf("%s\n", it->username);
		it = it->requestHead;
	}
}
void requestOption(char *reqFriend, profiles_lst *head, char *my_username) {
	profiles_lst *it = head;
	profile *pendprof = NULL, *inpending = NULL, *add=NULL;
	char **friendList, *friends=NULL, *_friend = NULL, friendscopy[100000];
	int friendNum=0, i, isfriend=0;
	printf("\n\n========================================================================\n\n\n");
	it = returnProfile2(it, reqFriend);
	if (it == NULL) { // could not find friend you requested
		printf("Dear %s, SocioPath doesn't have a member by the username: %s. You are being transferred to the profile menu to choose again.\n", my_username, reqFriend);
		return; //return to main menu
	}
	pendprof = it->user_data->requestHead;
	inpending = returnPending(pendprof, my_username);
	if (inpending != NULL) // already requested friendship 
	{
		printf("Dear %s, a friend request has already been sent to: %s. You are being transferred to the profile menu to choose again.\n", my_username, reqFriend);
		return;
	}
	it = head;
	it = returnProfile2(it, my_username);
	friends = it->user_data->friends;
	strcpy(friendscopy, friends);
	friendNum = num_of_friends1(friends);
	friendList = split(friendscopy, "_$_", friendNum, 3);
	for (i = 0;i < friendNum; i++)
	{
		_friend = friendList[i];
		if (strcmp(_friend, reqFriend) == 0)
			isfriend = 1;
	}
	if (isfriend == 1)
	{
		printf("Dear %s, %s is already your friend. You are being transferred to the profile menu to choose again.\n", my_username, reqFriend);
		return;
	}
	it = head;
	it = returnProfile(it, reqFriend);
	add = createProfile(my_username, "", "");
	add_last(add, it->user_data->requestHead);
	printPendingList(it->user_data->requestHead);
	printf("Dear %s, a friend request has been sent to: %s.\n", my_username, reqFriend);
	it = head;
	free(friendList);
	return;
}
int space(char *string) {
	int i = 0, len = strlen(string);
	for (i = 0; i < len; i++)
	{
		if (isspace(string[i]))
			return 1;
	}
	return 0;
}
void Print_friendsstatus(profiles_lst* new_lst, char *username) {

	int NumOfFriends = 0, i = 0;
	char **friends, friends2[10000];
	profiles_lst *curr_profile = NULL, *curr_profile2 = NULL;

	curr_profile = returnProfile2(new_lst, username);
	NumOfFriends = num_of_friends1(curr_profile->user_data->friends);
	if (NumOfFriends != 0) {
		printf("See what's on your friends' minds:\n");
		strcpy(friends2, curr_profile->user_data->friends);
		friends = split2(friends2, "_$_", NumOfFriends, 3);
		for (i = 0; i < NumOfFriends; i++) {
			curr_profile2 = returnProfile2(new_lst, *friends);
			if (curr_profile2->user_data->status != "" || curr_profile2->user_data->status != "\n")
				printf("%s: %s\n", curr_profile2->user_data->username, curr_profile2->user_data->status);
			else
				printf("%s has no status.\n", curr_profile2->user_data->username);
			friends++;

		}
	}
	else
		printf("You don't have friends yet.\n");
}
void profOption(profiles_lst* list, char* my_username) {
	profiles_lst *it = list, *it2 = list;
	char **friendList = NULL,friendscopy[100000];
	int numFriends = 0,i;
	it = returnProfile(it, my_username);
	printf("Your status: %s\n", it->user_data->status);
	if (isalpha(it->user_data->friends[0]) == 0)
		return;
	numFriends = num_of_friends2(it->user_data->friends);
	strcpy(friendscopy, it->user_data->friends);
	friendList = split2(friendscopy, "_$_", numFriends, 3);
	Print_friendsstatus(list, my_username);
	

}
void unfriendOption(char *unfriend, profiles_lst *head, char* my_username) {
	profiles_lst *it = head;
	char **friendList = NULL, *friends = NULL, newfriends[10000], *pnewfriends = newfriends, friendscopy[10000];
	int friendNum = 0,i=0,found=0;
	printf("\n\n========================================================================\n\n\n");
	newfriends[0] = '\0';
	it = returnProfile2(it, my_username);
	friends = it->user_data->friends;
	friendNum = num_of_friends1(friends);
	if (friendNum == 1) {
		if (strcmp(friends, unfriend)==0)
			strcpy(it->user_data->friends, "\n");
		else {
			printf("Dear %s, you don't have any friend with the username: %s. You are being transferred to the profile menu to choose again.\n", my_username, unfriend);
			return
		}
	}
	strcpy(friendscopy, friends);
	friendList = split2(friendscopy, "_$_", friendNum, 3);
	if (friendNum > 1)
	{
		for (i = 0;i < friendNum;i++) {
			if (strcmp(friendList[i], unfriend) == 0) {
				found = 1;
				friendList[i] = NULL;

			}
		}
		for (i = 0;i < friendNum;i++) {
			if (friendList[i] == NULL)
				continue;
			pnewfriends = strcat(pnewfriends, friendList[i]);
			pnewfriends = strcat(pnewfriends, "_$_");

		}

		if (friendNum > 1) {
			pnewfriends = strchr(pnewfriends, '\0');
			*(pnewfriends - 3) = '\n';
			*(pnewfriends - 2) = '\0';
			strcpy(it->user_data->friends, newfriends);
		}
	}

	
	
	//printf("%s\n", it->user_data->friends);
	if (found == 0 && !(friendNum == 1)) {
		printf("Dear %s, you don't have any friend with the username: %s. You are being transferred to the profile menu to choose again.\n", my_username, unfriend);
		return;
	}
}
void free_pending(profile* requestHead) {

	profile* temp = NULL;

	while (requestHead != NULL) {
		temp = requestHead;
		requestHead = requestHead->requestHead;
		free(temp);

	}
}
profiles_lst *createProfiles_lst()
{
	profiles_lst *newLst = NULL;
	newLst = (profiles_lst*)malloc(sizeof(profiles_lst));
	if (newLst == NULL) {
		printf("Error in creating profiles_lst node\n");
		exit(1);
	}
	newLst->user_data = NULL;
	newLst->next = NULL;
	
	return newLst;
}
void printProfilesLst(profiles_lst *head) {
	profiles_lst *it = head;
	printf("Printing profiles_lst users\n");
	while (it != NULL) {
		printf("Username: %s\n", it->user_data->username);
		printf("Status: %s\n", it->user_data->status);
		printf("Friends: %s", it->user_data->friends);
		printPendingList(it->user_data->requestHead);
		it = it->next;
		printf("\n");
	}
	

}
profile *createPendingList(char *pendingLine) {
	char **friendList = NULL;
	int friendNum = 0,numFriends = 0,i =0;
	profile *head = NULL, *pnew=NULL;
	if (*pendingLine == '\n' || *pendingLine == '\0')
		return head;
	numFriends = num_of_friends1(pendingLine);
	friendList = split2(pendingLine, "_$_", numFriends, 3);
	for (i = numFriends-1; i >= 0; i--) {
		pnew = createProfile(friendList[i], "", "");
		pnew->requestHead = head;
		head = pnew;
	}
	//printPendingList(head);
	return head;

}
profiles_lst *readProfileList(profiles_lst *head, char* my_username, FILE *fptr) {
	char line[10000], *pline = NULL;
	int i = 0;
	profile *newPro = NULL, *pendingHead = NULL ;
	profiles_lst *lstHead = NULL, *lsttemp=NULL, *it=NULL, *pendit=NULL;
	while (!feof(fptr)) // create profiles, ignoring pending for now
	{
		fgets(line, 10000, fptr);
		if (feof(fptr))
			break;
		pline = increasePointer(line); // line = username
		replaceNewline(pline);
		newPro = createProfile(pline, NULL, NULL);
		fgets(line, 10000, fptr);
		pline = increasePointer(line); // line = status
		replaceNewline(pline);
		strcpy(newPro->status, pline);
		fgets(line, 10000, fptr);
		pline = increasePointer(line); // line = friends
		strcpy(newPro->friends, pline);
		fgets(line, 10000, fptr);
		pline = increasePointer(line); // line = char *pending
		pendingHead = createPendingList(pline);
		//printPendingList(pendingHead);
		newPro->requestHead = pendingHead; // insert pending list;
		//printPendingList(newPro->requestHead);
		lstHead = createProfiles_lst(); // creating linked list of all profiles so far
		lstHead->user_data = newPro;
		lstHead->next = lsttemp;
		lsttemp = lstHead;
		//printPendingList(lsttemp->user_data);
		
	}
	head = lsttemp;

	return head;
	}
int inFriendList(char**friendList, int friendNum, char* secFriend) {
	int i = 0;
	for (i = 0; i < friendNum;i++)
	{
		if (strcmp(friendList[i], secFriend) == 0)
			return 1;
	}
	return 0;
	
}
int inSecondCircle(char **secondCircle, char*maybe, int secondLen) {
	int i = 0;
	for (i = 0;i < secondLen;i++) {
		if (strcmp(secondCircle[i], maybe) == 0)
			return 1; // is inside secondCircle do not print
	}
	return 0; // is not inside can print

}
void printNetworkOption(profiles_lst *head, char* my_username) {
	profiles_lst *it = head;
	profile *profiter = NULL;
	int friendNum = 0, i = 0, j=0,k=0,count=0, l=0, secfriendNum=0, alreadyexist=0;
	char **first = NULL, *firstfriends = NULL, *secfriends = NULL, **second = NULL, *friendsforprint[10000] = { "" }, **pfinal = friendsforprint;
	char firstcopy[100000], secondcopy[100000];
	printf("\n\n========================================================================\n\n\n");
	pfinal = friendsforprint;
	printf("Dear %s, your social network is:\n", my_username);
	printf("You: %s\n", my_username);
	it = returnProfile2(it, my_username);
	firstfriends = it->user_data->friends;
	friendNum = num_of_friends1(firstfriends);
	strcpy(firstcopy, firstfriends);
	first = split(firstcopy, "_$_", friendNum, 3);
	printf("Your friends: ");
	for (i = 0; i < friendNum; i++) {
		if (i == friendNum - 1)
		{
			printf("%s", first[i]);
			continue;
		}
		printf("%s, ", first[i]);
	}
	printf("\n");
	it = head;
	printf("Friend of your friends: ");
	for (j = 0; j < friendNum; j++) {
		it = returnProfile2(it, first[j]);
		secfriends = it->user_data->friends;
		secfriendNum = num_of_friends1(secfriends);
		strcpy(secondcopy, secfriends);
		second = split(secondcopy, "_$_", secfriendNum, 3);
		for (k = 0; k < secfriendNum;k++) {
			/*if (strcmp(my_username, second[k]) == 0)
				continue;*/
			if (!inFriendList(first, friendNum, second[k]) && strcmp(my_username, second[k]) != 0 && !inSecondCircle(pfinal, second[k],l)) {
				pfinal[l] = second[k];
				l++;
				//printf("%s, ", second[k]);
			}
			

		}
		it = head;
	}
	for ( count = 0; count < l; count++) {
		if (count == l - 1)
		{
			printf("%s", pfinal[count]);
			continue;
		}
		printf("%s, ", pfinal[count]);
	}
	printf("\n");

	return;
}
void remove_from_pending(profiles_lst* head, char* username, char* pend_name) {

	profiles_lst *curr_user = NULL;
	profile *iter = NULL, *prev = NULL, *requesthead = NULL;

	curr_user = returnProfile2(head, username);
	iter = curr_user->user_data->requestHead;

	if (iter == NULL)
		return;
	if (strcmp(iter->username, pend_name) == 0) {
		curr_user->user_data->requestHead = iter->requestHead;
		free(iter);
		return;
	}
	while (iter != NULL) {
		if (strcmp(iter->username, pend_name) == 0) {
			prev->requestHead = iter->requestHead;
			free(iter);
			printPendingList(curr_user->user_data->requestHead);
			return;
		}
		prev = iter;
		iter = iter->requestHead;

	}
}
int how_many_pending(profile *requesthead) {

	int counter = 0;
	profile* iter = requesthead;

	if (iter != NULL) {
		while (iter != NULL) {
			counter++;
			iter = iter->requestHead;
		}
		return counter;
	}
	else
		return 0;
} 
void update_statusOption(profiles_lst *head, char* username) {

	profiles_lst* profile = NULL;
	char status[STATUS_LEN], *newline=NULL;

	printf("\n\n========================================================================\n\n\n");
	profile = returnProfile2(head, username);
	if (profile == NULL) {
		printf("Profile does not excist.\n\n");
	}
	else {
		printf("Update your SocioPath status to share with your friends.\n\nInput: ", username);
		fgets(status, STATUS_LEN, stdin);
		newline = strchr(status, '\n');
		if (newline != NULL)
			*newline = '\0';
		strcpy(profile->user_data->status, status);
		printf("Your status has been updated to: %s\n", profile->user_data->status);
	}
} // status
void check_friends_statusOption(profiles_lst *head, char *username, char *friend_name) {

	profiles_lst *friend_to_check = NULL;

	friend_to_check = returnProfile2(head, friend_name);
	if (friend_to_check == NULL) {
		printf("\nDear %s, you don't have a friend with the username: %s. You are being transferred to the profile menu to choose again.\n"
			, username, friend_name);
	}
	else if (strcmp(friend_to_check->user_data->status, "") == 0)
		printf("\n%s doesn't have a status.\n", friend_name);
	else
		printf("\n%s status is: %s\n", friend_name, friend_to_check->user_data->status);

}
void add_friend(profiles_lst* head, char* username, char* app_friend) {

	char *friends = NULL, *ptr = NULL;
	int numofFriends = 0;
	profiles_lst* curr_profile = NULL;

	curr_profile = returnProfile2(head, username);
	friends = curr_profile->user_data->friends;
	ptr = friends;
	numofFriends = num_of_friends2(friends);

	if (numofFriends == 0) {
		*friends = '\0';
		strcat(friends, app_friend);
		strcat(friends, "\n");
		strcpy(curr_profile->user_data->friends, ptr);
		return;
	}

	for (; friends != '\0'; friends++) {
		if (*friends == '\n') {
			*friends = '\0';
			strcat(friends, "_$_");
			strcat(friends, app_friend);
			strcat(friends, "\n");
			strcpy(curr_profile->user_data->friends, ptr);
			printf("%s", curr_profile->user_data->friends);
			return;
		}
	}
}
void check_requestsOption(profiles_lst* head, char*username) {

	profiles_lst *curr_profile = NULL;
	profile *requestHead = NULL;
	char input[1000], **split_ptr = NULL, *ptr = NULL;
	int NumOfPending = 0, i = 0;

	curr_profile = returnProfile2(head, username);

	if (curr_profile == NULL)
		return;
	requestHead = curr_profile->user_data->requestHead;
	NumOfPending = how_many_pending(curr_profile->user_data->requestHead);
	if (NumOfPending == 0) {
		printf("Dear %s, you don't have any pending requests.", username);
		return;
	}
	printf("Dear %s, you have %d friend request.\n The pending friend requests are from the users:\n", username, NumOfPending);
	for (i = 0; i < NumOfPending; i++) {
		printf("* %s\n", requestHead->username);
		requestHead = requestHead->requestHead;
	}
	requestHead = curr_profile->user_data->requestHead;
	printf("To approve the request, enter \"approve::<username>\".\n"
		"To refuse and delete the request, enter \"refuse::<username>\".\n"
		"To go back to the main selection menu, enter \"&\".\nInput: ");
	fgets(input, 1000, stdin);
	printf("\n\n");
	ptr = strchr(input, ':');
	if (ptr != NULL) {
		ptr++;
		if (*ptr != ':') {
			printf("Dear %s, you have entered an illegal input. You are being transferred to the profile menu to choose again.\n\n", username);
			return;
		}
	}
	else
		return;

	split_ptr = split(input, "::", 2, 2);
	if (strcmp("approve", *split_ptr) == 0) {
		split_ptr++;
		if (returnPending(requestHead, *split_ptr) == NULL) {
			printf("Dear %s, you have entered an illegal input. You are being transferred to the profile menu to choose again.\n\n", username);
			return;
		}
		add_friend(head, username, *split_ptr);
		printf("\nDear %s, %s has been added to your friends list.\n");
		remove_from_pending(head, username, *split_ptr);
	}


	else if (strcmp("refuse", *split_ptr) == 0) {
		split_ptr++;
		if (returnPending(requestHead, *split_ptr) == NULL) {
			printf("Dear %s, you have entered an illegal input. You are being transferred to the profile menu to choose again.\n\n", username);
			return;
		}
		remove_from_pending(head, username, *split_ptr);
		printf("\nDear %s, %s request has been refused.\n");
		//printProfilesLst(head);
	}
	else if (strcmp("&", input) == 0)
		return;
	else {
		printf("Dear %s, you have entered an illegal input. You are being transferred to the profile menu to choose again.\n\n", username);
		return;
	}
}
void print_to_file(FILE *fptr, profiles_lst *head) {

	profiles_lst *iter = head;
	profile* requestHead = iter->user_data->requestHead;
	int NumOfPending = 0, i = 0;
	char username[USER_LEN], status[STATUS_LEN], friends[10000], pending[10000], *pending_ptr = pending;

	while (head != NULL) {
		iter = head;
		head = head->next;
		strcpy(username, iter->user_data->username);
		fputs("Username_", fptr);
		fputs(username, fptr);
		fputs("\n", fptr);
		strcpy(status, iter->user_data->status);
		fputs("Status_", fptr);
		fputs(status, fptr);
		fputs("\n", fptr);
		strcpy(friends, iter->user_data->friends);
		fputs("Friends_", fptr);
		fputs(friends, fptr);
		if (num_of_friends1(friends) == 0) {
			if (strcmp(friends, "\n") != 0)
				fputs("\n", fptr);
		}
		NumOfPending = how_many_pending(requestHead);
		if (NumOfPending == 0)
			strcpy(pending, "");
		for (i = 0; i < NumOfPending; i++) {
			if (i > 0)
				strcat(pending_ptr, requestHead->username);
			else
				strcpy(pending_ptr, requestHead->username);
			if (requestHead->requestHead != NULL) {
				strcat(pending_ptr, "_$_");
			}
			requestHead = requestHead->requestHead;
		}
		fputs("Pending_", fptr);
		fputs(pending, fptr);
		fputs("\n", fptr);
		free_pending(iter->user_data->requestHead);
		free(iter);
		if (head != NULL)
			requestHead = head->user_data->requestHead;
	}
	fclose(fptr);
}
int profileMenu(char *username,int var2) { //0 to go to main menu, 1 to exit 
	char input[1000], *cptr = NULL, *nlptr = NULL, **friends = NULL;
	int NumOfFriends = 0, i=0;
	FILE *fptr=NULL, *fptrw=NULL;
	profiles_lst *new_lst = (profiles_lst*)malloc(sizeof(profiles_lst)), *head = NULL, *curr_profile = NULL, *curr_profile2 = NULL;
	profile *new_profile = NULL;
	fptr = fopen("profile.txt", "r");
	if (new_lst != NULL) {
		new_lst = readProfileList(new_lst, username, fptr);
	}
	fclose(fptr);
	//printProfilesLst(new_lst);
	if (var2 == 1) {
		new_profile = createProfile(username, "", "");
		head = createProfiles_lst();
		head->next = new_lst;
		head->user_data = new_profile;
		new_lst = head;
		//printProfilesLst(new_lst);
	}

	curr_profile = returnProfile2(new_lst, username);
	printf("\n\n\n=================================================================================================\n\n\n");

	while (1)
	{
		printf("Hi %s and welcome to your profile!\n", username);
		if (curr_profile->user_data->status != "")
			printf("Your status: %s\n\n", curr_profile->user_data->status);
		else 
			printf("You don't have a status yet.\n");

		Print_friendsstatus(new_lst, username);
		printf("\nWhat would you like to do next? Choose the option by entering the matched string.\n\n");
		printf("\"profile\"- show your profile.\n");
		printf("\"status\"- update your current status.\n");
		printf("\"checkStatus <friend_username>\"- check the current status of a specific friend, whose username you enter in the place of <friend_username>.\n"); /**/
		printf("\"checkRequests\"- check incoming friend requests.\n");
		printf("\"printFriends\"- print the list of your friends (usernames).\n");
		printf("\"search\" <query>- search SocioPath network for a username.\n");
		printf("\"request <username>\"- send a friend request to the given username.\n"); //*
		printf("\"unfriend <friend_username>\"- unfriend the entered friend.\n"); //*
		printf("\"printNetwork\"- print your social network.\n");
		printf("\"#\"- log out and return to the first App screen.\n");
		printf("\"$\"- exit the app.\n\n");

		printf("Input:");
		fgets(input, 999, stdin);
		nlptr = strchr(input, '\n');
		*nlptr = '\0';
		if (space(input) == 0) { // either Profile, Status,checkRequests, printFriends, Search, printNetwork, # , $
			if (strcmp(input, "profile") == 0) {
				profOption(new_lst, username);

			}
			else if (strcmp(input, "status") == 0) {
				update_statusOption(new_lst, username);
				profOption(new_lst, username);
			}
			else if (strcmp(input, "checkRequests") == 0) {
				check_requestsOption(new_lst, username);
			}
			else if (strcmp(input, "printFriends") == 0) {
				printFriendsOption(returnProfile2(new_lst, username)->user_data);
			}
			else if (strcmp(input, "printNetwork") == 0) {
				printNetworkOption(new_lst, username);
			}
			else if (strcmp(input, "#") == 0) {
				if (var2 != 1)
				{
					printf("Back to main screen:\n\n1.Log in\n2.Create a new account\n3.Exit the App\n\n");
					printf("Input:");
				}
				fptrw = fopen("profile.txt", "w");
				print_to_file(fptrw, new_lst);
				fclose(fptrw);
				return 1;
			}
			else if (strcmp(input, "$") == 0) {
				printf("Thank you and goodbye!");
				fptrw = fopen("profile.txt", "w");
				print_to_file(fptrw, new_lst);
				fclose(fptrw);
				return 0;
			}
		}
		else { //checkstatus, request, unfriend, search
			cptr = strstr(input, " ");
			*cptr = '\0';
			cptr++; // cptr is the 2nd word, input is the first word
			if (strcmp(input, "checkStatus") == 0) {
				check_friends_statusOption(new_lst, username, cptr);
			}
			else if (strcmp(input, "request") == 0) {
				requestOption(cptr, new_lst, username);
				printf("ENTER reques, with %s as username", cptr);
			}
			else if (strcmp(input, "unfriend") == 0) {
				unfriendOption(cptr, new_lst, username);
				printf("ENTER unfriend, with %s as  friend username", cptr);
			}
			else if (strcmp(input, "search") == 0) {
				searchOption(new_lst, cptr, username);
					printf("ENTER Search\n");
			}


		}
	}
	return 0;
}

