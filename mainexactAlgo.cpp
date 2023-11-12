//#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#define MAX_RECT_DIMENSION_SIZE 1
#define MIN_RECT_DIMENSION_SIZE 0

#define vect vector<Rectangle>

//string FOLDER_PATH_BASE = "JSON_";

struct Rectangle
{
    float height;
    float staring_point; 
    float ending_point;
    float starting_point_height;
    int id;
};

struct Bin
{
    float height;
    float current_width_fited;
    float current_width_empty;
    int id;
    vect rect_inside;
};

Bin createSquareBin(int &bin_count){

    Bin bin;
    bin.height = MAX_RECT_DIMENSION_SIZE;
    bin.current_width_fited = MAX_RECT_DIMENSION_SIZE;
    bin.current_width_empty = 0;
    bin.id = ++bin_count;
    return bin;
}

vect load_rects(int instance_number)
{
    int number_rect = 0;
    float height_rect = 0;
    int i;

    vect rectangles;

    string file_chosed_path = "./Instances/cleaned/" + to_string(instance_number) + ".txt";
    fstream file_chosen;

    file_chosen.open(file_chosed_path);

    file_chosen >> number_rect;

    for (i = 0; i < number_rect; i++)
    {
        file_chosen >> height_rect;

        Rectangle rectangle;
        rectangle.height = height_rect;
        rectangle.id = i + 1;
        rectangles.push_back(rectangle);
    }

    return rectangles;
}

vect load_rects()
{
    int number_rect = 0;
    float height_rect = 0;
    int i;

    vect rectangles;

    cin >> number_rect;

    for (i = 0; i < number_rect; i++)
    {
        cin >> height_rect;

        Rectangle rectangle;
        rectangle.height = height_rect;
        rectangle.id = i + 1;
        rectangles.push_back(rectangle);
    }

    return rectangles;
}

vector<Bin> fit_into_bins(vector<Rectangle> rectangles) {
    while (rectangles.size() > 0)
    {
        
    }
    
}

int main(){
    int instance_number = 1;

    cout << "Digite o numero da instancia que quer testar \n";
    cout << "Lembrando que temos 499 (0 a 500) instancias\n";

    cin >> instance_number;

    while (instance_number == 0 || instance_number > 500)
    {
        cout << "Numero de instancia invalido, Digite normalmente\n";
        cin >> instance_number;
    }

    auto start = high_resolution_clock::now();

    vect rectangles = load_rects(instance_number);
    //vect rectangles = load_rects();
    vector<Bin> bins_created = fit_into_bins(rectangles);
    // printRetangles(rectangles);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    ofstream textfile("numberofbins.txt", ios::app);
    textfile << to_string(bins_created.size()) << ",";
    textfile.close();

    // show_result(bins_created);
    //draw_rect(rectangles.at(0).width * 10, rectangles.at(0).height * 10);
    //output_to_draw_grapher(bins_created);
    cout << "Quantidade de bins criadas: " << bins_created.size() << endl;
    cout << "Tempo de execução: " << duration.count() << " ms \n";
}
