#include<bits/stdc++.h>
using namespace std;

#define MAX_RECT_DIMENSION_SIZE 1
#define MIN_RECT_DIMENSION_SIZE 0
#define rect pair<float, float>
#define vect vector<rect> 

struct Point {
    float x;
    float y;
};

struct Rect {
    float width;
    float height;
};

struct Bin {
    float width;
    float height;
    vector<pair<Point, Point>> cuts;
};

int main() {
    int qnt_rectangles;
    cin >> qnt_rectangles;

    vector<Rect> rectangles;
    vector<Bin> bins;

    for(int i = 0; i < qnt_rectangles; ++i){
        float width, height;
        cin >> width >> height;
        Rect rectangle;
        rectangle.width = width;
        rectangle.height = height;
        rectangles.push_back(rectangle);
    }

    vector<Rect> rectangles_by_width(rectangles);
    // Order by first element (width) non-cresc
    sort(rectangles_by_width.begin(), rectangles_by_width.end(), [](const auto& left, const auto& right) {
        return left.width > right.width;
    });

    vector<Rect> rectangles_by_height(rectangles);
    // Order by second element (height) non-cresc
    sort(rectangles_by_height.begin(), rectangles_by_height.end(), [](const auto& left, const auto& right) {
        return left.height > right.height;
    });

    // And then was bin...
    
    float bin_dimension = max(rectangles_by_width[0].width, rectangles_by_height[0].height);
    Bin bin;
    bin.width = bin_dimension;
    bin.height = bin_dimension;
    bins.push_back(bin);

    cout << bin_dimension << '\n';

}