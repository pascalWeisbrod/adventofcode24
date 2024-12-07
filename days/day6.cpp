#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

char getCharAtPos(vector<string>* text, int x, int y)
{
    if (x < 0 || x >= text -> at(0).size() || y < 0 || y >= text -> size())
    {
        return '.';
    }
    return text -> at(y)[x];
}

void makeMove(vector<string>* text, int pos[], int dir[])
{
    while (getCharAtPos(text, pos[0] + dir[0], pos[1] + dir[1]) != '.')
    {
        int dx = dir[1];
        int dy = -dir[0];
        dir[0] = dx;
        dir[1] = dy;
    }
    pos[0] = pos[0] + dir[0];
    pos[1] = pos[1] + dir[1];
}

bool isInfiniteLoop(vector<string>* text, int x, int y, int dx, int dy)
{
    int pos[2] = { x, y };
    int dir[2] = { dx, dy };

    unordered_set<string> moves;
    do    
    {
        string xy = to_string(pos[0]) + "," + to_string(pos[1]) + "," + to_string(dir[0]) + to_string(dir[1]);

        if (moves.find(xy) != moves.end())
        {
            return true;
        }
        moves.insert(xy);
        makeMove(text, pos, dir);
    }
    while  (pos[0] >= 0 && pos[0] < text->at(0).size() && pos[1] >= 0 && pos[1] < text->size());

    return false;
}
void work(const string& input)
{
    string text = input;
    vector<string> lines;
    int s_pos[2];
    while (text.size() > 0)
    {
        int ll = text.find("\n");
        string line = text.substr(0, ll);
        text.erase(0, ll + 1);

        int idx = line.find("^");
        if (idx != -1)
        {
            s_pos[0] = idx;
            s_pos[1] = lines[0].size() - lines.size() - 1;
            line[idx] = '.';
        }
        lines.insert(lines.begin(), line);
    }

    cout << "Go!" << endl;

    int direction[2] = { 0, 1 };
    int pos[2] = { s_pos[0], s_pos[1] };

    unordered_set<string> didFindPos;
    unordered_set<string> obstacles;
int i = 0;
    do    
    {
        string xy = to_string(pos[0]) + "," + to_string(pos[1]);
        didFindPos.insert(xy);

        makeMove(&lines, pos, direction);

        if (!(pos[0] >= 0 && pos[0] < lines[0].size() && pos[1] >= 0 && pos[1] < lines.size()))
        {
            break;
        }

        lines[pos[1]].at(pos[0]) = '#';

        if (isInfiniteLoop(&lines, s_pos[0], s_pos[1], 0, 1))
        {
            xy = to_string(pos[0]) + "," + to_string(pos[1]);
            obstacles.insert(xy);
        }
        lines[pos[1]].at(pos[0]) = '.';
    }
    while  (pos[0] >= 0 && pos[0] < lines[0].size() && pos[1] >= 0 && pos[1] < lines.size());

    cout << "Distinct positions: " << didFindPos.size() << endl;
    cout << "Positions to create a loop: " << obstacles.size() << endl;
}
