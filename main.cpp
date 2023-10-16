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
    vector<pair<Point, Point>> rectangles;
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

void remove_point(vector<Point> & points, const Point & point_to_remove) {
    points.erase(
        remove_if(points.begin(), points.end(), [&](Point const & point) {
            return point.x == point_to_remove.x && point.y == point_to_remove.y;
        }),
        points.end()
    );
}

void insert_first_bin_fits_rectangle(Rectangle rectangle){
    cout << "Inserting rectangle " << rectangle.width << ' ' << rectangle.height << endl;

    for (int i = 0; i < bins.size(); ++i) {
        auto & bin = bins[i];
        cout << "Trying on Bin " << (i + 1) << " (" << bin.width << ", " << bin.height << ")\n";
        cout << "Availables " << bin.available_points.size() << endl;
        for (auto point : bin.available_points) {
            cout << "Available point " << ' ' << point.x << ' ' << point.y << "?\n";
            float required_width = point.x + rectangle.width;
            float required_height = point.y + rectangle.height;

            Point top_right(required_width, required_height);

            bool is_outside_bin = required_width > bin.width || required_height > bin.height; 
            
            if (is_outside_bin)
                continue;

            bool is_there_instersection = false;
            // Checking for intersection of rectangles
            for (auto other_point : bin.available_points) {
                if (other_point.x <= point.x)
                    continue;
                    
                if (other_point.x < top_right.x) {
                    is_there_instersection = true;
                    break;
                }
            }

            if (is_there_instersection) {
                cout << "Has intersection :(\n";
                continue;
            }

            bin.rectangles.emplace_back(point, top_right);
            // placing rectangle new available points
            Point top_left(point.x, required_height);
            Point bottom_right(required_width, point.y);
            bin.available_points.push_back(top_left);
            bin.available_points.push_back(top_right);
            bin.available_points.push_back(bottom_right);

            remove_point(bin.available_points, point);
            cout << "Yep! New available points.\n";
            return;
        }
    }

    cout << "Need to create a new bin...\n";
    // TODO: no bin fits, then create a new one with 3 available points...
    auto bin = createSquareBin(bin_dimension);
    Point initial_point(0, 0);
    Point top_left(0, rectangle.height);
    Point top_right(rectangle.width, rectangle.height);
    Point bottom_right(rectangle.width, 0);
    bin.available_points.push_back(top_left);
    bin.available_points.push_back(top_right);
    bin.available_points.push_back(bottom_right);
    remove_point(bin.available_points, initial_point);
    bins.push_back(bin);
}

void output_to_draw_grapher() {
    int bin_size_factor = 100;
    int bin_draw_size = 100 * bin_dimension;
    for (int i = 0; i < bins.size(); ++i) {
        Point top_left(i * bin_draw_size, 0);
        Point bottom_right((i + 1) * bin_draw_size, bin_draw_size);
        cout << 'r'<< top_left.x << ',' << top_left.y << ',' << bottom_right.x << ',' << bottom_right.y << ',';
        // TODO: rectangles inside...? available points are unsufficient
        auto rectangles = bins[i].rectangles;
        for (int j = 0; j < rectangles.size(); ++j){
            auto rect_top_left = rectangles[j].first;
            auto rect_bottom_right = rectangles[j].second;
            int rounded_top_left_x = rect_top_left.x * bin_size_factor + top_left.x;
            int rounded_top_left_y = rect_top_left.y * bin_size_factor;
            int rounded_bottom_right_x = rect_bottom_right.x * bin_size_factor + top_left.x;
            int rounded_bottom_right_y = rect_bottom_right.y * bin_size_factor;
            cout << "rect"<< rounded_top_left_x << ',' << rounded_top_left_y << ',' << rounded_bottom_right_x << ',' << rounded_bottom_right_y << ',';
        }
    }
    cout<<'\n';
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

        insert_first_bin_fits_rectangle(rectangle);
        put_widther != put_widther; // alternate by width/height rects
    }
    
    int qnt_rectangles_inserted = 0;
    for (auto bin : bins) {
        qnt_rectangles_inserted += bin.rectangles.size();
    }
    cout << "------------------------------\n";
    cout << "Rectangles inserted: " << qnt_rectangles_inserted << endl;
    cout << "Qnt. bins: " << bins.size() << endl;
    cout << "Output grapher:\n";
    output_to_draw_grapher();
}