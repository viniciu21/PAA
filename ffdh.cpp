#include "ffdh.h"

string FOLDER_PATH_BASE = "JSON_";

void draw_rect(int width, int height)
{
    using std::cout;
    cout << "+";
    for (int i = 0; i < width - 2; i++)
    {
        cout << "-";
    }
    cout << "+\n";

    for (int i = 0; i < height - 2; i++)
    {
        cout << "|";
        for (int j = 0; j < width - 2; j++)
        {
            cout << " ";
        }
        cout << "|\n";
    }

    cout << "+";
    for (int i = 0; i < width - 2; i++)
    {
        cout << "-";
    }
    cout << "+\n";
}

Bin createSquareBin(int &bin_count){

    Bin bin;
    bin.width = MAX_RECT_DIMENSION_SIZE;
    bin.height = MAX_RECT_DIMENSION_SIZE;
    bin.current_width_fited = MAX_RECT_DIMENSION_SIZE;
    bin.current_height_fited = MIN_RECT_DIMENSION_SIZE;
    bin.current_width_empty = 0;
    bin.id = ++bin_count;
    return bin;
}

vect load_rects(int instance_number)
{
    int number_rect = 0;
    float width_rect = 0;
    float height_rect = 0;
    int i;

    vect rectangles;

    string file_chosed_path = "./Instances/cleaned/" + FOLDER_PATH_BASE + to_string(instance_number) + ".txt";
    fstream file_chosen;

    file_chosen.open(file_chosed_path);

    file_chosen >> number_rect;

    for (i = 0; i < number_rect; i++)
    {
        file_chosen >> width_rect >> height_rect;

        Rectangle rectangle;
        rectangle.width = width_rect;
        rectangle.height = height_rect;
        rectangle.id = i + 1;
        rectangles.push_back(rectangle);
    }

    return rectangles;
}

vect load_rects()
{
    int number_rect = 0;
    float width_rect = 0;
    float height_rect = 0;
    int i;

    vect rectangles;

    cin >> number_rect;

    for (i = 0; i < number_rect; i++)
    {
        cin >> width_rect >> height_rect;

        Rectangle rectangle;
        rectangle.width = width_rect;
        rectangle.height = height_rect;
        rectangle.id = i + 1;
        rectangles.push_back(rectangle);
    }

    return rectangles;
}

void printRectangle(Rectangle rectangle)
{
    cout << "width: " + to_string(rectangle.width)
         << " height: " + to_string(rectangle.height) 
         << " Starting point " + to_string(rectangle.staring_point) 
         << " Ending point " + to_string(rectangle.ending_point)
         << endl;
}

void printRetangles(vect rectangles)
{
    for (auto rectangle : rectangles)
    {
       printRectangle(rectangle);
    }
}


bool compareByHeight(const Rectangle &a, const Rectangle &b)
{
    return a.height > b.height;
}

bool add_rect_into_bin(Rectangle &rect, vector<Bin> &bins)
{

    for (auto &&bin : bins){

        float offsetW = bin.current_width_fited - rect.width;
        float requiredH = bin.current_height_fited + rect.height;
        float emptySpaceWidthBin = bin.current_width_empty + rect.width;
        
        if (bin.current_height_fited == 0) {
            bin.current_height_fited = rect.height;
        } else if (requiredH <= MAX_RECT_DIMENSION_SIZE) {
            
            // cout << "Retangulo entrou na bin (por caber por cima)" + to_string(bin.id) << " ";
            rect.staring_point = 0;
            rect.ending_point = rect.width;
            rect.starting_point_height = bin.current_height_fited;
            // printRectangle(rect);

            bin.current_height_fited = requiredH;
            bin.rect_inside.push_back(rect);

            return true;
        }

        if (offsetW >= 0){

            // cout << "Retangulo entrou na bin (por caber de lado)" + to_string(bin.id) << " ";
            rect.staring_point = bin.current_width_empty;
            rect.ending_point = bin.current_width_empty + rect.width;
            rect.starting_point_height = 0;
            // printRectangle(rect);

            bin.current_width_fited = offsetW;
            bin.current_width_empty = emptySpaceWidthBin;

            // cout << "atualizando comprimento para " + to_string(bin.current_width_fited) << endl;

            bin.rect_inside.push_back(rect);
            return true;
        }
    }

    return false;
}

vector<Bin> fit_into_bins(const vect & rectangles)
{
    vector<Bin> bins;
    int bin_count = 0;
    bins.push_back(createSquareBin(bin_count));
    vect rectangles_by_height(rectangles);
    // Order by second element (height) non-cresc
    sort(rectangles_by_height.begin(), rectangles_by_height.end(), compareByHeight);

    for (auto rectangle : rectangles_by_height)
    {
        if (!add_rect_into_bin(rectangle, bins))
        {
            // cout << "Não conseguiu colocar na bin" << endl;
            // cout << "Criando uma nova bin " << endl;

            bins.push_back(createSquareBin(bin_count));
            add_rect_into_bin(rectangle, bins);
        }
    }
    return bins;
}

void show_result(vector<Bin> bins) {
    for (auto &&bin : bins){
        cout << "Bin de id " << bin.id << " criada com os seguintes retangulos: " << endl;
        printRetangles(bin.rect_inside);

        cout << "\n \n" << endl;
    }
    
}

void output_to_draw_grapher(vector<Bin> bins) {
    int bin_size_factor = 20;
    int bin_draw_size = bin_size_factor * MAX_RECT_DIMENSION_SIZE;
    int bin_margin = 5;
    for (int i = 0; i < bins.size(); ++i) {
        int points_bin_margin = bin_margin * i;
        int top_left_x = i * bin_draw_size + points_bin_margin;
        int top_left_y = 0;
        int bottom_right_x = (i + 1) * bin_draw_size + points_bin_margin;
        int bottom_right_y = bin_draw_size;
        cout << 'r'<< top_left_x << ',' << top_left_y << ',' << bottom_right_x << ',' << bottom_right_y << ',';
        auto rectangles = bins[i].rect_inside;
        for (int j = 0; j < rectangles.size(); ++j){
            auto rect_top_left_x = rectangles[j].staring_point;
            auto rect_top_left_y = rectangles[j].starting_point_height;
            auto rect_bottom_right_x = rectangles[j].ending_point;
            auto rect_bottom_right_y = rect_top_left_y + rectangles[j].height;
            int rounded_top_left_x = rect_top_left_x * bin_size_factor + top_left_x;
            int rounded_top_left_y = rect_top_left_y * bin_size_factor;
            int rounded_bottom_right_x = rect_bottom_right_x * bin_size_factor + top_left_x;
            int rounded_bottom_right_y = rect_bottom_right_y * bin_size_factor;
            cout << "r"<< rounded_top_left_x << ',' << rounded_top_left_y << ',' << rounded_bottom_right_x << ',' << rounded_bottom_right_y << ',';
        }
    }
    cout<<'\n';
}

int solve(const vect & rectangles){
    vector<Bin> bins_created = fit_into_bins(rectangles);
    return bins_created.size();
}
