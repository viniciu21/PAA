#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <iostream>
#include "ffdh.h"
#include <cstdlib> 
#include <time.h> 

using namespace std;

vector<Bin> swap_and_generate_bins(int a, int b, vector<Bin> bins);
vect rectangles_from_items(const vector<double> & items);
vector<Bin> sequencing_generate_bins(const vector<double> & items);
vector<Bin> local_search(const vector<double> & items);

#endif // LOCAL_SEARCH_H