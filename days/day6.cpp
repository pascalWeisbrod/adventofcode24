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

    int startPos[2] = { found % lineLength, lineCount - 1 - (found / lineLength) };

    unordered_set<string> didFindPos;
    unordered_set<string> obstacles;

    do    
    {
        string xy = to_string(pos[0]) + "," + to_string(pos[1]);
        didFindPos.insert(xy);

        makeMove(&text, pos, direction);
    }
    while  (pos[0] >= 0 && pos[0] < lineLength && pos[1] >= 0 && pos[1] < lineCount);

    int infinities = 0;
    for (int i = 0; i < text.size(); i++)
    {
        int x = i % lineLength;
        int y = lineCount - 1 - (i / lineLength);
        char dummy = getCharAtPos(&text, x, y);
        if (dummy == '\n')
        {
            continue;
        }
        int insertPos = text.size() - (y + 1) * lineLength + x;
        text[insertPos] = '#';
        if (dummy != '#' && insertPos != found)
        {
            if (isInfiniteLoop(&text, startPos[0], startPos[1], 0, 1))
            {
                infinities++;
            }
        }
        text[insertPos] = dummy;
    }
    cout << "Distinct positions: " << didFindPos.size() << endl;
    cout << "Positions to create a loop: " << infinities << endl;
}
