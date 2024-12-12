#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;


struct Point
{
    int x;
    int y;

    Point(int a, int b) { x = a; y = b; }
};
class Field 
{
    public:
        char plant;
        vector<Point> points;
        Field(char plant)
        {
            this -> plant = plant;
        }
        void expand(Point otherField)
        {
            points.push_back(otherField);
        }
        bool contains(Point point)
        {
            for (Point p : points)
            {
                if (p.x == point.x && p.y == point.y)
                    return true;
            }
            return false;
        }
};

char getCharAt(vector<string>* lines, int x, int y)
{
    if (x < 0 || x >= lines -> at(0).size() || y < 0 || y >= lines -> size())
        return '.';

    return lines -> at(y).at(x);
}


int getPerimiter(vector<string>* lines, vector<Point>* points)
{
    int perimiter = 0;
    for (Point p : *points)
    {
        perimiter += 4;
        int x = p.x;
        int y = p.y;
        for (Point q : { Point(x + 1, y), Point(x - 1, y), Point(x, y + 1), Point(x, y - 1) })
            if (getCharAt(lines, x, y) == getCharAt(lines, q.x, q.y))
                perimiter -= 1;
    }
    return perimiter;
}

void fillField(vector<string>* lines, unordered_set<string>* explored, Field* field, int x, int y)
{
    string hash = to_string(x) + "," + to_string(y);
    int size = explored -> size();
    explored -> insert(hash);
    if (explored -> size() == size)
        return;

    field -> expand(Point(x,y));
    for (Point p : { Point(x + 1, y), Point(x - 1, y), Point(x, y + 1), Point(x, y - 1) })
    {
        if (field -> plant == getCharAt(lines, p.x, p.y))
                fillField(lines, explored, field, p.x, p.y);
    }
}

void work(const string& input)
{
    string text = input;
    vector<string> lines;
    while (text.size() > 0)
    {
        int l = text.find("\n");
        lines.push_back(text.substr(0, l));
        text.erase(0, l + 1);
    }


    cout << "Go!" << endl;


    vector<Field> fields;
    unordered_set<string> explored;

    int price = 0;
    for (int i = 0; i < lines.size(); i ++)
    {
        for (int j = 0; j < lines[0].size(); j++)
        {
            Field f(getCharAt(&lines, j, i));
            fillField(&lines, &explored, &f, j, i);
            if (f.points.size() == 0)
                continue;
            int area = f.points.size();
            int perimiter = getPerimiter(&lines, &f.points);
            int field_prize = area * perimiter;
            cout << "Plant " << f.plant << ": Area " << area << ", Perimiter " << perimiter << endl; 
            price += area * perimiter;
        }
    }

    cout << "Price: " << price << endl;
}
