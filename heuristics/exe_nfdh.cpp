#include <iostream>
#include "next_fit_decreasing_height.h"

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

    cout << next_fit_decreasing_height(items).size() << endl;
    return 0;
}