#include <stack>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int howManyInputs;
	stack <string> givenLetters;
	string phrase;
	char letter;
	int expressionLength;
	string first, second;
	cin >> howManyInputs;
	string expression;

	for (int i = 0; i < howManyInputs; i++)
	{
		cin >> expression;
		expressionLength = expression.length();
		reverse(expression.begin(), expression.end());

		for(int j = 0; j < expressionLength; j++)
		{
			letter = expression[j];
			string character(1, letter);
			switch (letter)
			{
			case 'f':
			case 't':
				phrase += character;
				break;
			case 'N':			
			case 'A':				
			case 'K':
				givenLetters.push(character);
				break;
			case '(':
				givenLetters.push(")");
				break;
			case ')':
				while (givenLetters.top() != ")")
				{
					phrase += givenLetters.top();
					givenLetters.pop();
				}
				givenLetters.pop();
			default:
				break;
			}
		}
		reverse(phrase.begin(), phrase.end());

		expression = phrase;
		expressionLength = expression.length();
		for (int j = expressionLength - 1; j >= 0; j--)
		{
			letter = expression[j];
			string character(1, letter);
			switch (letter)
			{
			case 'f':
			case 't':
				givenLetters.push(character);
				break;
			case 'N':
				first = givenLetters.top();
				givenLetters.pop();
				if (first == "t")
				{
					givenLetters.push("f");
				}
				else
				{
					givenLetters.push("t");
				}
				break;
			case 'A':
				first = givenLetters.top();
				givenLetters.pop();
				second = givenLetters.top();
				givenLetters.pop();
				if (first == "t" || second == "t")
				{
					givenLetters.push("t");
				}
				else
				{
					givenLetters.push("f");
				}
				break;
			case 'K':
				first = givenLetters.top();
				givenLetters.pop();
				second = givenLetters.top();
				givenLetters.pop();
				if (first == "t" && second == "t")
				{
					givenLetters.push("t");
				}
				else
				{
					givenLetters.push("f");
				}
				break;
			default:
				break;
			}
		}
		cout << givenLetters.top() << endl;
		givenLetters.pop();

		phrase = "";
	}
	return 0;
}