#include <iostream>
#include <string>
#include <vector>

using namespace std;

void fill(vector<int>* positions)
{
    for (int i = 0; i < positions -> size(); i++)
    {
        int value = positions -> at(i);

        if (value == -1)
        {
            for (int j = positions -> size() - 1; j >= i; j--)
            {
                if (positions -> at(j) != -1)
                {
                    value = positions -> at(j);
                    (*positions)[j] = -1;
                    break;
                }
            }
        }

        (*positions)[i] = value;
    }
}

class File
{
    public:
        int count;
        int id;
        File(int c, int v)
        {
            count = c;
            id = v;
        }
};
void fileToIntVector(vector<File>* files, vector<int>* ints)
{
    for (int i = 0; i < files -> size(); i++)
    {
        File f = files -> at(i);
        if (f.count == 0)
            continue;
        for (int j = 0; j < f.count; j++)
            ints -> push_back(f.id);
    }
}
long long checksum(vector<int>* positions)
{
    long long sum = 0;
    for (int i = 0; i < positions -> size(); i++)
    {
        int value = positions -> at(i);
        if (value < 0)
            continue;
        sum += value * i;
    }
    return sum; 
}
void work(const string& input)
{
    string text = input;
    vector<int> positions;
    vector<File> positions2;

    for (int i = 0; i < text.size(); i++)
    {
        int value = text.at(i) - '0';
        if (i % 2 == 0) 
        {
            for (int j = 0; j < value; j++)
            {
                positions.push_back(i / 2);
            }
            File f(value, i / 2);
            positions2.push_back(f);
        }
        else
        {
            for (int j = 0; j < value; j++)
            {
                positions.push_back(-1);
            }
            File d(value, -1);
            positions2.push_back(d);
        }
    }


    cout << "Go!" << endl;


    fill(&positions);

    vector<File> files;
    for (int i = 0; i < positions2.size(); i++)
    {
        File value = positions2.at(i);
        if (value.id == -1)
        {
            for (int j = positions2.size() - 1; j >= i; j--)
            {
                File current = positions2.at(j);
                if (current.id == -1)
                    continue;
                if (current.count <= value.count)
                {
                    files.push_back(current);
                    value.count -= current.count;
                    positions2[j].id = -1;
                }
            }
        }
        files.push_back(value);
        
    }

    vector<int> part2;
    for (File f : files)
        for (int i = 0; i < f.count; i++)
            part2.push_back(f.id);



    cout << "Part 1 Checksum: " << checksum(&positions) << endl;
    cout << "Part 2 Checksum: " << checksum(&part2) << endl;
}
