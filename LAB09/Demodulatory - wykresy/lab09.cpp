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
    cout << "\n Tb = " << Tb << endl;

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

    float W = 2;
    float fn = W * pow(Tb, (-1.0)); // fn = W * Tb ^ (-1)

    //float fn1 = 14; 
    //float fn2 = 7; 

    float fn1 = (W + 1) / Tb;
    float fn2 = (W + 2) / Tb;

    float* m = new float[N]; // sygnał
    float* m_ZP = new float[N];
    float* ZA = new float[N];
    float* ZP = new float[N];
    float* ZF = new float[N];

    float* x = new float[N];
    float* x_ZP = new float[N];
    float* p = new float[N];
    float* p_ZP = new float[N];
    float* h_test = new float[10];
    float* c = new float[N];
    float* c_ZP = new float[N];

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


    cout << " Demodulacja ASK - ZA(t)  - sygnał x(t) = " << endl; // sygnał x(t)

    //A* sin(2 * PI * fn * t)

    for (int n = 0; n < N; n++)
    {

        m[n] = A1 * sin(2 * M_PI * fn * t_k[n]);

        x[n] = ZA[n] * m[n];       
    }

    fstream file_x;
    file_x.open("x.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku x.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_x.good() == true)
        {
            file_x << t_k[n] << ";" << x[n] << ";" << endl;
        }
    }
    file_x.close();

    cout << "koniec zapisu do pliku x.txt = " << endl;

    cout << "Całkowanie sygnału x(t) = " << endl;

    
    float Tb_ = Tb;
    float sum = 0;
    float h_prog = 894;

    int k = 0;

    for (int k = 0; k < 10; k++)
    {
        h_test[k] = 0;
    }

    cout << "\ntablica h_test =\n" << endl;

    for (int k = 0; k < 10; k++)
    {
        cout << h_test[k] << ";" << endl;
    }



    for (int n = 0; n < N; n++)
    {
        if (t_k[n] < Tb_)
        {
            sum += x[n];
            p[n] = sum;
        }
        else
        {
            h_test[k] = p[n-1];
            k++;
            sum = 0;            
            Tb_ = Tb_ + Tb;
            p[n] = sum;
        }
    }

    cout << "\ntablica h_test =\n" << endl;

    for (int k = 0; k < 10; k++)
    {
        cout << h_test[k] << ";" << endl;
    }

    float* h_test1 = new float[k];

    for (int i = 0; i < k; i++)
    {
        h_test1[i] = h_test[i];
       
    }

    cout << "\ntablica h_test 1 =\n" << endl;

    for (int i = 0; i < k; i++)
    {
        cout << h_test1[i] << ";" << endl;
    }
   
    cout << endl;

    float min_value = h_test1[0];

    for (i = 0; i < k; i++) {
        if (h_test1[i] < min_value) {
            min_value = h_test1[i];
        }
    }

    cout << "\nMinimum Element in h_test = " << min_value << endl;

    min_value += 5;

    cout << "\nMinimum Element in h_test = " << min_value << endl;
    

    fstream file_p;
    file_p.open("p.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku p.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_p.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_p << t_k[n] << ";" << p[n] << endl;
        }
    }
    file_p.close();


    //całkowanie w odcinkach od 0 do Tb

    for (int n = 0; n < N; n++)
    {
        if (p[n] < min_value)
        {
            c[n] = 0;
        }
        else
        {
            c[n] = 1;
        }

    }

    fstream file_c;
    file_c.open("c.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku c.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_c.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_c << t_k[n] << ";" << c[n] << endl;
        }
    }
    file_c.close();


    // -------------------------------------------------------------------------------


    //cout << endl << "ZA - DFT : " << endl;

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

    fstream file_ZP;
    file_ZP.open("ZP_1.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku ZP_1.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_ZP.good() == true)
        {
            file_ZP << t_k[n] << ";" << ZP[n] << ";" << endl;
        }
    }

    file_ZP.close();

   

    cout << " Demodulacja PSK - ZP(t)  - sygnał x(t) = " << endl; // sygnał x(t)

    //A* sin(2 * PI * fn * t)

    for (int n = 0; n < N; n++)
    {

        m[n] = A1 * sin(2 * M_PI * fn * t_k[n]);
        
        x_ZP[n] = ZP[n] * m[n];
        x_ZP[n] = -x_ZP[n];
       
    }

    fstream file_x_ZP;
    file_x_ZP.open("x_ZP.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku x_ZP.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_x_ZP.good() == true)
        {
            file_x_ZP << t_k[n] << ";" << x_ZP[n] << ";" << endl;
        }
    }
    file_x_ZP.close();

    cout << "koniec zapisu do pliku x_ZP.txt = " << endl;
    cout << "Całkowanie sygnału x_ZP(t) = " << endl;

    Tb_ = Tb;
    sum = 0;


    for (int n = 0; n < N; n++)
    {
        if (t_k[n] < Tb_)
        {
            sum += x_ZP[n];
            p_ZP[n] = sum;
        }
        else
        {          
            sum = 0;
            Tb_ = Tb_ + Tb;
            p_ZP[n] = sum;
        }
    }

    fstream file_p_ZP;
    file_p_ZP.open("p_ZP.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku p_ZP.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_p_ZP.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_p_ZP << t_k[n] << ";" << p_ZP[n] << endl;
        }
    }
    file_p_ZP.close();

    cout << " KONIEC: zapisywanie do pliku p_ZP.txt = " << endl;

    for (int n = 0; n < N; n++)
    {
        if (p_ZP[n] <= 0)
        {
            c_ZP[n] = 0;
        }
        else
        {
            c_ZP[n] = 1;
        }

    }


    fstream file_c_ZP;
    file_c_ZP.open("c_ZP.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku c_ZP.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_c_ZP.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_c_ZP << t_k[n] << ";" << c_ZP[n] << endl;
        }
    }
    file_c_ZP.close();



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


    /*cout << endl << "ZF - DFT : " << endl;

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
    }b

    ZF_1_DFT_file.close();*/


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
