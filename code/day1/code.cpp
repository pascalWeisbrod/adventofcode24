#include <iostream>
#include <ostream>
#include <string>
#include <climits>

void work(const std::string& input)
{
    std::string text = input;
    int length = 1000;
    int left[1000];
    int right[1000];


    for (int i = 0; i < length; i++) {
        std::string line = text.substr(0, text.find("\n"));
        std::string lstr = line.substr(0, line.find(" "));
        std::string rstr = line.substr(line.find_last_of(" "), line.size());
        text = text.substr(line.size() + 1, text.size());

        
        int l = std::stoi(lstr);
        int r = std::stoi(rstr);

        left[i] = l;
        right[i] = r;
    } 

    std::cout << "Go!" << std::endl;

    long similarityScore = 0;
    for (int i = 0; i < length; i++) {
        int count = 0;
        for (int j = 0; j < length; j++) {
            if (left[i] == right[j]) {
                count++;
            }
        }
        similarityScore += count * left[i];
    }

    long sum = 0;
    for (int i = 0; i < length; i++) {
        int lIdx = 0;
        int rIdx = 0;


        for (int j = 0; j < length; j++) {
            if (left[j] < left[lIdx]) {
                lIdx = j;
            }
        }

        for (int k = 0; k < length; k++) {
            if (right[k] < right[rIdx]) {
                rIdx = k;
            }
        }
        
        int lVal = left[lIdx];
        int rVal = right[rIdx];
        left[lIdx] = INT_MAX;
        right[rIdx] = INT_MAX;
        
        int dif = lVal - rVal;
        if (dif < 0)
        {
            dif = dif * -1;
        }
        sum += dif; 
    }
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Similarity Score: " << similarityScore << std::endl;
}
