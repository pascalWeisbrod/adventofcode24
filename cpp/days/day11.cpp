#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;


long long bling(long long stone, map<string, long long>* lookup, int depth)
{
    if (depth == 0)
        return 1;    

    string hash = to_string(stone) + "," + to_string(depth);

    if (lookup -> find(hash) != lookup -> end())
        return lookup -> at(hash);

    int digits = log10(stone) + 1;
    long long count = 0;
    if (stone == 0)
        count = bling(1, lookup, depth - 1);
    else if (digits % 2 == 0)
    {
        long long first = stone / pow(10, digits / 2);
        long long second = stone % (long long)(pow(10, digits / 2)); 

        count = bling(first, lookup, depth - 1) + bling(second, lookup, depth - 1);
    }
    else
        count = bling(stone * 2024, lookup, depth - 1); 

    lookup -> insert({ hash, count });
    return count;
}


long long blingbling(vector<long long>* stones, map<string, long long>* lookup, int blingblings)
{
    long long count = 0;
    for (int s : *stones)
    {
        count += bling(s, lookup, blingblings);
    }
    return count;
}

void work(const string& input)
{
    string text = input;
    vector<long long> stones;

    while (text.size() > 0)
    {
        int l = text.find(' ');
        if (l == -1)
            l = text.size();
        stones.push_back(stoll(text.substr(0, l)));
        text = text.erase(0, l + 1);
    }

    cout << "Go!" << endl;

    map<string, long long> lookup;
    long long count25 = blingbling(&stones, &lookup, 25);
    long long count75 = blingbling(&stones, &lookup, 75);


    cout << "Stone count after 25: " << count25 << endl;
    cout << "Stone count after 75: " << count75 << endl;
}
