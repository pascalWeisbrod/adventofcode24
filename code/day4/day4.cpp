#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string xmas = "XMAS";
bool xmasLineInDirection(vector<string> input, int x, int y, int dx, int dy)
{
    for (int i = 0; i < xmas.size(); i++)
    {
        int x2 = x + i * dx;
        int y2 = y + i * dy;
        if (y2 >= input.size() || y2 < 0 || x2 >= input[y2].size() || x2 < 0)
        {
            return false;
        }
        if (input[y2].at(x2) != xmas.at(i))
        {
            return false;
        }
    }
    return true;
}
int xmasLines(vector<string> input, int x, int y)
{
    int count = 0;
    count += xmasLineInDirection(input, x, y, 0, 1);
    count += xmasLineInDirection(input, x, y, 0, -1);
    count += xmasLineInDirection(input, x, y, 1, 0);
    count += xmasLineInDirection(input, x, y, -1, 0);
    count += xmasLineInDirection(input, x, y, -1, -1);
    count += xmasLineInDirection(input, x, y, -1, 1);
    count += xmasLineInDirection(input, x, y, 1, -1);
    count += xmasLineInDirection(input, x, y, 1, 1);
    return count;
}

void work(const string& input)
{
    string text = input;
    vector<string> lines;
    int lineLength = input.find("\n");
    while (text.size() > 0)
    {
        lines.push_back(text.substr(0, lineLength));
        text = text.substr(lineLength + 1, text.size() - lineLength - 1); 
    }

    cout << "Go!" << endl;

    int xmasCount = 0;
    
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            xmasCount += xmasLines(lines, j, i);
        }
    }
    
    cout << xmasCount << endl;
}
