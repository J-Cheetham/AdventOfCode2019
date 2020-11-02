#include <iostream>
#include <vector>
#include<string>
#include <fstream>

using namespace std;

vector<int> loadIntcodeFile()
{
    ifstream myFile("Intcode.txt");
    vector<int> intcode;

    for (string line; getline(myFile, line, ','); )
    {
        intcode.push_back(stoi(line));
    }
    return intcode;
}

void parseOpcode(string& opcode, int& operation, int& mode1, int& mode2, int& mode3)
{
    int j = 0;
    for (string::reverse_iterator rit = opcode.rbegin(); rit != opcode.rend(); ++rit)
    {
        if (j == 0)
        {
            operation = *rit - '0';
            //cout << "operation: " << operation << endl;
        }

        if (j == 2)
        {
            mode1 = *rit - '0';
            //cout << "mode1: " << mode1 << endl;
        }

        if (j == 3)
        {
            mode2 = *rit - '0';
            //cout << "mode2: " << mode2 << endl;
        }

        if (j == 4)
        {
            mode3 = *rit - '0';
            //cout << "mode3: " << mode3 << endl;
        }
        j++;
    }
}

int value(int mode, int index, vector<int>& intcode)
{
    int value = 0;
    if (mode == 0)
    {
        value = intcode[intcode[index]];
    }
    else
    {
        value = intcode[index];
    }
    return value;
}

vector<int> runIntcode(vector<int> intcode)
{
    int stepSize = 0;
    for (int i = 0; i < intcode.size(); i += stepSize)
    {
        /*cout << "i: " << i << endl;
        for (int i : intcode)
        {
            cout << i << ", ";
        }
        cout << endl;*/

        if (intcode[i] == 99)
        {
            //program complete
            //cout << "Exit using operation 99" << endl;
            break;
        }

        //set up and parse opcode
        string opcode = to_string(intcode[i]);
        int operation = 0;
        int mode1 = 0;
        int mode2 = 0;
        int mode3 = 0;

        parseOpcode(opcode, operation, mode1, mode2, mode3);

        //perform operation
        //addition
        if (operation == 1)
        {
            //never in immediate mode (1)
            int idxResult = intcode[i + 3];

            intcode[idxResult] = value(mode1, (i + 1), intcode) + value(mode2, (i + 2), intcode);
            stepSize = 4;
        }

        //multiplication
        else if (operation == 2)
        {
            //never in immediate mode (1)
            int idxResult = intcode[i + 3];

            intcode[idxResult] = value(mode1, (i + 1), intcode) * value(mode2, (i + 2), intcode);
            stepSize = 4;
        }

        //user input
        else if (operation == 3)
        {
            int userInput;
            cout << "What's your input value?" << endl;
            cin >> userInput;

            intcode[intcode[i + 1]] = userInput;
            stepSize = 2;
        }

        //output
        else if (operation == 4)
        {
            cout << "Output: " << value(mode1, (i + 1), intcode) << endl;
            stepSize = 2;
        }

        //TODO operation 5 & 6 is not working
        //TODO 
        //jump if true
        else if (operation == 5)
        {
            //Either firing when they should not or giving the wrong step size
            if (value(mode1, (i + 1), intcode) != 0)
            {
                stepSize = value(mode2, (i + 2), intcode);
                stepSize -= i;
            }
            else
            {
                stepSize = 3;
            }
        }

        //jump if false
        else if (operation == 6)
        {
            if (value(mode1, (i + 1), intcode) == 0)
            {
                stepSize = value(mode2, (i + 2), intcode);
                stepSize -= i;
            }
            else
            {
                stepSize = 3;
            }
        }

        //less than
        else if (operation == 7)
        {
            //never in immediate mode (1)
            int idxResult = intcode[i + 3];
            if (value(mode1, (i + 1), intcode) < value(mode2, (i + 2), intcode))
            {
                intcode[idxResult] = 1;
            }
            else
            {
                intcode[idxResult] = 0;
            }
            stepSize = 4;
        }

        //equals
        else if (operation == 8)
        {
            //never in immediate mode (1)
            int idxResult = intcode[i + 3];
            if (value(mode1, (i + 1), intcode) == value(mode2, (i + 2), intcode))
            {
                intcode[idxResult] = 1;
            }
            else
            {
                intcode[idxResult] = 0;
            }
            stepSize = 4;
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
    vector<int> result = runIntcode(intcode);

    /*int result = bruteforcesearch(intcode);
    cout << to_string(result) << endl;*/

    //vector<int> testcode = { 3,3,1105,-1,9,1101,0,0,12,4,12,99,1 };
    //vector<int> result = runIntcode(testcode);
}