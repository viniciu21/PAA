#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "next_fit_decreasing_height.h"
#include <cstdlib> 
#include <time.h> 

using namespace std;

vector<Bin> swap_and_generate_bins(int a, int b, vector<Bin> bins);
vector<Bin> local_search(const vector<double> & items);

#endif // LOCAL_SEARCH_H