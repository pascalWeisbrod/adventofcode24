#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>

using namespace std;

class Antenna{
    public:
        char frequency;
        int x;
        int y;
        Antenna(char f, int a, int b){
            frequency = f;
            x = a;
            y = b;
        }
};


void addLocations(unordered_set<string>* locations, vector<Antenna>* frequencies, int limit_x, int limit_y)
{
    for (int i = 0; i < frequencies -> size(); i++)
    {
        Antenna a = frequencies -> at(i);
        for (int j = 0; j < frequencies -> size(); j++)
        {
            if (i == j)
                continue;

            Antenna b = frequencies -> at(j);
            int dx = b.x - a.x;
            int dy = b.y - a.y;

            int x = a.x + 2 * dx;
            int y = a.y + 2 * dy;

            if (x < 0 || x > limit_x - 1 || y < 0 || y > limit_y - 1)
                continue;

            string loc = to_string(x) + "," + to_string(y);
            locations -> insert(loc);
        }
    }
}

void addAllLocations(unordered_set<string>* locations, vector<Antenna>* frequencies, int limit_x, int limit_y)
{
    for (int i = 0; i < frequencies -> size(); i++)
    {
        Antenna a = frequencies -> at(i);
        for (int j = 0; j < frequencies -> size(); j++)
        {
            if (i == j)
                continue;

            Antenna b = frequencies -> at(j);
            int dx = b.x - a.x;
            int dy = b.y - a.y;

            int x = a.x;
            int y = a.y;

            int factor = 0;
            while (!(x < 0 || x > limit_x - 1 || y < 0 || y > limit_y - 1))
            {
                string loc = to_string(x) + "," + to_string(y);
                locations -> insert(loc);
                factor++;
                x = a.x + factor * dx;
                y = a.y + factor * dy;
            }

        }
    }
}

void work(const string& input)
{
    string text = input;
    map<char, vector<Antenna>> frequencies;

    int y = 0;
    int lineSize = 0;
    while (text.size() > 0)
    {
        lineSize = text.find("\n");
        string line = text.substr(0, lineSize);
        text = text.substr(lineSize + 1, text.size() - lineSize - 1);

        for (int x = 0; x < line.size(); x++)
        {
            char c_x = line.at(x);
            if (c_x != '.')
            {
                auto hit = frequencies.find(c_x);
                if (hit == frequencies.end())
                {
                    frequencies.insert({ c_x, {} });
                }
                Antenna a(c_x, x, y);
                frequencies.at(c_x).push_back(a);
            }
        }
        y++;
    }

    cout << "Go!" << endl;

    unordered_set<string> locations;
    unordered_set<string> locations2;
    for (auto it = frequencies.begin(); it != frequencies.end(); ++it) {
        addLocations(&locations, &(it -> second), lineSize, y); 
        addAllLocations(&locations2, &(it -> second), lineSize, y); 
    }

    cout << "Unique locations: " << locations.size() << endl;
    cout << "Unique locations with resonant: " << locations2.size() << endl;
}
