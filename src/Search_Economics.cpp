#include "Search_Economics.h"

Search_Economics::Search_Economics(string filename, int rounds, int iterations, int searcher_num, int region_num, int sample_num)
{
    this->filename = filename;
    this->rounds = rounds;
    this->iterations = iterations;

    this->searcher_num = searcher_num;
    this->region_num = region_num;
    this->sample_num = sample_num;
    this->sample_V_num = searcher_num * sample_num;
    // 成上 2 的目的 ? 

    this->input = Readfile(filename);
    this->dimension = input.weight.size();
};

vector<int> Search_Economics::get_random_0_1_vector()
{
    vector<int> temp(dimension);
    for (int i = 0; i < dimension; i++)
    {
        temp[i] = rand() % 2;
    }
    return temp;
};

int *get_binary(int Which_region)
{
    static int temp_binary[100];
    int i;
    for (i = 0; Which_region > 0; i++)
    {
        temp_binary[i] = Which_region % 2;
        Which_region = Which_region / 2;
    }
    return temp_binary;
};

vector<int> check_region_character(int archive_num, vector<int> Position, int Which_region)
{
    int *region_character = get_binary(Which_region);
    for (int j = 0; j < archive_num; j++)
    {
        Position[j] = region_character[j];
    }
    return Position;
}

vector<Struct_Searcher> Search_Economics::Initialization()
{
    if (region_num == 1)
    {
        this->archive_num = 1;
    }
    else
    {
        this->archive_num = log2(region_num);
    }
    cout << "searcher_num " << searcher_num << endl;
    cout << "region_num " << region_num << endl;
    cout << "sample_num " << sample_num << endl;

    vector<Struct_Searcher> searcher(searcher_num, Struct_Searcher(dimension, region_num));
    for (int i = 0; i < searcher_num; i++)
    {
        searcher[i].Which_region = rand() % region_num;
        searcher[i].Solution.Position = check_region_character(archive_num, get_random_0_1_vector(), searcher[i].Which_region);
    }
    return searcher;
};

vector<Struct_Region> Search_Economics::Resoure_Arrangement()
{
    vector<Struct_Region> region_list(region_num, Struct_Region(sample_num, sample_V_num ,dimension));
    for (int i = 0; i < region_num; i++)
    {
        for (int j = 0; j < sample_num; j++)
        {
            region_list[i].Sample[j].Solution.Position = check_region_character(archive_num, get_random_0_1_vector(), i);
        }
    }
    return region_list;
};
// -------------------------------------------------------------------------------------------------------
// Transition
int random(int lb, int ub)
{
    return lb + (rand() % (ub - lb + 1));
};

int Search_Economics::get_fitness(vector<int> position)
{
    int fitness = 0;
    for (unsigned int i = 0; i < position.size(); i++)
    {
        if (position[i] == 1)
        {
            fitness += input.profits[i];
        }
    }
    return fitness;
};

int Search_Economics::get_worst_sample_index(Struct_Region region)
{
    int worst_Sample_index = 0;
    for (int i = 0; i < sample_num; i++)
    {
        if (region.Sample[worst_Sample_index].Solution.Fitness < region.Sample[i].Solution.Fitness)
        {
            worst_Sample_index = i;
        }
    }
    return worst_Sample_index;
};

vector<Struct_Region> Search_Economics::update_region(vector<Struct_Region> region_list)
{
    for (int i = 0; i < region_num; i++)
    {
        for (int j = 0; j < sample_num; j++)
        {
            region_list[i].Sample[j].Solution.Fitness = get_fitness(region_list[i].Sample[j].Solution.Position);
            if (region_list[i].Sample[j].Solution.Fitness < region_list[i].Best_fitness)
            {
                region_list[i].Best_fitness = region_list[i].Sample[j].Solution.Fitness;
            }
        }

        for (int j = 0; j < sample_V_num; j++)
        {
            region_list[i].Sample_V[j].Solution.Fitness = get_fitness(region_list[i].Sample_V[j].Solution.Position);
        }

        // 最差的Sample被Sample_V取代
        int worst_Sample_index = get_worst_sample_index(region_list[i]);
        for (int j = 0; j < sample_V_num; j++)
        {
            if (region_list[i].Sample_V[j].Solution.Fitness < region_list[i].Sample[worst_Sample_index].Solution.Fitness)
            {
                region_list[i].Sample[worst_Sample_index].Solution = region_list[i].Sample_V[j].Solution;
            }
        }
    }
    return region_list;
};

vector<Struct_Region> Search_Economics::Transition(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list)
{
    for (int k = 0; k < searcher_num; k++)
    {
        for (int i = 0; i < region_num; i++)
        {
            vector<int> child1(dimension, 0), child2(dimension, 0);

            for (int j = 0; j < sample_num; j++)
            {
                int start = random(log2(region_num), dimension - 1);
                int end = random(log2(region_num), dimension - 1);
                while (start == end)
                {
                    end = random(log2(region_num), dimension - 1);
                }
                if (start > end)
                {
                    swap(start, end);
                }
                for (int d = 0; d < dimension; d++)
                {
                    if (d >= start && d <= end)
                    {
                        child1[d] = searcher_list[k].Solution.Position[d];
                        child2[d] = region_list[i].Sample[j].Solution.Position[d];
                    }
                    else
                    {
                        child1[d] = region_list[i].Sample[j].Solution.Position[d];
                        child2[d] = searcher_list[k].Solution.Position[d];
                    }
                }

                child1 = check_region_character(archive_num, child1, i);
                child2 = check_region_character(archive_num, child2, i);

                region_list[i].Sample_V[j * searcher_num].which_searcher = k;
                region_list[i].Sample_V[j * searcher_num].Solution.Position = child1;

                region_list[i].Sample_V[j * searcher_num + 1].which_searcher = k;
                region_list[i].Sample_V[j * searcher_num + 1].Solution.Position = child2;
            }
        }
    }

    region_list = update_region(region_list);

    return region_list;
};
// -------------------------------------------------------------------------------------------------------
// Expected_Valued
double Search_Economics::get_T(Struct_Region region)
{
    return region.t_b / region.t_a;
};

