#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <time.h>

using namespace std;
using namespace chrono;

void buildHeap(int tab[],int rozmiar){
    int j, k, x;
    for (int i = 2; i <= rozmiar; i++) {
      j = i;
      k = j / 2;
      x = tab[i];
      while ((k > 0) && (tab[k] < x)) {
        tab[j] = tab[k];
        j = k;
        k = j / 2;
      }
      tab[j] = x;
    }
}

void deconstructHeap(int tab[], int rozmiar){
    int j,k, m,i;
    for (i = rozmiar; i > 1; i--) {
      swap(tab[1], tab[i]);
      j = 1;
      k = 2;
      while (k < i) {
        if ((k + 1 < i) && (tab[k + 1] > tab[k]))
          m = k + 1;
        else
          m = k;
        if (tab[m] <= tab[j]) break;
        swap(tab[j], tab[m]);
        j = m;
        k = j + j;
      }
    }
}

void openAndPopulateFile(string file_name, int tab[], int rozmiar){
    fstream plik;
    int value;
    plik.open(file_name + ".txt", ios::in | ios::out );
    if( plik.good() == true )
    {
        for(int i = 1; i <= rozmiar; i++){
           value = rand() % 31;
           plik << value << endl;
           cout <<setw(4)<<value;
           tab[i] = value;
        }

        plik.close();
    }
}

void saveResultsToFile(string file_name, int tab[], int rozmiar){
    fstream plik;
    plik.open( file_name + ".txt", ios::in | ios::out );

    if(plik.good() == true){
        cout << "Po sortowaniu:\n\n";
        for(int i = 1; i <= rozmiar; i++){
            plik << tab[i]<<endl;
            cout<< setw(4) << tab[i];
        }
        plik.close();
    }
}

int main() {
    auto start = high_resolution_clock::now();

    const int N = 20; // liczebnoœæ zbioru
    int d[N + 1];
    srand((unsigned) time(NULL));
    // Wype³niamy tablicê liczbami pseudolosowymi i wyœwietlamy je
    openAndPopulateFile("test",d, N);
    cout << endl;
    // Budujemy kopiec
    buildHeap(d,N);


    // Rozbieramy kopiec
    deconstructHeap(d,N);

    // Wyœwietlamy wynik sortowania
    saveResultsToFile("zapis", d, N);

    cout <<endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout <<"Czas w mikrosekundach: " << duration.count() << endl;
    return 0;
}
