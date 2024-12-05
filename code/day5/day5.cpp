#include <iostream>
#include <string>
#include <vector>
#include <map>


using namespace std;

void sort(map<int, vector<int>>* noSpecs, vector<int>* line)
{
    for (int i = 0; i < (*line).size(); i++)
    {
        for (int j = 0; j < (*line).size() - 1; j++)
        {
            int first = (*line).at(j);
            int second = (*line).at(j + 1);
            bool contained = false;
            
            auto found = (*noSpecs).find(second);
            if (found == (*noSpecs).end())
            {
                continue;
            }
            for (int v : found -> second)
            {
                if (v == first)
                {
                    (*line)[j] = second;
                    (*line)[j + 1] = first;
                }
            }
        }
    }
}

bool lineValue(map<int, vector<int>>* noSpecs, vector<int>* line)
{
    vector<int> shouldPass;
    vector<int> shouldNotPass;
    for (int j = 0; j < (*line).size(); j++)
    {
        int value = (*line).at(j);

        for (int v : shouldNotPass)
        {
            if (v == value)
            {
                return false;
            }
        }
        shouldPass.erase(remove(shouldPass.begin(), shouldPass.end(), value), shouldPass.end());
        if ((*noSpecs).find(value) != (*noSpecs).end())
        {
            for (int v : (*noSpecs)[value])
            {
                shouldNotPass.push_back(v);
            }
        }
        shouldNotPass.push_back(value);
        for (int v : (*noSpecs)[value])
        {
            shouldNotPass.push_back(v);
        }
    }
    return true;
}

void work(const string& input)
{
    string text = input;
    map<int, vector<int>> invertedSpecs;
    vector<vector<int>> updates;
    bool didSplit = false;
    while (text.size() > 0)
    {
        int linelength = text.find("\n");
        string line = text.substr(0, linelength);
        text = text.substr(linelength + 1, text.size() - linelength - 1);

        if (line.size() == 0)
        {
            didSplit = true;
            continue;
        }

        if (!didSplit) 
        {
            int splitIdx = line.find("|");
            int l = stoi(line.substr(0, splitIdx));
            int r = stoi(line.substr(splitIdx + 1, line.size() - splitIdx - 1));


            if (invertedSpecs.find(r) == invertedSpecs.end())
            {
                invertedSpecs[r] = vector<int>({});
            }
            invertedSpecs[r].push_back(l);
            continue;
        }

        vector<int> update;
        while (line.size() > 0)
        {
            int endOfInt = line.find(",");
            int value = stoi(line.substr(0, endOfInt));
            update.push_back(value);
            line = line.substr(endOfInt + 1, line.size() - endOfInt - 1);
            if (endOfInt < 1)
            {
                break;
            }
        }
        updates.push_back(update);
    }

    
    cout << "Go!" << endl;

    long correctOrderings = 0;
    long wrongOrderings = 0;

    for (int i = 0; i < updates.size(); i++)
    {
        bool lineIsGood = lineValue(&invertedSpecs, &(updates.at(i)));
        if (lineIsGood)
        {
            correctOrderings += updates.at(i)[updates.at(i).size() / 2];
            continue;
        }
        sort(&invertedSpecs, &(updates.at(i)));
        wrongOrderings += updates.at(i)[updates.at(i).size() / 2];
    }
    cout << "Correctly Ordered: " << correctOrderings << endl;
    cout << "Wrongly: " << wrongOrderings << endl;
}
