#ifndef FFDH_H
#define FFDH_H

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

struct Rectangle
{
    float width;
    float height;
    float staring_point; 
    float ending_point;
    float starting_point_height;
    int id;
};

struct Bin
{
    float width;
    float height;
    float current_width_fited;
    float current_height_fited;
    float current_width_empty;
    int id;
    vect rect_inside;
};

void draw_rect(int width, int height);
Bin createSquareBin(int &bin_count);
vect load_rects(int instance_number);
vect load_rects();
void printRectangle(Rectangle rectangle);
void printRetangles(vect rectangles);
bool compareByHeight(const Rectangle &a, const Rectangle &b);
bool add_rect_into_bin(Rectangle &rect, vector<Bin> &bins);
vector<Bin> fit_into_bins(const vect & rectangles);
void show_result(vector<Bin> bins);
void output_to_draw_grapher(vector<Bin> bins);
int solve(const vect & rectangles);

#endif