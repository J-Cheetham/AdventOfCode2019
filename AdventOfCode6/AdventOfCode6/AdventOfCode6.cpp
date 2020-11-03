// AdventOfCode6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

struct Orbit
{
    string Root;
    string Orbital;

    Orbit(){}

    Orbit(string root, string orbital)
    {
        Root = root;
        Orbital = orbital;
    }
};

struct Pair
{
    string Name;
    int OrbitCount;

    Pair(string name, int orbitCount)
    {
        Name = name;
        OrbitCount = orbitCount;
    }
};

vector<string> loadFile()
{
    ifstream myFile("Orbits.txt");
    vector<string> orbitInput;

    for (string line; getline(myFile, line); )
    {
        orbitInput.push_back(line);
    }
    return orbitInput;
}

void parseInput(vector<string>& orbitInput, vector<Orbit>& orbits)
{
    for (string str : orbitInput)
    {
        string delimiter = ")";
        string root = str.substr(0, str.find(delimiter));
        string orbital = str.substr(str.find(delimiter) + 1, str.size());
        orbits.emplace_back(Orbit(root, orbital));
    }
}

void createOrbitalMap(vector<Pair>& orbitalMap, vector<Orbit>& orbits)
{
    //insert first element if map is empty
    if (orbitalMap.empty())
    {
        for (Orbit& orbit : orbits)
        {
            if (orbit.Root == "COM")
            {
                orbitalMap.emplace_back(Pair(orbit.Orbital, 1));
                break;
            }
        }
    }

    //Loop over all items in orbits, add to orbital map with correct count of direct/indirect orbits
    for (vector<Pair>::size_type i = 0; i < orbitalMap.size(); i++)
    {
        //cout << "Orbital Map ID: " << orbitalMap[i].Name << endl;
        for (Orbit& orbit : orbits)
        {
            if (orbit.Root == orbitalMap[i].Name)
            {
                orbitalMap.emplace_back(Pair(orbit.Orbital, orbitalMap[i].OrbitCount + 1));
                //cout << "Inserted: " << orbit.Orbital << " into orbital map" << endl;
            }
        }
    }
}

int main()
{
    //vector<string> orbitInput = { "COM)B", "B)C", "C)D", "C)D", "D)E", "E)F", "B)G", "G)H", "D)I", "E)J", "J)K", "K)L" };
    vector<string> orbitInput = loadFile();
    vector<Orbit> orbits;
    vector<Pair> orbitalMap;

    parseInput(orbitInput, orbits);
    createOrbitalMap(orbitalMap, orbits);

    //calculate number of direct and indirect orbits
    int totalOrbits = 0;
    for (vector<Pair>::iterator it = orbitalMap.begin(); it != orbitalMap.end(); it++)
    {
        cout << it->Name << " => " << it->OrbitCount << endl;
        totalOrbits += it->OrbitCount;
    }
    cout << "Total Orbits: " << totalOrbits << endl;
}