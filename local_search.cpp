#include "local_search.h"


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

vect rectangles_from_items(const vector<double> & items) {
    vect rectangles;
    
    for (int i = 0; i < items.size(); ++i) {
        Rectangle rectangle;
        rectangle.width = 1;
        rectangle.height = items[i];
        rectangle.id = i + 1;
        rectangles.push_back(rectangle);
    }

    return rectangles;
}

vector<Bin> local_search(const vector<double> & items) {
    vect rectangles = rectangles_from_items(items); 
    vector<Bin> solution = first_fit_decreasing_height(rectangles);
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

// int main() {
//     srand(time(0)); 

//     int qnt_items;
//     cin >> qnt_items;
    
//     vector<double> items;
//     for(int i = 0; i < qnt_items; ++i) {
//         double item;
//         cin >> item;
//         items.push_back(item);
//     }

//     cout << local_search(items).size() << '\n';
//     return 0;
// }