// AdventOfCode6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

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

map<string, vector<string>> buildDiGraph(vector<Orbit>& orbits)
{
    map<string, vector<string>> diGraph;
    for (Orbit& orbit : orbits)
    {
        map<string, vector<string>>::iterator it;
        it = diGraph.find(orbit.Root);

        //if the root is not in the map as a key
        if (it == diGraph.end())
        {
            //add it to the map with the corresponding connection (its orbital)
            vector<string> children;
            children.push_back(orbit.Orbital);
            diGraph.emplace(orbit.Root, children);
        }
        //the root is in the map, check the orbital is listed as a connection
        else
        {
            //iterate through vector of connections to see if it's present
            if (find(it->second.begin(), it->second.end(), orbit.Orbital) == it->second.end())
            {
                //add the orbital as it's not in the vector of connections
                it->second.push_back(orbit.Orbital);
            }
        }

        //redeclare the iterator, you may have inserted an element which would render it invalid...
        it = diGraph.find(orbit.Orbital);

        //check the orbital to make sure that's in the map as well
        //if it's not, add it with it's connections
        if (it == diGraph.end())
        {
            vector<string> children;
            children.push_back(orbit.Root);
            diGraph.emplace(orbit.Orbital, children);
        }
        //the orbital is in the map, make sure the root is there as a connection
        else
        {
            //iterate through vector of connections to see if it's present
            if (find(it->second.begin(), it->second.end(), orbit.Root) == it->second.end())
            {
                //add the orbital as it's not in the vector of connections
                it->second.push_back(orbit.Root);
            }
        }
    }
    return diGraph;
}

vector<string> findShortestPath(map<string, vector<string>>& diGraph, string start, string end, vector<string> path, vector<string> shortest)
{
    path.push_back(start);

    //cout << "Current Path: ";
    //for (string str : path)
    //{
    //    cout << str << ", ";
    //}
    //cout << endl;

    if (start == end)
    {
        return path;
    }
    vector<string> children = diGraph.find(start)->second;
    for (string child : children)
    {
        //check child is not in the path already (avoids cycles)
        if (find(path.begin(), path.end(), child) == path.end())
        {
            //check the current path is shorter than the shortest path found so far
            if (shortest.empty() || path.empty() < shortest.size())
            {
                //recursive call to continue exploring that branch
                vector<string> newPath = findShortestPath(diGraph, child, end, path, shortest);
                
                //a return path means the newPath must be shorter than the current path
                if (!newPath.empty())
                {
                    shortest = newPath;
                    cout << "Current shortest path length: " << shortest.size() << endl;
                }
            }
        }
    }
    return shortest;
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
    //vector<string> orbitInput = { "COM)B", "B)C", "C)D", "D)E", "E)F", "B)G", "G)H", "D)I", "E)J", "J)K", "K)L", "K)YOU", "I)SAN", "K)SAN" };
    vector<string> orbitInput = loadFile();
    vector<Orbit> orbits;
    vector<Pair> orbitalMap;

    parseInput(orbitInput, orbits);
    map<string, vector<string>> properMap = buildDiGraph(orbits);

    /*for (map<string, vector<string>>::iterator it = properMap.begin(); it != properMap.end(); it++)
    {
        cout << "Node: " << it->first << " has children: ";
        for (string child : it->second)
        {
            cout << child << ", ";
        }
        cout << endl;
    }*/

    vector<string> path;
    vector<string> shortest;
    vector<string> finalPath = findShortestPath(properMap, "YOU", "SAN", path, shortest);

    cout << "Shortest Path: ";
    for (string s : finalPath)
    {
        cout << s << ", ";
    }
    cout << endl;
    cout << "Number of steps of shortest path: " << finalPath.size() << endl;

    //createOrbitalMap(orbitalMap, orbits);

    //calculate number of direct and indirect orbits
    /*int totalOrbits = 0;
    for (vector<Pair>::iterator it = orbitalMap.begin(); it != orbitalMap.end(); it++)
    {
        cout << it->Name << " => " << it->OrbitCount << endl;
        totalOrbits += it->OrbitCount;
    }
    cout << "Total Orbits: " << totalOrbits << endl;*/
}