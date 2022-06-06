// lab02_td.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <Math.h>
#include <fstream>

using namespace std;

int main()
{
    // FUNKCJA NR 14:
    // Wygenerować i wykreślić sygnały: bk(t) (k=1,2,3) 
    // dla fs = 22.05 kHz oraz Tc = 1s
    // Wykresy: b1
    //          b2 
    //          b3

    float fs = 22050; 
    float Ts = (1 / fs);
    float Tc = 1;  

    // N - ILOŚĆ PRÓBEK: (22050)
    int N = ceil(Tc / Ts); 
    
    float* t = new float[N]; // zad 4  - duży bufor (22000 próbek)
    float* b = new float[N];
  
    fstream file;
    file.open("b(t).txt", ios::out | ios::app);

    int Hk = 2; // Zmieniać ten parametr

    for (int n = 0; n < N; n++)
    {
        t[n] = (n / fs);
        b[n] = 0;
        
        for (int h = 1; h <= Hk; h++)
        {            
            b[n] += ((sin((h*t[n] * M_PI) / (2))) / (2 + cos(h*h * M_PI * t[n])));
        }        

        if (file.good() == true)
        {           
            file << t[n] << "; " << b[n] << ";" << endl;            
        }
        cout << t[n] << ";" << b[n] << ";" << endl;
    }

    file.close();

    delete[] t;
    delete[] b;
   
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
