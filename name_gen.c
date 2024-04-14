 /* Copyright 2024 Vitaly Castaño Solana <vita_cell@hotmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

 /************************** DESCRIPTION *******************************
Program that generates a person's name for use in a game profile
It generates random names using a combination of predefined syllables
and rules to add vowels and consonants coherently.

Here's how it works:

 -Minimum and maximum name lengths are defined, and a random length within that range is generated.
 -Dynamic memory is allocated to store the name.
 -The name is initialized as an empty string with string end /0.
 -Arrays of vowels, consonants, and fixed syllables are defined.
 -The seed for random numbers is initialized.
 -It iterates until the length of the name reaches the desired name's length.
 -In each iteration, a fixed syllable is randomly chosen and added/concatenated
 to the name.
 -Rules are applied to ensure the name has a coherent structure, such as
 avoiding three consecutive consonants or handling the "oo" sequence specially.
 -Finally, the generated name is printed, and memory is freed.

The code is made easy to understand. However, note that there are parts of the code that could be simplified or made more efficient, such as avoiding repeating certain operations inside the loop.
***********************************************************************/

#include <stdio.h>	// input/output handling library
#include <stdlib.h>	// standart library
#include <time.h>	// time handling library
#include <string.h> // string handling library
#include <stdbool.h> // true/false data type

// Macros (remove "//" before "printf" for enable)
#define DEBUG printf

/***********************************************************************
Makes sure that our string terminates with end character '\0'
***********************************************************************/
void write_string_termination(char *name, int name_length)
{
    if (name[name_length] != '\0')
    {
		name[name_length] = '\0';
	}
}