double Search_Economics::get_total_V(vector<Struct_Region> region_list)
{
    double total_all_region_V = 0;
    for (int i = 0; i < searcher_num; i++)
    {
        double all_region_V = 0;
        for (int j = 0; j < region_num; j++)
        {
            all_region_V += get_V(region_list[j], i);
        }
        total_all_region_V += all_region_V;
    }
    return total_all_region_V;
};

double Search_Economics::get_V(Struct_Region region, int which_searcher)
{
    double temp = 0.0;
    for (int i = 0; i < sample_V_num; i++)
    {
        if (region.Sample_V[i].which_searcher == which_searcher)
        {
            temp += region.Sample_V[i].Solution.Fitness;
        }
    }
    return temp /= sample_V_num;
};

double Search_Economics::get_total_sample_fitness(vector<Struct_Region> region_list)
{
    double all_sample_fitness = 0;
    for (int i = 0; i < region_num; i++)
    {
        for (int j = 0; j < sample_num; j++)
        {
            all_sample_fitness += region_list[i].Sample[j].Solution.Fitness;
        }
    }
    return all_sample_fitness;
}

double Search_Economics::get_M(Struct_Region region, double total_Sample_Fitness)
{
    return region.Best_fitness / total_Sample_Fitness;
};

vector<Struct_Searcher> Search_Economics::Expected_Valued(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list)
{
    double total_V = get_total_V(region_list);
    double total_Sample_Fitness = get_total_sample_fitness(region_list);

    for (int i = 0; i < searcher_num; i++)
    {
        for (int j = 0; j < region_num; j++)
        {
            region_list[j].T = get_T(region_list[j]);
            // cout << "T " << region_list[j].T << endl;
            region_list[j].V = 1 - (get_V(region_list[j], i) / total_V);
            // cout << "V " << region_list[j].V << endl;
            region_list[j].M = 1 - get_M(region_list[j], total_Sample_Fitness);
            // cout << "M " << region_list[j].M << endl;
            searcher_list[i].Region_expected_valued[j] = region_list[j].T * region_list[j].V * region_list[j].M;
            // cout << searcher_list[i].Region_expected_valued[j] << endl;
        }
    }
    return searcher_list;
};
// -------------------------------------------------------------------------------------------------------
// Vision_selection
int get_vector_max_index(vector<double> v)
{
    return max_element(v.begin(), v.end()) - v.begin();
}

void get_best_region_sample()
{

}

void Search_Economics::Vision_selection(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list)
{ 
    for (int i = 0; i < searcher_num; i++)
    {
        // cout << "current_region " << searcher_list[i].Which_region << endl;
        // for (int j = 0; j < region_num; j++)
        // {
        //     cout << searcher_list[i].Region_expected_valued[j] << endl;
        // }
        // 每個搜尋者挑選所有區域中最好的區域，並在從該區域中找出最好的 Sample，取代搜索者。
        int choose_region = get_vector_max_index(searcher_list[i].Region_expected_valued);
        searcher_list[i].Which_region = choose_region;
    }
};

void Search_Economics::Marketing_Survey(){

};

void Search_Economics::Run()
{
    vector<Struct_Searcher> searcher_list = Initialization();
    
    vector<Struct_Region> region_list = Resoure_Arrangement();

    for (int i = 0; i < iterations; i++)
    {
        region_list = Transition(searcher_list, region_list);

        searcher_list = Expected_Valued(searcher_list, region_list);

        Vision_selection(searcher_list, region_list);
    }
    print_solution(searcher_list, region_list);

};

void Search_Economics::print_solution(vector<Struct_Searcher> searcher_list, vector<Struct_Region> region_list)
{
    cout << "===========================" << endl;
    cout << "Region information " << endl;
    cout << "===========================" << endl;
    for (int i = 0; i < region_num; i++)
    {
        for (int j = 0; j < sample_num; j++)
        {
            cout << i << " Region " << j << " Sample " << endl;
            cout << "Fitness " << region_list[i].Sample[j].Solution.Fitness << endl;
            for (int k = 0; k < dimension; k++)
            {
                cout << region_list[i].Sample[j].Solution.Position[k] << " ";
            }
            cout << endl;
        }
        for (int j = 0; j < sample_V_num; j++)
        {
            cout << i << " Region " << j << " Sample_V " << endl;
            cout << "which_searcher " << region_list[i].Sample_V[j].which_searcher << endl;
            cout << "Fitness " << region_list[i].Sample_V[j].Solution.Fitness << endl;
            for (int k = 0; k < dimension; k++)
            {
                cout << region_list[i].Sample_V[j].Solution.Position[k] << " ";
            }
            cout << endl;
        }
    }
    cout << "===========================" << endl;
    cout << "Searcher information " << endl;
    cout << "===========================" << endl;
    for (int i = 0; i < searcher_num; i++)
    {
        cout << "searcher " << i << " Which_region "<< searcher_list[i].Which_region<< endl;
        for (int j = 0; j < region_num; j++)
        {
            cout <<"REV " << j << " : " << searcher_list[i].Region_expected_valued[j] << endl;
        }
    }
}
