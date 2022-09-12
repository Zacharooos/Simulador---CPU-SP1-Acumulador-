# Simulador---CPU-SP1-Acumulador-
Processor SP1 simulation, written in C

SP1 ́is a hypothetical processor specified for purely academic purposes.  It has three registers of 8 bits (1byte) each:
acc(accumulator) 
estat(status) 
epc(program counter)
The SP1 processor ISA ́ is composed of 16 instructions.  The format of the instructions are fixed, in this case 16 bits (8 bits for "oopcodee" 8 bits for the operand).The "statmant" register in carry, overflow and zero information from the "acc" register.
The goal of the work is to develop an emulator, in C language, for the SP1 processor.
