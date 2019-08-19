#ifndef READFILE_H_INCLUDED
#define READFILE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

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
#endif