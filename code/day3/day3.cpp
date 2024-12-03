#include <iostream>
#include <string>
#include <regex>

using namespace std;

void work(const string& input)
{
    long multiSums = 0;
    long multiCondSums = 0;
    bool enabled = true;

    regex expression ("^mul\\([0-9]+,[0-9]+\\)");
    regex enabledExpr ("^((do\\(\\))|(don't\\(\\))|(mul\\([0-9]+,[0-9]+\\)))");

    for (int i = 0; i < input.size(); i++)
    {
        string current = input.substr(i, input.size() - i);
        if(regex_search(current, enabledExpr))
        {
            if (current.at(0) == 'm')
            {
                int open = current.find("(") + 1;
                int close = current.find(")") - open;
                string parant = current.substr(open, close);

                int comma = parant.find(",");
                int x = stoi(parant.substr(0, comma));
                int y = stoi(parant.substr(comma + 1, parant.size() - comma - 1));

                multiSums += x * y;
                if (enabled)
                {
                    multiCondSums += x * y;
                }
                continue;
            }
            if (current.at(2) == '(')
            {
                enabled = true;
                continue;
            }
            enabled = false;
        }
    }
    cout << "Multiplier: " << multiSums << endl;
    cout << "Multiplier under condition: " << multiCondSums << endl;
}
