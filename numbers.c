#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define MAX_LINE 5
#define MAX_CHAR 100


char * translate_number (int x);

int main (int argc, char *argv[])
{
	/* ifp: input file pointer*/
	FILE *ifp;
	/* ofp: output file pointer*/
	FILE *ofp;
	/*number: an integer number to be translated*/
	int number;
	/*output: will hold a pointer of the translated string output*/
	char *output;
	/*c: a character to be entered - meant to recieve EOF*/
	char c;
	/*line: i a line in the input file (ifp)*/
	char line[MAX_LINE];
	/*the number of command line argument recieved*/
	int num_of_arguments = argc-1;


	/*this switch case will start the relevant sub program based on the number of argument we recienved*/
	switch (num_of_arguments) {
		/*2 arguments: the first one will be an input file
		the second one will be the output file*/
		case 2 : 
			/*if we were not able to open the input file in read mode*/
			if ((ifp=fopen(argv[1], "r")) == NULL)
				fprintf(stderr ,"Cannot Open file %s\n", argv[1]);
			/*if we were not able to open the output file in write mode*/
			else if ((ofp=fopen(argv[2], "w"))== NULL)
				fprintf(stderr, "Cannot Open file %s\n", argv[2]);
			/*we succeded to open both files*/
			else 
			{
				/*while the input file still has line*/
				while (fgets(line, MAX_LINE, ifp)!= NULL)
				{
				/*replance the enter \n with \0 as string termination*/
				*(strchr(line, '\n'))='\0';
					/*convert the line to integer and assigne to number*/
					number = atoi (line);
					/*translate the number to a string and assigne to output*/
					output = translate_number (atoi(line));
					/*write output to the ouptu file*/
					fprintf(ofp, "%s\n", output);
				}
			}
			/*after we done, close both files*/
			fclose(ifp);
			fclose(ofp);
		break;

		/*we recieved only one file, this will be the input file, the output will
		be redirected to the standart output*/
		case 1 : 
			/*Similiar to "case 2", instead writing the output to an output file
			we printing it to the standart output*/
			if ((ifp=fopen(argv[1], "r")) == NULL)
				fprintf(stderr, "Cannot Open file %s\n", argv[1]);
			else 
			{
				while (fgets(line, MAX_LINE, ifp)!= NULL)
				{
					*(strchr(line, '\n'))='\0';
					number = atoi (line);
					output = translate_number (atoi(line));
					printf("%s\n", output);
				}
			}
			fclose(ifp);
		break;

		/*we didnt recieve output and input files, the input number will be taken
		directly from the standart input and the output will be redirected to the 
		standart output*/
		case 0 : printf("Enter a number to be translated:\n");
			do 
			{	
				/*scan the number with scanf and assign the value to number variable*/
				scanf ("%i", &number);
				/*if translate return a 0 value, this means that the entered number is >= 100 and number is < 0*/
				if (*translate_number(number) == '0')
					/*redirect the error message to the system's standart error*/
					fprintf(stderr, "Not Supported Number\n" );
				else
					/*translate didn't retrun '0', then print the string*/
					printf("%s\n", translate_number(number));
				/*loop while we didn't recieve EOF*/
			} while ((c = getchar()) != EOF);
		break;

		/*we rcieved more that 2 arguments, print the usage*/
		default : fprintf(stderr, "Not Supported\nUsage:  ./numbers <input file> <output file>\nOr\t./numbers <input file>\nOr\t./numbers\n");
		break;
	}
return OK;	
}


/*translate a digit between 0-99 to english*/
char * translate_number(int x){

	/*output of the String translated number*/
	char output_string[MAX_CHAR];
	/*pointer to output_string*/
	char *ptr;
	/*single digit numbers in english*/
	char *single_digit_number[]={"zero", "one","two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
	/*number in englesh when the second digit of a number is zero*/
	char *second_digit_is_zero[]={"0","", "twenty ", "thirty ", "fourty ", "fifty ", "sixty ", "sevnety ", "eighty ", "ninty "};
	/*the number in english when the first digit is one*/
	char *first_digit_is_one[]={"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","ninteen","twenty"};
	ptr = output_string;


	/*if the number between 0-9, return the name of it which located in the number idex in single_digit_number array*/
	if (x >= 0 && x < 10)
		return single_digit_number[x];
	/*if number between 9-99 but the first digit is one*/
	else if(x > 9 && x < 100 && x/10 == 1)
		return first_digit_is_one[x%10];
	/*if the number between 9-99 but the second digit is zero*/
	else if (x > 9 && x < 100 && x%10 == 0)
		return second_digit_is_zero[x/10];
	/*if a number that the second digit is not zero and the first digit is not one,
	it result in english as a combination between the both arrays (second_digit_is_zero and single_digit_number)*/
	else if(x > 9 && x < 100 && x%10 != 0 && x/10 !=1)
	{
		/*copy the right string from the first array to the output_string*/
		strcpy (output_string, second_digit_is_zero[x/10]);
		/*concatante the right string to it from the right array*/
		strcat (output_string, single_digit_number[x%10]);
		/*return a pointer of the ouput_string*/
		return ptr;
	}
	else return second_digit_is_zero[0];
}