#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Robot
{
    public:
        int pos_x;
        int pos_y;
        int dir_x;
        int dir_y;
        Robot(int x, int y, int dx, int dy)
        {
            pos_x = x;
            pos_y = y;
            dir_x = dx;
            dir_y = dy;
        }
        void update(int x, int y)
        {
            // TODO: why do class variables not update correctly
            // TODO: implement correct "modolation"
            pos_x = x;
            pos_y = y;
        }
};


void work(const string& input)
{
    vector<Robot> robots;
    string text = input;
    while (text.size() > 0)
    {
        int l = text.find('\n');
        if (l == -1)
            l = text.size() - 1;
        string line = text.substr(0, l);
        string pos = line.substr(0, line.find(' '));
        string dir = line.substr(line.find(' ') + 1, line.size() - line.find(' '));
        string xs = pos.substr(2, pos.find(',') - 2);
        string ys = pos.substr(pos.find(',') + 1, pos.size() - pos.find(','));
        string xd = dir.substr(2, dir.find(',') - 2);
        string yd = dir.substr(dir.find(',') + 1, dir.size() - dir.find(','));
        int x = stoi(xs);
        int y = stoi(ys);
        int dx = stoi(xd);
        int dy = stoi(yd);
        robots.push_back(Robot(x, y, dx, dy));
        text = text.erase(0, l + 1);
    }

     
    int width = 101; // Example 11, Real 101
    int tall = 103; // Example 7, Real 103
    int moves = 100;

    cout << "Go!" << endl;
    
    vector<Robot> sol;

    int count[4] = { 0, 0, 0, 0 };
    for (Robot r : robots)
    {
        int new_x = ((r.pos_x + r.dir_x * moves) % width + width) % width; 
        int new_y = ((r.pos_y + r.dir_y * moves) % tall + tall) % tall;
        sol.push_back(Robot(new_x, new_y, 0, 0));

        if (new_x > width / 2 && new_y > tall / 2)
            count[0]++;
        if (new_x < width / 2 && new_y > tall / 2)
            count[1]++;
        if (new_x > width / 2 && new_y < tall / 2)
            count[2]++;
        if (new_x < width / 2 && new_y < tall / 2)
            count[3]++;
    }

    for (int i = 0; i < tall; i++)
    {
        string line = "";
        for (int j = 0; j < width; j++)
        {
            int robos = 0;
            for (Robot r : sol)
            {
                if (r.pos_x == j && r.pos_y == i)
                {
                    robos++;
                }
            }
            line.append(to_string( robos));
        }
        cout << line << endl;
    }

    int finalValue = 1;
    for (int c : count)
    {
        finalValue *= c;
        cout << c << endl;
    }
    
    cout << "Count: " << finalValue << endl; 
}
