#include <iostream>
#include <string>
#include <vector>
using namespace std;

int copyCost = 1;
int delCost = 1;
int insCost = 1;
int subCost = 1;

int maxCost = 2;

string key;

string input;


string processToken( string token )
{
	vector<vector<int>> transforms{token.size()};
	for(int i = 0; i < token.size(); i++)
	{
		transforms[i].resize(key.size());
		for(int j = 0; j < key.size(); j++)
		{
			
		}
	}

	return "(" + token + ")";
}

int main()
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
	while(!cin.eof())
	{
		// Temp String
		string s;

		// Read the next line
		getline(cin, s);

		// Put in the input
		input += s + "\n";
	}


	// Print some output
	cout << "You Entered: \n";
	cout << key << "\n";
	cout	<< "Max: " << maxCost 
			<< "\nCopy: " << copyCost 
			<< "\nDel: " << delCost 
			<< "\nIns: " << insCost 
			<< "\nSub: " << subCost << "\n";

	cout << input;

	bool inWord = false;
	string token;
	string output = "";
	for( int i = 0; i < input.size(); i++ )
	{
		char c = input[i];
		if( !inWord)
		{
			if( isalpha(c) )
			{
				inWord = true;
				token = c;
			}
			else
			{
				output += c;
//				output.append(string{c});
			}
		}
		else
		{
			if( isalpha(c) )
			{
				token += c;
			}
			else
			{
				//Process token
				output += processToken(token) + c;
//				output.append(string{c});
				inWord = false;
			}
		}
	}
	cout << output;

	char a;
	cin >> a;
	return 0;
}