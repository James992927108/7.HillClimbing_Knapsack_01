#include "Readfile.h"

void Read_templete(string templete,vector<int> &value)
{
    fstream f(templete);
    int temp;
    while(f >> temp)
    {
        value.push_back(temp);
    }
    f.close();    
}
Readfile::Readfile()
{

};
Readfile::Readfile(string filename)
{
    string folder = "Knapsack_01/" + filename + "/";
    string c =folder + "p" + filename + "_c.txt";
    string w =folder + "p" + filename + "_w.txt";
    string p =folder + "p" + filename + "_p.txt";
    string s =folder + "p" + filename + "_s.txt";

    fstream fc(c);
    fc >> knapsack_capacity;
    fc.close();

    Read_templete(w,weight);
    Read_templete(p,profits);
    Read_templete(s,optimal_selection);
};