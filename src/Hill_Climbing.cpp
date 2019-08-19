# include "Hill_Climbing.h"

Hill_Climbing::Hill_Climbing(string filename, int rounds ,int iterations)
{
    this->filename = filename;
    this->rounds = rounds;
    this->iterations = iterations;

    input = Readfile(filename);
};

vector<int> Hill_Climbing::Initial_solution()
{   
    vector<int> solution(input.weight.size());
    for (unsigned int i = 0; i < solution.size(); i ++){
        solution[i] = 0;
    }
    return solution ;
};

vector<int> Hill_Climbing::Transition(vector<int> &solution){

    int max_w = input.knapsack_capacity;
    int weight;
    do
    {
        weight = 0;
        int randon_select_index = rand()%(solution.size());
        solution[randon_select_index] = !solution[randon_select_index];
        // print_solution(solution);
        for(unsigned int i = 0 ; i < solution.size() ; i++)
        {
            if(solution[i] == 1)
            {
                weight += input.weight[i];
            }
        }
        // cout << "weight : " << weight <<endl;
    }while(weight > max_w);
    
    return solution;
};

int Hill_Climbing::Evalution(vector<int> &solution)
{
    int fitness = 0;
    for(unsigned int i = 0; i < solution.size(); i++)
    {
        if(solution[i] == 1)
        {
            fitness += input.profits[i];
        } 
    }
    return fitness;
};

Solution Hill_Climbing::Determination(Solution candidata, Solution global){
    if(candidata.fitness > global.fitness)
    {
        global.position = candidata.position;
        global.fitness = candidata.fitness;
    }
    return global;
};

void Hill_Climbing::print_solution(Solution candidata)
{   
    for (unsigned int i = 0 ;i < input.weight.size() ; i ++)
    {
        cout << candidata.position[i] << " ";
    }
    cout << endl;
    cout << candidata.fitness << endl;
};

void Hill_Climbing::Run()
{
    int round = 0;

    while (round < rounds)
    {
        // cout << "round : " << round << endl;

        global.position = Initial_solution();
        global.fitness = Evalution(global.position);

        candidata.position = Initial_solution();
        candidata.fitness = Evalution(candidata.position);
    
        for (int i = 0; i < iterations ; i ++){
            // cout << i << endl;
            candidata.position = Transition(candidata.position);
            // for(int j = 0; j < candidata.position.size(); j++)
            // {
            //     cout << candidata.position[j] << " ";
            // }
            // cout << endl;
            candidata.fitness = Evalution(candidata.position);

            global = Determination(candidata,global);
            
            if(candidata.position == input.optimal_selection)
            {
                // cout << i << endl;
                ++count; 
                break;
            }
        }
        print_solution(global);
        ++round;
    }
};