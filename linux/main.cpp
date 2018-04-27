/**
 *	ITEC360 Spring 2018
 *	Project 2: Edit Distance Project
 *	Andrew McGuiness
 *	4/24/2018
 *	
 *	Summary: The project is to implement a dynamic programming solution to 
 *	calculating the shortest edit distance between two string.  The user 
 *	supplies a key term, a max distance, a costs for copy, deletion, 
 *	insertion and substitution, respectively.  Then the user supplies
 *	a body of text.  The program reads in the body of text, and for each
 *	word (sequence of letters) the program will calculate the edit distance
 *	to the key term.  If the edit distance is less than or equal to the max
 *	edit distance, the word will be printed surrounded by parenthesis.  If 
 *	the edit distance is too large, the work will be printed as normal.
 *	
 *	Compiling:
 *		To compile the program, you can use the supplied makefile, just run
 *		the "make" command in the same directory as the makefile.  To manually
 *		compile you will need to include the -std=c++11 flag.
 *
 *	Running:
 *		If you used the included makefile, an executable will be produced named
 *		"editdis".  Calling the command "./editdis" from the terminal will 
 *		run the program.  You can supply input to it from standard input.
 *
 *		> ./editdis < test.txt
 *	
 *
 *	Recurrence Equation:
 *	The primary algorithm used is based on the "Wagner-Fischer" algorithm.  The
 *	recurrence relation for the algorithm is as follows:
 *
 *	s(1..i)     -- Contains the first word
 *	t(1..j)     -- Contains the second word
 *    
 *	M(i, j) = M(i-1, j-1) + copyCost;    if s(i) = t(j)
 *	M(i, j) = min(  
 *					M(i-1, j  ) + deletionCost,
 *					M(i  , j-1) + insertionCost,
 *					M(i-1, j-1) + substitutionCost
 *				);
 *
 *	Base Case:  M(i, 0) = i * insertionCost;
 *				M(0, j) = j * deletionCost;
 *
 *    
 *	The Algorithm is modified to allow for variables costs in all areas.  This
 *	algorithm assumes that only a single operation can be performed and that
 *	substitution is only allowed if s(i) and t(j) are different.  If they are
 *	the same, then only a copy is allowed.
 *	
 *	References: I used the wikipedia article: https://en.wikipedia.org/wiki/Edit_distance
 *	to better understand the problem and the algorithm.  My recurrence relation
 *	is heavily based on the information in that article.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int copyCost = 0;
int delCost  = 1;
int insCost  = 1;
int subCost  = 1;
int maxCost  = 2;

string key;
string input;


/**
 *	\brief Process a token and calculate it's edit distance from the token into 
 *	the key.
 *	
 *	\param token The string from input to process
 *	
 *	\return The processed token with or without parens, depending on edit distance.
 */
string processToken(const string& token)
{
	/**
	 *	"To transform string s into string t, use a 2D array M in which M(i, j) 
	 *	gives the least cost way to transform s(1 .. i) into t(1 .. j)."
	 *	
	 *	Using this logic, I make a 2D vector, transforms[i][j] to represent
	 *	the tables M(i, j).  Then I made (s = rowTerm = token), which goes from 1..i 
	 *	in the outter loop.  Then (t = colTerm = key) which fors from 1..j in the
	 *	inner loop.  So s transforms into t by having s across the left and t across
	 *	the top.   
	 */


	// This is not really needed, it just helps me wrap my mind around the problem
	string rowTerm = token; // the "s" term
	string colTerm = key; // the "t" term


	// This algorithm translates from left to right, top to bottom.  It will fill an entire
	//	row with data, then move to the next.  This has the effect of stepping the rowTerm
	//	by one letter each loop of the outer loop.

	vector<vector<int>> transforms{rowTerm.size() + 1};
	for (int i = 0; i < rowTerm.size() + 1; i++)
	{

		transforms[i].resize(colTerm.size() + 1);
		for (int j = 0; j < colTerm.size() + 1; j++)
		{
			// Remove cost moving down since first col is null
			if (i == 0)
				transforms[i][j] = delCost * j;

			// Insert cost going left since first row is null
			else if (j == 0)
				transforms[i][j] = insCost * i;

			// Compare the two characters, if they are equal it is a copy!
			else if (tolower(rowTerm[i - 1]) == tolower(colTerm[j - 1]))
				transforms[i][j] = transforms[i - 1][j - 1] + copyCost;

			// We need to do some form of manipulation, find the best and use it
			else
			{
				// Cost of the previous string left, but add a letter
				int insertion = transforms[i - 1][j] + insCost;

				// Cost of the previous string up, but remove a letter 
				int deletion = transforms[i][j - 1] + delCost;

				// Cost of the previous string diagnolly but with a substitution
				int substitution = transforms[i - 1][j - 1] + subCost;

				// Find the best and use it
				transforms[i][j] = min(substitution, min(insertion, deletion));
			}
		}
	}

	// If the transform cost was less than max, surround it with parens
	if (transforms[rowTerm.size()][colTerm.size()] <= maxCost)
		return "(" + token + ")";


	// Just return the token
	return token;
}

/**
 *	Get input from the user to populate the *Global Variables* D:
 */
void getInput()
{
	// Get the key term
	cin >> key;

	// Get the costs
	cin >> maxCost;
	cin >> copyCost;
	cin >> delCost;
	cin >> insCost;
	cin >> subCost;

	// While not the end of a file
	while (!cin.eof())
	{
		// Temp String
		string s;

		// Read the next line
		getline(cin, s);

		// Put in the input
		input += s + "\n";
	}
}

/**
 *	\brief Process the user's entered text body.  Each word will be checked for it's edit 
 *	distance to the key term.  The output will be the same as the input, but, words within
 *	the max edit distance will be surrounded by parens.
 *	
 *	\param input Text block from the user's input to process.
 *	
 *	\return Altered text block with some words possibly surrounded by parens.
 */
string processText(const string& input)
{
	bool inWord = false; // Are we currently in a word?

	string token;	// When we are in a word, token holds it
	string output;	// The altered input is saved to output

	/**
	 * The general format for this algorithm was taken from the project
	 * instructions.  I opted not be too clever.
	 */

	// Step through each letter of the input
	for (int i = 0; i < input.size(); i++)
	{
		char c = input[i];

		// If we are NOT in a word, check if we should be
		if (!inWord)
		{
			// It's a letter, this is the start of a word
			if (isalpha(c))
			{
				// Enter the word state and add the letter to the token
				inWord = true;
				token = c;
			}
			else
			{
				// Not in a word and it's not a letter, just push the char
				output += c;
			}
		}

		// We are inside a word, so see if we should be leaving it
		else
		{
			// The char is a letter, continue adding to the token
			if (isalpha(c))
				token += c;

			// The char isn't a letter, time to leave the word and process the token.
			else
			{
				//Process token
				output += processToken(token) + c;
				inWord = false;
			}
		}
	}

	// Send back the altered input
	return output;
}

void printOutput()
{
	// Print some output
	cout	<< key		<< "\n";
	cout	<< maxCost	<< "\n"
			<< copyCost << " "	<< delCost << " " 
			<< insCost	<< " "	<< subCost << "\n";

	cout << processText(input);
}

int main()
{
	getInput();

	cout << "\n\n";

	printOutput();

	return 0;
}
