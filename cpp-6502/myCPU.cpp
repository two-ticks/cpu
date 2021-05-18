#include <stdio.h>
#include <stdlib.h>
using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;
struct Memory
{
    static constexpr u32 MAX_MEM = 1024 * 64; //constexpr suggest compiler to evaluate value at compile time
    Byte Data[MAX_MEM];
    void Initialise()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i] = 0;
        }
    }
    /*read a byte*/
    Byte operator[](u32 Address) const
    {
        //Address < MAX_MEM
        return Data[Address];
    }
};

struct CPU
{
    Word PC; //program counter
    Word SP; //stack pointer

    Byte A, X, Y; //accumulator, registers
    Byte C : 1;   //carry

    /*status flags*/
    Byte Z : 1; //zero
    Byte I : 1; //interrupt
    Byte D : 1; //decimal
    Byte B : 1; //break
    Byte V : 1; //overflow
    Byte N : 1; //negative

    void Reset(Memory &memory)
    {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialise();
    }

    Byte FetchByte(u32 Cycles, Memory &memory) //fetch byte from memory where PC points
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    /*opcodes*/
    static constexpr Byte INS_LDA_IM = 0xA9;

    void Execute(u32 Cycles, Memory &memory)
    {
        while (Cycles > 0)
        {
            Byte Ins = FetchByte(Cycles, memory);
            switch (Ins)
            {
            case INS_LDA_IM:
            {
                Byte Value = FetchByte(Cycles, memory);
                A = Value;
                Z = (A == 0);
                N = (A & 0b10000000) > 0;
            }
            break;

            default:
            {
                printf("invalid instrcution");
                break;
            }
            }
        }
    }
};

int main()
{
    Memory mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2, mem); //Execute(ClockCycles, MemoryInstructions)
    return 0;
}