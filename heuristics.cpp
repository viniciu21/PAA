#include <iostream>
#include "next_fit_decreasing_height.h"
#include "local_search.h"
#include "tabu_search.h"

using namespace std;

vector<double> get_items_from_instance(int instance_number) {
    vector<double> items;

    string file_chosed_path = "./Instances/1dcleaned/JSON_" + to_string(instance_number) + ".txt";
    fstream file_chosen;

    file_chosen.open(file_chosed_path);

    int qnt_items;
    file_chosen >> qnt_items;

    for (int i = 0; i < qnt_items; i++)
    {
        double item_value;
        file_chosen >> item_value;
        items.push_back(item_value);
    }

    return items;
}

int main() {
    cout << "Number of instance? ";
    int instance_number;
    cin >> instance_number;

    vector<double> items = get_items_from_instance(instance_number);

    cout << "Available algorithms:\n\n";
    cout << "1 - Next fit decreasing height (NFDH) Heuristic\n";
    cout << "2 - Local search (LS) Heuristic\n";
    cout << "3 - Tabu search (TS) Heuristic\n";
    cout << "\nWhich one do you wanna use? ";
    int algorithm_selected;
    cin >> algorithm_selected;

    vector<Bin> solution;
    switch (algorithm_selected) {
        case 1:
            solution = next_fit_decreasing_height(items);
            break;
        case 2:
            solution = next_fit_decreasing_height(items);
            break;
        case 3:
            solution = tabu_search(items);
            break;
    }
    cout << solution.size() << '\n';
    return 0;
}