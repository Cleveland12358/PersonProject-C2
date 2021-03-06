#pragma once
#include "pch.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include<map>
using namespace std;
string b;
extern int j;
extern int count_;
extern vector<string> str;
extern vector<string> str_shorted;
extern map<string, int> strmap;
extern map<string, int>::iterator q;
extern ofstream d;
extern string a;
extern int w;
extern int max;
extern bool flag1;

int tem = 0;

inline char ToLower(const char &c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 32;
}

void agefile(string filename)//打开文件统计字符函数
{
	char c;
	ifstream s(filename);
	if (!s)
	{
		cout << "error" << endl;
		flag1 = false;
	}
	while (s.get(c))//采用get函数读取字符
	{
		b += ToLower(c);
		++j;
	}
	if (flag1 == true)
	{
	//	cout << "characters: " << j << endl; //输出字符数
		d << "characters: " << j << endl; //输出字符数
	}
	else
	{
		d << "error" << endl;
	}
}
void count_all()//统计单词数以及行数函数
{
	string buf;
	bool notempty;
	int i;
	string lineBuf;
	for (i = 0; i < j; i++)
	{
		if (b[i] == '\n')
		{
			for (int s3 = 0; s3 != lineBuf.size(); s3++)
			{
				if (lineBuf[s3] > 32)
				{
					count_++;
					break;
				}
			}
			lineBuf.clear();
		}
		else
		{
			lineBuf += b[i];
		}

		if ((b[i] >= '0'&&b[i] <= '9') ||
			(b[i] >= 'A' && b[i] <= 'Z') ||
			(b[i] >= 'a' && b[i] <= 'z'))//遇到数字、字母存起来
		{
			buf += b[i];
		}
		else//分隔符
		{
			if (buf != "")
			{
				str.push_back(buf);
				buf.clear();
			}
		}
	}
	if (buf != "")
	{
		for (int k3 = 0; k3 < buf.size(); k3++)
		{
			if (buf[k3] > 32)//判断全空格的情况
				notempty = true;
		}
		if (notempty == true)
			count_++;

		str.push_back(buf);
		buf.clear();
	}

	for (i = 0; i < str.size(); i++)
	{
		bool flag = false, flag4 = false;
		for (int k = 0; k < str[i].size(); k++)
		{
			if (str[i][k] > 32)
				flag = true;
		}
		if (   (str[i][0] >= 'a' && str[i][0] <= 'z') 
			&& (str[i][1] >= 'a' && str[i][1] <= 'z')
			&& (str[i][2] >= 'a' && str[i][2] <= 'z')
			&& ( str[i][3] >= 'a' && str[i][3] <= 'z'))
		{
			flag = true;
			flag4 = true;
		}

		if (str[i].size() > 3 && flag == true && flag4 == true)//剔除4个字母以下
		{
			str_shorted.push_back(str[i]);
		}
	}

	for (i = 0; i < str_shorted.size(); i++)
	{
		strmap[str_shorted[i]]++;
	}
//	cout << "words: " << str_shorted.size() << endl;
//	cout << "lines: " << count_ << endl;//输出

	d << "words: " << str_shorted.size() << endl;
	d << "lines: " << count_ << endl;//输出

}

void addword(bool flag = true)//统计单词数词频最多的10个单词以及输出单词
{
	int max = -999;
	bool flag2 = false;
	q = strmap.begin();
	int min_val = strmap.size() < 10 ? strmap.size() : 10;
	for (int s1 = 0; s1 < min_val; s1++)//采用遍历10次的的方式，如果不足十次bool值置false跳出循环
	{
		flag2 = false;
		if (flag == false)
		{
			break;
		}
		flag = true;
		max = -999;
		while (q != strmap.end())//采用map函数进行存取遍历
		{
			if (q->second > max)
			{
				flag2 = true;
				max = q->second;
				a = q->first;
			}
			q++;
		}
		if (flag2 == true)
		{
	//		cout << "<" << a << ">: " << max << endl;
			d << "<" << a << ">: " << max << endl;
		}
		q = strmap.begin();
		strmap[a] = -10;
	}
}

#pragma once
