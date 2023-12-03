#include <iostream>
#include "local_search.h"

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

    cout << local_search(items).size() << endl;
    return 0;
}