/***********************************************************************
Function for generating a random pronounceable person name without
using a database
***********************************************************************/
void generate_name()
{
	// define and initialize the possible range for the name
	int min_length = 3; // we don't want a name with less than 3 letters
    int max_length = 8; // theoretically we aim for a maximum of 8 letters

	// Generate a length between min_length and max_legth
	// int length = 3 + (random % (6))
	// the random % 6 will give us the remainder between 0 and 5
	// theoretically max possible name length
	int length = min_length + rand() % (max_length - min_length + 1);

	// actual name length
	unsigned short name_length = 0; // count the characters inside name[]

	// name characters array with dynamic memory allocation for 20 chars
	// size, +1 char for \0
	//char* name = (char*)malloc((length + 1) * sizeof(char)); // +1 for last '\0' char
	char* name = (char*)malloc((20 + 1) * sizeof(char)); // reserve memory  for

	if (name == NULL)
	{
		printf("ERROR: couldn't assign memory for name characters array\n");
		exit(1);
    }

	// Initialize name as an empty string with \0 for string handling functions
	name[0] = '\0';

	// Define the letters that can be used unitarily
	char vowels[] = "aeiou";
	char consonants[] = "bcdfghjklmnpqrstvwxyz"; // Keep in mind that “Y”
	// can sometimes function as a vowel (which is known as a semivowel).

	// define most frequent syllables that start with a consonant
	char* syllables_consonant[] = {"ba", "be", "bi", "bo", "bu", "da", "de",
									"di", "do", "du", "la", "le", "li", "lo",
									"lu", "ma", "me", "mi", "mo", "mu", "na",
									"ne", "ni", "no", "nu", "pa", "pe", "pi",
									"po", "pu", "ra", "re", "ri", "ro", "ru",
									"sa", "se", "si", "so", "su", "ta", "te",
									"ti", "to", "tu", "va", "liy","man","mar",
									"vit", "ye", "tom", "lay", "fri", "rom",
									"mor", "dal", "fre", "fro", "ch", "ha",
									"je", "ja", "ju", "ga", "mon", "mir"};

		// define most frequent syllables that start with a vowel
	char* syllables_vowel[] = {"oo", "imp", "um", "ius", "ip", "olf", "ali"};

	// vars for trigger double letters randomly
	unsigned int probability = 0;
	//unsigned int probability_result = 0;

	// Initialize random numbers' seed
	srand(time(NULL));

	// count the WHILE loop runs (for debug only)
	int temp_run_count = 0;
	//int name_length = 0;

	DEBUG("Name before the WHILE loop: %s\n", name);

	// Start building the name
	//for (int i = 0; name_length < length; i++) // run FOR until it reaches the max length
	do
	{
		// Use some existing syllable
		//while (i < (length) )
		//{

			DEBUG("Name length at starting while loop: %d\n", name_length);

			// at he first (0) while loop run, randomly decide with 50% of
			// probability if to start with a vower or a consonant letter
			if (temp_run_count == 0)
			{
				memset(name, '\0', sizeof(name)); // clears the whole string

				if (rand() % 100 <=49) // if probability is between 0-49
				{
					name[name_length] = vowels[rand() % strlen(vowels)]; // add a vowel
					DEBUG("We started the name with a vowel: %c\n", name[0]);
				}
				else if ( (rand() % 100 <=99) && (rand() % 100 >=50) ) // if probability is between 50 and 99
				{
					name[name_length] = consonants[rand() % strlen(consonants)]; // add a consonant
					DEBUG("We started the name with a consonant: %c\n", name[0]);
				}

				name_length = strlen(name); // get current name length
				write_string_termination(name, name_length);
				//name[name_length] = '\0'; // add end character for correct string handling
				DEBUG("Name after generating the first letter: %s\n", name);
				DEBUG("Name length after generating the first letter: %d\n", name_length);
			}

			// if we have a vowel as last char of the string (before "/0")
			//if (strchr("bcdfghjklmnpqrstvwxyz", name[name_length - 1]) == NULL)
			if (strchr("aeiou", name[name_length - 1]) != NULL)
			{
				// Use some existing syllable
				// declare, choose and store a random syllable
				char* syllable_con = syllables_consonant[rand() %
							(sizeof(syllables_consonant) / sizeof(syllables_consonant[0]))];

				// Obtain the length of the selected syllable
				int syllable_length = strlen(syllable_con);
				DEBUG("\nSelected consonant syllable length: %d\n", syllable_length);
				DEBUG("Name before adding a consonant syllable: %s\n", name);
				DEBUG("\nOur consonant syllable to add: %s\n", syllable_con);

				strcat(name, syllable_con); // Concatenate the name with syllable
				name_length = strlen(name); // get name length
				write_string_termination(name, name_length);
				//name[name_length] = '\0'; // add end character for correct string handling
				//name_length = name_length + strlen(syllable); // update the name length

				// copy a syllable into the name
				//for (int e = 0; syllable[e] != '\0'; e++)
				/*for (int e = 0; e < syllable_length; e++)
				{
					DEBUG("%c", syllable[e]);
					DEBUG("\nName length: %d\n", name_length);
					name[name_length] = syllable[e]; // copy the syllable's letter into the name
					name_length = strlen(name);
					//i = i + 1;
				}*/
				DEBUG("\nName after adding a consonant syllable: %s\n", name);
				DEBUG("Name length: %d\n", name_length);
				DEBUG(" --- now we finished a consonant syllable integration\n");
			}

			// if we have a consonant as last char of the string (before "/0")
			if (strchr("bcdfghjklmnpqrstvwxyz", name[name_length - 1]) != NULL)
			{
				// Use some existing syllable
				// declare, choose and store a random syllable
				char* syllable_vow = syllables_vowel[rand() %
							(sizeof(syllables_vowel) / sizeof(syllables_vowel[0]))];

				// Obtain the length of the selected syllable
				int syllable_length = strlen(syllable_vow);
				DEBUG("\nSelected vowel syllable length: %d\n", syllable_length);
				DEBUG("Name before adding a vowel syllable: %s\n", name);
				DEBUG("\nOur vowel syllable to add: %s\n", syllable_vow);

				strcat(name, syllable_vow); // Concatenate the name with syllable
				name_length = strlen(name); // get name length
				write_string_termination(name, name_length);
				//name[name_length] = '\0'; // add end character for correct string handling
				//name_length = name_length + strlen(syllable); // update the name length

				// copy a syllable into the name
				//for (int e = 0; syllable[e] != '\0'; e++)
				/*for (int e = 0; e < syllable_length; e++)
				{
					DEBUG("%c", syllable[e]);
					DEBUG("\nName length: %d\n", name_length);
					name[name_length] = syllable[e]; // copy the syllable's letter into the name
					name_length = strlen(name);
					//i = i + 1;
				}*/
				DEBUG("\nName after adding a vowel syllable: %s\n", name);
				DEBUG("Name length: %d\n", name_length);
				DEBUG(" --- now we finished a vowel syllable integration\n");
			}

		//}

		// If we have some vowel at previous position &&
		// previous position is not 'q' letter
		if ( (strchr("aeiou", name[name_length - 1]) != NULL)
							&& (name[name_length - 1] != 'q')
							&& (name_length + 1) < length )
		{ // If a position is even, add a consonant
			// consonants[random % 5-1] == 0-4 range
			DEBUG("\n 1º IF previous char: %c\n", name[name_length - 1]);
			DEBUG("\n TRUE: we have a vowel at previous position and it is not 'q'\n");

			int random_index = rand() % strlen(consonants);
			char selected_consonant = consonants[random_index];
			name[name_length] = selected_consonant;
			name_length++;
			write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
			//name[name_length] = '\0';
			DEBUG("Selected consonant character is '%c' at the position %d of consonants array.\n", selected_consonant, random_index);


			// Add just 1 consonant letter randomly
			//name[name_length] = consonants[rand() % strlen(consonants)];
			DEBUG("1 -d--- added consonant: %c\n", name[name_length - 1]);
			//DEBUG("\n -i--- Name after adding a consonant: %s\n", name);

			// Be careful with this, this return the size of 'consonants'
			// in bytes, not the number of elements
			//name[name_length] = consonants[rand() % (sizeof(consonants) - 1)];

			name_length = strlen(name); // get total name length
			probability = rand() % 100; // 0-99 range random number

			// we want to add some probability for double consonant
			if ( (name_length > 1 && (name_length + 1) < length)
						&& // we do "name_length + 1 < length" for test if we have enough room for a vowel in "case"
						(name[name_length - 1] == 't' ||
						name[name_length - 1] == 'd' ||
						name[name_length - 1] == 'l' ||
						name[name_length - 1] == 'h' ||
						name[name_length - 1] == 's' ||
						name[name_length - 1] == 'n' ||
						name[name_length - 1] == 'f' ||
						name[name_length - 1] == 'g')
						&&
						(probability >= 70 && probability <= 99) ) // 29% probability
			{
				DEBUG("\n CASE TRUE with %d%% of probability\n", probability);
				switch (name[name_length - 1]) // the position before string's end "/0"
				{
					case 't':
						name[name_length] = 't'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 't' ***\n");
						break;

					case 'd':
						name[name_length] = 'd'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 'd' ***\n");
						break;

					case 'l':
						name[name_length] = 'l'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 'l' ***\n");
						break;

					case 's':
						name[name_length] = 's'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 's' ***\n");
						break;

					case 'n':
						name[name_length] = 'n'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 'n' ***\n");
						break;

					case 'f':
						name[name_length] = 'f'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 'f' ***\n");
						break;

					case 'g':
						name[name_length] = 'g'; // add same consonant letter
						//i++;
						if (name_length < length) // add a vowel if here is a room before max length
						{	// add a vowel
							//name[name_length + 1] = vowels[rand() % (sizeof(vowels) - 1)]; // in bytes
							name[name_length + 1] = vowels[rand() % strlen(vowels)];
						}
						//name_length++; // increase position
						//write_string_termination(name, name_length);
						//name[name_length] = '\0'; // put string end "/0" at the end in the increased position
						DEBUG("\n *** CASE 'g' ***\n");
						break;
					DEBUG("\n CASE: we added a consonant, for make it double, and then we added a vowel\n");
				}
				//name_length = strlen(name);
				//write_string_termination(name, name_length);
			}
			name_length = strlen(name); // get name length
			write_string_termination(name, name_length);
			DEBUG("\n -i--- Name after adding a consonant: %s\n", name);
		}
		else if (name_length < length)
		{ // add a vowel
			if ( (name_length >= 0 && name_length < length - 1) && (name[name_length - 1] == 'q') )
			{
				DEBUG("\n TRUE: we have a 'q' at previous position\n");
				name[name_length] = 'u'; // put 'u' after 'q'
				DEBUG("2 -d--- added 'u' is: %c\n", name[name_length]);
				//name_length++;
				//write_string_termination(name, name_length);
				//name[name_length] = '\0';
				//i++; // increase 'i' after that

				DEBUG("\n -i--- We added 'u' after 'q'\n");
				DEBUG(" -i--- Name after adding 'u': %s\n", name);

				name_length = strlen(name); // get name length
				write_string_termination(name, name_length);

				if (name_length < length) // if still is less than length
				{ // add a vowel after 'u'
					name[name_length] = vowels[rand() % strlen(vowels)];
					DEBUG("3 -d--- added vowel: %c\n", name[name_length]);
					name_length++;
					write_string_termination(name, name_length);
					//name[name_length] = '\0';

					DEBUG("\n -i--- We added a vowel after 'u'\n");
					DEBUG(" -i--- Name after adding a vowel after 'u': %s\n", name);

					//i++; // increase 'i' position after the 'u'
					if (name_length < length) // if 'i' position is still is less than length
					{ // add a consonant after vowel
						name[name_length] = consonants[rand() % strlen(consonants)];
						name_length++;
						write_string_termination(name, name_length);
						//name[name_length] = '\0';
						DEBUG("4 -d--- added consonant: %c\n", name[name_length]);

						DEBUG("\n -i--- We added a consonant after 'u + vowel'\n");
						DEBUG(" -i--- Name after adding a consonant: %s\n", name);
					}
				}
			}
			// We don't want 3 consonants
			else if ((strchr("bcdfghjklmnpqrstvwxyz", name[name_length - 2]) != NULL)
						&& (strchr("bcdfghjklmnpqrstvwxyz", name[name_length - 1]) != NULL)
						&& name_length < length )
			{
				DEBUG("\n TRUE: we have 2 consonants and we must to add a vowel\n");

				name[name_length] = vowels[rand() % strlen(vowels)];
				name_length++;
				write_string_termination(name, name_length);
				//name[name_length] = '\0';
				DEBUG("5 -d--- added vowel: %c\n", name[name_length]);

				DEBUG(" -i--- Name after adding a vowel: %s\n", name);
			}
			else if (name_length < length)
			{
				name[name_length] = vowels[rand() % strlen(vowels)];
				name_length++;
				write_string_termination(name, name_length);
				//name[name_length] = '\0';
				DEBUG("6 -d--- added vowel: %c\n", name[name_length]);

				DEBUG(" -i--- Name after just adding a vowel: %s\n", name);
			}
		}

		name_length = strlen(name); // get name length
		write_string_termination(name, name_length);

		for (int j = 0; j < length - 1; j++)
		{	// Test for double 'oo', and if 'oo' has a vowel before it
			if (name[j] == 'o' && name[j + 1] == 'o')
			{
				// this DEBUG will print 2 times, because of 2x 'o'
				DEBUG("\n TRUE: we have a double 'oo' or we have a vowel before 'oo'\n");

				// Verify if we have vowel before "oo"
				// char *strchr(const char *str, int character)
				// strchr returns a pointer other than NULL, it means
				// the character is a vowel
				if (j > 0 && strchr("aeiou", name[j - 1]) != NULL)
				{
					// We found a vowel before "oo"
					DEBUG("\n !!! We found a vowel before 'oo' !!!\n");
					DEBUG("\tBefore modify vowel before 'oo': %s\n", name);
					name[j - 1] = consonants[rand() % strlen(consonants)];
					name_length = strlen(name); // get name length
					write_string_termination(name, name_length);
					//name[name_length] = '\0';
					DEBUG("7 -d--- added consonant: %c\n", name[j - 1]);
					DEBUG("\t -i--- After modify vowel before 'oo': %s\n\n", name);

				}
				// Verify if we have "oo" at the start of the name
				if (name[0] == 'o' && name[1] == 'o')
				{
					DEBUG("\n !!! We have 'oo' at the start !!!\n");
					DEBUG("\tBefore modify 'oo' at start: %s\n", name);

					// Move every char to the next position
					memmove(name + 1, name, length);

					// Put a consonant at 0 position
					name[0] = consonants[rand() % strlen(consonants)];
					name_length = strlen(name); // get name length
					write_string_termination(name, name_length);
					//name[name_length] = '\0';
					DEBUG("8 -d--- added consonant: %c\n", name[0]);

					DEBUG("\tAfter modify 'oo' at start: %s", name);

					//i++;
				}
			}
		}

		for (int t = 0; t < length - 1; t++)
		{	// Test for double 'uu'
			if ( (name[t] == 'u') && (name[t + 1] == 'u') )
			{
				DEBUG("\n TRUE: we have a double 'uu'\n");
				DEBUG("\tName before modify 'uu': %s\n", name);

				//char non_u_vowel;

				do // we don't want to generate 'u' again
				{
					name[t + 1] = vowels[rand() % strlen(vowels)];
				}
				while (name[t + 1] == 'u');

				//name[t + 1] = vowels[rand() % strlen(vowels)];
				name_length = strlen(name); // get name length
				write_string_termination(name, name_length);
				//name[name_length] = '\0';
				DEBUG("9 -d--- added consonant: %c\n", name[t + 1]);
				DEBUG("\t -i--- Name after modify 'uu': %s\n\n", name);

			}
		}

		// we should test our generated name at every loop, for 3 consecutive
		// identical consonants, and replace one of these
		for (int p = 0; p < name_length - 2; p++)
		{	// will check always 3 consecutive letters
			if (name[p] == name[p + 1] &&
				name[p + 1] == name[p + 2] &&
				strchr(consonants, name[p]) != NULL)
			{
				DEBUG("\n 11 -d--- Found three consecutive identical consonants at position %d: %c\n x3", p, name[p]);

				// Replace one of the consecutive identical consonants with a different consonant or a vowel
				char replacement = (rand() % 2 == 0) ? consonants[rand() % strlen(consonants)] : vowels[rand() % strlen(vowels)];
				name[p] = replacement;

				DEBUG(" Replaced with: %c\n", replacement);
			}
		}
		name_length = strlen(name); // get name length
		// we need to know the actual real length
		//name_length = sizeof(name) / sizeof(name[0]); // this returns a ponter size only

		//name_length = strlen(name);
		//i = name_length;
		write_string_termination(name, name_length);
		temp_run_count = temp_run_count + 1;
		DEBUG("\nWe finished the WHILE loop run time %d\n", temp_run_count);
	}
	while (name_length < length); // run WHILE until it reaches the max length

	DEBUG("\nGenerated name length: %d\n", name_length);
	//name[name_length] = '\0'; // add NULL character string's end after the latest position
	//write_string_termination(name, name_length);

	DEBUG("\nGenerated name length after adding 0 at the end of the string: %d\n", name_length);
	printf("\n\tGENERATED NAME RESULT: %s\n", name);
	free(name); // clean the memory
}

