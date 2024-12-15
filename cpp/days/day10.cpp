#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int getValueAt(vector<string>* map, int x, int y)
{
    if (x < 0 || x >= map -> at(0).size() || y < 0 || y >= map -> size())
        return -1;

    char value = map -> at(y).at(x);

    if (value == '.')
        return -2;
    return value - '0';
}

int lifeFindsAWay(vector<string>* map, int x, int y, int callerValue, unordered_set<string>* nines)
{
    int value = getValueAt(map, x, y);
    if (value < -1 || value > 9 || value != callerValue + 1)
        return false;
    if (value == 9)
    {
        string ninepos = to_string(x) + "," + to_string(y);
        nines -> insert(ninepos);
        return 1;
    }

    int up = lifeFindsAWay(map, x, y + 1, value, nines);
    int down = lifeFindsAWay(map, x, y + -1, value, nines);
    int left = lifeFindsAWay(map, x - 1, y, value, nines);
    int right = lifeFindsAWay(map, x + 1, y, value, nines);
    return up + down + left + right;
}

void work(const string& input)
{
    string text = input;
    vector<string> map;

    while (text.size() > 0)
    {
        int ll = text.find('\n');
        string line = text.substr(0, ll);
        text = text.erase(0, ll + 1);

        map.push_back(line);
    }


    cout << "Go!" << endl;

    int trailheadsScore = 0;
    int trailcount = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (getValueAt(&map, j, i) == 0)
            {
                unordered_set<string> reachableNines;
                trailcount += lifeFindsAWay(&map, j, i, -1, &reachableNines);
                trailheadsScore += reachableNines.size();
            }
        }
    }

    cout << "Mountain Peaks counted: " << trailheadsScore << endl;
    cout << "Distinct Trails counted: " << trailcount << endl;
}
