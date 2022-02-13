#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Basics of programming 1 (Course ID: VIEEAA00)
Name: Tushig Bat-Erdene
Neptun ID: QBI3JH
Academic year: 2020/21/1
Date: 2020/11/01
Homework Specification: Morse code
I chose Morse homework to challenge myself to create a Morse converter program that should be
controlled by the command-line tool. I created a program that can convert code text into the
Morse and decode Morse code into the text using a binary tree. Also, I added history which can
display the previous conversions and add them into the history.txt file.
And Morse file into text file, and text file into Morse file was so challenging to me, their options
can generate file.txt and newfile.txt only after exiting the program.

Using linked list to create binary tree which will help to search
*/
typedef struct Binary_Tree
{
	char character;
	int key;
	struct Binary_Tree * left;
	struct Binary_Tree * right;
}

Binary_Tree;
/*Creating structure of library which contains character, and string has morse code in it*/
typedef struct MorseLibrary
{
	char character;
	char *Morse_code;
}

MorseLibrary;

/*Creating array which contains all characters and its translation in morse*/
MorseLibrary characters[] = {
	{'a', ".-"},
	{'b', "-..."},
	{'c', "-.-."},
	{'d', "-.."},
	{'e', "."},
	{'f', "..-."},
	{'g', "--."},
	{'h', "...."},
	{'i', ".."},
	{'j', ".---"},
	{'k', "-.-"},
	{'l', ".-.."},
	{'m', "--"},
	{'n', "-."},
	{'o', "---"},
	{'p', ".--."},
	{'q', "--.-"},
	{'r', ".-."},
	{'s', "..."},
	{'t', "-"},
	{'u', "..-"},
	{'v', "...-"},
	{'w', ".--"},
	{'x', "-..-"},
	{'y', "-.--"},
	{'z', "--.."},
	{'0', "-----"},
	{'1', ".----"},
	{'2', "..---"},
	{'3', "...--"},
	{'4', "....-"},
	{'5', "....."},
	{'6', "-...."},
	{'7', "--..."},
	{'8', "---.."},
	{'9', "----."},
	{':', "--..."},
	{',', "--..--"},
	{'(', "-.--."},
	{')', "-.--.-"},
	{'!', "-.-.--"},
	{'/', "-..-."},
	{'=', "-...-"},
	{'-', "-....-"},
	{'@', ".--.-."},
	{'+', ".-.-."},
	{'.', ".-.-.-"},
	{'"', ".-..-."},
	{' ', "   "}
};

