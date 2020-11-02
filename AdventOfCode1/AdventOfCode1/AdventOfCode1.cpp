#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> loadFile()
{
    ifstream myFile("Modules");
    vector<int> modules;
    for (string line; getline(myFile, line); )
    {
        modules.push_back(stoi(line));
    }

    return modules;
}

int oneModuleTotalFuelRequirement(int module)
{
    int moduleFuelRequirement = 0;
    moduleFuelRequirement += int((floor((module / 3)) - 2));

    if (moduleFuelRequirement >= 0)
    {
        moduleFuelRequirement += oneModuleTotalFuelRequirement(moduleFuelRequirement);
    }
    else
    {
        return 0;
    }
}

int calculateFuel(vector<int> modules)
{
    int totalFuelRequired = 0;

    for (int module : modules)
    {
        totalFuelRequired += oneModuleTotalFuelRequirement(module);
    }
    
    return totalFuelRequired;
}

int main()
{
    vector<int> moduleWeights = loadFile();
    int totalFuel = calculateFuel(moduleWeights);
    cout << totalFuel << endl;
}
