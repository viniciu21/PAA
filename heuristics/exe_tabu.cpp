#include <iostream>
#include "tabu_search.h"

using namespace std;

int main() {
    int qnt_items;
    cin >> qnt_items;

    vector<double> items;
    for (int i = 0; i < qnt_items; i++)
    {
        double item_value;
        cin >> item_value;
        items.push_back(item_value);
    }

    auto start = high_resolution_clock::now();

    auto bins = tabu_search(items);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << bins.size() << ' ' << duration.count() << endl;
    return 0;
}