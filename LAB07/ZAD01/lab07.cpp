// lab07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <Math.h>
#include <bitset> 
#include <fstream>

using namespace std;

int main()
{
    //std::cout << "Hello World!\n";

    char bit_char;
    int i;
    float B = 8;
    //int b[B];

    float* b = new float[B];

    //cout << "enter a character: ";
    //cin >> bit_char;
    bit_char = 'B';
    for (i = 0; i < 8; i++) {
        b[i] = bit_char % 2;
        bit_char = bit_char / 2;
    }
    /*cout << endl;
    for (i = 8; i > 0; i--) {
        cout << s[i];
    }
    cout << endl;
    cout << s[0];
    cout << s[1];
    cout << s[2];
    cout << s[3];
    cout << s[4];
    cout << s[5];
    cout << s[6];
    cout << s[7];*/


    cout << endl;
    int a;
    for (i = 1, a = 6; i < 8; i++, a--) {
        cout << b[a];
    }

    //float Tb = (1/7);
    float Tb = 0.142857;
        cout << "\nTb = " << Tb;
        cout << endl;

    float Tc = B * Tb;
        cout << "TC = " << Tc;
        cout << endl;

    float fs = 50000; //100 KHz
    float Ts = (1 / fs);
        cout << "TS = " << Ts;
        cout << endl;
    float N = ceil(Tc / Ts); // exception: cant divide by zero
        cout << "N = " << N;
        cout << endl;
    float* S_B = new float[N]; // bufor binarny
    float* t_k = new float[N]; // etykiety czasu
    float TMP_TB = 0; // tymczasowy czas trwania bitu

    float A1 = 0;
    float A2 = 1;
    float fn = 7; //7 Hz   // fn = W * Tb ^ (-1)
    float fn1 = 14; // 14 Hz;
    float fn2 = 7; //  Hz;    

    float* m = new float[N]; // sygnał
    float* ZA = new float[N];
    float* ZP = new float[N];
    float* ZF = new float[N];

   cout << "petla = " << endl;
   int n = 0;
   for (int k = 0; k < N; k++)
    {
        t_k[k] = k / fs; // etykieta czasu
        TMP_TB = TMP_TB + Ts;
        if (TMP_TB >= Tb)
        {
            n++;
            TMP_TB = 0;
        }

        S_B[k] = b[n];
    }
   cout << endl;

   fstream file;
   file.open("b.txt", ios::out | ios::app);


   /*for (int n = 0; n < N; n++)
   {
       cout << t_k[n] << ";" << S_B[n] << ";" << endl;
       
   }*/
   cout << "zapisywanie do pliku = " << endl;

   for (int n = 0; n < N; n++)
   {
        if (file.good() == true)
        {
            file << t_k[n] << ";" << S_B[n] << ";" << endl;
        }
   }

   file.close();

   for (int n = 0; n < N; n++)
   {
       //t[n] = (n / fs);
       //s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
       //s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);

       m[n] = sin(2 * M_PI * fn * t_k[n]);
       //m[n] = A1 * sin(2 * M_PI * Fm * t[n] + phi1);

       //Za[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
       if (S_B[n] == 0)
       {
           ZA[n] = A1 * m[n];
       }
       else
       {
           ZA[n] = A2 * m[n];
       }

       //ZA[n] = A2 * m[n];
       
       //ZA[n] = A1(Ka * (m[n] + 1)) * cos(2 * M_PI * Fn * t[n]);

       //Za_dB[n] = 10 * log10(Za[n]);

       //x[n] = s1[n] + s2[n];

           //cout << t[n] << ";" << m[n]+1 << ";" << endl;
       //cout << t_k[n] << ";" << ZA[n] << ";" << endl;
       //cout << t[n] << ";" << x[n] << ";" << endl;
           //cout << t[n] << ";" << x[n] << ";" << endl;
   }
   fstream file1;
   file1.open("ZA_1.txt", ios::out | ios::app);
   cout << "zapisywanie do pliku = " << endl;
   for (int n = 0; n < N; n++)
   {
       if (file1.good() == true)
       {
           file1 << t_k[n] << ";" << ZA[n] << ";" << endl;
       }
   }

   file1.close();

   cout << endl << " ZP_T = " << endl;

   for (int n = 0; n < N; n++)
   {
       //t[n] = (n / fs);
       //s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
       //s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);

       //m[n] = sin(2 * M_PI * fn * t_k[n]);
       //m[n] = A1 * sin(2 * M_PI * Fm * t[n] + phi1);

       //Za[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
       if (S_B[n] == 0)
       {
           ZP[n] = sin(2 * M_PI * fn * t_k[n]);
       }
       else
       {
           ZP[n] = sin(2 * M_PI * fn * t_k[n] + M_PI);
       }

       //ZA[n] = A2 * m[n];

       //ZA[n] = A1(Ka * (m[n] + 1)) * cos(2 * M_PI * Fn * t[n]);

       //Za_dB[n] = 10 * log10(Za[n]);

       //x[n] = s1[n] + s2[n];

           //cout << t[n] << ";" << m[n]+1 << ";" << endl;
       //cout << t_k[n] << ";" << ZA[n] << ";" << endl;
       //cout << t[n] << ";" << x[n] << ";" << endl;
           //cout << t[n] << ";" << x[n] << ";" << endl;
   }

   fstream file3;
   file3.open("ZP_1.txt", ios::out | ios::app);
   cout << "zapisywanie do pliku = " << endl;
   for (int n = 0; n < N; n++)
   {
       if (file3.good() == true)
       {
           file3 << t_k[n] << ";" << ZP[n] << ";" << endl;
       }
   }

   file3.close();


   cout << endl << " ZF_T = " << endl;

   for (int n = 0; n < N; n++)
   {
       //t[n] = (n / fs);
       //s1[n] = A1 * sin(2 * M_PI * f1 * t[n] + phi1);
       //s2[n] = A2 * sin(2 * M_PI * f2 * t[n] + phi2);

       //m[n] = sin(2 * M_PI * fn * t_k[n]);
       //m[n] = A1 * sin(2 * M_PI * Fm * t[n] + phi1);

       //Za[n] = sin(2 * M_PI * f1 * t[n] * cos(3 * M_PI * t[n]) + t[n] * phi1);
       if (S_B[n] == 0)
       {
           ZF[n] = sin(2 * M_PI * fn1 * t_k[n]);
       }
       else
       {
           ZF[n] = sin(2 * M_PI * fn2 * t_k[n]);
       }

       //ZA[n] = A2 * m[n];

       //ZA[n] = A1(Ka * (m[n] + 1)) * cos(2 * M_PI * Fn * t[n]);

       //Za_dB[n] = 10 * log10(Za[n]);

       //x[n] = s1[n] + s2[n];

           //cout << t[n] << ";" << m[n]+1 << ";" << endl;
       //cout << t_k[n] << ";" << ZA[n] << ";" << endl;
       //cout << t[n] << ";" << x[n] << ";" << endl;
           //cout << t[n] << ";" << x[n] << ";" << endl;
   }


   fstream file4;
   file4.open("ZF_1.txt", ios::out | ios::app);
   cout << "zapisywanie do pliku = " << endl;
   for (int n = 0; n < N; n++)
   {
       if (file4.good() == true)
       {
           file4 << t_k[n] << ";" << ZF[n] << ";" << endl;
       }
   }

   file4.close();

   //zmienić parametry fn1 fn2 (ze wzorów)


   // Wygenerować sygnały zmodulowane Za(T), Zp(T), ZF(T)
   // Sygnał binarny posłuży do zmodulowania sygnałów nośnych ASK, PSK, FSK


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