/***********************************************************************
Clear any trash inside buffer

 * DESCRIPTION: This function is useful in situations where you want to
 * discard any additional characters in the input buffer, such as after
 * reading input with scanf() or fgets(), to prevent those characters
 * from affecting subsequent input operations.
 *
 * FUNCTIONALITY:
 * from the standard input using getchar().

 * -The loop continues as long as the character read (tmp_c) is not a
 * newline character ('\n') and not the end-of-file (EOF) character.

 * -Inside the loop, there is no operation other than reading characters.

 * -The purpose of this loop is to clear the input buffer by consuming
 * all characters in it until either a newline character or EOF is encountered.

 * -Once a newline character or EOF is encountered, the loop terminates,
 * and the function returns, leaving the input buffer cleared.
***********************************************************************/
void clear_input_buffer()
{
    int tmp_c; //stores characters read from the input buffer
	// reads from standard input and stores the character,
	// loops as long as the character read if
	// is not a newline character ('\n') and not the
	// end-of-file (EOF) character
    while((tmp_c = getchar()) != '\n' && tmp_c != EOF); // -clears the
    // buffer and cut if too much characters, reads characters
}

/***********************************************************************
Get user's input
***********************************************************************/
int get_user_input() //(char *fun_player_action)
{
	printf("\nPress ENTER for generate again\n");
	printf("Type anything and press ENTER for exit\n");
	int input = getchar();

	if (input == '\n')
	{
		//printf("ENTER\n"); // ENTER pressed
		return 1; // Return 1 to indicate ENTER is pressed
	}
	else
	{
		//printf("Key other than ENTER pressed\n");
		return 0; // Return 0 to indicate a key other than ENTER is pressed
	}
    //while (getchar() != '\n'); // clear buffer input
	clear_input_buffer();
    //printf("Press ENTER\n: ");
    //*fun_player_action = getchar();

    /*if(*fun_player_action != '\n') // not ENTER
    {
        clear_input_buffer();
    }
    else
    {
        printf("ENTER\n"); // ENTER press
    }*/

    //getchar(); // clean buffer
}

int main(void)
{
	//char player_action;
	//srand(time(NULL));

	do
	{
		generate_name();
		printf("\n\n ********************************************** \n");
		//get_user_input(&player_action); // read user's input
		//get_user_input();
	}
	while(get_user_input());

	printf("\nBye!\n");

	return 0;
}
