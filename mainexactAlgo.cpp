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

string FOLDER_PATH_BASE = "JSON_";

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
    int id;
    vect rect_inside;
};

Bin createSquareBin(vect rects, int id){
    Bin bin;
    bin.height = MAX_RECT_DIMENSION_SIZE;
    bin.rect_inside = rects;
    bin.id = id;
    return bin;
}

vect load_rects(int instance_number)
{
    int number_rect = 0;
    float height_rect = 0;
    int i;

    vect rectangles;

    string file_chosed_path = "./Instances/1dcleaned/" + FOLDER_PATH_BASE + to_string(instance_number) + ".txt";
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


void printRectangle(Rectangle rectangle)
{
    cout << " height: " + to_string(rectangle.height) 
         << endl;
}

void printRetangles(vect rectangles)
{
    for (auto rectangle : rectangles)
    {
       printRectangle(rectangle);
    }
}


bool verify_fit(vector<Rectangle> rectangles, float rectangleToFit) {
    float value = 0; 
    
    for(auto rectangle : rectangles) {
        value = value + rectangle.height; 
    }

    if (value >= 1 ) {
        return false; 
    }else {
        value = value + rectangleToFit; 
        if (value > 1) {
            return false;
        }

        return true; 
    }
}

void printPromisses(vector<vector<Rectangle>> promises) {
    for(int i = 0; i < promises.size(); i ++) {
        for (int j = 0; j < promises[i].size(); j++)
        {
            cout << promises[i][j].height << " "; 
        }
            cout << endl; 
    }
    cout << "\n" << "\n" << "\n";
}

vector<Bin> fit_into_bins(vector<Rectangle> rectangles) {
    
    vector<Bin> bins;

    Rectangle rect;
    rect.height = 0; 
    vector<vector<Rectangle>> promises; 
    promises.resize(rectangles.size());
    
    vector<Rectangle> rectanglesfor; 

    rectanglesfor = rectangles;

    for (int i = 0; i < rectanglesfor.size(); ++i) {
        promises[i].resize(1, rect);
    }

    int count = 0; 

    while (rectanglesfor.size() > 0)
    {
        for (int i = 0; i < rectanglesfor.size(); i++) {    
            rectanglesfor[i].ending_point = i;
            promises[i].push_back(rectanglesfor[i]);

            for (int j = 0; j < rectanglesfor.size(); j++) {
                if( i == j ) {
                    continue;
                }

                if(verify_fit(promises[i], rectanglesfor[j].height)) {
                    rectanglesfor[j].ending_point = j;
                    promises[i].push_back(rectanglesfor[j]);
                }    
            }
        }

        //printPromisses(promises);

        int maxValue = 0;
        for (int i = 0; i < promises.size(); i++) { 
            if(promises[i].size() > maxValue)  {
                maxValue = promises[i].size();
            }
        }

        for (int i = 0; i < promises.size(); i++) {
            if(promises[i].size() == maxValue) {
                rectanglesfor.clear();
                for (int k = 0; k < rectangles.size(); k++) {
                    bool indexRetirado = false; 
                    for(int j = 1; j < promises[i].size(); j++) {  
                        //cout << promises[i][j].ending_point << " "; 
                        if(promises[i][j].ending_point == k) {
                            indexRetirado = true; 
                        }
                    }

                    //cout << endl;

                    if (!indexRetirado) {
                        rectanglesfor.push_back(rectangles[k]);
                    } 
                }
                count = count + 1; 
                bins.push_back(createSquareBin(promises[i], count));
                rectangles = rectanglesfor;
                break;
            }
        }
        
        //cout << rectanglesfor.size() << endl; 

        //printRetangles(rectanglesfor);

        promises.clear();
        promises.resize(rectanglesfor.size());
    
        for (int i = 0; i < rectanglesfor.size(); ++i) {
            promises[i].resize(1, rect);
        }

        //printPromisses(promises);
        
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

int main(){
    int instance_number = 1;

    cout << "Digite o numero da instancia que quer testar \n";
    cout << "Lembrando que temos 499 (0 a 500) instancias\n";

    // cin >> instance_number;

    // while (instance_number == 0 || instance_number > 500)
    // {
    //     cout << "Numero de instancia invalido, Digite normalmente\n";
    //     cin >> instance_number;
    // }
    auto startALl = high_resolution_clock::now();

    for (size_t i = 1; i <= 500; i++)
    {
        vect rectangles = load_rects(i);
        auto start = high_resolution_clock::now();
        
        //vect rectangles = load_rects();
        vector<Bin> bins_created = fit_into_bins(rectangles);
        // printRetangles(rectangles);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        // ofstream textfile("numberofbins.txt", ios::app);
        // textfile << to_string(bins_created.size()) << ",";
        // textfile.close();

        //show_result(bins_created);
        // //draw_rect(rectangles.at(0).width * 10, rectangles.at(0).height * 10);
        // //output_to_draw_grapher(bins_created);
        cout << "Quantidade de bins criadas: " << bins_created.size() << endl;
        cout << "Tempo de execução: " << duration.count() << " ms \n";
    }

    auto stopALl = high_resolution_clock::now();
    auto durationAll = duration_cast<microseconds>(stopALl - startALl);
        cout << "Tempo de execução: " << durationAll.count() << " ms \n";

}
