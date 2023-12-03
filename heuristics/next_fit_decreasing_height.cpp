#include "next_fit_decreasing_height.h"

vector<Bin> sequencing_generate_bins(const vector<double> & items) {
    int qnt_bins = 1;
    vector<Bin> bins;
    bins.push_back({0, 1, 0, 1, 0, qnt_bins});

    double current_sum = 0;
    for (int i = 0; i < items.size(); ++i) {
        auto item = items[i];

        if (current_sum + item > 1) {
            current_sum = 0;
            ++qnt_bins;
            bins.push_back({0, 1, 0, 1, 0, qnt_bins});
        }

        current_sum += item;
        bins.back().rect_inside.push_back({1, (float) item, 0, 0, 0, i});
    }

    return bins;
}

vector<Bin> next_fit_decreasing_height(vector<double> items) {
    sort(items.begin(), items.end(), greater<double>());
    return sequencing_generate_bins(items);
}