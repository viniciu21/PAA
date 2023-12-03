#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include <iostream>
#include "local_search.h"
#include "next_fit_decreasing_height.h"
#include <list>

using namespace std;

vector<Bin> tabu_search(const vector<double> & items);

#endif // TABU_SEARCH_H