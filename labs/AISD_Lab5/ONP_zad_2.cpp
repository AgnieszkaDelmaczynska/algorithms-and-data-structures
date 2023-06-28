#include <stack>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int howManyInputs;
	stack <char> stack1;
	stack <char> stack2;
	char letter;
	cin >> howManyInputs;
	string expression;
	int expressionLength;
	for (int i = 0; i < howManyInputs; i++)
	{
		cin >> expression;
		expressionLength = expression.length();
		for (int j = 0; j < expressionLength; j++)
		{
			letter = expression[j];

			switch (letter)
			{
			case 'f':
			case 't':
				stack1.push(letter);
				break;
			case 'N':
				if (stack2.empty())
				{
					stack2.push(stack1.top());
					stack1.pop();
				}
				stack2.push(letter);
				break;
			case 'A':			
			case 'K':
				if (stack2.empty())
				{
					stack2.push(stack1.top());
					stack1.pop();
				}
				stack2.push(stack1.top());
				stack1.pop();

				stack2.push(letter);
			default:
				break;
			}
		}
		int temp = stack2.size();
		for (int k = 0; k < temp; k++)
		{
			cout << stack2.top();
			stack2.pop();
		}
		cout << endl;
	}
	return 0;
}