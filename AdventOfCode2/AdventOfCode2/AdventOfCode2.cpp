// AdventOfCode2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include<string>
#include <fstream>

using namespace std;

vector<int> loadIntcodeFile()
{
    ifstream myFile("Intcode");
    vector<int> intcode;

    for (string line; getline(myFile, line, ','); )
    {
        intcode.push_back(stoi(line));
    }
    return intcode;
}

vector<int> runIntcode(vector<int> intcode)
{

    for (int i = 0; i < intcode.size(); i += 4)
    {
        if (intcode[i] == 99)
        {
            break;
        }

        int idx1 = intcode[int(i + 1)];
        int idx2 = intcode[i + 2];
        int idxResult = intcode[i + 3];

        if (intcode[i] == 1)
        {
            int result = intcode[idx1] + intcode[idx2];
            intcode[idxResult] = result;
        }
        else if (intcode[i] == 2)
        {
            int result = intcode[idx1] * intcode[idx2];
            intcode[idxResult] = result;
        }
    }
    return intcode;
}

int bruteForceSearch(vector<int>& intcode)
{
    intcode[1] = 0;
    intcode[2] = 0;
    while (true)
    {
        //copies intcode each time. Not efficient but allows us to throw away a failed attempt and leave the original intcode unchanged.
        vector<int> output = runIntcode(intcode);
        int result = output[0];

        //check to see if we've found the answer
        if (result == 19690720)
        {
            return ((100 * output[1]) + output[2]);
        }
        //check if we've reached the max value of the noun
        else if (intcode[1] > 99)
        {
            cout << "no result found for verb value: " << to_string(intcode[2]) << endl;
            intcode[1] = 0;
            intcode[2] += 1;
        }
        //increment value of the noun
        else
        {
            intcode[1] += 1;
        }
    }
    cout << "no result found" << endl;
    return -1;
}


int main()
{
    vector<int> intcode = loadIntcodeFile();

    int result = bruteForceSearch(intcode);
    cout << to_string(result) << endl;
}