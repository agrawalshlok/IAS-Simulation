#include <bits/stdc++.h>
using namespace std;

// macros
#define ll long long int
#define pb(x) push_back(x)
#define vs vector<string>
#define fsn(i, s, e) for (ll i = (ll)s; i < (ll)e; i++)
#define fn(i, s) for (ll i = 0; i < (ll)s; i++)

vs memory(1000);         // global vector of strings of size 1000
ll PC, MAR, AC;          // these registers store integer values.
string MBR, IR, IBR, MQ; // these register store binary strings
bool show = false;       // this represent whether we want to show the changes in registers.

// OPcodes
string STORMX = "00100001";
string LOADMX = "00000001";
string ADDMX = "00000101";
string SUBMX = "00000110";
string MULMX = "00001011";
string LOADMQMXop = "00001001";
string LOADMQop = "00001010";
string LSHop = "00010100";
string JUMPMXleft = "00001101";

// the following function converts a decimal number to a 40 bit binary string. Negative numbers are converted as well.
string decimalToBinary(ll x)
{
    ll tc = 1;
    fn(i, 40) tc <<= 1;
    string s = "0000000000000000000000000000000000000000";
    if (x < 0)
        x += tc;
    fn(i, 40)
    {
        if (x % 2)
            s[39 - i] = '1';
        x >>= 1;
    }
    return s;
}
// the following function converts a decimal number to a 80 bit binary string. Negative numbers are covered as well.
string decimalToBinary80bit(ll x)
{
    ll tc = 1;
    fn(i, 80) tc <<= 1;
    string s = "0000000000000000000000000000000000000000";
    s += s;
    if (x < 0)
        x += tc;
    fn(i, 80)
    {
        if (x % 2)
            s[79 - i] = '1';
        x >>= 1;
    }
    return s;
}
// following function converts a binary string to a decimal value and returns it. Negative numbers are represented as 2's complements.
ll binaryToDecimal(string s)
{
    ll tc = 1;
    fn(i, 40) tc <<= 1;
    ll x = 0;
    fn(i, s.size())
    {
        x <<= 1;
        if (s[i] == '1')
            x++;
    }
    if (s[0] == '1')
        return x - tc;
    return x;
}
// the following function prints values in all the registers except MQ.
void printlocations()
{
    cout << "PC = " << PC << endl;
    cout << "MAR = " << MAR << endl;
    cout << "MBR = " << MBR << endl;
    cout << "IBR = " << IBR << endl;
    cout << "IR = " << IR << endl;
    cout << "AC = " << AC << endl;
    cout << endl;
}
// cpp implementation of assembly code to execute JUMP M(x,0:19)
void JUMP()
{
    IR = IBR.substr(0, 8);
    MAR = binaryToDecimal(IBR.substr(8, 12));
    PC = MAR;
    if (show)
    {
        cout << "After JUMP:\n";
        printlocations();
    }
}
// implementation of asssembly code to execute LOAD M(x)
void LOAD()
{
    IR = MBR.substr(0, 8);
    MAR = binaryToDecimal(MBR.substr(8, 12));
    MBR = memory[MAR];
    AC = binaryToDecimal(MBR);
    if (show)
    {
        cout << "After LOAD:\n";
        printlocations();
    }
}
// implementation of assembly code to execute ADD M(X)
void ADD()
{
    IR = IBR.substr(0, 8);
    MAR = binaryToDecimal(IBR.substr(8, 12));
    MBR = memory[MAR];
    AC = AC + binaryToDecimal(MBR);
    if (show)
    {
        cout << "After ADD:\n";
        printlocations();
    }
}
// implementation of asssembly code to execute STOR M(x)
void STOR(ll x)
{
    IR = IBR.substr(0, 8);
    MAR = binaryToDecimal(IBR.substr(8, 12));
    MBR = decimalToBinary(AC);
    memory[x] = MBR;
    if (show)
    {
        cout << "After STOR:\n";
        printlocations();
    }
}
// implementation of asssembly code to execute SUB M(x)
void SUB()
{
    IR = IBR.substr(0, 8);
    MAR = binaryToDecimal(IBR.substr(8, 12));
    MBR = memory[MAR];
    AC = AC - binaryToDecimal(MBR);
    if (show)
    {
        cout << "After SUB:\n";
        printlocations();
    }
}
// implementation of asssembly code to execute LOAD MQ
void LOADMQ()
{
    AC = binaryToDecimal(MQ);
    if (show)
    {
        cout << "After LOAD MQ:\n";
        cout << "MQ = " << MQ << endl;
        printlocations();
    }
}
// implementation of asssembly code to execute LOAD MQ M(x)
void LOADMQMX()
{
    IR = MBR.substr(0, 8);
    MAR = binaryToDecimal(MBR.substr(8, 12));
    MBR = memory[MAR];
    MQ = MBR;
    if (show)
    {
        cout << "After LOAD MQ MX:\n";
        cout << "MQ = " << MQ << endl;
        printlocations();
    }
}
// implementation of asssembly code to execute MUL M(x)
void MUL()
{
    IR = IBR.substr(0, 8);
    MAR = binaryToDecimal(IBR.substr(8, 12));
    MBR = memory[MAR];
    ll prod = binaryToDecimal(MQ) * binaryToDecimal(MBR);
    string result = decimalToBinary80bit(prod);
    MQ = result.substr(40, 40);
    AC = binaryToDecimal(result.substr(0, 40));
    if (show)
    {
        cout << "After MUL:\n";
        cout << "MQ = " << MQ << endl;
        cout << "AC in binary = " << result.substr(0, 40) << endl;
        printlocations();
    }
}
// implementation of asssembly code to execute LSH
void LSH()
{
    string ac = decimalToBinary(AC);
    ac = ac.substr(1, 39);
    ac.pb('0');
    AC = binaryToDecimal(ac);
    if (show)
    {
        cout << "After LSH:\n";
        printlocations();
    }
}
/*
the following functions fetches and decodes instructions.
it runs till the program encounters no instructions in the memory or when jump happens.
*/
void run()
{
    while (1)
    {
        if (memory[PC] == "-1")
            break;
        MAR = PC;
        MBR = memory[MAR];
        IBR = MBR.substr(20, 20);
        string op1 = memory[PC].substr(0, 8), op2 = memory[PC].substr(20, 8);

        if (op1 == STORMX)
            STOR(binaryToDecimal(memory[PC].substr(8, 12)));
        else if (op1 == LOADMX)
            LOAD();
        else if (op1 == ADDMX)
            ADD();
        else if (op1 == SUBMX)
            SUB();
        else if (op1 == LSHop)
            LSH();
        else if (op1 == MULMX)
            MUL();
        else if (op1 == LOADMQop)
            LOADMQ();
        else if (op1 == LOADMQMXop)
            LOADMQMX();
        else if (op1 == JUMPMXleft)
            JUMP();

        if (op2 == STORMX)
            STOR(binaryToDecimal(memory[PC].substr(28, 12)));
        else if (op2 == LOADMX)
            LOAD();
        else if (op2 == ADDMX)
            ADD();
        else if (op2 == SUBMX)
            SUB();
        else if (op2 == LSHop)
            LSH();
        else if (op2 == MULMX)
            MUL();
        else if (op2 == LOADMQop)
            LOADMQ();
        else if (op2 == LOADMQMXop)
            LOADMQMX();
        else if (op2 == JUMPMXleft)
            JUMP();

        if (op1 != JUMPMXleft && op2 != JUMPMXleft)
            PC++;
        else
            break;
    }
}
/*the following function takes x and y as numbers to add and converts them to binary and stores it in memory.
memory locations 0 and 1 are used to store the instructions necessary to perform the operation.
we jump to zero at end to make sure that the next operations performed will be accurate.
at the end we return the value stored at the memory loaction 200 in decimal form.
*/
ll addition(ll x, ll y)
{
    memory[0] = "0000000100000110010000000101000001100101"; // LOAD M(100), ADD M(101)
    memory[1] = "0010000100001100100000001101000000000000"; // STOR M(200) JUMP M(0,1:19)
    string first, second;
    first = decimalToBinary(x);
    second = decimalToBinary(y);
    memory[100] = first;
    memory[101] = second;
    run();
    return binaryToDecimal(memory[200]);
}
/*the following function takes x and y as numbers to subtract and converts them to binary and stores them in memory.
memory locations 0 and 1 are used to store the instructions necessary to perform the operation.
we jump to zero at end to make sure that the next operations performed will be accurate.
at the end we return the value stored at the memory loaction 200 in decimal form.
*/
ll subtract(ll x, ll y)
{
    memory[0] = "0000000100000110010000000110000001100101"; // LOAD M(100), SUB M(101)
    memory[1] = "0010000100001100100000001101000000000000"; // STOR M(200) JUMP M(0,1:19)
    string first, second;
    first = decimalToBinary(x);
    second = decimalToBinary(y);
    memory[100] = first;
    memory[101] = second;
    run();
    return binaryToDecimal(memory[200]);
}
/*the following function takes x and y as numbers to multiply and converts them to binary and stores them in memory.
memory locations 0,1 and 2 are used to store the instructions necessary to perform the operation.
we jump to zero at end to make sure that the next operations performed will be accurate.
at the end we return the value stored at the memory loaction 200 in decimal form.
*/
ll multiply(ll x, ll y)
{
    memory[0] = "0000100100000110010000001011000001100101"; // LOAD MQ M(100), MUL M(101)
    memory[1] = "0000101000000000000000100001000011001000"; // LOAD MQ STOR M(200)
    memory[2] = "0000000000000000000000001101000000000000"; // JUMP M(0,1:19)
    string first, second;
    first = decimalToBinary(x);
    second = decimalToBinary(y);
    memory[100] = first;
    memory[101] = second;
    run();
    return binaryToDecimal(memory[200]);
}
/*the following function takes x as number to left shift and converts it to binary and stores it in memory.
memory locations 0 and 1 are used to store the instructions necessary to perform the operation.
we jump to zero at end to make sure that the next operations performed will be accurate.
at the end we return the value stored at the memory loaction 200 in decimal form.
*/
ll leftshift(ll x)
{
    memory[0] = "0000000100000110010000010100000000000000"; // LOAD M(100), LSH
    memory[1] = "0010000100001100100000001101000000000000"; // STOR M(200) JUMP M(0,1:19)
    string first;
    first = decimalToBinary(x);
    memory[100] = first;
    run();
    return binaryToDecimal(memory[200]);
}
int main()
{
    fn(i, 1000) memory[i] = "-1"; // all the memory locations are initialize to -1. they will later represent unused memory locations.
    ll choice;                    // we take input from user to perform whatever operation they desire.
    while (1)
    { // the input will run in a loop which will run till the user's satisfaction.
        cout << "Press 1 for addition.(prints values in registers)\n";
        cout << "Press 2 for subtraction.(prints values in registers)\n";
        cout << "Press 3 for multiplication.(prints values in registers)\n";
        cout << "Press 4 for left shift.(prints values in registers)\n";
        cout << "Press 5 for first 10 numbers of a given Arithmetic Progression.\n";
        cout << "Press 6 for first 10 numbers of a given Geometric Progression.\n";
        cout << "Press 7 for the first 10 numbers of Fibonacci Series.\n";
        cout << "Press 8 for the Factorial of first 10 natural numbers.\n";
        cout << "Press 9 for the first 10 powers of 2 (from 1).\n";
        cout << "Press 0 to exit.\n";
        cin >> choice;
        cout << endl;

        if (choice == 1)
        {
            ll first, second;
            cout << "Enter two numbers to add.\n";
            cin >> first >> second;
            show = true; // this will make the instructions print the values at all registers.
            ll ans = addition(first, second);
            show = false; // to make sure that registers only print when desired.
            cout << "Sum = " << ans << endl;
            cout << endl;
        }

        if (choice == 2)
        {
            ll first, second;
            cout << "Enter two numbers to subtract.\n";
            cin >> first >> second;
            show = true; // this will make the instructions print the values at all registers.
            ll ans = subtract(first, second);
            show = false; // to make sure that registers only print when desired.
            cout << "subtraction = " << ans << endl;
            cout << endl;
        }

        if (choice == 3)
        {
            ll first, second;
            cout << "Enter two numbers to multiply.\n";
            cin >> first >> second;
            show = true; // this will make the instructions print the values at all registers.
            ll ans = multiply(first, second);
            show = false;
            cout << "product = " << ans << endl;
            cout << endl;
        }

        if (choice == 4)
        {
            ll num;
            cout << "Enter a number to left shift by 1.\n";
            cin >> num;
            show = true; // this will make the instructions print the values at all registers.
            ll ans = leftshift(num);
            show = false; // to make sure that registers only print when desired.
            cout << "left shift = " << ans << endl;
            cout << endl;
        }

        if (choice == 5)
        {
            ll a, d;
            cout << "Enter the first number of AP: ";
            cin >> a;
            cout << "Enter the common difference of AP: ";
            cin >> d;
            fsn(i, 1, 11)
            {
                ll nMinus1 = subtract(i, 1);
                ll prod = multiply(nMinus1, d);
                ll term = addition(a, prod);
                memory[500 + i] = decimalToBinary(term);
                // using assembly instructions to perform operation and storing it in adjacent memory locations in binary form
            }
            cout << endl;
            fn(i, 10)
            {
                cout << binaryToDecimal(memory[501 + i]) << " ";
                // printing the values in adjacent memory locations in decimal form.
            }
            cout << endl;
            cout << endl;
        }

        if (choice == 6)
        {
            ll a, r;
            cout << "Enter the first number of GP: ";
            cin >> a;
            cout << "Enter the common ratio of GP: ";
            cin >> r;
            memory[501] = decimalToBinary(a);
            fsn(i, 2, 11)
            {
                a = multiply(a, r);
                memory[500 + i] = decimalToBinary(a);
                // using assembly instructions to perform operation and storing it in adjacent memory locations in binary form
            }
            cout << endl;
            fn(i, 10)
            {
                cout << binaryToDecimal(memory[501 + i]) << " ";
                // printing the values in adjacent memory locations in decimal form.
            }
            cout << endl;
            cout << endl;
        }

        if (choice == 7)
        {
            ll f = 0, s = 1;
            memory[501] = decimalToBinary(f);
            memory[502] = decimalToBinary(s);
            fsn(i, 3, 11)
            {
                f = binaryToDecimal(memory[500 + i - 1]);
                s = binaryToDecimal(memory[500 + i - 2]);
                ll term = addition(f, s);
                memory[500 + i] = decimalToBinary(term);
                // using assembly instructions to perform operation and storing it in adjacent memory locations in binary form
            }
            fn(i, 10)
            {
                cout << binaryToDecimal(memory[501 + i]) << " ";
                // printing the values in adjacent memory locations in decimal form.
            }
            cout << endl;
            cout << endl;
        }

        if (choice == 8)
        {
            ll term = 1;
            fsn(i, 1, 11)
            {
                term = multiply(term, i);
                memory[500 + i] = decimalToBinary(term);
                // using assembly instructions to perform operation and storing it in adjacent memory locations in binary form
            }
            fn(i, 10)
            {
                cout << binaryToDecimal(memory[501 + i]) << " ";
                // printing the values in adjacent memory locations in decimal form.
            }
            cout << endl;
            cout << endl;
        }

        if (choice == 9)
        {
            ll term = 1;
            memory[501] = decimalToBinary(term);
            fsn(i, 2, 11)
            {
                term = leftshift(term);
                memory[500 + i] = decimalToBinary(term);
                // using assembly instructions to perform operation and storing it in adjacent memory locations in binary form
            }
            fn(i, 10)
            {
                cout << binaryToDecimal(memory[501 + i]) << " ";
                // printing the values in adjacent memory locations in decimal form.
            }
            cout << endl;
            cout << endl;
        }

        if (choice < 1 || choice > 9)
            break;
    }
    return 0;
}