#include "q1.h"
#include "q2.h"

User *create_user() {
	User *new_user;
	new_user = (User*)malloc(sizeof(User)); // NEEDS TO BE FREED
	if (NULL == new_user)
	{
		printf("Error in creation of new user");
		exit(1);
	}
	strcpy(new_user->securityAnswer, "");
	strcpy(new_user->username, "");
	new_user->randomNum = 0;
	strcpy(new_user->password, "");
	new_user->next = NULL;
	return new_user;
}

User *searchUser(User *head,char* username) {
	User *it = head;
	while (it != NULL) {
		if (strcmp(username, it->username) == 0)
			return it;
		it = it->next;
	}
	return NULL;
}
User *addUser(User *head, User *new_user) {
	User *temp = head;
	while (head != NULL) {
		if (head->next == NULL)
		{
			head->next = new_user;
			break;
		}
		head = head->next;
	}
	return temp;

}
int *turnPasswordStringIntoIntArray(char* password) {
	int *intarr=NULL, i = 0;
	intarr = (int*)malloc(SIZE_PASSWORD*sizeof(int));
	if (NULL == intarr) { printf("Error in turnPasswordStringIntoIntArray"); exit(1); }
	for (i = 0;i < SIZE_PASSWORD; i++) {
		intarr[i] = password[i];
		//printf("%d\n", intarr[i]);
	}
	return intarr;
}
int validateUsername(char* username, int len) {
	int i = 0, correct = 1;
	char c = '\0';
	for (;i < len;i++) {
		c = username[i];
		if (c != ' ' || c < 48 || c >0 || c < 65 || c > 90 || c < 97 || c > 122)
		{
			correct = 0;
			return correct;
		}
	}
	return correct;
}
int validateAnswer(char* securityAnswer, int len) {
	int i = 0, correct = 1;
	char c = '\0';
	for (;i < len;i++) {
		c = securityAnswer[i];
		if (c != ' ' || c < 48 || c >0 || c < 65 || c > 90 || c < 97 || c > 122) // check if legit character by ascii values
		{
			correct = 0;
			return correct;
		}
	}
	return correct;
}
int convertPassword(int *password, int randomNum) {
	int i = 0, result = password[0];

	for (i = 1; i < SIZE_PASSWORD; i++)
	{
		result &= password[i];
	}
	if (result % 2 == 0)
		result <<= 4;
	else
		result >>= 6;

	result ^= randomNum;

	return result;
}
char *intToBinary(int password) {
	char* binary = NULL;
	int i = 31;
	binary = (char*)calloc(33, sizeof(char)); // NEEDS TO BE FREED
	if (NULL == binary){
		printf("Error in intToBinary");
		exit(1);
	}
	while (i >= 0)
	{
		binary[i] = password % 2 + '0';
		password = password / 2;
		i--;
	}
	binary[32] = '\0';
	return binary;
}
int matchPassword(int* passarr, User *user) { //put relevant head and pass array, return if password is ok or not
	User *it = user;
	int passenc = 0;
	char *bipass;
	if (user == NULL)
		return 0;
	if (passarr == NULL)
		return 0;
	passenc = convertPassword(passarr, user->randomNum);
	bipass = intToBinary(passenc);
	if (strcmp(bipass, user->password) == 0) //password is ok
	{
		return 1;
	}
	else
	{
		return 0;
	} // password is not ok



}
int usernameInList(char* username, User *head) {
	while (head != NULL) {
		if (strcmp(username, head->username) == 0)
			return 1; // 1 is correct
		head = head->next;
	}
	return 0; // not in there
}
User* fill_user(char *username, char* password, int randomNum, char *securityAnswer) {
	User *new_user;
	new_user = (User*)malloc(sizeof(User)); // NEEDS TO BE FREED
	if (NULL == new_user)
	{
		printf("Error in creation of new user");
		exit(1);
	}
	strcpy(new_user->username, username);
	strcpy(new_user->securityAnswer, securityAnswer);
	strcpy(new_user->password, password);
	new_user->randomNum = randomNum;

	new_user->next = NULL;
	return new_user;
}
void printUser(User *user) {
	printf("Username: %s\n", user->username);
	printf("Password: %s\n", user->password);
	printf("randomNum: %d\n", user->randomNum);
	printf("securityAnswer: %s\n\n", user->securityAnswer);
}
void printUserList(User *head) {
	int count = 0;
	while (head != NULL) {
		printUser(head);
		head = head->next;
		count++;
		printf("This is count: %d\n", count);
	}
}
char **split(char *line, char *delimiter,int loop, int delim_len)  //split string and put it into a list that points to substrings
{
	int k = 0,len;
	char *p=line, *i, *is_newline=NULL, **list= NULL;
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
			if(is_newline!=NULL)
				*is_newline = '\0';
			else {
				len = strlen(p);
				*(p + len - 1)= '\0';
			}
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
User *createUserList(FILE *fptr, char *string, int max) {
	int j = 0,k=0;
 	char **list=NULL, c= '\0';
	User *new_user = NULL, *head = NULL;
	while (!feof(fptr)) 
	{
		while (!feof(fptr)) {
			if (c == '\n')
			{
				c = '\0';
				break;
			}
			c = fgetc(fptr);
			*(string + k) = c;
			k++;
			if (feof(fptr) == 1)
				return new_user;
		}
		*(string + k) = '\0';
		k = 0;
		//printf("%s\n", string);
		list = split(string, "_$_",4, 3);
		new_user = create_user();
		new_user = fill_user(list[0], list[1], atoi(list[2]), list[3]);
	
		if (head == NULL)
		{
			//printUser(new_user);
			head = new_user;
			continue;
		}
		new_user->next = head;
		head = new_user;
		free(list);
		//printUser(new_user);
		
	}
	return new_user;
}
char *create_password(int *randomNum, char username[51]) {

	int result = 0, upper_checker = 0, lower_checker = 0, num_checker = 0, i = 0, var = 0, valid = 0, password_val[SIZE_PASSWORD], checker = 0, password[SIZE_PASSWORD];
	int randomNum1 = 0;
	char *enc_password = NULL;

	while (valid == 0)
	{
		printf("Welcome %s! Please choose a password.\nInput: ", username);
		var = _getch();
		printf("*");
		for (i = 0; var != 13; i++)
		{
			password[i] = var;
			var = _getch();
			if (var != 13)
				printf("*");

		}
		printf("\n");
		while (upper_checker == 0 || lower_checker == 0 || num_checker == 0)
		{
			if (i != SIZE_PASSWORD) {
				printf("\n\nDear %s, your password must be 8 characters long, and contain at least "
					"each of the following : A digit, a lower case letter and an upper case letter. "
					"Please try again.\n", username);
				break;
			}
			for (i = 0; i < SIZE_PASSWORD - 1; i++)
			{
				if (password[i] > 64 && password[i] < 91)//checking for uppercase.
					upper_checker++;
				else if (password[i] > 96 && password[i] < 123)//Checking for lowercase.
					lower_checker++;
				else if (password[i] > 47 && password[i] < 58)//Checking for numbers.
					num_checker++;
				else // Invalid input.
				{
					checker = 0;
					break;
				}

			}
			if (upper_checker == 0 || lower_checker == 0 || num_checker == 0) {
				printf("\n\nDear %s, your password must be 8 characters long, and contain at least "
					"each of the following : A digit, a lower case letter and an upper case letter. "
					"Please try again.\n", username);
				break;
			}
			printf("\n");
			printf("Please validate your password.\nInput: ");
			var = _getch();
			for (i = 0; var != 13; i++)
			{
				printf("*");
				password_val[i] = var;
				var = _getch();
			}
			for (i = 0; i < SIZE_PASSWORD; i++) { //Checking if the validation match the password.
				if (password_val[i] != password[i]) {
					upper_checker = 0, lower_checker = 0, num_checker = 0;
					valid = 0;
					printf("\n\nWe are truly sorry - The passwords do not match. Please repeat password acquisition process.\n");
					break;
				}
				else
					valid = 1;
			}
			if (valid == 0)
				break;
		}
	}

	srand((unsigned)time(NULL));
	randomNum1 = rand();
	result = password[0];

	for (i = 1; i < SIZE_PASSWORD; i++)
	{
		result &= password[i];
	}
	if (result % 2 == 0)
		result <<= 4;
	else
		result >>= 6;

	result ^= randomNum1;
	*randomNum = randomNum1;
	enc_password = intToBinary(result);

	return enc_password;
}
char *splitter(char *line, char *delimiter) /*returns the first word, the word between delimiters and the last word accordingly*/
{
	static char *str, *i, *step;
	if (line != NULL) /*if line contains string*/
		str = line;
	if (str == NULL) /*return null pointer if line is empty*/
		return str;
	i = strstr(str, delimiter); /*split str by delimiter, value is substring*/
	if (i == NULL) /*str returns null if delimiter is not there -> meaning if there is no delimiter we reached the end of the line*/
	{
		step = str; /*str is now only 1 word, so we return it*/
		str = NULL; /*nullify str*/
		return step;
	}
	step = str;
	*i = '\0'; /*string stamp*/
	str = i + strlen(delimiter); /*advance str by delimiter to next segment*/
	return step; /*return inteded segment*/
}
User* create_account(User *head)
{
	User *new_user = (User*)malloc(sizeof(User)), *temp = head;
	int  i = 0, var = 0, valid = 0, checker = 0, stam = -1, *randomNum = &stam;
	char username[USER_LEN], *password = NULL, security_answer[ANSWER_LEN];
	printf("\n\n========================================================================\n\n\n");
	printf("Hello dear guest, please choose a username.\nInput: ");
	fgets(username, USER_LEN, stdin);
	printf("\n\n");
	while (checker < 2)
	{
		for (i = 0; username[i] != '\0'; i++)
		{
			if (username[i] == '\n')
				username[i] = '\0';
			if (username[i] != ' ' && isalpha(username[i]) == 0 && username[i] != '\0')
			{
				printf("Dear guest, your username must contain only letters and at least one space. Please try again.\nInput: ");
				fgets(username, USER_LEN, stdin);
				printf("\n");
				break;
			}
			if (username[i] == ' ')
				checker++;
		}
		while (temp != NULL)
		{
			if (strcmp(temp->username, username) == 0)
			{
				printf("We are truly sorry - The username you chose is already being used.Please choose again.\nInput: ");
				fgets(username, USER_LEN, stdin);
				printf("\n");
				break;
			}
			temp = temp->next;
		}
		checker++;
	}
	checker = 0;


	password = create_password(randomNum, username); //Creating the password.
	printf("\n\n");
	while (valid == 0)
	{
		printf("Question: When was your last underground guitar jam?\nInput: ");
		fgets(security_answer, ANSWER_LEN, stdin);
		for (i = 0; security_answer[i] != '\0'; i++)
		{
			if (security_answer[i] == '\n') {
				security_answer[i] = '\0';
				break;
			}

			if (security_answer[i] != ' ' && isalpha(security_answer[i]) == 0 && security_answer[i] != '\n' && isdigit(security_answer[i]) == 0)
			{
				printf("\nDear %s, security answer can contain only letters, numbers and spaces. Please try again.\n", username);
				valid = 0;
				break;
			}
			if (security_answer[i] == '\n')
				security_answer[i] = '\0';
			else
				valid = 1;
		}
	}

	if (new_user != NULL) {// allocation succeeded
		strcpy(new_user->username, username);
		strcpy(new_user->securityAnswer, security_answer);
		strcpy(new_user->password, password);
		new_user->randomNum = *randomNum;
		new_user->next = head;
	}

	return new_user;

}
void exitFunc(FILE *fptr, User *head) {
	User *it = head;
	char *ans = NULL;
	int len = 0,count=0;
	while (it != NULL) {
		fprintf(fptr, "%s_$_%s_$_%d_$_", it->username, it->password, it->randomNum);
		ans = it->securityAnswer;
		len = strlen(ans);
		while (*ans != '\0') {
		/*	if (count == len-1)
				break;*/
			fputc(*ans, fptr);
			ans++;
			count++;

		}
		if (it->next != NULL)
			fprintf(fptr, "\n");
		it = it->next;

	}
	it = head;
	while (head != NULL) {
		it = head;
		head = head->next;
		free(it);
	}

}
int logIn(int* var, int* input, User *head) {
	User *it = head, *searchit = head, *base = head;
	int user_exist = 0, password_ok = 0, *passarr = NULL, count = 0, *secpassarr = NULL, secpass_ok;
	char **list = NULL, *string = NULL, badpassword[9], answer[101], *encnewpass, c = '\0', *is_sograim = NULL;
	if (NULL == (string = ((char*)malloc((USER_LEN + PASSWORD_LEN + 3)*sizeof(char)))))
	{
		printf("Memory Error occured in logIn");
		return 1;
	}
	while (user_exist == 0) {
		it = base;
		printf("\n\n=================================================================================================\n\n\n");
		printf("Please enter your username and password in the format:'username::password'.\n");
		printf("To go back to the first screen enter '#'.\n");
		printf("To exit the app please enter '$'.\n\n");
		printf("Input: ");
		gets(string);
		//c = getchar();
		if (strcmp(string, "#") == 0)
		{
			printf("\n\n=================================================================================================\n\n\n");
			printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
			printf("1.Log in\n");
			printf("2.Create a new account\n");
			printf("3.Exit the app\n\n");
			printf("Input: ");
			return 1; //return var == 1, while loop continues
		}
		if (strcmp(string, "$") == 0) {
			printf("Thank you for using sociopath, Bye!");
			return 0; // loop will continue to run and enter the exit condition
		}
		is_sograim = string;
		is_sograim = strchr(is_sograim, ':');
		if (is_sograim == NULL)
		{
			printf("\n\nDear guest, please enter your username and password in the following way: username::password.\n");
			printf("Username does not exist in our memory banks. Please try again.\n\n");
			gets(string);
		}
		else if (is_sograim != NULL)
		{
			if (*is_sograim != ':')
			{
				printf("\n\nDear guest, please enter your username and password in the following way: username::password.\n");
				printf("Username does not exist in our memory banks. Please try again.\n\n");
				gets(string);
			}

		}

		list = split2(string, "::", 1, 2); // split the list
										   //printf("%s %s\n", list[0], list[1]); //print check

		passarr = turnPasswordStringIntoIntArray(list[1]); // int array of password
		it = searchUser(head, list[0]);// it = user
		head = base;
		password_ok = matchPassword(passarr, it); // 1 if pass is ok
		free(passarr);
		passarr = NULL;
		if (usernameInList(list[0], searchit) == 0) //username is not in the list
		{
			searchit = head;
			printf("Username does not exist in our memory banks. Please try again.\n\n");
			continue;
		}
		else if ((usernameInList(list[0], searchit) == 1 && password_ok == 1)) // password is ok, and the name is in the list
		{
			searchit = head;
			user_exist = 1;
			//printf("PASSWORD IS OK");
			return profileMenu(list[0], 0);
		}
		else if ((usernameInList(list[0], searchit) == 1 && password_ok == 0)) // password is not ok, and the name is in the list
		{
			searchit = head;
			while (1)
			{
				printf("\n\n=================================================================================================\n\n\n");
				printf("Dear %s, you have entered a wrong password.\n", it->username);
				printf("Please choose one of the following options:\n");
				printf("1.Re-enter password\n");
				printf("2.If you forgot your password, press '!'\n");
				printf("3.To go back to the first screen enter '#'\n");
				printf("4.To exit the app please enter '$'.\n\n");
				printf("Input: ");
				scanf("%s", badpassword);
				c = getchar();
				if (strcmp(badpassword, "#") == 0) {
					printf("\n\n=================================================================================================\n\n\n");
					printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
					printf("1.Log in\n");
					printf("2.Create a new account\n");
					printf("3.Exit the app\n\n");
					printf("Input: ");
					return 1;
				}
				else if (strcmp(badpassword, "$") == 0) { printf("Thank you for using SocioPath, Bye!"); return 0; }// EXIT // }
				else if (strcmp(badpassword, "!") == 0) {
					printf("\n\n\n=================================================================================================\n\n\n");
					printf("Question: where did you last perform your last air guitar jam?\n");
					printf("To go back to the first screen enter '#'\n");
					printf("To exit the app please enter '$'.\n\n");
					printf("Input: ");
					scanf("%s", answer);
					c = getchar();
					if (strcmp(answer, "#") == 0) {
						printf("\n\n=================================================================================================\n\n\n");
						printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
						printf("1.Log in\n");
						printf("2.Create a new account\n");
						printf("3.Exit the app\n\n");
						printf("Input: ");
						return 1;
					}
					if (strcmp(answer, "$") == 0) { printf("Thank you for using SocioPath, Bye!"); return 0; }// EXIT 
					if (strcmp(answer, it->securityAnswer) == 0) // answer is correct
					{


						encnewpass = create_password(&(it->randomNum), it->username);
						strcpy(it->password, encnewpass);
						//printf("CHECK IF PASS IS VALID AND ENTER IT INTO TXT FILE");
						return profileMenu(list[0], 0);

					}//CHECK IF PASS IS VALID AND ENTER INTO TXT FILE
					while (strcmp(answer, it->securityAnswer) != 0)
					{
						if (strcmp(badpassword, "$") == 0) { printf("Thank you for using SocioPath, Bye!"); return 0; }// EXIT  
						if (strcmp(badpassword, "#") == 0) {
							printf("\n\n=================================================================================================\n\n\n");
							printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
							printf("1.Log in\n");
							printf("2.Create a new account\n");
							printf("3.Exit the app\n\n");
							printf("Input: ");
							return 1; //return var == 0, while loop continues
						}
						printf("\nDear %s, you have entered a wrong answer, please try again.\n", it->username);
						scanf("%s", answer);
						c = getchar();
						count++;
						if (strcmp(answer, it->securityAnswer) == 0) // answer is correct
						{
							printf("Hello dear %s! Please choose a new password.\nInput: ", it->username);
							encnewpass = create_password(&(it->randomNum), it->username);
							strcpy(it->password, encnewpass);
							printf("\n\n========================================================================\n\n\n");
							return 1;
						}

						if (count == 2) {
							printf("\nDear %s, you failed to enter the correct answer 3 times.\n", it->username);
							printf("\n\n=================================================================================================\n\n\n");
							printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
							printf("1.Log in\n");
							printf("2.Create a new account\n");
							printf("3.Exit the app\n\n");
							printf("Input: ");
							return 1; //return input == 1, while loop continues
						}



					}

				}
				secpassarr = turnPasswordStringIntoIntArray(badpassword);
				secpass_ok = matchPassword(secpassarr, it);
				if (secpass_ok == 0) // password not ok
				{
					//printf("PASSWORD IS NOT OK");
					continue;
				}
				else {
					//printf("PASS #2 IS OK");
					return profileMenu(list[0], 0);
				}
				//GO TO PROFILE PAGE


			}
		}
	}



	return *var;
}

	