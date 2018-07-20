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

using namespace std;
    map<string,int> command_format;
    map<string,int> name_line;
    map<string,int> register_hash;
    map<string,pair<int,int>> command_opcode_functionOpcode;


int getReg(char* arg,int n){
    int reg = 0;
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
    if(*p=='\0')
        return -1;              // Unexpected charaters

    // Parse
    while(*p >= '0' && *p <= '9'){
        reg = 10 * reg + (*p - '0');
        p++;
    }
    while (*p == ' ') p++;               // Skip the space following the number
    if (*p != '\0'&&*p!=',') return -1;           // Unexpected characters
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

int judge_format(const char* command)
{
    string command_string(command);
    return command_format.find(command_string)->second;
}

int main(void){

    string command("in");
    char line[40];
    command_format.insert(pair<string,int>("add",0));
    command_format.insert(pair<string,int>("ori",1));
    command_format.insert(pair<string,int>("j",2));
    pair<int,int> test_pair(1,2);
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("add",test_pair));//false!
    ifstream code("cputest.asm");

    int line_no = 0;
    while(code>>command)
    {
        if(command[0]=='.')continue;
        else
        {
            if(command_format.count(command)) line_no++;
            if(command.data()[command.length()-1]==':')
            {
                command.assign(command.substr(0,command.length()-1));
                cout<<command<<" "<<line_no<<endl;
                name_line.insert(pair<string,int>(command,line_no));
            }
            //cout<<line_no<<endl;
        }
    }
    code.close();
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
    char arg1[20], arg2[20], arg3[20];
    int rs,rt,rd,shamt,fun_op,op,immediate;
    ifstream word("cputest.asm");

    while(word>>command)
    {
        if(command_format.count(command))
        {
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
                rs=getReg(line,0);
                rt=getReg(line,1);
                rd=getReg(line,2);
                if (rd == -1||rt==-1||rs==-1)
                {
                    cout << "Syntax error at Line " << line_no << "." << endl;
                    code.close();
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
            }
            else if(format==1)//ordinary I-format
            {
                rs=getReg(line,0);
                rt=getReg(line,1);
            }
            else if(format==2)//J-format
            {

            }
        }

    }


    return 0;
}