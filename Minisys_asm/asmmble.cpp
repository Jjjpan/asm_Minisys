// A simple and naive MIPS assembler
// Use this command to make: g++ MIPS.cpp -o MIPS
// Usage: ./MIPS CodeFile
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

// A function used to extract the register number from string "$xx"
int getReg(char* arg){
    int reg = 0;
    char *p = arg;
    while (*p == ' ') p++;       // Skip the space at the beginning
    if (*p == '$') p++;
    else return -1;              // Unexpected charaters

    // Parse
    while(*p >= '0' && *p <= '9'){
        reg = 10 * reg + (*p - '0');
        p++;
    }
    while (*p == ' ') p++;               // Skip the space following the number
    if (*p != '\0'||*p!='$') return -1;           // Unexpected characters
    else return reg;
}

// Output a binary number with a given length to an object of ostream
void printBin(int num, int digi, ostream& os){
    char *bin = (char*)malloc(digi*sizeof(char)+1);
    memset(bin, '0', digi * sizeof(char));
    bin[digi]='\0';
    char *p = bin + (digi - 1);
    int sign = (num >= 0)? 1: -1;
    num = num * sign;

    while (num > 0){
        if (num & 1) *p = '1';
        num >>= 1;
        p--;
    }
    // Transform to the 2's complement
    if (sign == -1){
        p = bin + (strlen(bin) - 1);
        while (p >= bin && *p != '1') p--;      // Find the last '1'
        if (p >= bin && *p == '1') p--;         // Skip the last '1'
        while (p >= bin) {
            *p = ('0' + '1') - *p;
            p--;
        }
    }
    os << bin;
    delete bin;
}


