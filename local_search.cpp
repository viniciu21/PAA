#include "local_search.h"

vector<double> get_sequencing_items_from_bins(const vector<Bin> & bins) {
    vector<double> items;
    for (auto bin : bins) {
        for (auto rect : bin.rect_inside) {
            items.push_back(rect.height);
        }
    }
    return items;
}

vector<Bin> swap_and_generate_bins(int a, int b, vector<Bin> bins) {
    vector<double> items = get_sequencing_items_from_bins(bins);
    swap(items.at(a), items.at(b));
    return sequencing_generate_bins(items);
}

vector<Bin> local_search(const vector<double> & items) {
    vector<Bin> solution = next_fit_decreasing_height(items);
    vector<Bin> best_solution = solution;

    bool can_improve = true;

    while (can_improve) {
        solution = best_solution;

        for (int i = 0; i < items.size(); ++i) {
            int i_other_item = rand() % items.size();

            vector<Bin> bins = swap_and_generate_bins(i, i_other_item, solution);
            
            if (bins.size() < best_solution.size())
                best_solution = bins;
        }
        can_improve = solution.size() > best_solution.size();
    }

    return solution;
}