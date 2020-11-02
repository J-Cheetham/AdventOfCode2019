#include <iostream>
#include <string>

using namespace std;

bool hasAdjacentDigits(int number)
{
    int startOfGroup = INT_MAX;
    string sNumber = to_string(number);
    for (int i = 0; i < sNumber.size() - 1; i++)
    {
        //two adjacent digits match
        if (sNumber[i] == sNumber[i + 1] && sNumber[i] != startOfGroup)
        {
            //check it's not part of a larger group
            if (sNumber[i + 1] != sNumber[i + 2])
            {
                //if its not part of a larger group, return true
                return true;
            }
            else
            {
                //if it is part of a larger group, remember what the start of the group is and continue to loop.
                startOfGroup = sNumber[i];
            }
        }
    }
    //cout << "Has no adjacent digits" << endl;
    return false;
}

bool isIncreasing(int number)
{
    string sNumber = to_string(number);

    for (int i = 0; i < sNumber.size() - 1; i++)
    {
        if (sNumber[i] > sNumber[i + 1])
        {
            //cout << "Decreases" << endl;
            return false;
        }
    }
    //cout << "Always Increasing" << endl;
    return true;
}


int main()
{

    //int value = 112233;
    //if (isIncreasing(value) && hasAdjacentDigits(value))
    //{
    //    cout << "valid password" << endl;
    //}
    //else
    //{
    //    cout << "invalid password" << endl;
    //}

    int counter = 0;
    for (int i = 284639; i < 748759; i++)
    {
        if (isIncreasing(i) && hasAdjacentDigits(i))
        {
            counter++;
        }
    }
    cout << "Total possible passwords: " << counter << endl;
}

