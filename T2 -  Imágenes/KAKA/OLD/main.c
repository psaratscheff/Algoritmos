// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

// Driver program to test above functions
int main()
{
    //char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    pixel p1; p1.r=1;p1.g = 11;p1.b=111;
    pixel p2;p2.r=2;p2.g = 22;p2.b=222;
    pixel p3;p3.r=3;p3.g = 33;p3.b=3;
    pixel p4;p4.r=4;p4.g = 44;p4.b=4;
    pixel p5;p5.r=5;p5.g =55;p5.b=5;
    pixel p6;p6.r=6;p6.g =66;p6.b=6;



    pixel arr[] = {p1,p2,p3,p4,p5,p6};

//    int freq[] = {5, 9, 12, 13, 16, 45};
      int freq[] = {12, 9, 9191911, 0, 16, 111};

    int size = sizeof(arr)/sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}
