#include "next_fit_decreasing_height.h"

vector<Bin> next_fit_decreasing_height(vector<double> items) {
    sort(items.begin(), items.end(), greater<double>());
    return sequencing_generate_bins(items);
}