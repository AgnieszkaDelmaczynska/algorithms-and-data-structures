#include <stack>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int howManyInputs;
	stack <char> givenLetters;
	char letter;
	int expressionLength;
	char first, second;
	cin >> howManyInputs;
	string expression;

	for (int i = 0; i < howManyInputs; i++)
	{
		cin >> expression;
		expressionLength = expression.length();
		for (int j = expressionLength - 1; j >= 0; j--)
		{
			letter = expression[j];

			switch (letter)
			{
			case 'f':
			case 't':
				givenLetters.push(letter);
				break;
			case 'N':
				first = givenLetters.top();
				givenLetters.pop();
				if (first == 't')
				{
					givenLetters.push('f');
				}
				else
				{
					givenLetters.push('t');
				}
				break;
			case 'A':
				first = givenLetters.top();
				givenLetters.pop();
				second = givenLetters.top();
				givenLetters.pop();
				if (first == 't' || second == 't')
				{
					givenLetters.push('t');
				}
				else
				{
					givenLetters.push('f');
				}
				break;
			case 'K':
				first = givenLetters.top();
				givenLetters.pop();
				second = givenLetters.top();
				givenLetters.pop();
				if (first == 't' && second == 't')
				{
					givenLetters.push('t');
				}
				else
				{
					givenLetters.push('f');
				}
				break;
			default:
				break;
			}
		}
		cout << givenLetters.top() << endl;
		givenLetters.pop();
	}
	return 0;
}