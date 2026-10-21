// Coding Assignment 6
// Name: Arshan Mungala
// ID : 1002148516

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 1000 
 
/* Node for storing information */
typedef struct Digimon
{
    char *name;
    float SP;
    char attribute;
    int HP;
    struct Digimon *next_ptr;
}
DIGIMON;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char*key)
{
    unsigned int hash = 0;

    while (*key)
    {
        hash = hash *31 + (unsigned char)(*key);
        key++;
    }
    return hash % HASHTABLESIZE;
}

void AddNode(DIGIMON *NewNode, DIGIMON *DigiGuide[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (DigiGuide[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		DigiGuide[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		DIGIMON *TempPtr = DigiGuide[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(DIGIMON *DigiGuide[])
{
	DIGIMON *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = DigiGuide[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(DIGIMON *DigiGuide[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Digimon to delete from the DigiGuide ");
	fgets(LookupName,sizeof(LookupName),stdin);
	LookupName[strcspn(LookupName,"\n")] = '\0';

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	DIGIMON *TempPtr = DigiGuide[HashIndex];
	DIGIMON *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nDigimon %s does not exist in the DigiGuide\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == DigiGuide[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					DigiGuide[HashIndex] = TempPtr->next_ptr;
					printf("\nDigimon %s has been deleted from the DigiGuide\n\n", TempPtr->name);
					free(TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nDigimon %s has been deleted from the DigiGuide\n\n", TempPtr->name);
					free(TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nDigimon %s does not exist in the DigiGuide\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(DIGIMON *DigiGuide[])
{
	int i;
	DIGIMON *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = DigiGuide[i];

		printf("\nDigiGuide[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(DIGIMON *DigiGuide[])
{
	int i;
	DIGIMON *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = DigiGuide[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(DIGIMON *DigiGuide[])
{
	DIGIMON *TempPtr = NULL;
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Digimon's name ");
	fgets(LookupName,sizeof(LookupName),stdin);
	LookupName[strcspn(LookupName,"\n")] = '\0';
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = DigiGuide[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					printf("SP\t\t%.2f\n", TempPtr->SP);
					printf("Attribute\t%c\n", TempPtr->attribute);
					printf("HP\t\t%d\n", TempPtr->HP);

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nDigimon %s not found in DigiGuide\n\n", LookupName);
}

void AddNewDigimon(DIGIMON *DigiGuide[])
{
	int HashIndex = 0;
	DIGIMON *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(DIGIMON));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Digimon's name ");
	fgets(TempBuffer, sizeof(TempBuffer), stdin);
	TempBuffer[strcspn(TempBuffer, "\n")] = '\0';
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's SP ", NewNode->name);
	scanf(" %f", &(NewNode->SP));
	
	printf("\n\nEnter %s's attribute ", NewNode->name);
	scanf(" %c", &(NewNode->attribute));
	NewNode->attribute = toupper(NewNode->attribute);
	
	printf("\n\nEnter %s's HP ", NewNode->name);
	scanf(" %d", &(NewNode->HP));
	
	getchar();

	AddNode(NewNode, DigiGuide);
}

int ReadFileIntoHashTable(int argc, char *argv[], DIGIMON *DigiGuide[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	DIGIMON *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(DIGIMON));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->SP = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->attribute = *token;
			
			token = strtok(NULL, "|");
			NewNode->HP = atoi(token);

			AddNode(NewNode, DigiGuide);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	DIGIMON *DigiGuide[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, DigiGuide);
 
	do
	{
		printf("\n\nDigiGuide Menu\n\n"
			   "1. Show all Digimon in DigiGuide for a given letter\n"
			   "2. Look up Digimon by name\n"
			   "3. How many Digimon are in the DigiGuide?\n"
			   "4. Display the DigiGuide\n"
			   "5. Add a new Digimon\n"
			   "6. Delete a Digimon from the DigiGuide\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		getchar();
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(DigiGuide);
				break;
			case SHOWBYNAME:
				ShowByName(DigiGuide);
				break;
			case COUNT:
				printf("Your DigiGuide contains %d Digimon\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(DigiGuide);
				break;
			case ADD:
				AddNewDigimon(DigiGuide);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(DigiGuide))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(DigiGuide);

	return 0;
}