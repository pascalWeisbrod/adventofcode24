#include <iostream>
#include <string>
#include <vector>

using namespace std;

void work(const string& input)
{
    string text = input;
    vector<int> positions;
    int files = 0;

    for (int i = 0; i < text.size(); i++)
    {
        int value = text.at(i) - '0';
        for (int j = 0; j < value; j++)
        {
            switch (i % 2) {
                case 0:
                    files++;
                    positions.push_back(i / 2);
                    break;
                case 1:
                    positions.push_back(-1);
                    break;
            }
        }
    }


    cout << "Go!" << endl;


    long long checksum = 0;
    for (int i = 0; i < positions.size() && i < files; i++)
    {
        int value = positions.at(i);

        if (value == -1)
        {
            for (int j = positions.size() - 1; j >= 0; j--)
            {
                if (positions.at(j) != -1)
                {
                    value = positions.at(j);
                    positions[j] = -1;
                    break;
                }
            }
        }

        positions[i] = value;
        checksum += i  * value;
    }

    cout << checksum << endl;
}
