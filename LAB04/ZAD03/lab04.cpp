// lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <Math.h>

using namespace std;

int main()
{
    float fs = 8000; // 1 kHz
    float fs_b = 22050;
    float Ts = (1 / fs);
    float Tc = 1;  // 1 s

    int N = ceil(Tc / Ts);

    float* s1 = new float[N];
    float* s2 = new float[N];
        float* x = new float[N];
        float* y = new float[N];
        float* z = new float[N];
        float* v = new float[N];
        float* u = new float[N];
        float* b = new float[N];
        int Hk = 10;  // Zmieniać ten parametr: 2, 6, 10

    float* t = new float[N];
    float* X = new float[N];
    float* M = new float[N];
    float* M_dec = new float[N];
    float* fk = new float[N];
    float* X_re = new float[N];
    float* X_im = new float[N];

    float A1 = 1;
    float A2 = 0.5;    
        float f1 = 100;
    float f2 = 66;
        float phi1 = 2;
    float phi2 = 0;

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);        
        x[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
        //cout << t[n] << ";" << x[n] << ";" << endl;
    }           

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        y[n] = cos(2 * sqrt(t[n] * (sin(M_PI * t[n] * t[n]) + 2 * M_PI) / 3));        
    }

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);        
        z[n] = y[n] * (sin(0.2 * M_PI * t[n]) * abs(x[n] / 5));        
    }

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        v[n] = sqrt(abs(x[n])) * cos(0.5 * y[n]) + z[n];      
    }

    for (int n = 0; n < N; n++)
    {      
        if ((n / fs) < 0.1)
        {
            t[n] = (n / fs); // = n * Ts                    
            u[n] = sin(6 * M_PI * t[n]) * cos(5 * M_PI * t[n]);            
        }
        else if (((n / fs) >= 0.1) && ((n / fs) < 0.4))
        {
            t[n] = (n / fs);
            u[n] = -1.1 * t[n] * cos(41 * M_PI * t[n] * t[n]);           
        }

        else if (((n / fs) >= 0.4) && ((n / fs) < 0.72))
        {
            t[n] = (n / fs);
            u[n] = t[n] * sin(20 * (t[n] * t[n] * t[n] * t[n]));         
        }
        else if (((n / fs) >= 0.72) && ((n / fs) < 1))
        {
            t[n] = (n / fs);
            u[n] = 3.3 * (t[n] - 0.72) * cos(27 * t[n] + 1.3);            
        }
    }

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        b[n] = 0;

        for (int h = 1; h <= Hk; h++)
        {
            b[n] += ((sin((h * t[n] * M_PI) / (2))) / (2 + cos(h * h * M_PI * t[n])));
        }            
    }

    for (int k = 0; k < N; k++)
    {
        X_re[k] = 0;
        X_im[k] = 0;

        for (int n = 0; n < N; n++)
        {
            X_re[k] += b[n] * cos((-2 * M_PI * k * n) / (N));
            X_im[k] += b[n] * sin((-2 * M_PI * k * n) / (N)); 
        }    
    }
   
    for (int k = 0; k < N; k++)
    {
        M[k] = sqrt((X_re[k] * X_re[k]) + (X_im[k] * X_im[k]));       
        M_dec[k] = 10 * log10(M[k]);
        fk[k] = k * (fs / N);            
    }

   /*for (int k = 0; k < N; k++)
    {      
        cout << fk[k] << ";" << (M[k] * 2) / N << endl; // wykres w skali amplitudowej
    }*/
    
    //cout << "\n--------------\n" << endl;

    for (int k = 0; k < N; k++)
    {
        cout << fk[k] << ";" << M_dec[k] << endl; // wykres w skali decybelowej
    }

    delete[] s1;
    delete[] s2;
    delete[] x;
    delete[] y;
    delete[] z;
    delete[] v;
    delete[] u;
    delete[] b;
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
