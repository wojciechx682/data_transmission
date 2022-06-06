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
    char bit_char;
    int i;
    float B = 8;
    float* b = new float[B];

    bit_char = 'B';
    for (i = 0; i < 8; i++) {
        b[i] = bit_char % 2;
        bit_char = bit_char / 2;
    }    
    int a;
    for (i = 1, a = 6; i < 8; i++, a--) {
        cout << b[a];
    }
       
    float Tb = 0.142857;  // float Tb = (1/7); 
    float Tc = B * Tb;
    float fs = 50000; 
    float Ts = (1 / fs);       
    float N = ceil(Tc / Ts);   

    float* S_B = new float[N]; // bufor binarny
    float* t_k = new float[N]; // etykiety czasu
    float* fk = new float[N];  // etykiety częstotliwości

    float TMP_TB = 0; // tymczasowy czas trwania bitu

    float A1 = 0.5;
    float A2 = 1;
    //float fn = 7; 

    float W = 100;
    float fn = W * pow(Tb, (-1.0)); // fn = W * Tb ^ (-1)

    //float fn1 = 14; 
    //float fn2 = 7; 

    float fn1 = (W + 1) / Tb;
    float fn2 = (W + 2) / Tb;

    float* m = new float[N]; // sygnał
    float* ZA = new float[N];
    float* ZP = new float[N];
    float* ZF = new float[N];

    float* X_re = new float[N];
    float* X_im = new float[N];
    float* M = new float[N];
    float* M_dec = new float[N];

    cout << "wykres binarny = " << endl;
    int n = 0;
    for (int k = 0; k < N; k++)
    {
        t_k[k] = k / fs; 
        TMP_TB = TMP_TB + Ts;
        if (TMP_TB >= Tb)
        {
            n++;
            TMP_TB = 0;
        }
        S_B[k] = b[n];
    }
    cout << endl;

    fstream binary_plot;
    binary_plot.open("b.txt", ios::out | ios::app);

    cout << "zapisywanie do pliku b.txt = " << endl;

    for (int n = 0; n < N; n++)
    {
        if (binary_plot.good() == true)
        {
            binary_plot << t_k[n] << ";" << S_B[n] << ";" << endl;
        }
    }

    binary_plot.close();

    for (int n = 0; n < N; n++)
    {
       
        m[n] = sin(2 * M_PI * fn * t_k[n]);
        
        if (S_B[n] == 0)
        {
            ZA[n] = A1 * m[n];
        }
        else
        {
            ZA[n] = A2 * m[n];
        }        
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

    cout << endl << "ZA - DFT : " << endl;

    /*for (int k = 0; k < N; k++)
    {
        X_re[k] = 0;
        X_im[k] = 0;

        for (int n = 0; n < N; n++)
        {
            X_re[k] += ZA[n] * cos((-2 * M_PI * k * n) / (N));
            X_im[k] += ZA[n] * sin((-2 * M_PI * k * n) / (N));
        }
    }

    for (int k = 0; k < N; k++)
    {
        M[k] = sqrt((X_re[k] * X_re[k]) + (X_im[k] * X_im[k]));
        M_dec[k] = 10 * log10(M[k]);
        fk[k] = k * (fs / N);

    }

    fstream ZA_1_DFT_file;
    ZA_1_DFT_file.open("ZA_1_DFT.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku ZA_1_DFT = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (ZA_1_DFT_file.good() == true)
        {
            ZA_1_DFT_file << fk[n] << ";" << M_dec[n] << ";" << endl;
        }
    }

    ZA_1_DFT_file.close();*/


    cout << endl << " ZP_T = " << endl;

    for (int n = 0; n < N; n++)
    {
       
        if (S_B[n] == 0)
        {
            ZP[n] = sin(2 * M_PI * fn * t_k[n]);
        }
        else
        {
            ZP[n] = sin(2 * M_PI * fn * t_k[n] + M_PI);
        }
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

    /*cout << endl << "ZP - DFT : " << endl;

    for (int k = 0; k < N; k++)
    {
        X_re[k] = 0;
        X_im[k] = 0;

        for (int n = 0; n < N; n++)
        {
            X_re[k] += ZP[n] * cos((-2 * M_PI * k * n) / (N));
            X_im[k] += ZP[n] * sin((-2 * M_PI * k * n) / (N));
        }
    }

    for (int k = 0; k < N; k++)
    {
        M[k] = sqrt((X_re[k] * X_re[k]) + (X_im[k] * X_im[k]));
        M_dec[k] = 10 * log10(M[k]);
        fk[k] = k * (fs / N);
    }

    fstream ZP_1_DFT_file;
    ZP_1_DFT_file.open("ZP_1_DFT.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku ZP_1_DFT = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (ZP_1_DFT_file.good() == true)
        {
            ZP_1_DFT_file << fk[n] << ";" << M_dec[n] << ";" << endl;
        }
    }

    ZP_1_DFT_file.close();*/


    cout << endl << " ZF_T = " << endl;

    for (int n = 0; n < N; n++)
    {       
        if (S_B[n] == 0)
        {
            ZF[n] = sin(2 * M_PI * fn1 * t_k[n]);
        }
        else
        {
            ZF[n] = sin(2 * M_PI * fn2 * t_k[n]);
        }       
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


    cout << endl << "ZF - DFT : " << endl;

    for (int k = 0; k < N; k++)
    {
        X_re[k] = 0;
        X_im[k] = 0;

        for (int n = 0; n < N; n++)
        {
            X_re[k] += ZF[n] * cos((-2 * M_PI * k * n) / (N));
            X_im[k] += ZF[n] * sin((-2 * M_PI * k * n) / (N));
        }
    }

    for (int k = 0; k < N; k++)
    {
        M[k] = sqrt((X_re[k] * X_re[k]) + (X_im[k] * X_im[k]));
        M_dec[k] = 10 * log10(M[k]);
        fk[k] = k * (fs / N);
    }

    fstream ZF_1_DFT_file;
    ZF_1_DFT_file.open("ZF_1_DFT.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku ZP_1_DFT = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (ZF_1_DFT_file.good() == true)
        {
            ZF_1_DFT_file << fk[n] << ";" << M_dec[n] << ";" << endl;
        }
    }

    ZF_1_DFT_file.close();


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
