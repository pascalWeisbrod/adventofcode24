#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isCorrectEquation(long long final, long long result, vector<long long>* values, int idx)
{
    if (values -> size() == idx)
    {
        return result == final;
    }

    bool mul = isCorrectEquation(final, result * values -> at(idx), values, idx + 1);
    bool add = isCorrectEquation(final, result + values -> at(idx), values, idx + 1);
    return mul || add;
}

bool beholdTheConcatenator(long long final, long long result, vector<long long>* values, int idx)
{
    if (idx == values -> size())
    {
        return result == final;
    }

    if (isCorrectEquation(final, result, values, idx))
    {
        return true;
    }

    long long combined = stoll(to_string(result) + to_string(values -> at(idx)));

    bool mul = beholdTheConcatenator(final, result * values -> at(idx), values, idx + 1);
    bool add = beholdTheConcatenator(final, result + values -> at(idx), values, idx + 1);
    bool combiNation = beholdTheConcatenator(final, combined, values, idx + 1);
    return mul || add || combiNation;

}

void work(const string& input)
{
    string text = input;
    vector<vector<long long>> lines;
    
    while (text.size() > 0)
    {
        int ll = text.find("\n");
        string line = text.substr(0, ll);
        text.erase(0, ll + 1);

        vector<long long> values;
        int splitidx = line.find(":");
        long long solution = stoll(line.substr(0, splitidx));
        values.push_back(solution);
        line.erase(0, splitidx + 2);

        while (line.size() > 0 && splitidx != -1) {
            splitidx = line.find(" ");
            string number = line.substr(0, splitidx);
            values.push_back(stoll(number));
            line.erase(0, splitidx + 1);
        }
        lines.push_back(values);
    }

    cout << "Go!" << endl;


    long long calibration_result = 0;
    long long concated_result = 0;

    for (vector<long long> line : lines)
    {
        long long lineValue = line[0];
        if (isCorrectEquation(lineValue, 0, &line, 1))
        {
            calibration_result += lineValue;
            concated_result += lineValue; 
        }
        else if (beholdTheConcatenator(lineValue, 0, &line, 1))
        {
            concated_result += lineValue; 
        }
    }

    cout << "Calibration Result: " << calibration_result << endl;
    cout << "Concated Result: " << concated_result << endl;
}
