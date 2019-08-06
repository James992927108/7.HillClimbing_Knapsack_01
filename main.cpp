# include "Hill_Climbing.h"
#include <cstdlib>

int main(int argc, char *argv[] ){
    srand((unsigned) time(NULL) );
    string filename = string(argv[1]);
    int rounds = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    if (string(argv[4]) == "HC")
    {
        Hill_Climbing HC(filename, rounds ,iterations);
        HC.Run();
        cout << filename <<" " << HC.count << endl; 
    }
    return 0;
};