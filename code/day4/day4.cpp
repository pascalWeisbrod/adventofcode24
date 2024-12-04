#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string xmas = "XMAS";
const string mas = "MAS";
bool xmasLineInDirection(vector<string> input, string searchFor, int x, int y, int dx, int dy)
{
    for (int i = 0; i < searchFor.size(); i++)
    {
        int x2 = x + i * dx;
        int y2 = y + i * dy;
        if (y2 >= input.size() || y2 < 0 || x2 >= input[y2].size() || x2 < 0)
        {
            return false;
        }
        if (input[y2].at(x2) != searchFor.at(i))
        {
            return false;
        }
    }
    return true;
}
int xmasLines(vector<string> input, int x, int y)
{
    int count = 0;
    count += xmasLineInDirection(input, xmas, x, y, 0, 1);
    count += xmasLineInDirection(input, xmas, x, y, 0, -1);
    count += xmasLineInDirection(input, xmas, x, y, 1, 0);
    count += xmasLineInDirection(input, xmas, x, y, -1, 0);
    count += xmasLineInDirection(input, xmas, x, y, -1, -1);
    count += xmasLineInDirection(input, xmas, x, y, -1, 1);
    count += xmasLineInDirection(input, xmas, x, y, 1, -1);
    count += xmasLineInDirection(input, xmas, x, y, 1, 1);
    return count;
}
int masX(vector<string> input, int x, int y)
{
    int size = mas.size() - 1;
    bool rd = xmasLineInDirection(input, mas, x, y, 1, 1);
    bool ld = xmasLineInDirection(input, mas, x + size, y, -1, 1);
    bool ru = xmasLineInDirection(input, mas, x, y + size, 1, -1);
    bool lu = xmasLineInDirection(input, mas, x + size, y + size, -1, -1);
    bool crossDown = rd && ld;
    bool crossUp = ru && lu;
    bool crossRight = rd && ru;
    bool crossLeft = ld && lu;

    return crossDown + crossUp + crossRight + crossLeft;
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
    int masXCount = 0;
    
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            xmasCount += xmasLines(lines, j, i);
            masXCount += masX(lines, j, i);
        }
    }
    
    cout << "XMAS count found: " << xmasCount << endl;
    cout << "MAS-X count found: " << masXCount << endl;
}
