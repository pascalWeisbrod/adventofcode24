#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../day.h"

using namespace std;

int vectorIsSafe(vector<int> line)
{
    bool increasing = line[1] > line[0];
    for (int j = 0; j < line.size() - 1; j++)
    { 
        int dif = line[j + 1] - line[j];
        if ((increasing == dif < 0) || abs(dif) < 1 || abs(dif) > 3)
        {
            return j;   
        }
    }
    return -1;
}

vector<int> copy(vector<int> v, int skippedIdx)
{
    vector<int> u;
    for (int i = 0; i < v.size(); i++)
    {
        int value = v[i];
        if (i == skippedIdx)
        {
            continue;
        }
        u.push_back(value);
    }
    return u;
}

void work(const string& input)
{
    string inputText = input; 
    vector<vector<int>> reportVector;
    int reports[6][5];
    int lastLineEnd = 0;
    while (inputText.find("\n") != -1)
    {
        string line = inputText.substr(0, inputText.find("\n"));
        inputText = inputText.substr(line.size() + 1, inputText.size());

        vector<int> lineVector;
        while (line.find(" ") != -1)
        {
            int space = line.find(" ");
            string value = line.substr(0, abs(space));
            line = line.substr(value.size() + 1, line.size());
            lineVector.push_back(stoi(value));
        }
        lineVector.push_back(stoi(line));
        reportVector.push_back(lineVector);
    }

    cout << "Go!" << endl;

    int safeCount = 0;
    int dampedSafeCount = 0;
    for (int i = 0; i < reportVector.size(); i++)
    {
        int menaceIdx = vectorIsSafe(reportVector[i]);
        bool isSafe = menaceIdx == -1;
        safeCount += isSafe;

        if (isSafe)
        {
            dampedSafeCount += isSafe;
            continue;
        }

        vector<int> a = copy(reportVector[i], menaceIdx - 1);
        vector<int> b = copy(reportVector[i], menaceIdx);
        vector<int> c = copy(reportVector[i], menaceIdx + 1);
        if (vectorIsSafe(a) == -1 || vectorIsSafe(b) == -1 || vectorIsSafe(c) == -1)
        {
            dampedSafeCount++;
        }
    }


    cout << "Safe count: " << safeCount << endl;
    cout << "Damped Safe count: " << dampedSafeCount << endl;
}