int main(int argc, char** argv){
    // Check the input
    if (argc != 2){
        cout << "Error: File name needed." << endl;
        exit(-1);
    }

    ifstream code(argv[1]);
    //char *objname = new char[strlen(argv[1]) + 10];
    //strcpy(objname, argv[1]);

    /*int i;
    // Find the suffix
    for (i = strlen(objname) - 1; i >= 0; i--) if (objname[i] == '.') break;
    // Give the output file a ".mips" suffix
    if (objname[i] == '.'){
         objname[i + 1] = '\0';
         strcat(objname, "coe");
    }
    else strcat(objname, ".coe");

    ofstream obj(objname);
    delete objname;*/

    /****************************************************
     The instruction strctures
     R-type:
        +------------------------------------------------+
        | opcode | rs    | rt    | rd    | shamt | funct |
        |--------+-------+-------+-------+-------+-------|
        | 6-bit  | 5-bit | 5-bit | 5-bit | 5-bit | 6-bit |
        +------------------------------------------------+
     I-type:
        +------------------------------------------------+
        | opcode | rs    | rt    | immediate             |
        |--------+-------+-------+-----------------------|
        | 6-bit  | 5-bit | 5-bit | 16-bit                |
        +------------------------------------------------+
     J-type:
        +------------------------------------------------+
        | opcode | jump address                          |
        |--------+---------------------------------------|
        | 6-bit  | 26-bit                                |
        +------------------------------------------------+
    */

    /*
        read the initialization of ROM
        create file of dmem32.coe
    */

    const char empty_mem[9]="00000000";
    const char title_mem[100]="memory_initialization_radix = 16;";
    const char subtitle_mem[100]="memory_initialization_vector =";
    const char empty_cmd[9]="00000000";
    const char title_cmd[100]="memory_initialization_radix = 16;";
    const char subtitle_cmd[100]="memory_initialization_vector =";
    ofstream mem_write("dmem32.coe");
    ofstream obj("prgmip32.coe");

    mem_write<<title_mem<<endl<<subtitle_mem<<endl;
    obj<<title_cmd<<endl<<subtitle_cmd<<endl;
    char judge[20];
    //code.getline(judge,20,'#');
    /*while(code>>judge)
    {
        code.getline(judge,20,':');
        if(!strcmp(judge,"start"))
            break;
        else
        {

        }
    }*/
























    char command[20], arg1[20], arg2[20], arg3[20];
    int line_no = 0;
    while (code >> command){
        line_no++;                      // The current line
        //code >> command;
        if (!strcmp(command, "add")){   // ADD $rd, $rs, $rt
            printBin(0, 6, obj);        // OpCode
            //code >> arg1 >> arg2 >> arg3;
            code.getline(arg1, 20, ',');
            int rd = getReg(arg1);
            if (rd == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20, ',');
            int rs = getReg(arg2);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg3, 20);
            int rt = getReg(arg3);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(rd, 5, obj);
            printBin(0, 5, obj);       // shamt
            printBin(0x20, 6, obj);    // funct
            obj << endl;
        }
        else if (!strcmp(command, "sub")){    // SUB $rd, $rs, $rt
            printBin(0, 6, obj);       // OpCode

            code.getline(arg1, 20, ',');
            int rd = getReg(arg1);
            if (rd == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20, ',');
            int rs = getReg(arg2);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg3, 20);
            int rt = getReg(arg3);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(rd, 5, obj);
            printBin(0, 5, obj);       // shamt
            printBin(0x22, 6, obj);    // funct
            obj << endl;
        }
        else if (!strcmp(command, "and")){ // AND $rd, $rs, $rt
            printBin(0, 6, obj);       // OpCode

            code.getline(arg1, 20, ',');
            int rd = getReg(arg1);
            if (rd == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20, ',');
            int rs = getReg(arg2);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg3, 20);
            int rt = getReg(arg3);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(rd, 5, obj);
            printBin(0, 5, obj);       // shamt
            printBin(0x24, 6, obj);    // funct
            obj << endl;
        }
        else if (!strcmp(command, "or")){// OR $rd, $rs, $rt
            printBin(0, 6, obj);       // OpCode

            code.getline(arg1, 20, ',');
            int rd = getReg(arg1);
            if (rd == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20, ',');
            int rs = getReg(arg2);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg3, 20);
            int rt = getReg(arg3);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(rd, 5, obj);
            printBin(0, 5, obj);       // shamt
            printBin(0x25, 6, obj);    // funct
            obj << endl;
        }
        else if (!strcmp(command, "slt")){// SLT $rd, $rs, $rt
            printBin(0, 6, obj);       // OpCode

            code.getline(arg1, 20, ',');
            int rd = getReg(arg1);
            if (rd == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20, ',');
            int rs = getReg(arg2);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg3, 20);
            int rt = getReg(arg3);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(rd, 5, obj);
            printBin(0, 5, obj);       // shamt
            printBin(0x2A, 6, obj);    // funct
            obj << endl;
        }
        else if (!strcmp(command, "beq")){  // BEQ $rs, $rt, imm
            printBin(0x4, 6, obj);     // OpCode

            code.getline(arg1, 20, ',');
            int rs = getReg(arg1);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20, ',');
            int rt = getReg(arg2);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            int offset;
            code >> offset;

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(offset, 16, obj);    // immediate
            obj << endl;
        }
        else if (!strcmp(command, "lw")){  // LW $rt, offset($rs)
            printBin(0x23, 6, obj);      // OpCode

            code.getline(arg1, 20, ',');
            int rt = getReg(arg1);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20);
            int offset = 0;
            int sign = 1;
            char *p = arg2;

            while (*p == ' ') p++;
            if (*p == '-'){
                p++;
                sign = -1;
            }
            // Parse
            while (*p >= '0' && *p <= '9'){
                offset = 10 * offset + (*p - '0');
                p++;
            }
            offset = sign * offset;

            while (*p == ' ') p++;    // Skip the space before '('
            if (*p == '(') p++;
            else {
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            char *q = arg2 + (strlen(arg2) - 1);
            while (*q == ' ') q--;
            if (*q == ')') *q = '\0';     // Find the ')' and delete it
            else {                        // No ')' found, syntax error occurred
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            int rs = getReg(p);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(offset, 16, obj);
            obj << endl;
        }
        else if (!strcmp(command, "sw")){ // SW $rt, offset($rs)
            printBin(0x2B, 6, obj);      // OpCode

            code.getline(arg1, 20, ',');
            int rt = getReg(arg1);
            if (rt == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            code.getline(arg2, 20);
            int offset = 0;
            int sign = 1;
            char *p = arg2;

            while (*p == ' ') p++;
            if (*p == '-'){
                p++;
                sign = -1;
            }
            // Parse
            while (*p >= '0' && *p <= '9'){
                offset = 10 * offset + (*p - '0');
                p++;
            }
            offset = sign * offset;

            while (*p == ' ') p++;        // Skip the space before '('
            if (*p == '(') p++;
            else {
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            char *q = arg2 + (strlen(arg2) - 1);
            while (*q == ' ') q--;
            if (*q == ')') *q = '\0';    // Find the ')' and delete it
            else {                       // No ')' found, syntax error occurred
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            int rs = getReg(p);
            if (rs == -1){
                cout << "Syntax error at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(rs, 5, obj);
            printBin(rt, 5, obj);
            printBin(offset, 16, obj);
            obj << endl;
        }
        else if (!strcmp(command, "j")){ // J addr
            printBin(0x02, 6, obj);      // OpCode

            int addr;
            code >> addr;
            if (addr < 0){               // Negative address is not allowed
                cout << "Invalid address at Line " << line_no << "." << endl;
                code.close();
                obj.close();
                exit(-1);
            }

            printBin(addr, 26, obj);
            obj << endl;
        }
        else if (!strcmp(command, "nop")){ // NOP
            printBin(0, 32, obj);
            obj << endl;
        }
        else {                            // No other instructions allowed
            cout << "Invalid instruction at Line " << line_no << "." << endl;
            code.close();
            obj.close();
            exit(-1);
        }
    }

    code.close();
    obj.close();

    return 0;
}
