#include<bits/stdc++.h>
using namespace std;

#define MAX_RECT_DIMENSION_SIZE 1
#define MIN_RECT_DIMENSION_SIZE 0
#define rect pair<float, float>
#define vect vector<rect> 

int main() {
    int qnt_rectangles;
    cin >> qnt_rectangles;

    vect rectangles;
    vect bins;

    for(int i = 0; i < qnt_rectangles; ++i){
        float width, height;
        cin >> width >> height;
        rect rectangle = { width, height };
        rectangles.push_back(rectangle);
    }

    vect rectangles_by_width(rectangles);
    // Order by first element (width) non-cresc
    sort(rectangles_by_width.begin(), rectangles_by_width.end(), [](const auto& left, const auto& right) {
        return left.first > right.first;
    });

    vect rectangles_by_height(rectangles);
    // Order by second element (height) non-cresc
    sort(rectangles_by_height.begin(), rectangles_by_height.end(), [](const auto& left, const auto& right) {
        return left.second > right.second;
    });

    // And then was bin...
    
    //        ____
    //  ______|H |
    //  |  W  |  |
    //  ⁻⁻⁻⁻⁻⁻⁻⁻⁻⁻
    if (rectangles_by_width[0].second + rectangles_by_height[0].second <= MAX_RECT_DIMENSION_SIZE) {
        bins.emplace_back(rectangles_by_width[0].second + rectangles_by_height[0].second, rectangles_by_height[0].first);
    }
    //  ___
    //  |H |    
    //  |__|____
    //  |  W   |
    //  ⁻⁻⁻⁻⁻⁻⁻⁻
    else if (rectangles_by_width[0].first + rectangles_by_height[0].first <= MAX_RECT_DIMENSION_SIZE) {
        bins.emplace_back(rectangles_by_width[0].second + rectangles_by_height[0].second, rectangles_by_height[0].first);
    }
    // Need two bins...
    else {
        rect bin = {rectangles_by_width[0].first, rectangles_by_height[0].first};
        bins.emplace_back(bin);
        bins.emplace_back(bin);
    }    

    cout << bins.size() << '\n';
}