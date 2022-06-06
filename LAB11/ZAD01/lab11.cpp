// lab11.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

    int B_out = 4;
    int* b_out = new int[B_out];

    bit_char = 'h';

    for (i = 0; i < 8; i++) {
        b[i] = bit_char % 2;
        bit_char = bit_char / 2;
    }
    int a;
    cout << " b = " << endl;
    cout << " [ ";
    for (i = 1, a = 6; i < 8; i++, a--) {
        cout << b[a] << " ";
    }
    cout << "] " << endl;

    int B_temp = 4;
    int * b_temp = new int[B_temp];

    int v = 6;
    for (i = 0; i < 4; i++)
    {
        b_temp[i] = b[v];     
        v--;
    }
     
    cout << "\n b_temp = " << endl;
    cout << " [ ";
    for (i = 0; i < 4; i++)
    {
        cout << b_temp[i] << " ";
    }
    cout << "] ";
    cout << endl << endl;

    int x1 = b_temp[0] ^ b_temp[1] ^ b_temp[3];
    int x2 = b_temp[0] ^ b_temp[2] ^ b_temp[3];
    int x4 = b_temp[1] ^ b_temp[2] ^ b_temp[3];

    int X[] = { x1, x2, x4 };
        
    for (i = 0; i < 3; i++)
    {
        cout << " X[" << pow(2,i) << "] = " << X[i] <<  endl;;
    }

    int h = 7;
    int* H = new int[h];

    /*for (i = 0; i < 7; i++)
    {
        H[i] = 0;
    }*/
    /*cout << "\n\n H = \n";
    for (i = 0; i < 8; i++)
    {
        cout << H[i] << " ";;
    }*/

    cout << endl;
   
    int n;
    int m;
    int j = 0;
    int k = 0;

    for (i = 0; i < 8; i++)
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

    cout << "\ H = " << endl;
    cout << " [ ";
    for (i = 0; i < 7; i++)
    {
        cout << H[i] << " ";
    }
    cout << "] ";
    cout << endl << endl;    
   
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
    }   
    
    // Negacja bitu - wprowadzenie błędu

    H[4] = not(H[4]);

    cout << "\ H = " << endl;
    cout << " [ ";
    for (i = 0; i < 7; i++)
    {
        cout << H[i] << " ";
    }
    cout << "] ";
    cout << endl << endl;

    x1 = H[0];
    x2 = H[1];
    x4 = H[3];

    // detekcja i korekcja kodu Hamminga :

    x1_ = H[2] ^ H[4] ^ H[6];
    x2_ = H[2] ^ H[5] ^ H[6];
    x4_ = H[4] ^ H[5] ^ H[6];

    x1__ = x1 ^ x1_;
    x2__ = x2 ^ x2_;
    x4__ = x4 ^ x4_;
    
    for (i = 0; i < 8; i++)
    {
        p[i] = pow(2, i);
    }

    S = x1__ * p[0] + x2__ * p[1] + x4__ * p[2];

    cout << " S = " << S << endl;

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
        cout << endl;

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
