#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <chrono>

using namespace std;

#define BIN_SIZE 1

int qnt_input;
vector<double> values;
string FOLDER_PATH_BASE = "JSON_";


vector<double> load_rects(int instance_number)
{
    int number_rect = 0;
    int i;

    vector<double> valuesH;

    string file_chosed_path = "./Instances/1dcleaned/" + FOLDER_PATH_BASE + to_string(instance_number) + ".txt";
    cout <<  FOLDER_PATH_BASE + to_string(instance_number) << endl;
    fstream file_chosen;

    file_chosen.open(file_chosed_path);

    file_chosen >> number_rect;
    double value; 
    for (i = 0; i < number_rect; i++)
    {
        file_chosen >> value;
        valuesH.push_back(value);
    }

    return valuesH;
}

int solve(vector<double> values) {
    int min_qnt_bins = INT_MAX;
    do {
        vector<double> bins;
        bins.push_back(BIN_SIZE);
        for (auto value : values) {
            if (bins.back() - value < 0)
                bins.push_back(BIN_SIZE - value);
            else
                bins.back() -= value;
        }
        min_qnt_bins = min(min_qnt_bins, (int) bins.size());
    } while (next_permutation(values.begin(), values.end()));
    
    cout << min_qnt_bins << endl;

    return min_qnt_bins;
}

int main() {
    //for (int i = 1; i <= 2; ++i) {
        values = load_rects(1);
        solve(values);
    //}

    
    return 0;
}