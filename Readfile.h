#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std; 

class Readfile
{
    public:
        Readfile();
        Readfile(string filename);

    public:
        int knapsack_capacity;
        vector<int> weight;
        vector<int> profits;
        vector<int> optimal_selection;
};