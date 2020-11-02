// AdventOfCode3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <array>
#include <sstream>
#include <algorithm>

using namespace std;

class Coordinate
{
public:
    int X, Y;

    Coordinate()
    {
        X = 0;
        Y = 0;
    }

    Coordinate(int x, int y)
    {
        X = x;
        Y = y;
    }

    bool operator==(const Coordinate& other) const
    {
        return X == other.X && Y == other.Y;
    }

};

struct Intersection
{
    int Steps, X, Y;

    Intersection()
    {
        X = 0;
        Y = 0;
        Steps = 0;
    }

    Intersection(int x, int y, int steps)
    {
        X = x;
        Y = y;
        Steps = steps;
    }
};

ostream& operator<<(ostream& stream, const Coordinate& other)
{
    stream << "(" << other.X << ", " << other.Y << ")";
    return stream;
}

vector<vector<string>> loadDirections()
{
    ifstream myFile("Lines");
    vector<vector<string>> directions;
    vector<string> line1;
    vector<string> line2;
    bool endOfLine = false;

    for (string line; getline(myFile, line); )
    {
        if (!endOfLine)
        {
            stringstream ss(line);
            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                substr.erase(remove_if(substr.begin(), substr.end(), isspace), substr.end());
                //if (substr.find("\n"))
                //{
                //    substr.erase(substr.end() - 1, substr.end());
                //}
                line1.push_back(substr);
            }
            endOfLine = true;
            continue;
        }

        if (endOfLine)
        {
            stringstream ss(line);
            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                substr.erase(remove_if(substr.begin(), substr.end(), isspace), substr.end());
                line2.push_back(substr);
            }
        }
    }

    directions.push_back(line1);
    directions.push_back(line2);

    return directions;
}

vector<vector<Coordinate>> parseDirections(vector<vector<string>>& myDirections)
{
    vector<vector<Coordinate>> myCoordinates;
    for (vector<string> wire : myDirections)
    {
        vector<Coordinate> coordinates;
        coordinates.emplace_back(Coordinate(0, 0));

        for (string direction : wire)
        {
            char vector = direction[0];
            int magnitude = stoi(direction.substr(1, direction.size()));
            int startX = coordinates.back().X;
            int startY = coordinates.back().Y;

            if (vector == 'R')
            {
                for (int i = 1; i <= magnitude; i++)
                {
                    coordinates.emplace_back(Coordinate(startX + i, startY));
                }
            }
            else if (vector == 'L')
            {
                for (int i = 1; i <= magnitude; i++)
                {
                    coordinates.emplace_back(Coordinate(startX - i, startY));
                }
            }
            else if (vector == 'U')
            {
                for (int i = 1; i <= magnitude; i++)
                {
                    coordinates.emplace_back(Coordinate(startX, startY + i));
                }
            }
            else if (vector == 'D')
            {
                for (int i = 1; i <= magnitude; i++)
                {
                    coordinates.emplace_back(Coordinate(startX, startY - i));
                }
            }
        }
        myCoordinates.emplace_back(coordinates);
    }

    return myCoordinates;
}



vector<Intersection> findIntersections(vector<vector<Coordinate>>& wires)
{
    // TODO copy wire 1 and wire 2 into arrays and use those to loop.
    vector<Coordinate> wire1 = wires[0];
    vector<Coordinate> wire2 = wires[1];
    vector<Intersection> intersections;
    cout << wire1.size() << endl;
    cout << wire2.size() << endl;

    for (int i = 0; i < wire1.size(); i++)
    {
        for (int j = 0; j < wire2.size(); j++)
        {
            if (wire1[i] == wire2[j])
            {
                intersections.emplace_back(Intersection(wire1[i].X, wire2[j].Y, i + j));
            }
        }
    }

    //for (Coordinate wire1Coord : wire1)
    //{
    //    for (Coordinate wire2Coord : wire2)
    //    {
    //        if (wire1Coord == wire2Coord)
    //        {
    //            intersections.emplace_back(wire1Coord.X, wire1Coord.Y);
    //        }
    //    }
    //}
    intersections.erase(intersections.begin());
    return intersections;
}

int lowestSteps(vector<Intersection>& intersections)
{
    int lowestStepCount = INT_MAX;
    for (Intersection intersection : intersections)
    {
        if (intersection.Steps < lowestStepCount)
        {
            lowestStepCount = intersection.Steps;
        }
    }
    return lowestStepCount;
}

int shortestManhattenDist(vector<Coordinate>& intersections)
{
    int shortestDist = INT_MAX;
    for (Coordinate coordinate : intersections)
    {
        int manhattenDist = abs(coordinate.X) + abs(coordinate.Y);
        if (manhattenDist < shortestDist)
        {
            shortestDist = manhattenDist;
        }
    }
    return shortestDist;
}

int main()
{
    //vector<vector<string>> myDirections = loadDirections();
    //for (vector<string> line : myDirections)
    //{
    //    for (string direction : line)
    //    {
    //        cout << direction << endl;
    //        if (direction == "R83")
    //        {
    //            cout << "===============================" << endl;
    //        }
    //    }
    //}

    //vector<vector<string>> myDirections = {{"R8", "U5", "L5", "D3"}, {"U7", "R6", "D4", "L4"}};
    vector<vector<string>> myDirections = loadDirections();
    vector<string> wire1 = myDirections[0];
    vector<string> wire2 = myDirections[1];

    //cout << "wire1 contents" << endl;
    //for (string direction : wire1)
    //{
    //    cout << direction << endl;
    //}


    //cout << "wire2 contents" << endl;
    //for (string direction : wire2)
    //{
    //    cout << direction << endl;
    //}

    cout << "parseDirections() called" << endl;
    vector<vector<Coordinate>> wires = parseDirections(myDirections);
    cout << "parseDirections() finished" << endl;

   /* for (vector<Coordinate> wire : wires)
    {
        for (Coordinate coordinate : wire)
        {
            cout << coordinate << endl;
        }
    }*/
    cout << "finding intersections" << endl;

    vector<Intersection> intersections = findIntersections(wires);
    cout << "findingIntersections() finished" << endl;

    int shortestStepCount = lowestSteps(intersections);
    
    cout << "Shortest step count is: "<< shortestStepCount << endl;


    //for (vector<Coordinate> wire : wires)
    //{
    //    for (Coordinate coordinate : wire)
    //    {
    //        cout << coordinate << endl;
    //    }
    //    cout << "=======================" << endl;
    //}
}

