#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define BIN_SIZE 1

int qnt_input;
vector<double> values;

int main() {
    cin >> qnt_input;

    for (int i = 0; i < qnt_input; ++i) {
        double value;
        cin >> value;
        values.push_back(value);
    }

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
    return 0;
}