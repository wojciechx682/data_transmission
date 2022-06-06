// lab12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <bitset>
#include <math.h>
#include <cmath>
#define M_PI 3.14159265358979323846

// #include <Eigen/Sparse>

using namespace std;
using namespace Eigen;
using std::cout;
using std::endl;
using std::string;
using std::bitset;

string TextToBinaryString(string words) {
    string binaryString = "";
    for (char& _char : words) {
        binaryString += bitset<8>(_char).to_string();
    }
    return binaryString;
}

void removeRow(Eigen::MatrixXd& matrix, unsigned int rowToRemove)
{
    unsigned int numRows = matrix.rows() - 1;
    unsigned int numCols = matrix.cols();

    if (rowToRemove < numRows)
        matrix.block(rowToRemove, 0, numRows - rowToRemove, numCols) = matrix.block(rowToRemove + 1, 0, numRows - rowToRemove, numCols);

    matrix.conservativeResize(numRows, numCols);
}

int main()
{ 

    // 'h' = 0 1 1 0 1 0 0 0 
    // 'hh' = 0 1 1 0 1 0 0 0 0 1 1 0 1 0 0 0 
    
    string str = "hh";
    cout << " string text: '" << str << "'\n";
    
    string s2 = TextToBinaryString(str);

    cout << " str -> bin = " << s2 << "\n";

    const int SIZE = 16;
    const int SIZE2 = 11;
    //string s1 = "0110100001101000";
    int b1[SIZE];
    int b2[SIZE2];

    for (int i = 0; i < SIZE; i++) {
        b1[i] = s2[i] - '0';
    }

    cout << "\n b[] array - (16 elements) = " << endl << " ";
    for (int i = 0; i < 16; i++) {
        cout << b1[i] << " ";
    }    
    
    for (int i = 0; i < 11; i++) 
    {
        b2[i] = b1[i];        
    }

    cout << "\n  b[] array - (11 elements) = " << endl << " ";
    for (int i = 0; i < 11; i++) {
        cout << b2[i] << " ";
    }

    /* Zaimplenetnować koder oraz dekoder kodu Hamminga (15,11) z wykorzystaniem rachunku 
    macierzowego z operacją dodawania modulo 2. 
    W tym przypadku zakładamy, że struktura słowa kodowego (n=15, k=11, m=4) jest przedstawiona:

    STRUKTURA SŁOWA KODOWEGO :  (n = 15, k = 11, m = 4)

    x1 x2 x4 x8    x3 x5 x6 x7 x9 x10 x11 x12 x13 x14 x15
    -----------    --------------------------------------
        m = 4                      k = 11
    
    Procedura kodowania sprowadza się do realizacji następującej operacji macierzowej:

    c = bG,

    b - jest wektorem zawierającym bity wiadomości,
    c - jest wektorem słowa kodowego,
    G - jest macierzą generującą.

    Macierz generującą wyznacza się w następujący sposób:

    G = [ P | Ik ],

    Ik - jest macierzą jednostkową,
    P - jest macierzą okreśjalącą bity parzystości, w której kolumny reprezentją kolejne bity parzystości, 
        natomiast wiersze - bity wiadomości    */

    Matrix<int, 15, 4> P;
    Matrix<int, 11, 4> P_reduced_rows;
    Matrix<int, 11, 4> P_swap_cols;       
    Matrix<int, 1, 15> C;    
    Matrix<int, 11, 15> G;
    Matrix<int, 11, 11> Ik;
    Matrix<int, 4, 4> Ink;
    Matrix<int, 1, 11> b;
    Matrix<int, 4, 15> H;
    Matrix<int, 1, 4> s;
    Matrix<int, 1, 4> w;

    //const int size = 11;
    //MatrixXd Ik(size, size);
    //Ik = Eigen::MatrixXd::Identity(size, size);      

    P.row(0) << 0, 0, 0, 1;    
    P.row(1) << 0, 0, 1, 0;
    P.row(2) << 0, 0, 1, 1;
    P.row(3) << 0, 1, 0, 0;
    P.row(4) << 0, 1, 0, 1;
    P.row(5) << 0, 1, 1, 0;
    P.row(6) << 0, 1, 1, 1;
    P.row(7) << 1, 0, 0, 0;
    P.row(8) << 1, 0, 0, 1;
    P.row(9) << 1, 0, 1, 0;
    P.row(10) << 1, 0, 1, 1;
    P.row(11) << 1, 1, 0, 0;
    P.row(12) << 1, 1, 0, 1;
    P.row(13) << 1, 1, 1, 0;
    P.row(14) << 1, 1, 1, 1; 

    P_reduced_rows.row(0) << P.row(2);    
    P_reduced_rows.row(1) << P.row(4);
    P_reduced_rows.row(2) << P.row(5);
    P_reduced_rows.row(3) << P.row(6);
    P_reduced_rows.row(4) << P.row(8);
    P_reduced_rows.row(5) << P.row(9);
    P_reduced_rows.row(6) << P.row(10);
    P_reduced_rows.row(7) << P.row(11);
    P_reduced_rows.row(8) << P.row(12);
    P_reduced_rows.row(9) << P.row(13);
    P_reduced_rows.row(10) << P.row(14);  
   
    Ik.row(0) << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
    Ik.row(1) << 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0;
    Ik.row(2) << 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0;
    Ik.row(3) << 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0;
    Ik.row(4) << 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0;
    Ik.row(5) << 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0;
    Ik.row(6) << 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0;
    Ik.row(7) << 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0;
    Ik.row(8) << 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0;
    Ik.row(9) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0;
    Ik.row(10) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1;
   
    Ink.row(0) << 1, 0, 0, 0;
    Ink.row(1) << 0, 1, 0, 0;
    Ink.row(2) << 0, 0, 1, 0;
    Ink.row(3) << 0, 0, 0, 1;   

    P_swap_cols = P_reduced_rows;

    P_swap_cols.col(0) = P_reduced_rows.col(3);
    P_swap_cols.col(1) = P_reduced_rows.col(2);
    P_swap_cols.col(2) = P_reduced_rows.col(1);
    P_swap_cols.col(3) = P_reduced_rows.col(0); 
    
    cout << "\n\nHere is the matrix P :\n\n" << P_swap_cols << endl;    
    cout << "\nHere is the matrix Ik (11 x 11) :\n\n" << Ik << endl;   
    cout << "\nHere is the matrix Ink (4 x 4): \n\n" << Ink << endl;  

    G(P_swap_cols.rows(), P_swap_cols.cols() + Ik.cols());
    G << P_swap_cols, Ik;

    cout << "\nHere is the matrix G (15 x 11) :\n\n" << G << endl;

    cout << "\ncreate vector b from b[] array ->" << endl;

    for (int i = 0; i < 11; i++)
    {
        b(0, i) = b2[i];
    }

    cout << "\nb[] array - (11 elements) = " << endl << " ";
    for (int i = 0; i < 11; i++) {
        cout << b2[i] << " ";
    }

    // 'hh'   = 0 1 1 0 1 0 0 0 0 1 1 0 1 0 0 0 
    // b2[11] = 0 1 1 0 1 0 0 0 0 1 1

    cout << "\n\nvector b = \n" << b << endl;

    C = b*G;

    cout << "\nHere is the vector C (C = b*G) :\n" << C << endl;

    for (int i = 0; i < 15; i++)
    {
        C(0, i) = C(0, i) % 2;
    }
    cout << "\nHere is the vector C after modulo % 2 operation for each element :\n" << C << endl;
        
    C(0, 4) = 1; // WPROWADZENIE BŁĘDU
   
    H(Ink.rows(), Ink.cols() + P_swap_cols.transpose().cols());
    H << Ink, P_swap_cols.transpose();

    cout << "\nHere is the matrix H:\n" << H << endl;

    s << C * H.transpose();

    for (int i = 0; i < 4; i++)
    {
        s(0, i) = s(0, i) % 2;
    }

    w.row(0) << 1, 2, 4, 8;

    cout << "\nHere is the vector s:\n" << s << endl;
    cout << "\nHere is the Syndrome S:\n" << s.dot(w) << endl;

    if (s.dot(w) == 0)
    {
        cout << "\nBrak bledow w odczytaniu zakodowanego slowa\n" << endl;
    }
    else
    {
        cout << "\nWystapil blad w slowie zakodowanym na pozycji o indeksie = " << s.dot(w) << endl;

        int index = s.dot(w);

        if (index == 3)
        {
            C(0, 4) = not(C(0, 4));         
        }
        if (index == 4)
        {
            C(0, 5) = not(C(0, 5));
        }
        if (index == 6)
        {
            C(0, 6) = not(C(0, 6));
        }
        if (index == 7)
        {
            C(0, 7) = not(C(0, 7));
        }
        if (index == 9)
        {
            C(0, 8) = not(C(0, 8));
        }
        if (index == 10)
        {
            C(0, 9) = not(C(0, 9));
        }
        if (index == 11)
        {
            C(0, 10) = not(C(0, 10));
        }
        if (index == 12)
        {
            C(0, 11) = not(C(0, 11));
        }
        if (index == 13)
        {
            C(0, 12) = not(C(0, 12));
        }
        if (index == 14)
        {
            C(0, 13) = not(C(0, 13));
        }
        if (index == 15)
        {
            C(0, 14) = not(C(0, 14));
        }

        s << C * H.transpose();
        for (int i = 0; i < 4; i++)
        {
            s(0, i) = s(0, i) % 2;
        }

        cout << "\nHere is the vector C after modulo % 2 operation for each element :\n" << C << endl;
        cout << "\nHere is the vector s:\n" << s << endl;
        cout << "\nHere is the Syndrome S:\n" << s.dot(w) << endl;
    }
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