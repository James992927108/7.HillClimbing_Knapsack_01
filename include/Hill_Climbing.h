#include <random>
#include "Readfile.h"
#include "Solution.h"
using namespace std;

class Hill_Climbing
{
    public:
        Hill_Climbing(string filename,int rounds ,int iterations);
        void Run();
        vector<int> Initial_solution();
        vector<int> Transition(vector<int> &solution);
        int Evalution(vector<int> &solution);
        Solution Determination(Solution candidata, Solution global);
        void print_solution(Solution candidata);

        int count = 0;

    private:
        string filename;
        int rounds;
        int iterations;

        Readfile input;

        Solution candidata;
        Solution global;
};