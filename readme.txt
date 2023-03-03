I have implemented the IAS Computer using C++.

The following instructions are implemented:
1. LOAD MQ
2. LOAD MQ,M(X)
3. STOR M(X)
4. LOAD M(X)
5. ADD M(X)
6. SUB M(X)
7. MUL M(X)
8. LSH1
9. JUMP M(X,0:19)

To implement the above instructions, the following registers are used:
1. PC (Program Counter): stored as an integer.
2. AC (Accumulator): stored as an integer.
3. IR (Instruction Register): stored as a binary string.
4. MAR (Memory Address Register): stored as an integer.
5. MBR (Memory Buffer Register): stored as a binary string.
6. IBR (Instruction Buffer Register): stored as a binary string.
7. MQ (Multiplier/Quotient): stored as a binary string.

With the help of the instructions implemented, the following programs are made to check the instructions:
1. Addition of two numbers: Adds two numbers and prints the values of all the registers after each instruction is complete.
2. Subtraction of two numbers: Subtracts two numbers and prints the values of all the registers after each instruction.
3. Multiplication of two numbers: Multiplies two numbers and prints the values of all the registers after each instruction.
4. Left shift of a numbers: Gives out left shift result(Multiplication by 2) and prints the values of all the registers after each instruction.
(after this, none of the programs prints the values of registers as too many instructions will be performed to realistically print values after each instruction.)
5. First 10 numbers of an AP: Prints the first 10 numbers of an AP with first number and common difference as inputs. Tests: Addition, Subtraction and Multiplication. The numbers will be stored in consecutive memory locations in binary form and then printed after converting to decimal.
6. First 10 numbers of a GP: Prints the first 10 numbers of a GP with first number and common ratio as inputs. Tests: Multiplication. The numbers will be stored in consecutive memory locations in binary form and then printed after converting to decimal.
7. First 10 numbers of Fibonacci Series. Tests: Addition. The numbers will be stored in consecutive memory locations in binary form and then printed after converting to decimal.
8. Factorial of the first 10 natural numbers. Tests: Multiplication. The numbers will be stored in consecutive memory locations in binary form and then printed after converting to decimal.
9. First 10 powers of two. Tests: LSH. The numbers will be stored in consecutive memory locations in binary form and then printed after converting to decimal.

Note: When printing the registers, a garbage value may be printed if the particular instruction doesn't tamper with some register.
Note: JUMP happens after each instruction to make sure that PC==0 and the instructions which follow execute flawlessly.

How to Run the code:
- When the code first runs, the terminal shows a list of options. Press the number which represents the program which you desire to run.
- Enter the prompted values in input prompt (if there is an input).
- After the input/output cycle ends, the same menu shows up again. You can select the same or different program to run this time. Or press 0 to terminate the code.
- The first 4 programs are simple arithmetic operation and will show the values in registers after each instruction before it display the result.
- The rest require around 40(or more) instruction cycles, so printing the values in registers is impratical.