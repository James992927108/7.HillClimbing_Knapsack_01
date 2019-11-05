# include "Hill_Climbing.h"
# include "Search_Economics.h"
# include <ctime>
# include <string>
# include <cstdlib>

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
    if (string(argv[4]) == "SE")
    {
        // int archive_num = 2;
        int searcher_num = 3;
        int region_num = 2; // 需要偶數
        int sample_num = 2;
        Search_Economics SE(filename, rounds ,iterations, searcher_num, region_num, sample_num);
        SE.Run();
        // cout << filename <<" " << HC.count << endl; 
    }
    return 0;
};