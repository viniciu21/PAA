#include<bits/stdc++.h>
using namespace std;

#define MAX_RECT_DIMENSION_SIZE 1
#define MIN_RECT_DIMENSION_SIZE 0
#define rect pair<float, float>
#define vect vector<rect> 

struct Point {
    float x, y;
    Point(){
        x, y = 0.0;
    }
    Point(float x1, float y1) : x(x1), y(y1) {}
};

struct Rectangle {
    float width;
    float height;
    int id;
};

struct Bin {
    float width;
    float height;
    vector<Point> available_points;
};

vector<Rectangle> rectangles;
vector<Bin> bins;
float bin_dimension;

Bin createSquareBin(float dim) {
    Bin bin;
    bin.width = dim;
    bin.height = dim;
    Point initial_available_point;
    initial_available_point.x = 0;
    initial_available_point.y = 0;
    bin.available_points.push_back(initial_available_point);
    return bin;
}

void insert_first_bin_fits_rectangle(Rectangle rectangle){
    for (int i = 0; i < bins.size(); ++i) {
        auto bin = bins[i];
        for (auto point : bin.available_points) {
            float required_width = point.x + rectangle.width;
            float required_height = point.y + rectangle.height;

            Point extreme_point_rectangle;
            extreme_point_rectangle.x = required_width;
            extreme_point_rectangle.y = required_height;

            bool is_outside_bin = required_width > bin.width || required_height > bin.height; 
            
            if (is_outside_bin)
                continue;

            bool is_there_instersection = false;
            // Checking for intersection of rectangles
            for (auto other_point : bin.available_points) {
                if (other_point.x <= point.x)
                    continue;
                    
                if (other_point.x < extreme_point_rectangle.x) {
                    is_there_instersection = true;
                    break;
                }
            }

            if (is_there_instersection)
                continue;
            
            // TODO: add new available points and remove others
            return;
        }
    }

    // TODO: no bin fits, then create a new one with 3 available points...
}

int main() {
    int qnt_rectangles;
    cin >> qnt_rectangles;

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
    
    bin_dimension = max(rectangles_by_width[0].width, rectangles_by_height[0].height);
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

        insert_first_bin_fits_rectangle(rectangle);
        put_widther != put_widther; // alternate by width/height rects
    }
    
    cout << bins.size() << endl;
}