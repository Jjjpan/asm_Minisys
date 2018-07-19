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

set<string> S;
map<string,int> name_line;

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
    if (*p != '\0') return -1;           // Unexpected characters
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


int main(void){
    // Check the input
    /*if (argc != 2){
        cout << "Error: File name needed." << endl;
        exit(-1);
    }
*/
    S.insert("add");
    S.insert("ori");
    ifstream code("cputest-·ÂÕæ³ÌÐò.asm");
    //char  arg1[20], arg2[20], arg3[20];
    string command;
    int line_no = 0;
    while(code>>command)
    {
        if(command[0]=='.')continue;
        else
        {
            if(S.count(command)) line_no++;
            if(command.data()[command.length()-1]==':')
            {
                command.assign(command.substr(0,command.length()-1));
                cout<<command<<" "<<line_no<<endl;
                name_line.insert(pair<string,int>(command,line_no));
            }
            //cout<<line_no<<endl;
        }
    }
    return 0;
}