/*Creating a function that can make it possible to setting aside the characters in the binary tree*/
Binary_Tree* node(char item, int key)
{
	Binary_Tree *tmp = (Binary_Tree*) malloc(sizeof(Binary_Tree)); /*Creating node*/
	tmp->character = item;
	tmp->key = key;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

/*Inserting characters to Binary_Tree*/
/*It goes left or right depending on its key value*/
Binary_Tree* insert_characters(Binary_Tree *start, char value, int key)
{
	if (start == NULL)
		return node(value, key);
	if (key < start->key)
		start->left = insert_characters(start->left, value, key);
	else if (key > start->key)
		start->right = insert_characters(start->right, value, key);
	return start;
}

/*creating the binary tree*/
Binary_Tree* CreateMorse(void)
{
	Binary_Tree *start = NULL;
	char characters[60] = " tmo#09#8:gqz#,7nky()c#!dx/b=6-eawj1'p#@r#+.l#&iu#2#?fsv3h45"; /*Available characters in order of their insertion*/
	int keys[60] = { 31, 15, 8, 4, 2, 1, 3, 5, 6, 7, 10, 9, 13, 12, 11, 14, 23, 19, 16, 18, 17, 22, 21, 20, 26, 24, 25, 28, 27, 30, 29, 47, 39, 35, 34, 32, 33, 38, 36, 37, 43, 40, 42, 41, 45, 44, 46, 54, 52, 49, 48, 50, 51, 53, 57, 56, 55, 59, 58, 60 }; /*key values of characters*/

	start = insert_characters(start, characters[0], keys[0]);
	for (int i = 1; i < 60; i++) /*inserting all available characters to tree using insert function*/
	{
		insert_characters(start, characters[i], keys[i]);
	}

	return start;
}

/*adding items to Morse library*/
MorseLibrary InsertToML(char chr, char *string)
{
	MorseLibrary newItem;
	newItem.character = chr;
	newItem.Morse_code = string;
	return newItem;
}

/*Getting morse code from the Binary_Tree*/
char Get_Morse_Code(char *str, Binary_Tree *start)
{
	int size = strlen(str); /*getting length of the str*/
	Binary_Tree *pointer = start;
	for (int i = 0; i < size; i++)
	{
		if (str[i] == ' ') /*| is space*/
		{
			break;
		}

		if (str[i] == '-') /*dash is left*/
		{
			pointer = pointer->left;
		}

		if (str[i] == '.') /*dot is right*/
		{
			pointer = pointer->right;
		}

		if (pointer == NULL) /*if start couldn't find anything it will return 0*/
		{
			printf("Invalid code!\n");
			return 0;
		}
	}

	return pointer->character;

}

/*Deleting nodes from Binary tree*/
void delete_node(Binary_Tree *root)
{
	if (root == NULL) /*it will delete nodes till gets*/
	{
		return;
	}

	delete_node(root->left);
	delete_node(root->right);
	free(root);
}

/*Creating file.txt*/
void create_file()
{
	FILE * create_f;
	create_f = fopen("file.txt", "w"); /*opening file*/
	fprintf(create_f, "Content of the file: \n"); /*writing in a opened file*/
	fclose(create_f); /*closing file*/
}

/*Creating a newfile.txt*/
void create_newfile()
{
	FILE * create_nf;
	create_nf = fopen("newfile.txt", "w"); /*opening file*/
	fprintf(create_nf, "Content of the file: \n"); /*writing in a opened file*/
	fclose(create_nf); /*closing file*/
}

void add_text(char *txt) /*adding text to file.txt*/
{
	FILE * add_txt;
	add_txt = fopen("file.txt", "a"); /*appending char into the file.txt*/
	fputs(txt, add_txt);
	fputs(" ", add_txt);
	fclose(add_txt);
}

void add_morse_text(char *morsetxt) /*adding text to newfile.txt*/
{
	FILE * add_txt;
	add_txt = fopen("newfile.txt", "a"); /*appending char into the file.txt*/
	fputs(morsetxt, add_txt);
	fputs(" ", add_txt);
	fclose(add_txt);
}

void create_history_file() /*generating the history.txt file*/
{
	FILE * create_history;
	create_history = fopen("history.txt", "w"); /*opening and writing file*/
	fprintf(create_history, "Previous conversions are: \n"); /*writing inside the file*/
	fclose(create_history);	// closing the file
}

/*adding string to history.txt*/
void history_add_string(char *HistoryAdd)
{
	FILE * has;
	has = fopen("history.txt", "a");
	fputs(HistoryAdd, has);
	fputs(" ", has);
	fclose(has);
}

/*getting a line break with printing lower dashes to look better*/
void history_line_break()
{
	FILE * hlb;
	hlb = fopen("history.txt", "a");
	fputs("\n_________________________________________________\n", hlb);
	fclose(hlb);
}

/*Function to convert text to morse*/
void TextToMorse(char *txt, int length)
{
	/*loop for itterating the string*/
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < 49; j++) /*comparing the characters and morse code*/
		{
			if (txt[i] == characters[j].character)
			{
				printf("%s ", characters[j].Morse_code);
				add_morse_text(characters[j].Morse_code); /*adding converted morse code into the newfile.txt*/
				history_add_string(characters[j].Morse_code); /*adding converted morse code into the history.txt*/
			}
		}
	}
}

/*adding char to history.txt*/

