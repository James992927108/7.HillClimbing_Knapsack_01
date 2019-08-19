#include <random>
#include "Readfile.h"
#include "Solution.h"
#include <math.h>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct VS
{
    void Transition();
    void Expected_Valued();
    void Vision_selection();
};

struct Struct_T
{
    int t_a = 1;
    int t_b = 1;
    float T;
};

// struct Struct_V
// {
//     int h = archive_num;
//     int g = searcher_num;
// };
struct Struct_Searcher
{
    int Which_region;
    vector<int> Position;
    Struct_Searcher(int dimension)
    {
        Position = vector<int>(dimension,0);
    };
    Struct_Searcher(){};
};

struct Struct_Region
{
    Struct_T T;
    float V;
    float M;
    vector<vector<int>> Sample;

    Struct_Region(int dimension)
    {
        Sample = vector<vector<int>>(dimension,vector<int>(dimension,0));
    };
    Struct_Region(){};
};

class Search_Economics
{
    public:
        Search_Economics(string filename, int rounds, int iterations, int searcher_num, int region_num,int sample_num);

        vector<Struct_Searcher> Initialization();
        vector<Struct_Region> Resoure_Arrangement(vector<Struct_Searcher> searcher);
        VS Vision_Search();
        void Marketing_Survey();

        void Run();

        // vector<int> Transition(vector<int> &solution);
        // int Evalution(vector<int> &solution);
        // Solution Determination(Solution candidata, Solution global);
        // void print_solution(Solution candidata);

        // int count = 0;

    private:
        string filename;
        int rounds;
        int iterations;

        Readfile input;
        Struct_Region region;

        int archive_num; //子空間
        int region_num;  //區域個數                               
        int searcher_num;//探索者個數                               
        int sample_num;  //樣本個數
};