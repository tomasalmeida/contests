#include <iostream>
#include <string>
#include <vector>
using namespace std;

int char2int (char ch)
{
    return ((ch >= 'A') ? (ch - 'A' + 10) : (ch - '0'));
}

char int2char (int i)
{
    return ((i >= 10) ? (i - 10 + 'A') : (i + '0'));
}

vector <int> string2longint (string number)
{
    int size = number.size ();
    vector <int> convertedNumber(size);
    int i, j;
    for (i = 0, j = size - 1; i < size; i ++, j --)
    {
        convertedNumber [i] = char2int (number [j]);
    }
    return convertedNumber;
}

string longint2string (vector <int> number)
{
    int size = number.size ();
    string convertedNumber (size, ' ');
    int counterNew, counterOriginal;
    for (counterNew = 0, counterOriginal = size - 1; counterNew < size; counterNew ++, counterOriginal --)
    {
        convertedNumber [counterNew] = int2char (number [counterOriginal]);
    }
    return convertedNumber;
}

vector <int> ChangeBase (vector <int> originalNumber, int baseOrigin, int baseTarget)
{
    vector <int> numberReturn;
    int size = originalNumber.size ();
    if (size <= 0)
    {
        return numberReturn;
    }
	
    if (baseOrigin < baseTarget)
    {
        int multiplier [10] = {1, };
        int indexMult = 1;
        int valueMult = baseOrigin;
        while (valueMult < baseTarget)
        {
            multiplier [indexMult] = valueMult;
            valueMult *= baseOrigin;
            indexMult ++;
        }
        int positionNumber = 0;
        int counterExt , counterInt =0, numberAcum =0;
        for (counterExt = 0; counterExt < size - indexMult; counterExt += indexMult)
        {
        	numberAcum = 0;
            for (counterInt = 0; counterInt < indexMult; counterInt ++)
            {
                numberAcum += originalNumber [counterExt + counterInt] * multiplier [counterInt];
        	}
            originalNumber [positionNumber ++] = numberAcum;
        }
        	
        for (counterInt = 0, numberAcum = 0; counterExt < size; counterExt ++, counterInt ++)
        {
            numberAcum += originalNumber [counterExt] * multiplier [counterInt];            
        }
        originalNumber [positionNumber ++] = numberAcum;
        size = positionNumber;
        baseOrigin = valueMult;
    }
    int counterExt2, divModule, lastPosition = size - 1;
    if (baseOrigin == baseTarget)
    {
        for (counterExt2 = 0; counterExt2 < size; counterExt2 ++)
        {
            numberReturn.push_back (originalNumber [counterExt2]);
        }
        return numberReturn;
    }
    while (lastPosition >= 0)
    {
        divModule = 0;
        for (counterExt2 = lastPosition; counterExt2 >= 0; counterExt2 --)
        {
            originalNumber [counterExt2] += divModule * baseOrigin;
            divModule =  originalNumber [counterExt2] % baseTarget;
            originalNumber [counterExt2] /= baseTarget;
        }
        numberReturn.push_back (divModule);
        while (lastPosition >= 0 && originalNumber [lastPosition] == 0)
        {
            lastPosition --;
        }
    }
    return numberReturn;
}

int main ()
{
    string numberFormatted;
    int numberOfTests, baseOrigin, baseTarget;
    cin >> numberOfTests;
    while (numberOfTests --)
    {
        cin >> numberFormatted >> baseOrigin >> baseTarget;
		
        vector <int> originalNumber = string2longint (numberFormatted);
        
		vector <int> numberInNewBase = ChangeBase (originalNumber, baseOrigin, baseTarget);
        
		numberFormatted = longint2string (numberInNewBase);
        
		cout << numberFormatted << endl;
    }
    return 0;
}