void MorseTotext(char *str1, Binary_Tree *top)
{
	FILE *AddCharToNewfile, *hac;
	AddCharToNewfile = fopen("newfile.txt", "a"); /*appending char into the newfile.txt*/
	hac = fopen("history.txt", "a");

	char *str_token;
	history_add_string(str1);
	str_token = strtok(str1, " ");	// I had to make it return to a pointer to the first character
	printf(" Result: ");
	while (str_token != NULL)
	{
		printf("%c", Get_Morse_Code(str_token, top));
		fputc(Get_Morse_Code(str_token, top), AddCharToNewfile);
		fputc(Get_Morse_Code(str_token, top), hac);
		str_token = strtok(NULL, " ");	//getting spaces between morse codes
	}

	fclose(AddCharToNewfile);
	fclose(hac);
	history_line_break();

}

int main()
{
	Binary_Tree * top;
	top = CreateMorse();
	char *s = (char*) malloc(100);
	create_history_file();
	int menu;
	do {
		printf("\n_________________________________________________\n"
			" 0. Display the statistics\n"
			" 1. Convert text to Morse code\n"
			" 2. Convert Morse code to text\n"
			" 3. Text file to Morse file\n"
			" 4. Morse file to text file\n"
			" 5. Display previous conversions\n"
			" 6. Exit\n"
			"_________________________________________________\n "
			"Select /0-6/ --> ");
		scanf("%d", &menu);
		switch (menu)
		{
			/*Display the statistics*/
			case 0:
				printf("Displaying the statistics:\n");
				for (int i = 0; i < 49; i++) /*print all statistics*/
				{
					printf("%c < -> %s\n", characters[i].character, characters[i].Morse_code);
				}

				break;
				/*Convert text to morse*/
			case 1:

				printf(" Enter a text to convert into Morse\n"
					" (Please use non-capital letter /Ex: a not A/)\n"
					" : ");
				scanf(" %[^\t\n]s", s);
				int length = strlen(s);
				history_add_string(s);
				printf(" Result: ");
				TextToMorse(s, length);

				history_line_break();

				break;
				/*Convert morse to text*/
			case 2:
				; /*semi-colon added after the label it will give error without it*/
				char str1[100];
				printf(" Enter a Morse code to convert into text:\n"
					"Please use -> |<- to take space\n");
				scanf(" %[^\t\n]s ", str1);
				MorseTotext(str1, top);
				break;

			case 3:
				; /*semi-colon added after the label it will give error without it*/

				create_file();
				create_newfile();
				printf(" Enter the text to add in file.txt\n"
					" (Please use non-capital letter /Ex: a not A/)\n"
					" : ");
				scanf(" %[^\t\n]s", s);
				int length1 = strlen(s);
				add_text(s);
				history_add_string(s);

				printf(" Result: ");
				TextToMorse(s, length1);

				printf("\nFile converted into newfile.txt\n"
					" Please choose -> 6.exit < - first.\n");
				history_line_break();
				break;
			case 4:
				;
				/*semi-colon added after the label it will give error without it*/
				create_file();
				create_newfile();
				printf(" Enter a Morse code to convert into text:\n"
					" Please use -> |<- to take space\n");
				scanf(" %[^\t\n]s ", str1);
				add_text(str1);
				MorseTotext(str1, top);
				printf("\nFile converted into newfile.txt\n"
					" Please choose -> 6.exit < - first.\n");
				break;
			case 5:
				;
				FILE * print_history;	//printing the history
				char phc;
				print_history = fopen("history.txt", "r");
				while (fscanf(print_history, "%c", &phc) == 1)
				{
					printf("%c", phc);
				}

				fclose(print_history);

			case 6:
				break;
			default:
				break;
		}

		printf("\n"); /*line break*/
	} while (menu != 6);
	/*setting free strings*/
	delete_node(top);

	return 0;
}

/*references:
http://www.scphillips.com/morse/morse2.html.
http://www.hit.bme.hu/~ghorvath/bop/lecture/
http://www-personal.acfr.usyd.edu.au/tbailey/ctext/ctext.pdf
*/
