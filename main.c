#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 64

char stack[SIZE];
char sPostFixFull[SIZE];
int iTop = -1;

char newStack[SIZE];

int iMainLoop = 1;
int iMainSwitch = 0;

void push(char character);
char pop();

int priority(char character);
void appendString(char* sPostFix, char cAppendCharacter);
void infixToPostfix();

void newPush(int i);
int iPop();
void postfixEvaluation(char* postFix);

int main()
{
    infixToPostfix();
    postfixEvaluation(sPostFixFull);
}

void push(char character)
{
    stack[++iTop] = character;
}

char pop()
{
    if (iTop == -1)
    {
        return -1;
    }
    else
    {
        return stack[iTop--];
    }
}

void newPush(int i)
{
    iTop = iTop + 1;
    newStack[iTop] = i;
}

int iPop()
{
    int iFirstItem;
    iFirstItem = newStack[iTop];
    iTop = iTop - 1;
    return iFirstItem;
}

int priority(char character)
{
    if (character == '(')
    {
        return 0;
    }
    else if (character == '+' || character == '-')
    {
        return 1;
    }
    else if (character == '*' || character == '/')
    {
        return 2;
    }
}

void appendString(char* sPostFix, char cAppendCharacter)
{
    int length = strlen(sPostFix);
    sPostFix[length] = cAppendCharacter;
    sPostFix[length + 1] = '\0';
}

void infixToPostfix()
{
    char userExpression[SIZE];
    char *expPointer;
    char postFixChar;

    printf("Enter an expression (Max of 64 characters): ");
    scanf("%s", userExpression);

    expPointer = userExpression;

    while (*expPointer != '\0')
    {
        if (isalnum(*expPointer))
        {
            appendString(sPostFixFull, *expPointer);
        }
        else if (*expPointer == '(')
        {
            push(*expPointer);
        }
        else if (*expPointer == ')')
        {
            while ((postFixChar = pop()) != '(')
            {
                appendString(sPostFixFull, postFixChar);
            }
        }
        else
        {
            while (priority(stack[iTop]) >= priority(*expPointer))
            {
                appendString(sPostFixFull, pop());
            }

            push(*expPointer);
        }
        expPointer++;
    }

    while (iTop != -1)
    {
        appendString(sPostFixFull, pop());
    }

    printf("The Postfix is: ");
    printf(sPostFixFull);
}

void postfixEvaluation(char* postFix)
{
    char cPostFix;
    int iFirst;
    int iSecond;
    int iValue;
    int iPostFixIterator;

    for (iPostFixIterator = 0; postFix[iPostFixIterator] != '\0'; iPostFixIterator++)
    {
        cPostFix = postFix[iPostFixIterator];
        if (isdigit(cPostFix))
        {
            newPush(cPostFix - '0');
        }
        else if (cPostFix == '+' || cPostFix == '-' || cPostFix == '*' || cPostFix == '/')
        {
            iFirst = iPop();
            iSecond = iPop();

            switch (cPostFix)
            {
                case '*':
                {
                    iValue = iSecond * iFirst;
                    break;
                }
                case '/':
                {
                    iValue = iSecond / iFirst;
                    break;
                }
                case '+':
                {
                    iValue = iSecond + iFirst;
                    break;
                }
                case '-':
                {
                    iValue = iSecond - iFirst;
                    break;
                }
            }

            newPush(iValue);
        }
    }

    printf("\n Result: %d \n", iPop());
}