#pragma once
#ifndef PARAMETER_H
#define PARAMETER_H
#include<string>
#include<iostream>

extern std::string IV;
std::string hashdata(int num,std::string iv=IV);
std::string hashdata(std::string num,bool a,std::string iv=IV);
std::string padding(std::string str);		//padding the data,input is binary
std::string dectohex(int dec);		//turn dec to hex
std::string hextobin(std::string str);//turn hex to bin
std::string bintohex(std::string str); //turn bin to hex
std::string dectobin(int str);		//turn dec to bin
std::string iteration(std::string str, std::string iv);		//iteration function
std::string LenExtAttack(std::string md1, int len, std::string m3);		//length extension attack
#endif
