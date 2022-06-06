// lab13.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <bitset>
#include <fstream>
#define _USE_MATH_DEFINES
#include <Math.h>
#include <sstream>
#include <string>


using namespace std;

string TextToBinaryString(string words) {
    string binaryString = "";
    for (char& _char : words) {
        binaryString += bitset<8>(_char).to_string();
    }
    return binaryString;
}

int main()
{
    /*
    KODER NADMIAROWY (zastosować kod hammina H(7,4) lub H(15,11)
    MODULATOR
    KANAŁ TRANSMISYJNY
    DEMODULATOR
    DEKODER

     wiadomość teskstowa na tyle duża, aby strumień bitowy miał conajmniej 42 bity
     (zastosowałem 48 bitów = 6 znaków)

     -> Trik odnośnie długości wiadomości tekstowej ...

     następnie:

     mamy KODER HAMMINGA - koduje wiadomości w sposób blokowy (mamy blok 4 bitów, kodujemy na 7 bitach)

     cały strumień bitowy odpowiednio pociąć na paczki danych, które będziemy kodować koderem H(7,4)

     H(7,4) -> wychodzi WEKTOR C (przechowuje on STRUMIEN BINARNY DO MODULATORA)

     ten strumień binarny (C) -> przekazujemy do modulatora (ASK / PSK / FSK)

     z modulatora -> otrzymujemy próbki sygnału zmodulowanego

     */

     //cout << "Hello World!\n";

     // Symulacja systemu transmisyjnego

     // 'abcdef' = 01100001 01100010 01100011 01100100 01100101 01100110
     // 'a' = 01100001 


     //string str = "abcdef";
    string str = "AbcDEE";
    cout << " string text: '" << str << "'\n";

    string s2 = TextToBinaryString(str);

    cout << " str -> bin = " << s2 << "\n";

    //const int SIZE = 48;
    const int SIZE = 48;
    const int SIZE_4 = 4;
    const int SIZE_2 = 2;
    //const int SIZE_arr = 14;
    const int SIZE_arr = 84;
    //const int SIZE2 = 11;
    //string s1 = "0110100001101000";
    int b[SIZE];
    int b1[SIZE];
    int paczka1[SIZE_4];
    int C_[SIZE_arr];
    //int paczka2[SIZE_4];
    //int paczki[SIZE_2];
    //int b2[SIZE2];
    cout << "size = " << SIZE;


    for (int i = 0; i < SIZE; i++) {
        b[i] = s2[i] - '0';
    }

    /*for (int i = 0; i < SIZE; i++) {
        b[i] = s2[i] - '0';
    }*/

    /*b1[0] = b[7];
    b1[1] = b[6];
    b1[2] = b[5];
    b1[3] = b[4];
    b1[4] = b[3];
    b1[5] = b[2];
    b1[6] = b[1];*/
    cout << "\n\n b[] array - (48 elements) = " << endl;
    for (int i = 0; i < 48; i++) {

        cout << b[i] << " ";
        /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
        {
            cout << endl;
        }*/
    }

    int B_temp = 4;
    int* b_temp = new int[B_temp];


    int j = 0;
    int jj = 0;
    int y1 = 0;
    int y2 = 7;
    for (int q = 0; q < 12; q++)
    {
        for (int i = 0; i < 4; i++) {

            paczka1[i] = b[j];
            //paczka2[i] = b[j+4];
            j++;
            //cout << b[i] << " ";
            /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
            {
                cout << endl;
            }*/
        }
        cout << "\n\npaczka" << q + 1 << "  = " << endl;
        for (int i = 0; i < 4; i++) {

            //b_4_[i] = b[i];

            cout << paczka1[i] << " ";
            /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
            {
                cout << endl;
            }*/
        }


        for (int i = 0; i < 4; i++)
        {
            b_temp[i] = paczka1[i];
            //cout << b_temp[i] << " ";
        }

        cout << endl << endl;

        /*cout << "\n\n paczka" << q+1 << " = " << endl;
        cout << " [ ";
        for (int i = 0; i < 4; i++)
        {
            cout << b_temp[i] << " ";
        }
        cout << "] ";
        cout << endl << endl;*/


        int x1 = b_temp[0] ^ b_temp[1] ^ b_temp[3];
        int x2 = b_temp[0] ^ b_temp[2] ^ b_temp[3];
        int x4 = b_temp[1] ^ b_temp[2] ^ b_temp[3];

        int X[] = { x1, x2, x4 };

        for (int i = 0; i < 3; i++)
        {
            cout << " X[" << pow(2, i) << "] = " << X[i] << endl;;
        }

        int h = 7;
        int* H = new int[h];
        int n;
        int m;
        j = 0;
        int k = 0;

        for (int i = 0; i < 8; i++)
        {
            n = i;
            m = n;

            if (n > 0)
            {
                while (n % 2 == 0)
                {
                    n /= 2;
                }
                if (n == 1)
                {
                    H[m - 1] = X[j];
                    j++;
                }
            }

            if (n == 0 || n != 1)
            {
                if (n != 0)
                {
                    H[m - 1] = b_temp[k];
                    k++;
                }
            }
        }

        cout << "\n C = " << endl;
        cout << " [ ";
        for (int i = 0; i < 7; i++)
        {
            cout << H[i] << " ";
        }
        cout << "] ";
        cout << endl << endl;

        // ...NALEŻY ZDEKODOWAĆ POWYŻSZY WEKTOR C (KOD HAMMINGA H(7,4))
        // WEKTOR C -> MODULATOR
        //int x1_ = b_temp[0] ^ b_temp[1] ^ b_temp[3];
        //int x2_ = b_temp[0] ^ b_temp[2] ^ b_temp[3];
        //int x4_ = b_temp[1] ^ b_temp[2] ^ b_temp[3];

        //int x1__ = x1 ^ x1_;
        //int x2__ = x2 ^ x2_;
        //int x4__ = x4 ^ x4_;

        //int P = 7;
        //int* p = new int[P];

        //for (int i = 0; i < 8; i++)
        //{
        //    p[i] = pow(2, i);
        //}

        //int S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

        //cout << " S = " << S << "\n";

        //int B_out = 4;
        //int* b_out = new int[B_out];

        //if (S == 0)
        //{
        //    //cout << "\n Kod wejsciowy nie zawiera bledow\n";

        //    b_out[0] = H[2];
        //    b_out[1] = H[4];
        //    b_out[2] = H[5];
        //    b_out[3] = H[6];

        //    cout << "\n b_out = " << endl;
        //    cout << " [ ";

        //    for (int i = 0; i < 4; i++)
        //    {
        //        cout << b_out[i] << " ";
        //    }
        //    cout << "] ";
        //    cout << endl << endl;
        //}
        //else
        //{
        //    cout << "\n Blad w kodzie na pozycji S = [" << S << "] \n";

        //    cout << "\n Korekcja bledu : \n";

        //    H[S - 1] = not(H[S - 1]);

        //    cout << "\ H = " << endl;
        //    cout << " [ ";
        //    for (int i = 0; i < 7; i++)
        //    {
        //        cout << H[i] << " ";
        //    }
        //    cout << "] ";
        //    cout << endl << endl;

        //    b_out[0] = H[2];
        //    b_out[1] = H[4];
        //    b_out[2] = H[5];
        //    b_out[3] = H[6];

        //    cout << "\n b_out = " << endl;
        //    cout << " [ ";

        //    for (int i = 0; i < 4; i++)
        //    {
        //        cout << b_out[i] << " ";
        //    }
        //    cout << "] ";
        //    cout << endl << endl;
        //}


        cout << "\n y1 = " << y1 << "\n";
        cout << "\n y2 = " << y2 << "\n";
        k = 0;
        for (int l = y1; l < y2; l++)
        {
            cout << "->" << l << ", " << y1 << ", " << y2 << "\n";
            C_[l] = H[k];
            k++;
            //k++;
        }

        //j = 4;

        //int mm = 2;

        j = jj + 4;
        jj = j;
        cout << "\n j = " << j << endl;
        y1 = y1 + 7;
        y2 = y2 + 7;
        //k = 4;

    }

    //cout << "\n\n paczka2 - (4 elements) = " << endl;
    //for (int i = 0; i < 4; i++) {

    //    //b_4_[i] = b[i];

    //    cout << paczka2[i] << " ";
    //    /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
    //    {
    //        cout << endl;
    //    }*/
    //}

    //int paczki[2] = { paczka2, 2 };



    //cout << "\n\n b1[] array - (7 elements) = " << endl ;
    //for (int i = 6; i >= 0; i--) {

    //    cout << b1[i] << " ";
    //    /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
    //    {
    //        cout << endl;
    //    }*/
    //}


    /*cout << "\n b[0] = " << b[0] << endl;
    cout << "\n b[1] = " << b[1] << endl;
    cout << "\n b[2] = " << b[2] << endl;
    cout << "\n b[3] = " << b[3] << endl;
    cout << "\n b[4] = " << b[4] << endl;
    cout << "\n b[5] = " << b[5] << endl;
    cout << "\n b[6] = " << b[6] << endl;
    cout << "\n b[7] = " << b[7] << endl;*/

    /* for (int i = 0; i < 11; i++)
     {
         b2[i] = b1[i];
     }

     cout << "\n  b[] array - (11 elements) = " << endl << " ";
     for (int i = 0; i < 11; i++) {
         cout << b2[i] << " ";
     }*/

     // KODER HAMMINGA H(7,4) : 

     /*int v = 6;
     for (int i = 0; i < 4; i++)
     {
         b_temp[i] = b1[v];
         v--;
     }*/

     /*cout << "\n\n b_temp = " << endl;
     cout << " [ ";
     for (int i = 0; i < 4; i++)
     {
         cout << b_temp[i] << " ";
     }
     cout << "] ";
     cout << endl << endl;*/

     //cout << "\n\n b_temp = " << endl;
    
    cout << "\n\nb[] = " << endl;
    for (int i = 0; i < 48; i++) {

        cout << b[i] << " ";
        /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
        {
            cout << endl;
        }*/
    }

    cout << "\n\nC = " << endl;
    for (int i = 0; i < 84; i++) {

        //b_4_[i] = b[i];

        cout << C_[i] << " "; // WEKTOR NA WYJŚCIU KODERA
        /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
        {
            cout << endl;
        }*/
    }

    // MODULATOR

    // przekazać wektor C -> do MODULATORA 
    float B = 84;
    float fs = 50000;
    float Tb = 0.0208;  // float Tb = (1/7); 
    float Tc = B * Tb;
    float Ts = (1 / fs);
    float N = ceil(Tc / Ts);

    float* t_k = new float[N]; // etykiety czasu
    float* S_B = new float[N]; // bufor binarny

    float TMP_TB = 0; // tymczasowy czas trwania bitu

    cout << "\n\nwykres binarny = " << endl;
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
        S_B[k] = C_[n];
    }
    cout << endl;


    fstream binary_plot;
    binary_plot.open("b.txt", ios::out | ios::app);

    cout << "\n\nzapisywanie do pliku b.txt = " << endl;

    for (int n = 0; n < N; n++)
    {
        if (binary_plot.good() == true)
        {
            binary_plot << t_k[n] << ";" << S_B[n] << ";" << endl;
        }
    }

    binary_plot.close();

    cout << endl << " ZF_T = " << endl;

    float* ZF = new float[N];

    float W = 100;

    cout << "\n\nTb = " << Tb << endl; // Tb = 0.0208

    // 

    float fn = W * pow(Tb, (-1.0)); // fn = 1201,92307

    float fn1 = (W + 1) / Tb; // fn1 = 1250
    float fn2 = (W + 2) / Tb; // fn2 = 576,923

    //float fn1 = 15;
    //float fn2 = 75;

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
    cout << "\n\nzapisywanie do pliku ZF_1.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file4.good() == true)
        {
            file4 << t_k[n] << ";" << ZF[n] << ";" << endl;
        }
    }

    file4.close();

    // DEMODULATOR

    cout << "\n\nDemodulacja FSK - ZF(t)  - sygnal x1(t) = " << endl;

    float* m = new float[N]; // sygnał
    float A1 = 0.5;

    float* x1_ZF = new float[N];
    float* x2_ZF = new float[N];

    for (int n = 0; n < N; n++)
    {
        m[n] = A1 * sin(2 * M_PI * fn1 * t_k[n]);

        x1_ZF[n] = ZF[n] * m[n];
        //x_ZP[n] = -x_ZP[n];
    }

    fstream file_x_ZF1;
    file_x_ZF1.open("x1_ZF.txt", ios::out | ios::app);
    cout << "\n\nzapisywanie do pliku x1_ZF.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_x_ZF1.good() == true)
        {
            file_x_ZF1 << t_k[n] << ";" << x1_ZF[n] << ";" << endl;
        }
    }
    file_x_ZF1.close();

    cout << "\n\nkoniec zapisu do pliku x_ZF.txt = " << endl;


    cout << "\n\nDemodulacja FSK - ZF(t)  - sygnal x2(t) = " << endl;

    for (int n = 0; n < N; n++)
    {
        m[n] = A1 * sin(2 * M_PI * fn2 * t_k[n]);

        x2_ZF[n] = ZF[n] * m[n];
        //x_ZP[n] = -x_ZP[n];
    }

    fstream file_x_ZF2;
    file_x_ZF2.open("x2_ZF.txt", ios::out | ios::app);
    cout << "zapisywanie do pliku x2_ZF.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_x_ZF2.good() == true)
        {
            file_x_ZF2 << t_k[n] << ";" << x2_ZF[n] << ";" << endl;
        }
    }
    file_x_ZF2.close();

    cout << "\n\nkoniec zapisu do pliku x2_ZF.txt = " << endl;

   
    cout << "\n\nCałkowanie sygnału x1_ZF(t) = " << endl;


    float Tb_ = Tb;
    float sum = 0;

    float* p1_ZF = new float[N];
    float* p2_ZF = new float[N];
    float* p_ZF = new float[N];
    

    for (int n = 0; n < N; n++)
    {
        if (t_k[n] < Tb_)
        {
            sum += x1_ZF[n];
            p1_ZF[n] = sum;
        }
        else
        {
            sum = 0;
            Tb_ = Tb_ + Tb;
            p1_ZF[n] = sum;
        }
    }

    for (int n = 0; n < N; n++)
    {
        p1_ZF[n] = -p1_ZF[n];
    }

    fstream file_p_ZF_1;
    file_p_ZF_1.open("p1_ZF.txt", ios::out | ios::app);
    cout << "\n\nzapisywanie do pliku p1_ZF.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_p_ZF_1.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_p_ZF_1 << t_k[n] << ";" << p1_ZF[n] << endl;
        }
    }
    file_p_ZF_1.close();

    cout << "\n\nKONIEC: zapisywanie do pliku p1_ZF.txt = " << endl;


    cout << "\n\nCałkowanie sygnału x2_ZF(t) = " << endl;

    Tb_ = Tb;
    sum = 0;

    for (int n = 0; n < N; n++)
    {
        if (t_k[n] < Tb_)
        {
            sum += x2_ZF[n];
            p2_ZF[n] = sum;
        }
        else
        {
            sum = 0;
            Tb_ = Tb_ + Tb;
            p2_ZF[n] = sum;
        }
    }

    fstream file_p_ZF_2;
    file_p_ZF_2.open("p2_ZF.txt", ios::out | ios::app);
    cout << "\n\nzapisywanie do pliku p2_ZF.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_p_ZF_2.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_p_ZF_2 << t_k[n] << ";" << p2_ZF[n] << endl;
        }
    }
    file_p_ZF_2.close();

    cout << "\n\nKONIEC: zapisywanie do pliku p2_ZF.txt = " << endl;

    cout << "\n\nDodawanie sygnałów p1 i p2 = " << endl;

    for (int n = 0; n < N; n++)
    {
        p_ZF[n] = p1_ZF[n] + p2_ZF[n];

    }

    fstream file_p_ZF_;
    file_p_ZF_.open("p_ZF.txt", ios::out | ios::app);
    cout << "\n\nzapisywanie do pliku p_ZF.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_p_ZF_.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_p_ZF_ << t_k[n] << ";" << p_ZF[n] << endl;
        }
    }
    file_p_ZF_.close();

    cout << "\n\nKONIEC: zapisywanie do pliku p_ZF.txt = " << endl;


    cout << "\n\nsygnał wyjściowy c(t) (ZF) = " << endl;

    float* c_ZF = new float[N];

    for (int n = 0; n < N; n++)
    {
        if (p_ZF[n] < 25)
        {
            c_ZF[n] = 0;
        }
        else
        {
            c_ZF[n] = 1;
        }
    }

    fstream file_c_ZF;
    file_c_ZF.open("c_ZF.txt", ios::out | ios::app);
    cout << "\n\nzapisywanie do pliku c_ZF.txt = " << endl;
    for (int n = 0; n < N; n++)
    {
        if (file_c_ZF.good() == true)
        {
            //file_p << t_k[n] << ";" << p[n] << ";" << endl;
            file_c_ZF << t_k[n] << ";" << c_ZF[n] << endl;
        }
    }
    file_c_ZF.close();

    // C(t) -> BIN

    float* c = new float[N];


    int binary_one = 0;
    int binary_zero = 0;

    //int TRESH = Tb/2;
    int ilosc_probek = N / B;
    n = 0;
    Tb_ = Tb;
    

    int* b_out = new int[84];

    for (int i = 0; i < B; i++)
    {
        while (t_k[n] < Tb_)
        {
            if (c_ZF[n] == 0)
            {
                binary_zero++;

            }
            if (c_ZF[n] == 1)
            {
                binary_one++;
            }
            n++;
        }

        if (binary_zero > (0.5 * ilosc_probek))
        {
            b_out[i] = 0;
        }
        if (binary_zero < (0.5 * ilosc_probek))
        {
            b_out[i] = 1;
        }

        binary_zero = 0;
        binary_one = 0;
        Tb_ = Tb_ + Tb;
    }

    for (int i = 0; i < 84; i++)
    {
        cout << "\n C_[" << i << "] = " << C_[i] << "; ";
        cout << " b_out[" << i << "] = " << b_out[i] << endl;
    }

    for (int i = 0; i < 12; i++)
    {

    }

    int* b_decode = new int[7];

    for (int i = 0; i < 7; i++)
    {
        b_decode[i] = b_out[i];
    }

    int* C_decode = new int[7];

    
    for (int i = 0; i < 7; i++)
    {
        C_decode[i] = C_[i];
    }
    
    cout << "\n\n c decode = " << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << C_decode[i] << " ";
    }
    cout << endl;

    b_temp[0] = C_decode[2];
    b_temp[1] = C_decode[4];
    b_temp[2] = C_decode[5];
    b_temp[3] = C_decode[6];

    cout << "\n\n b_temp = " << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << b_temp[i] << " ";
    }
    cout << endl;

    int x1 = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    int x2 = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    int x4 = b_temp[1] ^ b_temp[2] ^ b_temp[3];

    int x1_ = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    int x2_ = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    int x4_ = b_temp[1] ^ b_temp[2] ^ b_temp[3];

    int x1__ = x1 ^ x1_;
    int x2__ = x2 ^ x2_;
    int x4__ = x4 ^ x4_;

    int P = 7;
    int* p = new int[P];

    for (int i = 0; i < 8; i++)
    {
        p[i] = pow(2, i);
    }

    int S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

    cout << " S = " << S << "\n";

    if (S == 0)
    {
        cout << "\n Kod wejsciowy nie zawiera bledow\n";

        b_out[0] = C_decode[2];
        b_out[1] = C_decode[4];
        b_out[2] = C_decode[5];
        b_out[3] = C_decode[6];

        cout << "\n b_out = " << endl;
        cout << " [ ";

        for (int i = 0; i < 4; i++)
        {
            cout << b_out[i] << " ";
        }
        cout << "] ";
        cout << endl << endl;
    }


    cout << "\n\n paczki z C_ = " << endl;

    j = 0;
    //int k = 7;

    int* b_out_ = new int[48];

    int k1 = 0;
    int k2 = 4;

    for (int q = 0; q < 12; q++)
    {
        for (int i = 0; i < 7; i++)
        {
            C_decode[i] = C_[j];
            j++;
        }

        cout << "C_decode[" << q << "] = ";

        for (int i = 0; i < 7; i++)
        {
            cout << C_decode[i] << " ";
        }
        cout << endl;


        int x1 = C_decode[2] ^ C_decode[4] ^ C_decode[6];
        int x2 = C_decode[2] ^ C_decode[5] ^ C_decode[6];
        int x4 = C_decode[4] ^ C_decode[5] ^ C_decode[6];


        int x1_ = C_decode[2] ^ C_decode[4] ^ C_decode[6];
        int x2_ = C_decode[2] ^ C_decode[5] ^ C_decode[6];
        int x4_ = C_decode[4] ^ C_decode[5] ^ C_decode[6];

        int x1__ = x1 ^ x1_;
        int x2__ = x2 ^ x2_;
        int x4__ = x4 ^ x4_;

        int P = 7;
        int* p = new int[P];

        for (int i = 0; i < 8; i++)
        {
            p[i] = pow(2, i);
        }

        int S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

        cout << " S = " << S << "\n";

        int B_out = 4;
        int* b_out = new int[B_out];

        if (S == 0)
        {
            //cout << "\n Kod wejsciowy nie zawiera bledow\n";

            b_out[0] = C_decode[2];
            b_out[1] = C_decode[4];
            b_out[2] = C_decode[5];
            b_out[3] = C_decode[6];

            cout << "\n b_out = " << endl;
            cout << " [ ";

            for (int i = 0; i < 4; i++)
            {
                cout << b_out[i] << " ";
            }
            cout << "] ";
            cout << endl << endl;
        }
        else
        {
            cout << "\n Blad w kodzie na pozycji S = [" << S << "] \n";

            cout << "\n Korekcja bledu : \n";

            C_decode[S - 1] = not(C_decode[S - 1]);

            cout << "\ H = " << endl;
            cout << " [ ";
            for (int i = 0; i < 7; i++)
            {
                cout << C_decode[i] << " ";
            }
            cout << "] ";
            cout << endl << endl;

            b_out[0] = C_decode[2];
            b_out[1] = C_decode[4];
            b_out[2] = C_decode[5];
            b_out[3] = C_decode[6];

            cout << "\n b_out = " << endl;
            cout << " [ ";

            for (int i = 0; i < 4; i++)
            {
                cout << b_out[i] << " ";
            }
            cout << "] ";
            cout << endl << endl;
        }


        
        for (int i = 0; i < 4; i++)
        {
            b_out_[k1] = b_out[i];
            k1++;
        }


        //j = 0;
       // j = j + 7;

        
        //k1 = k1 + 4;
        //k2 = k2 + 4;
        //k = k + 7;

    }

    cout << "\n\n b_out_ = " << endl;
    for (int i = 0; i < 48; i++)
    {
        cout << b_out_[i] << " ";
        
    }

    cout << "\n\nb_cout[0] = " << b_out_[0] << endl;

    string s = "";


    for (int i = 0; i < 48; i++)
    {
        s += to_string(b_out_[i]);
    }

    cout << "\n\nstring s = " << s << endl;

    stringstream sstream(s);
    string s1;

    while (sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        s1 += c;
    }

    cout << "\n\nstr = " << str << endl;
    cout << "\n\ns1 = " << s1 << endl;

    if (str == s1)
    {
        cout << "\n\n TAK \n\n";
    }


    /*cout << "\n sprawdzenie poprawności wiadomości : " << endl;

    int res = str.compare(s1);

    cout << "\n\n res = " << res << endl;

    if (res == 0)
    {
        cout << "\n Wiadomosc została przesłana bez błędów \n\n";

    }*/

    
    /*
    ✓ KODER NADMIAROWY (zastosować kod hammina ✓ H(7,4) lub H(15,11)
    ✓ MODULATOR (FSK)
    -> KANAŁ TRANSMISYJNY
    ✓ DEMODULATOR (FSK)
    ✓ DEKODER (H(7,14)

     wiadomość teskstowa na tyle duża, aby strumień bitowy miał conajmniej 42 bity
     (zastosowałem 48 bitów = 6 znaków)

     -> Trik odnośnie długości wiadomości tekstowej ...

     następnie:

     mamy KODER HAMMINGA - koduje wiadomości w sposób blokowy (mamy blok 4 bitów, kodujemy na 7 bitach)

     cały strumień bitowy odpowiednio pociąć na paczki danych, które będziemy kodować koderem H(7,4)

     H(7,4) -> wychodzi WEKTOR C (przechowuje on STRUMIEN BINARNY DO MODULATORA)

     ten strumień binarny (C) -> przekazujemy do modulatora (ASK / PSK / FSK)

     z modulatora -> otrzymujemy próbki sygnału zmodulowanego

     ---------------------------
     zadanie 2:


     ! mając b i b' możemy wykonać :

        -> obliczenie parametru BER ( bit error rate ) - współczynnik błędnych bitów po stronie odbiorczej
           BER(b,b')


    Kanał transmisyjny : DOŁĄCZENIE SZUMU białego (do sygnału na wyjście z modulatora)

    następnie :
    - demodulowanie sygnału z szumem

     */





    //for (int q = 0; q < 2; q++)
    //{
    //   

    //    for (int i = 0; i < 4; i++) {

    //        paczka1[i] = b[j];
    //        //paczka2[i] = b[j+4];
    //        j++;
    //        //cout << b[i] << " ";
    //        /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
    //        {
    //            cout << endl;
    //        }*/
    //    }
    //    cout << "\n\npaczka" << q + 1 << "  = " << endl;
    //    for (int i = 0; i < 4; i++) {

    //        //b_4_[i] = b[i];

    //        cout << paczka1[i] << " ";
    //        /*if (i == 7 || i == 15 || i == 23 || i == 31 || i == 39)
    //        {
    //            cout << endl;
    //        }*/
    //    }


    //    for (int i = 0; i < 4; i++)
    //    {
    //        b_temp[i] = paczka1[i];
    //        //cout << b_temp[i] << " ";
    //    }

    //    cout << endl << endl;

    //    /*cout << "\n\n paczka" << q+1 << " = " << endl;
    //    cout << " [ ";
    //    for (int i = 0; i < 4; i++)
    //    {
    //        cout << b_temp[i] << " ";
    //    }
    //    cout << "] ";
    //    cout << endl << endl;*/


    //    int x1 = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    //    int x2 = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    //    int x4 = b_temp[1] ^ b_temp[2] ^ b_temp[3];

    //    int X[] = { x1, x2, x4 };

    //    for (int i = 0; i < 3; i++)
    //    {
    //        cout << " X[" << pow(2, i) << "] = " << X[i] << endl;;
    //    }

    //    int h = 7;
    //    int* H = new int[h];
    //    int n;
    //    int m;
    //    j = 0;
    //    int k = 0;

    //    for (int i = 0; i < 8; i++)
    //    {
    //        n = i;
    //        m = n;

    //        if (n > 0)
    //        {
    //            while (n % 2 == 0)
    //            {
    //                n /= 2;
    //            }
    //            if (n == 1)
    //            {
    //                H[m - 1] = X[j];
    //                j++;
    //            }
    //        }

    //        if (n == 0 || n != 1)
    //        {
    //            if (n != 0)
    //            {
    //                H[m - 1] = b_temp[k];
    //                k++;
    //            }
    //        }
    //    }

    //    cout << "\n C = " << endl;
    //    cout << " [ ";
    //    for (int i = 0; i < 7; i++)
    //    {
    //        cout << H[i] << " ";
    //    }
    //    cout << "] ";
    //    cout << endl << endl;

    //    // ...NALEŻY ZDEKODOWAĆ POWYŻSZY WEKTOR C (KOD HAMMINGA H(7,4))
    //    // WEKTOR C -> MODULATOR
    //    int x1_ = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    //    int x2_ = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    //    int x4_ = b_temp[1] ^ b_temp[2] ^ b_temp[3];

    //    int x1__ = x1 ^ x1_;
    //    int x2__ = x2 ^ x2_;
    //    int x4__ = x4 ^ x4_;

    //    int P = 7;
    //    int* p = new int[P];

    //    for (int i = 0; i < 8; i++)
    //    {
    //        p[i] = pow(2, i);
    //    }

    //    int S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

    //    cout << " S = " << S << "\n";

    //    int B_out = 4;
    //    int* b_out = new int[B_out];

    //    if (S == 0)
    //    {
    //        //cout << "\n Kod wejsciowy nie zawiera bledow\n";

    //        b_out[0] = H[2];
    //        b_out[1] = H[4];
    //        b_out[2] = H[5];
    //        b_out[3] = H[6];

    //        cout << "\n b_out = " << endl;
    //        cout << " [ ";

    //        for (int i = 0; i < 4; i++)
    //        {
    //            cout << b_out[i] << " ";
    //        }
    //        cout << "] ";
    //        cout << endl << endl;
    //    }
    //    else
    //    {
    //        cout << "\n Blad w kodzie na pozycji S = [" << S << "] \n";

    //        cout << "\n Korekcja bledu : \n";

    //        H[S - 1] = not(H[S - 1]);

    //        cout << "\ H = " << endl;
    //        cout << " [ ";
    //        for (int i = 0; i < 7; i++)
    //        {
    //            cout << H[i] << " ";
    //        }
    //        cout << "] ";
    //        cout << endl << endl;

    //        b_out[0] = H[2];
    //        b_out[1] = H[4];
    //        b_out[2] = H[5];
    //        b_out[3] = H[6];

    //        cout << "\n b_out = " << endl;
    //        cout << " [ ";

    //        for (int i = 0; i < 4; i++)
    //        {
    //            cout << b_out[i] << " ";
    //        }
    //        cout << "] ";
    //        cout << endl << endl;
    //    }


    //    cout << "\n y1 = " << y1 << "\n";
    //    cout << "\n y2 = " << y2 << "\n";
    //    k = 0;
    //    for (int l = y1; l < y2; l++)
    //    {
    //        cout << "->" << l << ", " << y1 << ", " << y2 << "\n";
    //        C_[l] = H[k];
    //        k++;
    //        //k++;
    //    }












    //    //j = 4;

    //    //int mm = 2;

    //    j = jj + 4;
    //    jj = j;
    //    cout << "\n j = " << j << endl;
    //    y1 = y1 + 7;
    //    y2 = y2 + 7;
    //    //k = 4;

    //}

    // dekoder

    /*int x1 = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    int x2 = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    int x4 = b_temp[1] ^ b_temp[2] ^ b_temp[3];


    int x1_ = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    int x2_ = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    int x4_ = b_temp[1] ^ b_temp[2] ^ b_temp[3];

    int x1__ = x1 ^ x1_;
    int x2__ = x2 ^ x2_;
    int x4__ = x4 ^ x4_;

    int P = 7;
    int* p = new int[P];

    for (i = 0; i < 8; i++)
    {
        p[i] = pow(2, i);
    }

    int S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

    cout << " S = " << S << "\n";

    if (S == 0)
    {
        cout << "\n Kod wejsciowy nie zawiera bledow\n";

        b_out[0] = H[2];
        b_out[1] = H[4];
        b_out[2] = H[5];
        b_out[3] = H[6];

        cout << "\n b_out = " << endl;
        cout << " [ ";

        for (i = 0; i < 4; i++)
        {
            cout << b_out[i] << " ";
        }
        cout << "] ";
        cout << endl << endl;
    }
    else
    {
        cout << "\n Blad w kodzie na pozycji S = [" << S << "] \n";

        cout << "\n Korekcja bledu : \n";

        H[S - 1] = not(H[S - 1]);

        cout << "\ H = " << endl;
        cout << " [ ";
        for (i = 0; i < 7; i++)
        {
            cout << H[i] << " ";
        }
        cout << "] ";
        cout << endl << endl;

        b_out[0] = H[2];
        b_out[1] = H[4];
        b_out[2] = H[5];
        b_out[3] = H[6];

        cout << "\n b_out = " << endl;
        cout << " [ ";

        for (i = 0; i < 4; i++)
        {
            cout << b_out[i] << " ";
        }
        cout << "] ";
        cout << endl << endl;
    }*/



    //// Negacja bitu - wprowadzenie błędu
    //H[4] = not(H[4]);

    //cout << "\ H = " << endl;
    //cout << " [ ";
    //for (i = 0; i < 7; i++)
    //{
    //    cout << H[i] << " ";
    //}
    //cout << "] ";
    //cout << endl << endl;

    //x1 = H[0];
    //x2 = H[1];
    //x4 = H[3];

    //// detekcja i korekcja kodu Hamminga :
    //x1_ = H[2] ^ H[4] ^ H[6];
    //x2_ = H[2] ^ H[5] ^ H[6];
    //x4_ = H[4] ^ H[5] ^ H[6];

    //x1__ = x1 ^ x1_;
    //x2__ = x2 ^ x2_;
    //x4__ = x4 ^ x4_;

    //for (i = 0; i < 8; i++)
    //{
    //    p[i] = pow(2, i);
    //}

    //S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

    //cout << " S = " << S << endl;

    //if (S == 0)
    //{
    //    cout << "\n Kod wejsciowy nie zawiera bledow\n";

    //    b_out[0] = H[2];
    //    b_out[1] = H[4];
    //    b_out[2] = H[5];
    //    b_out[3] = H[6];

    //    cout << "\n b_out = " << endl;
    //    cout << " [ ";

    //    for (i = 0; i < 4; i++)
    //    {
    //        cout << b_out[i] << " ";
    //    }
    //    cout << "] ";
    //    cout << endl << endl;
    //}
    //else
    //{
    //    cout << "\n Blad w kodzie na pozycji S = [" << S << "] \n";

    //    cout << "\n Korekcja bledu : \n";

    //    H[S - 1] = not(H[S - 1]);

    //    cout << "\ H = " << endl;
    //    cout << " [ ";
    //    for (i = 0; i < 7; i++)
    //    {
    //        cout << H[i] << " ";
    //    }
    //    cout << "] ";
    //    cout << endl;

    //    b_out[0] = H[2];
    //    b_out[1] = H[4];
    //    b_out[2] = H[5];
    //    b_out[3] = H[6];

    //    cout << "\n b_out = " << endl;
    //    cout << " [ ";

    //    for (i = 0; i < 4; i++)
    //    {
    //        cout << b_out[i] << " ";
    //    }
    //    cout << "] ";
    //    cout << endl << endl;
    //}


    cout << endl;
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
