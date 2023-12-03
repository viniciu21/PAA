#include <iostream>
#include "ffdh.h"

using namespace std;

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
    auto qnt_bins = first_fit_decreasing_height(rectangles).size();
    // printRetangles(rectangles);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    ofstream textfile("numberofbins.txt", ios::app);
    textfile << to_string(qnt_bins) << ",";
    textfile.close();

    // show_result(bins_created);
    //draw_rect(rectangles.at(0).width * 10, rectangles.at(0).height * 10);
    //output_to_draw_grapher(bins_created);
    cout << "Quantidade de bins criadas: " << qnt_bins << endl;
    cout << "Tempo de execução: " << duration.count() << " ms \n";
}