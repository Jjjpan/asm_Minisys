#ifndef INITIAL_H_INCLUDED
#define INITIAL_H_INCLUDED
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
    map<string,int> reg_name_num;
    map<string,int> register_hash;
    map<string,pair<int,int> > command_opcode_functionOpcode;
    map<string,pair<int,int> > name_high_low;
void initial_command_format(void)
{
    command_format.insert(pair<string,int>("add",0));
    command_format.insert(pair<string,int>("addu",0));
    command_format.insert(pair<string,int>("sub",0));
    command_format.insert(pair<string,int>("subu",0));
    command_format.insert(pair<string,int>("and",0));
    command_format.insert(pair<string,int>("or",0));
    command_format.insert(pair<string,int>("xor",0));
    command_format.insert(pair<string,int>("nor",0));
    command_format.insert(pair<string,int>("slt",0));
    command_format.insert(pair<string,int>("sltu",0));
    command_format.insert(pair<string,int>("sllv",0));
    command_format.insert(pair<string,int>("srlv",0));
    command_format.insert(pair<string,int>("srav",0));
    command_format.insert(pair<string,int>("sll",3));
    command_format.insert(pair<string,int>("srl",3));
    command_format.insert(pair<string,int>("sra",3));
    command_format.insert(pair<string,int>("jr",5));
    command_format.insert(pair<string,int>("addi",1));
    command_format.insert(pair<string,int>("addiu",1));
    command_format.insert(pair<string,int>("andi",1));
    command_format.insert(pair<string,int>("ori",1));
    command_format.insert(pair<string,int>("xori",1));
    command_format.insert(pair<string,int>("lw",6));
    command_format.insert(pair<string,int>("sw",6));
    command_format.insert(pair<string,int>("beq",6));
    command_format.insert(pair<string,int>("bne",6));
    command_format.insert(pair<string,int>("slti",1));
    command_format.insert(pair<string,int>("sltiu",1));
    command_format.insert(pair<string,int>("lui",4));
    command_format.insert(pair<string,int>("j",2));
    command_format.insert(pair<string,int>("jal",2));
    return;
}

void initial_command_opcode_functionOpcode(void)
{
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("add",make_pair(0,32)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("addu",make_pair(0,33)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sub",make_pair(0,34)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("subu",make_pair(0,35)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("and",make_pair(0,36)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("or",make_pair(0,37)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("xor",make_pair(0,38)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("nor",make_pair(0,39)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("slt",make_pair(0,42)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sltu",make_pair(0,43)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sll",make_pair(0,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("srl",make_pair(0,2)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sra",make_pair(0,3)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sllv",make_pair(0,4)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("srlv",make_pair(0,6)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("srav",make_pair(0,7)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("jr",make_pair(0,8)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("addi",make_pair(8,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("addiu",make_pair(9,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("andi",make_pair(12,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("ori",make_pair(13,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("xori",make_pair(14,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("lui",make_pair(15,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("lw",make_pair(35,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sw",make_pair(43,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("beq",make_pair(4,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("bne",make_pair(5,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("slti",make_pair(10,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("sltiu",make_pair(11,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("j",make_pair(2,0)));
    command_opcode_functionOpcode.insert(pair<string,pair<int,int> >("jal",make_pair(3,0)));
    return;
}

void initial_reg_name_num(void)
{
    reg_name_num.insert(pair<string,int>("zero",0));
    reg_name_num.insert(pair<string,int>("at",1));
    reg_name_num.insert(pair<string,int>("v0",2));
    reg_name_num.insert(pair<string,int>("v1",3));
    reg_name_num.insert(pair<string,int>("a0",4));
    reg_name_num.insert(pair<string,int>("a1",5));
    reg_name_num.insert(pair<string,int>("a2",6));
    reg_name_num.insert(pair<string,int>("a3",7));
    reg_name_num.insert(pair<string,int>("t0",8));
    reg_name_num.insert(pair<string,int>("t1",9));
    reg_name_num.insert(pair<string,int>("t2",10));
    reg_name_num.insert(pair<string,int>("t3",11));
    reg_name_num.insert(pair<string,int>("t4",12));
    reg_name_num.insert(pair<string,int>("t5",13));
    reg_name_num.insert(pair<string,int>("t6",14));
    reg_name_num.insert(pair<string,int>("t7",15));
    reg_name_num.insert(pair<string,int>("s0",16));
    reg_name_num.insert(pair<string,int>("s1",17));
    reg_name_num.insert(pair<string,int>("s2",18));
    reg_name_num.insert(pair<string,int>("s3",19));
    reg_name_num.insert(pair<string,int>("s4",20));
    reg_name_num.insert(pair<string,int>("s5",21));
    reg_name_num.insert(pair<string,int>("s6",22));
    reg_name_num.insert(pair<string,int>("s7",23));
    reg_name_num.insert(pair<string,int>("t8",24));
    reg_name_num.insert(pair<string,int>("t9",25));
    reg_name_num.insert(pair<string,int>("i0",26));
    reg_name_num.insert(pair<string,int>("i1",27));
    reg_name_num.insert(pair<string,int>("gp",28));
    reg_name_num.insert(pair<string,int>("s9",28));
    reg_name_num.insert(pair<string,int>("sp",29));
    reg_name_num.insert(pair<string,int>("s8",30));
    reg_name_num.insert(pair<string,int>("fp",30));
    reg_name_num.insert(pair<string,int>("ra",31));
    for(int i=0;i<32;i++)
        reg_name_num.insert(pair<string,int>(to_string(i),i));

    return;
}
#endif // INITIAL_H_INCLUDED
