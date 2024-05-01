#include "SortingAlgorithm.hpp"
#include "Eigen/Eigen"
#include <iostream>
#include <numeric>
#include <chrono>
#include <random>

using namespace std;
using namespace Eigen;
using namespace SortLibrary;


vector<int> generateVecInt(const size_t dimV)
{
    vector<int> v(dimV);
    int i=1;
    iota(v.begin(),v.end(),i); // creo vettore di n interi consecutivi a partire da 1
    for (unsigned int i=0; i<dimV; i++)
        v[i] = rand() % 1000; // perturbo tutti gli elementi di v
    return v;
}

vector<double> generateVecDouble(const size_t dimV)
{
    vector<double> v(dimV);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-100.0, 100.0);
    for (unsigned int i=0; i<dimV; i++)
    {
        v[i]= dis(gen);
    }
    return v;
}

double ElapsedTime_avg(VectorXd& elap_times)
{
    int N = elap_times.size();
    double time =0;
    for (unsigned int i=0; i<N; i++)
    {
        time += elap_times[i];
    }
    return time/N;
}

Vector2d compareTimes_int(const unsigned int& N, size_t& dimV)
{
    VectorXd elapsed_timesM(N);
    VectorXd elapsed_timesB(N);
    for (unsigned int n=0; n< N; n++)
    {   vector<int> vM = generateVecInt(dimV);
        vector<int> vB = vM;
        // Riordino il vettore usando Mergesort
        chrono::steady_clock::time_point t_beginM = chrono::steady_clock::now() ;
        MergeSort(vM);
        chrono::steady_clock::time_point t_endM = chrono::steady_clock::now() ;
        elapsed_timesM[n] = chrono::duration_cast<chrono::microseconds>(t_endM - t_beginM).count();
        // Riordino il vettore usando Bubblesort
        chrono::steady_clock::time_point t_beginB = chrono::steady_clock::now() ;
        BubbleSort(vB);
        chrono::steady_clock::time_point t_endB = chrono::steady_clock::now() ;
        elapsed_timesB[n] = chrono::duration_cast<chrono::microseconds>(t_endB - t_beginB).count();
    }
    Vector2d compare;
    compare[0] = ElapsedTime_avg(elapsed_timesM);
    compare[1] = ElapsedTime_avg(elapsed_timesB);
    return compare;
}


Vector2d compareTimes_double(const unsigned int& N, size_t& dimV)
{
    VectorXd elapsed_timesM(N);
    VectorXd elapsed_timesB(N);
    for (unsigned int n=0; n< N; n++)
    {   vector<double> vM = generateVecDouble(dimV) ;
        vector<double> vB = vM;
        // Riordino il vettore usando Mergesort
        chrono::steady_clock::time_point t_beginM = chrono::steady_clock::now() ;
        MergeSort(vM);
        chrono::steady_clock::time_point t_endM = chrono::steady_clock::now() ;
        elapsed_timesM[n] = chrono::duration_cast<chrono::microseconds>(t_endM - t_beginM).count();
        // Riordino il vettore usando Bubblesort
        chrono::steady_clock::time_point t_beginB = chrono::steady_clock::now() ;
        BubbleSort(vB);
        chrono::steady_clock::time_point t_endB = chrono::steady_clock::now() ;
        elapsed_timesB[n] = chrono::duration_cast<chrono::microseconds>(t_endB - t_beginB).count();
    }
    Vector2d compare;
    compare[0] = ElapsedTime_avg(elapsed_timesM);
    compare[1] = ElapsedTime_avg(elapsed_timesB);
    return compare;
}

int main()
{
    const unsigned int N = 5; // numero di esperimenti per tipo
    size_t dim1 = 10;
    size_t dim2 = 100;
    size_t dim3 = 1000;
    size_t dim4 = 5000;

    // CASO 1 - vettore di interi con n=10
    Vector2d ElapsedTime1= compareTimes_int(N, dim1);
    cout << "Il tempo impiegato per un vettore di " << dim1 << " interi e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime1[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime1[1] << endl;

    // CASO 2 - vettore di interi con n=100
    Vector2d ElapsedTime2= compareTimes_int(N, dim2);
    cout << "Il tempo impiegato per un vettore di " << dim2 << " interi e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime2[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime2[1] << endl;

    // CASO 3 - vettore di interi con n=1000
    Vector2d ElapsedTime3= compareTimes_int(N, dim3);
    cout << "Il tempo impiegato per un vettore di " << dim3 << " interi e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime3[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime3[1] << endl;

    // CASO 4 - vettore di interi con n=5000
    Vector2d ElapsedTime4= compareTimes_int(N, dim4);
    cout << "Il tempo impiegato per un vettore di " << dim4 << " interi e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime4[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime4[1] << endl;

    // CASO 5 - vettore di double con n=10
    Vector2d ElapsedTime5= compareTimes_double(N, dim1);
    cout << "Il tempo impiegato per un vettore di " << dim1 << " double e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime5[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime5[1] << endl;

    // CASO 6 - vettore di double con n=100
    Vector2d ElapsedTime6= compareTimes_double(N, dim2);
    cout << "Il tempo impiegato per un vettore di " << dim2 << " double e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime6[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime6[1] << endl;

    // CASO 7 - vettore di double con n=1000
    Vector2d ElapsedTime7= compareTimes_double(N, dim3);
    cout << "Il tempo impiegato per un vettore di " << dim3 << " double e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime7[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime7[1] << endl;

    // CASO 8 - vettore di double con n=5000
    Vector2d ElapsedTime8= compareTimes_double(N, dim4);
    cout << "Il tempo impiegato per un vettore di " << dim4 << " double e' di: "<< endl  ;
    cout << "--> Mergesort: " << ElapsedTime8[0] << endl;
    cout << "--> Bubblesort: " << ElapsedTime8[1] << endl;

    return 0;
}

