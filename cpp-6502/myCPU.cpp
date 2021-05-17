#include <stdio.h>
#include <stdlib.h>

struct CPU
{
    using Byte = unsigned char;
    using Word = unsigned short;
    Word PC; //program counter
    Word SP; //stack pointer

    Byte A, X, Y; //accumulator, registers
    Byte C : 1;   //carry

    //status flags
    Byte Z : 1; //zero
    Byte I : 1; //interrupt
    Byte D : 1; //decimal
    Byte B : 1; //break
    Byte V : 1; //overflow
    Byte N : 1; //negative

    void Reset()
    {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
    }
};

int main()
{
    CPU cpu;
    cpu.Reset();
    return 0;
}