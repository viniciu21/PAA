#include "local_search.h"

vect rectangles_from_itens(const vector<double> & itens) {
    vect rectangles;
    
    for (int i = 0; i < itens.size(); ++i) {
        Rectangle rectangle;
        rectangle.width = 1;
        rectangle.height = itens[i];
        rectangle.id = i + 1;
        rectangles.push_back(rectangle);
    }

    return rectangles;
}

int local_search(const vector<double> & itens) {
    vect rectangles = rectangles_from_itens(itens); 
    vector<Bin> bins = first_fit_decreasing_height(rectangles);
    return bins.size();
}

int main() {
    int qnt_items;
    cin >> qnt_items;
    
    vector<double> items;
    for(int i = 0; i < qnt_items; ++i) {
        double item;
        cin >> item;
        items.push_back(item);
    }

    cout << local_search(items);
    return 0;
}