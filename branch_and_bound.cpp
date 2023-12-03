#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <map>
#include <set>
#include <stack>
#include "ffdh.h"

using namespace std;

#define BIN_SIZE 1

int qnt_input;
int sup_limit, inf_limit;
vector<double> values;

class Node {
public:
    vector<double> bins;
    set<int> i_values;

    Node(set<int> i_values, vector<double> bins) {
        this->i_values = i_values;
        this->bins = bins;
    }
};


int get_inf_limit() {
    double sum_all_values = 0, sum_values_in_node = 0;
    for (auto value : values)
        sum_all_values += value;

    return ceil(sum_all_values/BIN_SIZE);
}

double get_bound_by_relaxation(const Node & node) {
    double sum_all_values = 0;
    for (auto value : values)
        sum_all_values += value;

    double sum_values_in_node = 0;
    for (auto i_value_in_node : node.i_values)
        sum_values_in_node += values[i_value_in_node];
    
    auto sum_values_not_in_node = sum_all_values - sum_values_in_node;
    return ceil(sum_values_not_in_node/BIN_SIZE);
}

bool is_promising(const Node & node) {
    return node.bins.size() + get_bound_by_relaxation(node) <= sup_limit;
}

int branch_and_bound() {
    stack<Node> nodes;
    for (int i = 0; i < qnt_input; ++i) {
        // It is guaranted that value ≤ BIN_SIZE
        nodes.push(Node({i}, {BIN_SIZE - values[i]}));
    }

    while(!nodes.empty()) {
        auto node = nodes.top();
        nodes.pop();
        
        if (node.i_values.size() == values.size()) {
            int qnt_bins = node.bins.size();
            if (qnt_bins == inf_limit)
                return qnt_bins;
            else
                sup_limit = min(sup_limit, qnt_bins);
        } 
        else if (is_promising(node)) {
            auto i_values = node.i_values;
            for (int i = 0; i < values.size(); ++i) {
                if (i_values.find(i) == i_values.end()) {
                    auto value = values[i];

                    Node new_node(node.i_values, node.bins);
                    new_node.i_values.insert(i);
                    
                    // Next-fit strategy
                    auto it_fits = node.bins.back() - value >= 0;
                    if (it_fits)
                        new_node.bins.back() -= value;
                    else
                        new_node.bins.push_back(BIN_SIZE - value);
                    
                    nodes.push(new_node);
                }
            }
        }
    }

    return sup_limit;
}

int ffdh_heuristic() {
    return 13;
}   

int main() {
    // cin >> qnt_input;
    
    vect rectangles;

    // for (int i = 0; i < qnt_input; ++i) {
    //     double value;
    //     cin >> value;
    //     values.push_back(value);
    //     Rectangle rectangle;
    //     rectangle.width = BIN_SIZE;
    //     rectangle.height = value;
    //     rectangle.id = 1;
    //     rectangles.push_back(rectangle);
    // }
    for (size_t i = 1; i <= 500; i++)
    {
        rectangles = load_rects(i);
        auto start = high_resolution_clock::now();
    
        sup_limit = first_fit_decreasing_height(rectangles).size();
        inf_limit = get_inf_limit();
        auto qnt_bins = branch_and_bound();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        ofstream textfile("numberofbins.txt", ios::app);
        textfile << to_string(i) << " " << to_string(rectangles.size()) << " " << to_string(qnt_bins) << " " << to_string(duration.count()) << "\n";
        textfile.close();
    }
    
    
    return 0;
}