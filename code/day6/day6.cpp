#include <iostream>
#include <string>
#include <map>
#include <unordered_set>

using namespace std;

char getCharAtPos(string* text, int x, int y)
{
    int lineLength = text->find("\n") + 1;
    int lineCount = text->size() / lineLength;
    if (x < 0 || x >= lineLength || y < 0 || y >= lineCount)
    {
        return '.';
    }
    return text->at(text -> size() - (y + 1) * lineLength + x);
}

void makeMove(string* text, int pos[], int dir[])
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

bool isInfiniteLoop(string* text, int x, int y, int dx, int dy)
{
    int pos[2] = { x, y };
    int dir[2] = { dx, dy };
    int lineLength = text -> find("\n") + 1;
    int lineCount = text -> size() / lineLength;

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
    while  (pos[0] >= 0 && pos[0] < lineLength && pos[1] >= 0 && pos[1] < lineCount);

    return false;
}
void work(const string& input)
{
    string text = input;
    int lineLength = text.find("\n") + 1;
    int lineCount = text.size() / lineLength;
    int found = text.find("^");
    text[found] = '.';

    cout << "Go!" << endl;

    int direction[2] = { 0, 1 };
    int pos[2] = { found % lineLength, lineCount - 1 - (found / lineLength) };

    map<string, bool> didFindPos;
    unordered_set<string> obstacles;

    do    
    {
        string xy = to_string(pos[0]) + "," + to_string(pos[1]);
        auto hit = didFindPos.find(xy);
        if (hit == didFindPos.end())
        {
            didFindPos.insert({xy, true});
        }
        int next_x = pos[0] + direction[0];
        int next_y = pos[1] + direction[1];
        char dummy = getCharAtPos(&text, next_x, next_y);
        if (dummy != '#')
        {
            int insertPos = text.size() - (next_y + 1) * lineLength + next_x;
            text[insertPos] = '#';
            if (isInfiniteLoop(&text, pos[0], pos[1], direction[0], direction[1]))
            {
                obstacles.insert(to_string(next_x) + "," + to_string(next_y));
            }
            text[insertPos] = dummy;
        }
        makeMove(&text, pos, direction);
    }
    while  (pos[0] >= 0 && pos[0] < lineLength && pos[1] >= 0 && pos[1] < lineCount);

    cout << "Distinct positions: " << didFindPos.size() << endl;
    cout << "Positions to create a loop: " << obstacles.size() << endl;
}
