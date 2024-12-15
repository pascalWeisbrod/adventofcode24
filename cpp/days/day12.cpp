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

Point followSide(vector<string>* lines, Point startPoint, Point direction, char plant)
{
    Point lookDirection(direction.y, direction.x * -1);
    Point current(startPoint.x, startPoint.y);
    while (getCharAt(lines, current.x, current.y) == plant && getCharAt(lines, current.x + lookDirection.x, current.y + lookDirection.y) != plant)
    {
        current.x++;
        current.y++;
    }
    return current;
}

int fillSides(vector<string>* lines, vector<Point>* points)
{
    Point startPoint = points -> at(0);
    char plant = getCharAt(lines, startPoint.x, startPoint.y);
    while (getCharAt(lines, startPoint.x, startPoint.y - 1) == plant)
        startPoint.y--;

    Point pos(startPoint.x, startPoint.y);
    Point dir(-1, 0);
    int count = 0;

    unordered_set<string> visited;
    int lastSize = 0;

    do
    {
        string hash = to_string(pos.x) + "," + to_string(pos.y) + "," + to_string(dir.x) + "," + to_string(dir.y);
        visited.insert(hash);
        if (visited.size() == lastSize)
            break;
        lastSize = visited.size();
        
        Point forward(pos.x + dir.x, pos.y + dir.y);

        if (getCharAt(lines, forward.x, forward.y) == plant)
        {
            pos.x = forward.x;
            pos.y = forward.y;
        }

        Point left(pos.x + dir.y * -1, pos.y + dir.x);
        Point right(pos.x + dir.y, pos.y + dir.x * -1);

        if (getCharAt(lines, left.x, left.y) == plant)
        {
            dir = Point(dir.y * -1, dir.x);
            count++;
        }
        else if (getCharAt(lines, forward.x, forward.y) != plant)
        {
            dir = Point(dir.y, dir.x * -1);
            count++;
        }
    } while (true);
    return count;
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
    int discountedPrice = 0;
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
            int sides = fillSides(&lines, &f.points);
            price += area * perimiter;
            discountedPrice += area * sides;
        }
    }

    cout << "Price: " << price << endl;
    cout << "Discounted Price: " << discountedPrice << endl;
}
