#pragma once
#ifndef QUATERNION_H
#define QUATERNTION_H
#include"head.h"


struct var {	//变量
	string name = "\0";	//变量名
	int value = 0;	//变量值
	char i = '\0';	//对应的终结符号或非终结符号
};

struct quatern{	//四元式
	string op;
	string arg1;
	string arg2;
	string result;
};

#endif // !QUATERNION_H

