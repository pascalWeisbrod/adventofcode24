#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "../day.h"

using namespace std;

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
    for (int i = 0; i < reportVector.size(); i++)
    {
        bool isSafe = true;
        bool increasing = reportVector[i][1] > reportVector[i][0];
        for (int j = 0; j < reportVector[i].size() - 1; j++)
        { 
            int dif = reportVector[i][j + 1] - reportVector[i][j];
            if ((increasing == dif < 0) || abs(dif) < 1 || abs(dif) > 3)
            {
                isSafe = false;
                break;
            }
        }
        safeCount += isSafe;
    }


    cout << "Safe count: " << safeCount << endl;
}
