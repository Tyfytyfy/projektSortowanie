#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;
// funckja służąca do otworzenia pliku i zapełnienia go losowyi liczbami
// arguemnty funkcji następująco to nazwa pliku, tablica do której mamy przepisać dane z pliku, żeby wykonywać kolejne operacje oraz rozmiar czyli ile liczb losujemy do pliku
void openAndPopulateFile(string file_name, int tab[], int rozmiar){
    fstream plik;
    int value; //zmienna pomocnicza
    plik.open(file_name + ".txt", ios::in | ios::out ); //otworzenie pliku
    if( plik.good() == true )
    {
        for(int i = 0; i < rozmiar; i++){
           value = rand() % 31; // losowanie liczb
           plik << value << endl; // wpisywanie liczb do pliku
           //cout <<value<< endl;
           tab[i] = value; // przypisywanie danych z pliku do tablicy
        }

        plik.close(); // zamknięcie pliku
    }
}
// funkcja służąca do wypisania posortowanych danych oraz zapisanie ich do pliku
// argumenty to nazwa pliku, tablica która będzie przechowywać posortowane dane, rozmiar tablicy
void saveResultsToFile(string file_name, int tab[], int rozmiar){
    fstream plik;
    plik.open( file_name + ".txt", ios::in | ios::out );//otworzenie pliku
    if(plik.good() == true){
        cout << "Po sortowaniu:\n\n";
        for(int i = 0; i < rozmiar; i++){
            plik << tab[i]<<endl; // wpisujemy posortowane dane do pliku
            cout<< setw(4) << tab[i];// wypisujemy posortowane dane
        }
        plik.close();// zamknięcie pliku
    }
}
// funkcja merge sort służy do posortowania przez scalania danego zbioru.
//i_p to index pierszego elementu w młodszym podzbiorze, i_k to index ostatniego elementu w starszym podzbiorze, tab[] to posortowany zbiór, pomoc[] to zbiór pomocniczy
void MergeSort(int i_p, int i_k, int tab[], int pomoc[])
{
  int i_s, i1, i2, i;
  //i_s to index pierwszego elemnetu w starszym podzbiorze, i1 to index elementów w młodszej połówce zbioru
  // i2 to index elementów w starszej połówce zbioru, i to index elementów w zbiorze pomocniczym
  i_s = (i_p + i_k + 1) / 2; // wyznaczamy index który jest wykorzysytwany do podziału zbioru na dwie częsci
  if (i_s - i_p > 1) MergeSort(i_p, i_s - 1, tab, pomoc);//sprawdzamy czy jest więcej niż jeden element, jeżeli tak to sortujemy go tym samym algorytmem
  if (i_k - i_s > 0) MergeSort(i_s, i_k, tab, pomoc); // sortujemy drugą połówkę
  //
  i1 = i_p;
  i2 = i_s;
  // sprawdzamy czy i1 i i2 wskazują elemnety podzbiorów, jeżeli któryś z nich wyszedł poza dopuszczalny zakres to zbiór jest wyczerpany
  // w takim przypadku do tablicy pomoc przypisujemy elementy drugiego zbioru
  // jeżeli żaden z podzbiorów nie jest wyczeprany to porównujemy kolejne elementy podzbiorów według index'ów i1 i i2
  // do tablicy pomoc zapisujemy zawsze mniejszy element
  // pętla jest kontynuowana aż do zapełnienia tablicy pomoc[]
  for (i = i_p; i <= i_k; i++)
    pomoc[i] = ((i1 == i_s) || ((i2 <= i_k) && (tab[i1] > tab[i2]))) ?
    tab[i2++] : tab[i1++];
  for (i = i_p; i <= i_k; i++) tab[i] = pomoc[i];
  //przypisujemy wartości tablicy pomoc do tablicy tab
}
int main()
{
    auto start = high_resolution_clock::now();

    const int N = 20; // Liczebnoœæ zbioru.
    int d[N],p[N];
    srand((unsigned)time(NULL));

    openAndPopulateFile("test", d, N);

    for(int i = 0; i < N; i++) cout << setw(4) << d[i];
    cout << endl;

    MergeSort(0,N-1, d, p);

    saveResultsToFile("zapis", d, N);
    cout<<endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout <<"Czas w mikrosekundach: " << duration.count() << endl;
    return 0;
}
