// lab02_td.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <Math.h>

using namespace std;

int main()
{ 
    /* FUNKCJA NUMER 5     
       x(t) = sin(2 pi * f * t * cos(3 pi * t) + t * phi)

    Wygenerować próbki do bufora,
    wykreślić postac uzyskanego sygnału.
    Wybrać parametry: f, fi, fs >= 8kHz, Tc >= 1s */

    float fs = 8000; // Hz
    float Ts = (1 / fs);
    float Tc = 1;  // 1 s

    int N = ceil(Tc / Ts);

    float* x = new float[N];
    float* t = new float[N];

    float f = 100; // wybór
    float phi = 2; // wybór

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);       
        x[n] = sin(2 * M_PI * f * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi);    
        cout << t[n] << ";" << x[n] << ";" <<endl;
    }

    delete[] x;
    delete[] t;

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
