// 04_02_不用strcpy函数实现两个字符串的赋值.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <process.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char strcpstring(char str1[],char str2[]);
	
    char str1[20] = "I am happy!";
	char str2[20];

	strcpstring(str1,str2);




	system("pause");


	return 0;
}
char strcpstring(char  str1[],char str2[]){


	int len = strlen(str1);  // 字符串计数

	for (int i = 0; i < len; i++)
	{
		str2[i] = str1[i];

	}	
	for (int j = 0; j < len; j++)
	{
		printf("%c", str2[j]);
	}
	printf("\n");

	return 0;

}

