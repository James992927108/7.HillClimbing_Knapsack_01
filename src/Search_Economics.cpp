# include "Search_Economics.h"

Search_Economics::Search_Economics(string filename, int rounds ,int iterations,int searcher_num, int region_num,int sample_num)
{
    this->filename = filename;
    this->rounds = rounds;
    this->iterations = iterations;

    this->searcher_num = searcher_num;
    this->region_num = region_num;
    this->sample_num = sample_num;

    input = Readfile(filename);
};

vector<int> get_random_0_1_vector(int dimension)
{
    vector<int> temp(dimension);
    for(int i = 0; i < dimension; i++)
    {
        temp[i] = rand() % 2;
    }
    return temp;
};

int* get_binary(int archive_num)
{
    static int temp_binary[100];
    int i;
    for (i = 0; archive_num > 0; i++)
    {
        temp_binary[i] = archive_num % 2;
        archive_num = archive_num / 2;
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
    // 解 01 問題，取決於要保留幾個bits，例如 
    // 如果 2 個 region 只需要 1 個 bit，
    // 0...............
    // 1...............
    // 如果 4 個 region 需要 2 個 bits
    // 00..............
    // 01..............
    // 10..............
    // 11..............

    if (region_num == 1)
    {
        this -> archive_num = 1;
    }
    else
    {
        this -> archive_num = log2(region_num);
    }
    cout <<"region_num " << region_num << endl;
    cout <<"archive_num " << archive_num << endl;

    unsigned int dimension = input.weight.size();
    vector<Struct_Searcher> searcher(searcher_num, Struct_Searcher(dimension));
    for(int i = 0; i < searcher_num; i++)
    {
        searcher[i].Position = get_random_0_1_vector(dimension);
        searcher[i].Which_region = rand() % region_num;
        searcher[i].Position = check_region_character(archive_num, searcher[i].Position, searcher[i].Which_region);
    }
    return searcher;
};

vector<Struct_Region> Search_Economics::Resoure_Arrangement(vector<Struct_Searcher> searcher)
{
    unsigned int dimension = input.weight.size();

    vector<Struct_Region> region_list(region_num,Struct_Region(dimension));
    for(int i = 0; i < region_num; i++)
    {
        for(int j = 0; j < sample_num; j++)
        {
            region_list[i].Sample[j] = get_random_0_1_vector(dimension);
            region_list[i].Sample[j] = check_region_character(archive_num, region_list[i].Sample[j], i);
        }
    }
    return region_list;
};

void VS::Transition()
{

};
void VS::Expected_Valued()
{

};
void VS::Vision_selection()
{

};

VS Search_Economics::Vision_Search()
{
    VS update;
    update.Transition();

    return update;
};

void Search_Economics::Marketing_Survey()
{

};

void Search_Economics::Run()
{
    vector<Struct_Searcher> searcher = Initialization();

    vector<Struct_Region> region_list = Resoure_Arrangement(searcher);

    unsigned int dimension = input.weight.size();
    for (int i = 0; i < searcher_num; i++)
    {
        cout << "---------------" << endl;
        cout << "searcher_num " << i << endl;
        cout << "which region " << searcher[i].Which_region << endl;
        for (unsigned int j = 0; j < dimension; j++)
            cout << searcher[i].Position[j] << " ";
        cout << endl;
    }

    // for (int i = 0; i < region_num; i++)
    // {
    //     cout << "---------------" << endl;
    //     cout << "which region " << i << endl;
    //     for (int j = 0; j < sample_num; j++)
    //     {
    //         cout << "which sample " << j << endl;
    //         for (unsigned int k = 0; k < dimension; k++)
    //         {
    //             cout << region_list[i].Sample[j][k] << " ";
    //         }
    //         cout << endl;
    //     }
    // }
};
