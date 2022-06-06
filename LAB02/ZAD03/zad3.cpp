// lab02_td.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <Math.h>


using namespace std;

int main()
{
    // FUNKCJA NR 1:
    
    // u[t] = sin(6*M_PI*t)*cos(5*M_PI*t)  // dla 0    <= t < 0.1
    // u[t] = -1.1 * t * cos(41*M_PI*t*t)  // dla 0.1  <= t < 0.4
    // u[t] = t * sin(20*(t*t*t*t))        // dla 0.4  <= t < 0.72
    // u[t] = 3.3*(t-0.72)*cos(27*t+1.3)   // dla 0.72 <= t < 1
    //   
    // Czas trwania sygnału wynika z definicji funkcji, natomiast częstotliwość próbkowania fs jest taka sama jak w poprzednim ćwiczeniju
  
    float fs = 8000; 
    float Ts = (1 / fs);
    float Tc = 1;  

    // N - ILOŚĆ PRÓBEK: (8000)
    int N = ceil(Tc / Ts); 

    float* u = new float[N];
    float* t = new float[N]; //zad 4  - duży bufor (22000 próbek)
    float* y = new float[N];
    float* z = new float[N];
    float* v = new float[N];

    float A = 1;
    float f = 100; // wybór TEN PARAMETR DOBRAĆ DO ZADANIA 4 (?)
    float phi = 2; // wybór

    for (int n = 0; n < N; n++)
    {
        // N - Ilość próbek

        if ((n / fs) < 0.1) 
        {
            t[n] = (n / fs); // = n * Ts                    
            u[n] = sin(6 * M_PI * t[n]) * cos(5 * M_PI * t[n]);          
            cout << t[n] << ";" << u[n] << ";" << endl;
        }
        else if (((n / fs) >= 0.1) && ((n / fs) < 0.4))
        {            
            t[n] = (n / fs);            
            u[n] = -1.1 * t[n] * cos(41 * M_PI * t[n] * t[n]);  // dla 0.1  <= t < 0.4          
            cout << t[n] << ";" << u[n] << ";" << endl;
        }

        else if (((n / fs) >= 0.4) && ((n / fs) < 0.72))
        {
            t[n] = (n / fs);            
            u[n] = t[n] * sin(20 * (t[n] * t[n] * t[n] * t[n]));        // dla 0.4  <= t < 0.72
            cout << t[n] << ";" << u[n] << ";" << endl;
        }
        else if (((n / fs) >= 0.72) && ((n / fs) < 1))
        {
            t[n] = (n / fs);           
            u[n] = 3.3 * (t[n] - 0.72) * cos(27 * t[n] + 1.3);        
            cout << t[n] << ";" << u[n] << ";" << endl;
        }
    }    

    delete[] u;
    delete[] t;
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
