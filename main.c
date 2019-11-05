#include "q2.h"
#include "q1.h"
#include <string.h>
int main()
{
	int rand = 0, all, var = 1, input = 0;
	int *pvar = &var, *pinput = &input;

	char string[ANSWER_LEN + USER_LEN + RANDOMNUM_LEN + PASSWORD_LEN], c, stringinput[100000];
	User *head = NULL, *new_user = NULL;
	FILE *fptr;
	//char testpass[9] = "monkeyfun", *binary;
	//int *pass2, pass3;

	all = ANSWER_LEN + USER_LEN + RANDOMNUM_LEN + PASSWORD_LEN;
	
	//printUserList(head);

	fptr = fopen("validation.txt", "r");
	if (NULL == fptr)
	{
		printf("Error Could not open file");
		return 1;
	}
	head = createUserList(fptr, string, all + 1);
	fclose(fptr);

	printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
	printf("1.Log in\n");
	printf("2.Create a new account\n");
	printf("3.Exit the app\n\n");
	printf("Input: ");

	while (var) {
		
		gets(stringinput);
		if (strcmp(stringinput, "1")==0)
		{
			var = logIn(pvar, pinput, head);
			if (var == 0)
			{
				fptr = fopen("validation.txt", "w");
				exitFunc(fptr, head);
				fclose(fptr);
			}

		}
		else if (strcmp(stringinput, "2") == 0) {
			printf("\n\n=================================================================================================\n\n\n");
			head = create_account(head);
			printUserList(head);
			var = profileMenu(head->username, 1);
			if (var != 0)
			{
				printf("Hello dear guest and welcome to 'SocioPath - Socialize in an alternative path'!\nWhat would you like to do next?\n");
				printf("1.Log in\n");
				printf("2.Create a new account\n");
				printf("3.Exit the app\n\n");
				printf("Input: ");
			}
			if (var == 0)
			{
				fptr = fopen("validation.txt", "w");
				exitFunc(fptr, head);
				fclose(fptr);
			}

		}
		else if ((strcmp(stringinput, "3") == 0)) {
			var = 1;
			fptr = fopen("validation.txt", "w");
			exitFunc(fptr, head);
			fclose(fptr);
			printf("RELEASE MEMORY AND EXIT");

		}
		else
		{
			printf("\nInvalid input. Dear guest, please enter '1', '2' or '3'.\n\nInput:");
		}
	}
	return 0;
}