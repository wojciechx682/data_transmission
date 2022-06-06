// lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <Math.h>

using namespace std;

// Wykres widma amplitudowego w skali decybelowej

int main()
{
    float fs = 1000; // 1 kHz
    float Ts = (1 / fs);
    float Tc = 1;  // 1 s

    int N = ceil(Tc / Ts);

    float* s1 = new float[N];
    float* s2 = new float[N];
    float* x = new float[N];
    float* t = new float[N];
    float* X = new float[N];
    float* M = new float[N];
    float* M_dec = new float[N];
    float* fk = new float[N];
    float* X_re = new float[N];
    float* X_im = new float[N];

    float A1 = 1;
    float A2 = 0.5;    
    float f1 = 25;
    float f2 = 66;
    float phi1 = 0;
    float phi2 = 0;

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
        s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);
        x[n] = s1[n] + s2[n];

        //cout << t[n] << ";" << s1[n] << ";" << endl;
        //cout << t[n] << ";" << s2[n] << ";" << endl;
        //cout << t[n] << ";" << x[n] << ";" << endl;
    }        
    
    for (int k = 0; k < N; k++)
    {
        X_re[k] = 0;
        X_im[k] = 0;

        for (int n = 0; n < N; n++)
        {
            X_re[k] += x[n] * cos((-2 * M_PI * k * n) / (N));
            X_im[k] += x[n] * sin((-2 * M_PI * k * n) / (N)); 
        }
        //cout << k << ";" << X_re[k] << ";" << X_im[k] <<  endl;       
    }
   
    for (int k = 0; k < N; k++)
    {
        M[k] = sqrt((X_re[k] * X_re[k]) + (X_im[k] * X_im[k]));
        // 10 * log10 M[k]
        M_dec[k] = 10 * log10(M[k]);

        fk[k] = k * (fs / N);            
    }

    for (int k = 0; k < (N/2); k++)
    {      
        cout << fk[k] << ";" << (M[k] * 2) / N << endl;
    }
   
    for (int k = 0; k < (N / 2); k++)
    {
        cout << fk[k] << ";" << M_dec[k] << endl;
    }

    delete[] s1;
    delete[] s2;
    delete[] x;
    delete[] t;
    delete[] X;
    delete[] M;
    delete[] X_re;
    delete[] X_im;
    delete[] fk;

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
