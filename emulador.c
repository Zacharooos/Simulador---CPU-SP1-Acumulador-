#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define LOADMEM 0
#define LOADVAL 1
#define STORE 2
#define ADD 3
#define SUB 4
#define MUL 5
#define DIV 6
#define INC 7
#define DEC 8
#define AND 9
#define OR 10
#define NOT 11
#define JMP 12
#define JZ 13
#define JNZ 14
#define HLT 15

#define ZERO 1
#define CARRY 2
#define OVFLOW 4


typedef struct inst
{
  unsigned char opcode;
  unsigned char operand;

}inst;

int main()
{
  FILE *arquivo = fopen ("teste.exe", "rb");
  unsigned char acc;
  unsigned char pc=0;
  unsigned char stat=0;
  unsigned char aux[2];
  unsigned char mem[256];
  inst emulador[256];



  while(fread(aux, sizeof(unsigned char), 2, arquivo))
    {
      emulador[pc].opcode= aux[0];
      emulador[pc].operand= aux[1];
      pc++;
    }


    pc=0;
  while (emulador[pc].opcode != HLT || pc < 256)
{
    switch (emulador[pc].opcode)
    {
      case LOADMEM:

        acc = mem[emulador[pc].operand];
        pc++;
        break;

      case LOADVAL:

        acc = emulador[pc].operand;
        pc++;
          break;

      case STORE:

        mem[emulador[pc].operand] = acc;
        pc++;
          break;

      case ADD:

        if (acc+mem[emulador[pc].operand] >255 && (stat<2))
          stat+=CARRY;
        acc+= mem[emulador[pc].operand];
        pc++;
          break;

      case SUB:

        acc-=mem[emulador[pc].operand];
        pc++;
          break;

      case MUL:

      if (acc*mem[emulador[pc].operand]>255 && stat<2)
        stat+=OVFLOW;
        acc*= mem[emulador[pc].operand];
        pc++;
          break;

      case DIV:

        if(emulador[pc].operand == 0)
        {
          printf("Erro, não é possível efetuar uma divisão por 0");
          return 1;
        }
        acc = acc/mem[emulador[pc].operand];
        pc++;
          break;

      case INC:

      if (acc+mem[emulador[pc].operand] >255 && stat<2)
        stat+=CARRY;
        acc++;
        pc++;
        break;

      case DEC:

        acc--;
        pc++;
          break;

      case AND:

      acc = acc & mem[emulador[pc].opcode];
      pc++;
          break;

      case OR:

        acc = acc | mem[emulador[pc].opcode];
        pc++;
        break;

      case NOT:

        acc = ~acc;
        pc++;
        break;

      case JMP:

        pc = emulador[pc].operand/2;
          break;

      case JZ:

      if(acc == 0)
        pc = emulador[pc].operand/2;
      else
        pc++;
          break;

      case JNZ:

      if(acc != 0)
        pc = emulador[pc].operand/2;
      else
        pc++;
          break;

      case HLT:

        printf("ACC: %d - STAT: %d\n", acc, stat);
        fclose(arquivo);
        return 0;
        break;
      }
	    if(acc==0 && ((stat%2) == 0))
	    	stat+=ZERO;
	    else if (stat%2 == 1)
	    	if (acc!=0)
	        stat-=ZERO;
    }
    printf("ACC: %d - STAT: %d\n", acc, stat);
    fclose(arquivo);
    return 0;
}
