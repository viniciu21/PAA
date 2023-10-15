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

struct Rectangle {
    float width;
    float height;
    int id;
};

struct Bin {
    float width;
    float height;
    vector<pair<Point, Point>> cuts;
};

Bin createSquareBin(float dim) {
    Bin bin;
    bin.width = dim;
    bin.height = dim;
    return bin;
}

int find_bin_fits(Rectangle rectangle){
    return -1; // STUB
}

void insertRectangleOnBinIndex(Rectangle rectangle, int i_bin){
    // STUB
}

int main() {
    int qnt_rectangles;
    cin >> qnt_rectangles;

    vector<Rectangle> rectangles;
    vector<Bin> bins;

    for(int i = 0; i < qnt_rectangles; ++i){
        float width, height;
        cin >> width >> height;
        Rectangle rectangle;
        rectangle.width = width;
        rectangle.height = height;
        rectangle.id = i;
        rectangles.push_back(rectangle);
    }

    vector<Rectangle> rectangles_by_width(rectangles);
    // Order by first element (width) non-cresc
    sort(rectangles_by_width.begin(), rectangles_by_width.end(), [](const auto& left, const auto& right) {
        return left.width > right.width;
    });

    vector<Rectangle> rectangles_by_height(rectangles);
    // Order by second element (height) non-cresc
    sort(rectangles_by_height.begin(), rectangles_by_height.end(), [](const auto& left, const auto& right) {
        return left.height > right.height;
    });

    // And then was bin...
    
    float bin_dimension = max(rectangles_by_width[0].width, rectangles_by_height[0].height);
    Bin bin = createSquareBin(bin_dimension);
    bins.push_back(bin);

    map<int, bool> id_rectangle_was_inserted;
    int i_widths = 0, i_heights = 0;
    bool put_widther = true;
    while (i_widths < qnt_rectangles || i_heights < qnt_rectangles){
        Rectangle rectangle;
        if (put_widther && i_widths < qnt_rectangles) {
            rectangle = rectangles_by_width[i_widths];
            ++i_widths;
        } else if (i_heights < qnt_rectangles) {
            rectangle = rectangles_by_height[i_heights];
            ++i_heights;
        }

        if(id_rectangle_was_inserted[rectangle.id])
            continue;

        id_rectangle_was_inserted[rectangle.id] = true;

        cout << rectangle.width << ' ' << rectangle.height << endl;

        int i_bin = find_bin_fits(rectangle);
        if (i_bin == -1) {
            auto bin = createSquareBin(bin_dimension);
            bins.push_back(bin);
        }
        insertRectangleOnBinIndex(rectangle, bins.size() - 1);
        put_widther != put_widther; // alternate by width/height rects
    }
    
    cout << bins.size() << endl;
}