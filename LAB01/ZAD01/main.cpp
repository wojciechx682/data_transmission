// lab01.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _USE_MATH_DEFINES
#include <iostream>
#include <Math.h>

//using namespace std;

int main()
{
    //std::cout << "Hello World!\n";

    float frequency = 100; // 100 Hz
    float Sampling_time = (1/frequency);
    float Total_time = 1;  // 1 s

    int N = ceil(Total_time / Sampling_time);

    float *s = new float[N];
    float *t = new float[N];
    
    float A = 1;
    float f = 1;
    float phi = 0;

    for(int n = 0; n < N; n++)
    {
        t[n] = (n/frequency);
        s[n] = A * sin(2 * M_PI * f * t[n] + phi);

        std::cout << t[n] << ";" << s[n] << ";" << std::endl;
    }

    delete[] s;
    delete[] t;

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
