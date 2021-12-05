#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;



void MergeSort(int i_p, int i_k, int tab[], int pomoc[]) {
  int i_s, i1, i2, i;
  i_s = (i_p + i_k + 1) / 2;
  if (i_s - i_p > 1) MergeSort(i_p, i_s - 1, tab, pomoc);
  if (i_k - i_s > 0) MergeSort(i_s, i_k, tab, pomoc);
  i1 = i_p;
  i2 = i_s;
  for (i = i_p; i <= i_k; i++)
    pomoc[i] = ((i1 == i_s) || ((i2 <= i_k) && (tab[i1] > tab[i2]))) ?
    tab[i2++] : tab[i1++];
  for (i = i_p; i <= i_k; i++) tab[i] = pomoc[i];
}
int main()
{
    const int N = 20; // Liczebnoœæ zbioru.
    int d[N],p[N];
    int i;
    srand((unsigned)time(NULL));
    for(i = 0; i < N; i++) d[i] = rand() % 100;
    for(i = 0; i < N; i++) cout << setw(4) << d[i];
    cout << endl;

    MergeSort(0,N-1, d, p);

    cout << "Po sortowaniu:\n\n";
    for(i = 0; i < N; i++) cout << setw(4) << d[i];
    cout << endl;
    return 0;
}
