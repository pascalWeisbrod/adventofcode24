#include <iostream>
#include <string>
#include <regex>

using namespace std;

void work(const string& input)
{
    regex expression ("^mul\\([0-9]+,[0-9]+\\)");
    long multiSums = 0;
    for (int i = 0; i < input.size(); i++)
    {
        string current = input.substr(i, input.size() - i);
        if(regex_search(current, expression))
        {
            int open = current.find("(") + 1;
            int close = current.find(")") - open;
            string parant = current.substr(open, close);

            int comma = parant.find(",");
            int x = stoi(parant.substr(0, comma));
            int y = stoi(parant.substr(comma + 1, parant.size() - comma - 1));
            multiSums += x * y;
        }
    }
    cout << multiSums << endl;
}
