#include <iostream>
#include <string>
#include <map>

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

    do    
    {
        string xy = to_string(pos[0]) + "," + to_string(pos[1]);
        auto hit = didFindPos.find(xy);
        if (hit == didFindPos.end())
        {
            didFindPos.insert({xy, true});
        }
        while (getCharAtPos(&text, pos[0] + direction[0], pos[1] + direction[1]) != '.')
        {
            int dx = direction[1];
            int dy = -direction[0];
            direction[0] = dx;
            direction[1] = dy;
        }
        pos[0] = pos[0] + direction[0];
        pos[1] = pos[1] + direction[1];
    }
    while  (pos[0] >= 0 && pos[0] < lineLength && pos[1] >= 0 && pos[1] < lineCount);


    cout << "Distinct positions: " << didFindPos.size() << endl;
}
