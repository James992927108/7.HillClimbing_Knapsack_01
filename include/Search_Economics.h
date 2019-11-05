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

struct Struct_T
{
    double T;
};

// struct Struct_V
// {
//     int h = archive_num;
//     int g = searcher_num;
// };
struct Struct_Solution
{
    vector<int> Position;
    double Fitness;

    Struct_Solution(int dimension)
    {
        Position = vector<int>(dimension, 0);
        Fitness = 0.0;
    }
    Struct_Solution(){};
};

struct Struct_Searcher
{
    int Which_region;
    vector<double> Region_expected_valued;
    Struct_Solution Solution;

    Struct_Searcher(int dimension, int region_num)
    {
        Solution = Struct_Solution(dimension);
        Region_expected_valued = vector<double>(region_num, 0.0);
    };
    Struct_Searcher(){};
};

struct Struct_Sample
{
    Struct_Solution Solution;

    Struct_Sample(int dimension)
    {
        Solution = Struct_Solution(dimension);
    }
    Struct_Sample(){};
};

struct Struct_Sample_V
{
    int which_searcher;
    Struct_Solution Solution;

    Struct_Sample_V(int dimension)
    {
        Solution = Struct_Solution(dimension);
    }
    Struct_Sample_V(){};
};

struct Struct_Region
{
    double T;

    int t_a = 1;
    int t_b = 1;

    double V;
    double M;

    double Best_fitness = __DBL_MAX__;

    vector<Struct_Sample> Sample;
    vector<Struct_Sample_V> Sample_V;

    Struct_Region(int sample_num, int sample_V_num, int dimension)
    {
        Sample = vector<Struct_Sample>(sample_num, Struct_Sample(dimension));
        Sample_V = vector<Struct_Sample_V>(sample_V_num, Struct_Sample_V(dimension));
    };
    Struct_Region(){};
};

class Search_Economics
{
public:
    Search_Economics(string filename, int rounds, int iterations, int searcher_num, int region_num, int sample_num);

    vector<Struct_Searcher> Initialization();
    vector<Struct_Region> Resoure_Arrangement();
    // Vision_Search
    vector<Struct_Region> Transition(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list);
    vector<Struct_Searcher> Expected_Valued(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list);
    void Vision_selection(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list);

    void Marketing_Survey();

    void Run();

    // int count = 0;

private:
    string filename;
    int rounds;
    int iterations;

    int searcher_num; //探索者個數
    int region_num;   //區域個數
    int sample_num;   //樣本個數
    int sample_V_num;

    Readfile input;
    int dimension;

    int archive_num; //子空間

    vector<Struct_Region> update_region(vector<Struct_Region> region_list);

    double get_T(Struct_Region region);
    double get_V(Struct_Region region, int which_searcher);
    double get_M(Struct_Region region, double total_Sample_Fitness);

    double get_total_V(vector<Struct_Region> region_list);
    double get_total_sample_fitness(vector<Struct_Region> region_list);

    vector<int> get_random_0_1_vector();
    int get_worst_sample_index(Struct_Region region);
    int get_fitness(vector<int> position);

    void print_solution(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list);
};