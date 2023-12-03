#include "tabu_search.h"

bool find_in_tabu_list(const pair<int,int> mov, const list<pair<int, int>> & tabu, int tabu_list_size = 5) {
    int i = 0; 
    
    for (auto p : tabu) {
        if (i >= min((int) tabu.size(), tabu_list_size))
            break;
        
        if (mov == p)
            return true;

        ++i;
    }

    return false;
}
vector<Bin> tabu_search(const vector<double> & items) {
    vector<Bin> solution = next_fit_decreasing_height(items);
    vector<Bin> best_solution = solution;

    bool can_improve = true;
    list<pair<int, int>> tabu;

    while (can_improve) {
        solution = best_solution;

        for (int i = 0; i < items.size(); ++i) {
            int i_other_item = i;
            while (i_other_item == i) {
                i_other_item = rand() % items.size();
            }

            if (find_in_tabu_list({i, i_other_item}, tabu))
                continue;

            tabu.push_front({i, i_other_item});
            vector<Bin> bins = swap_and_generate_bins(i, i_other_item, solution);
            
            if (bins.size() < best_solution.size()) {
                cout << "wow\n";
                best_solution = bins;
            }
        }
        can_improve = solution.size() > best_solution.size();
    }

    return solution;
}