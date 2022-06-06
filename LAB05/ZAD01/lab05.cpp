// lab03.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <Math.h>

using namespace std;

int main()
{
    float fs = 250000; // 1 kHz
    float fs_b = 22050;
    float Ts = (1 / fs);
    float Tc = 0.01;  // 1 s

    int N = ceil(Tc / Ts);

    float* m = new float[N];
    float* Za = new float[N];
    float* Zp = new float[N];
    float* Zf = new float[N];

    float Ka = 1; // współczynnik głębokości modulacji
    float Kp = 3 * M_PI; // ZMIENIĆ
   

    float Fm = 1000; // częst. sygnał modulującego  = 100 Hz
    float Fn = 10000; // częst. sygnał modulującego  = 100 Hz

    float Kf = 7500; // >= 0.75 * Fm ( Fn (?) )


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
        //s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
        //s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);

        m[n] = sin(2 * M_PI * Fm * t[n]);
        //m[n] = A1 * sin(2 * M_PI * Fm * t[n] + phi1);

        //Za[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
        Za[n] = (Ka * (m[n] + 1)) * cos(2 * M_PI * Fn * t[n]);
        //x[n] = s1[n] + s2[n];

            cout << t[n] << ";" << m[n]+1 << ";" << endl;
        //cout << t[n] << ";" << Za[n] << ";" << endl;
        //cout << t[n] << ";" << x[n] << ";" << endl;
            //cout << t[n] << ";" << x[n] << ";" << endl;
    }


    // MODULACJA KĄTOWA - FAZA 
    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        //s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
        //s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);

        m[n] = sin(2 * M_PI * Fm * t[n]);
        //m[n] = A1 * sin(2 * M_PI * Fm * t[n] + phi1);

        //Za[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
        Zp[n] = cos(2 * M_PI * Fn * t[n] + Kp * m[n]);
        //x[n] = s1[n] + s2[n];

        //   cout << t[n] << ";" << m[n] << ";" << endl;
        //cout << t[n] << ";" << Zp[n] << ";" << endl;
        //cout << t[n] << ";" << x[n] << ";" << endl;
            //cout << t[n] << ";" << x[n] << ";" << endl;
    }

    // MODULACJA KĄTOWA - CZĘSTOTLIWOŚCI 
    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        //s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
        //s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);

        m[n] = sin(2 * M_PI * Fm * t[n]);
        //m[n] = A1 * sin(2 * M_PI * Fm * t[n] + phi1);

        //Za[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
        Zf[n] = cos((2 * M_PI * Fn * t[n]) + ((Kf/Fm) * m[n]) );
        //x[n] = s1[n] + s2[n];

        //    cout << t[n] << ";" << m[n] << ";" << endl;
        //cout << t[n] << ";" << Zf[n] << ";" << endl;
        //cout << t[n] << ";" << x[n] << ";" << endl;
            //cout << t[n] << ";" << x[n] << ";" << endl;
    }


    delete[] s1;
    delete[] s2;
    delete[] x;
    delete[] y;
    delete[] z;
    delete[] v;
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
