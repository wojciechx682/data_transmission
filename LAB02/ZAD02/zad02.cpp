// zad02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <Math.h>


using namespace std;

int main()
{
    /* FUNKCJA NR 10:
       Dla dowolnego zestawu funkcji z tabeli 2 naelży wygenerowac 3 sygnały reprezentujące funkcje 
       y(t), z(t), v(t), gdzie x(t) jest funkcją wybraną w ćwiczeniu 1.
       Wykonać wykresy dla każdego z wygenerowanych sygnałów przy użyciu takich samych parametrach fs, oraz Tc jak w poprzednim ćwiczeniu
    
     x(t) = sin(2 pi * f * t * cos(3 pi * t) + t * fi)
 
     y(t) = cos(2*sqrt(t*(sin(pi*t*t)+2*pi)/3)
     z(t) = y(t) *(sin(0.2*pi*t)*abs(x(t)/5))
     v(t) = sqrt(abs(x(t))) * cos(0.5*y(t))+z(t) */
        

    float fs = 8000; //  wybór
    float Ts = (1 / fs);
    float Tc = 1;   //   wybór

    int N = ceil(Tc / Ts); // = n * Ts   

    float* x = new float[N];
    float* t = new float[N]; 
    float* y = new float[N];
    float* z = new float[N];
    float* v = new float[N];
       
    float f = 100; // wybór
    float phi = 2; // wybór

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);          // = n * Ts - można tego używać zamiennie                
        x[n] = sin(2 * M_PI * f * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi);
        //cout << t[n] << ";" << x[n] << ";" << endl; 
    }

    cout << endl << endl;

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        y[n] = cos(2 * sqrt(t[n] * (sin(M_PI * t[n] * t[n]) + 2 * M_PI) / 3));     
        //cout << t[n] << ";" << y[n] << ";" << endl;
    }

    for (int n = 0; n < N; n++)
    {
       t[n] = (n / fs);    
       //y[n] = cos(2 * sqrt(t[n] * (sin(M_PI * t[n] * t[n]) + 2 * M_PI) / 3));
       z[n] = y[n] * (sin(0.2 * M_PI * t[n]) * abs(x[n]/5));  
       cout << t[n] << ";" << z[n] << ";" << endl;
    }
    cout << endl << endl;

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);        
        v[n] = sqrt(abs(x[n])) * cos(0.5 * y[n]) + z[n];
        cout << t[n] << ";" << v[n] << ";" << endl;
    }
    cout << endl << endl;


    delete[] t;
    delete[] x;    
    delete[] y;
    delete[] z;
    delete[] v;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
