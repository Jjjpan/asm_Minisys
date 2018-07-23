#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<set>
#include<map>
#include"initial.h"

using namespace std;
map<string,int> name_line;

int getImme_LUI(char *arg)
{
    int reg;
    char* p=arg;
    while(*p==' ')p++;
    while(*p >= '0' && *p <= '9'){
        reg = 10 * reg + (*p - '0');
        p++;
    }
    while (*p == ' ') p++;
    if (*p != '\0') return -1;           // Unexpected characters
    else return reg;

}

int getImme_I(char* arg)
{
    int reg;
    char* p=arg;
    while (*p!='\0'&&*p!=',')p++;
    p++;
    while (*p!='\0'&&*p!=',')p++;
    if(*p=='\0')return -1;
    p++;
    while(*p==' ')p++;
    while(*p >= '0' && *p <= '9'){
        reg = 10 * reg + (*p - '0');
        p++;
    }
    while (*p == ' ') p++;
    if (*p != '\0') return -1;           // Unexpected characters
    else return reg;

}

int getImme_J(char* arg)
{
    char* p=arg;

    char* q=arg;
    while(*p==' ')p++;
    while(*p != '\0' && *p != ' '){
        *q=*p;
        p++;
        q++;
    }
    *q='\0';

    while (*p == ' ') p++;
    if (*p != '\0')
    {
        return -1;
    }          // Unexpected characters

    else

        return q-arg-2;

}

int getReg(char* arg,int n){
    char reg[50];
    int m=0;
    char *p = arg;
    while (*p == ' ') p++;       // Skip the space at the beginning
    while(m<=n&&*p!='\0')
        {
            if (*p == '$')
            {
                m++;
            }
            p++;
        }
    while(*p==' ')p++;
    if(*p=='\0')
        return -1;              // Unexpected charaters
    int reg_iter=0;
    // Parse
    while(*p != '\0' && *p != ','&&*p!=' '){
        reg[reg_iter]=*p;
        reg_iter++;
        p++;
    }
    reg[reg_iter]='\0';
    string reg_name(reg);
    while (*p == ' ') p++;               // Skip the space following the number
    cout<<reg_name<<endl;
    cout<<reg_name_num.count(reg_name)<<endl;
    if (*p != '\0'&&*p!=',') return -1;           // Unexpected characters

    else return reg_name_num.find(reg_name)->second;
}

// Output a binary number with a given length to an object of ostream
void printBin(int num, int digi, ostream& os){
    char *bin = (char*)malloc(digi*sizeof(char)+1);
    //memset(bin, '0', digi * sizeof(char));
    for(int i=0;i<digi;i++)
        bin[i]='0';
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

int judge_format(const char* command)
{
    string command_string(command);
    return command_format.find(command_string)->second;
}

int main(void){

    string command("in");
    char line[40];
    initial_command_format();
    initial_command_opcode_functionOpcode();
    initial_reg_name_num();

    ifstream code("cputest1.asm");

    int line_no = 0;
    while(code>>command)
    {
        string temp_command=command;
        if(temp_command[0]=='.')continue;
        else
        {
            if(command_format.count(temp_command)) line_no++;
            if(temp_command.data()[temp_command.length()-1]==':')
            {
                temp_command.assign(temp_command.substr(0,temp_command.length()-1));
                cout<<temp_command<<" "<<line_no<<endl;
                name_line.insert(pair<string,int>(temp_command,line_no));
            }
            //cout<<line_no<<endl;
        }
    }
    code.close();
    const char empty_mem[9]="00000000";
    const char title_mem[100]="memory_initialization_radix = 2;";
    const char subtitle_mem[100]="memory_initialization_vector =";
    const char empty_cmd[9]="00000000";
    const char title_cmd[100]="memory_initialization_radix = 2;";
    const char subtitle_cmd[100]="memory_initialization_vector =";
    ofstream mem_write("dmem32.coe");
    ofstream obj("prgmip32.coe");

    mem_write<<title_mem<<endl<<subtitle_mem<<endl;
    obj<<title_cmd<<endl<<subtitle_cmd<<endl;
    char arg1[20], arg2[20], arg3[20];
    int rs,rt,rd,shamt,fun_op,op,immediate;
    ifstream word("cputest1.asm");


    while(word>>command)
    {
        if(command_format.count(command))
        {
            memset(line,0,sizeof(line));
            word.get(line,40,'\n');
            for(int i=0;i<40&&line[i]!='\0';i++)
                if(line[i]=='#')
                {
                    line[i]='\0';
                    break;
                }
            int format=judge_format(command.data());
            if(format==0)//ordinary R-format
            {
                rs=getReg(line,1);
                rt=getReg(line,2);
                rd=getReg(line,0);
                if (rd == -1||rt==-1||rs==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                printBin(command_opcode_functionOpcode.find(command)->second.first,6,obj);
                //cout<<command_opcode_functionOpcode.find(command)->second.first;
                printBin(rs, 5, obj);
                printBin(rt, 5, obj);
                printBin(rd, 5, obj);
                printBin(0,5,obj);
                printBin(command_opcode_functionOpcode.find(command)->second.second,6,obj);
                obj<<endl;
            }
            else if(format==1)//ordinary I-format
            {
                rs=getReg(line,1);
                rt=getReg(line,0);
                immediate=getImme_I(line);
                if (rd == -1||rt==-1||immediate==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                printBin(command_opcode_functionOpcode.find(command)->second.first,6,obj);
                printBin(rs, 5, obj);
                printBin(rt, 5, obj);
                printBin(immediate, 16, obj);
                obj<<endl;
            }
            else if(format==2)//J-format
            {
                string command_string=command;
                immediate=getImme_J(line);
                line[immediate]='\0';

                if (immediate==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                string immediate_string(line);


                immediate=name_line.find(immediate_string)->second;
                printBin(command_opcode_functionOpcode.find(command_string)->second.first,6,obj);

                printBin(immediate,26,obj);

                obj<<endl;
            }
            else if(format==3)
            {
                string command_string=command;
                rt=getReg(line,1);
                rd=getReg(line,0);
                shamt=getImme_I(line);
                if (shamt==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                printBin(command_opcode_functionOpcode.find(command_string)->second.first,6,obj);
                printBin(0,5,obj);
                printBin(rt,5,obj);
                printBin(rd,5,obj);
                printBin(command_opcode_functionOpcode.find(command_string)->second.second,6,obj);
            }
            else if(format==4)//lui
            {
                string command_string=command;
                rt=getReg(line,0);
                immediate=getImme_LUI(line);
                if (immediate==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                printBin(15,6,obj);
                printBin(0,5,obj);
                printBin(rt,5,obj);
                printBin(immediate,16,obj);
            }
            else if(format==5)//jr
            {
                string command_string=command;
                rs=getReg(line,0);
                if(rs==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                printBin(0,6,obj);
                printBin(rs,5,obj);
                printBin(0,21,obj);
            }
            else if(format==6)//lw sw
            {
                string command_string=command;
                int offset=0;
                rt=getReg(line,0);
                for(int i=0;line[i]!='\0';i++)
                    if(line[i]=='('||line[i]==')')
                        line[i]=' ';
                rs=getReg(line,1);
                if(rs==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    word.close();
                    obj.close();
                    exit(-1);
                }
                printBin(command_opcode_functionOpcode.find(command_string)->second.first,6,obj);
                printBin(rs,5,obj);
                printBin(rt,5,obj);
                printBin(offset,16,obj);
            }
        }

    }
    word.close();
    obj.close();

    return 0;
}
