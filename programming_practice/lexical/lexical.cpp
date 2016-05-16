// lexical.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lexical.h"
#include <iostream>
using namespace std;

#define getchdo (ch=getchar())  //��ȡһ���ַ�
#define MAX 20  //��ʶ������󳤶�

enum symbol {
	nul, ident, number, plus_, minus_,
	times, odd, backslash, eql, neq,
	lss, leq, gtr, geq, lparen,
	rparen, comma, semicolon, period, becomes,
	beginsym, endsym, ifsym, thensym, whilesym,
	writesym, readsym, dosym, callsym, constsym,
	varsym, procsym
};
char symbol[][10] = {
	"nul", "ident", "number", "plus", "minus",
	"times", "odd", "backslash", "eql", "neq",
	"lss", "leq", "gtr", "geq", "lparen",
	"rparen", "comma", "semicolon", "period", "becomes",
	"beginsym", "endsym", "ifsym", "thensym", "whilesym",
	"writesym", "readsym", "dosym", "callsym", "constsym",
	"varsym", "procsym"
};
char word[][10] = {
	"begin","end","if","then","while","write","read","do","call","const","var","procedure"
};
char chr[] = {
	'+','-','*','/','\\','=','#','(',')',',',';','.'
};
int wsym[] = { beginsym,endsym,ifsym,thensym,whilesym,writesym,readsym,dosym,callsym,constsym,varsym,procsym };
int csym[] = { plus_,minus_,times,odd,backslash,eql,neq,lparen,rparen,comma,semicolon,period };

char ch = 32;  //��ȡ�ַ����˱���
char a[MAX + 1];
char id[MAX + 1];
int sym; //�������
int num; //������ֵ
int cp;  //�ַ���ָ��

int getsym() {
	while (ch == 32 || ch == 9 || ch == 10 || ch == 13)  //���Կհ׷�
		getchdo;
	if (ch >= 'a'&&ch <= 'z') {   //��ʶ��
		cp = 0;
		while (ch >= 'a'&&ch <= 'z') {   //ȡ��ĸ
			a[cp++] = ch;
			getchdo;
		}
		a[cp] = '\0';
		strcpy(id, a);
		int k;
		k = searchw(id);      //Ѱ���Ƿ��Ǳ�����
		if (k != -1)
			sym = wsym[k];   //ȡ��������
		else
			sym = ident;  //����Ϊ��ʶ��
	}
	else if (ch >= '0'&&ch <= '9') {   //������ֵ
		cp = 0;
		while (ch >= '0'&&ch <= '9') {   //ȡ����
			a[cp++] = ch;
			getchdo;
		}
		a[cp] = '\0';
		strcpy(id, a);
		sym = number;  //����Ϊ��������
		num = atoi(id); //ת���ַ���Ϊ����
	}
	else if (ch == ':') {
		getchdo;
		if (ch == '=') {
			sym = becomes;
			getchdo;
		}
		else
			sym = nul;
	}
	else if (ch == '<') {
		getchdo;
		if (ch == '=') {
			sym = leq;
			getchdo;
		}
		else
			sym = lss;
	}
	else if (ch == '>') {
		getchdo;
		if (ch == '=') {
			sym = geq;
			getchdo;
		}
		else
			sym = gtr;
	}
	else {
		int k = searchc(ch);
		sym = csym[k];
		getchdo;
	}
}

int searchw(char *a) {
	for (int i = 0;i<12;i++) {
		if (strcmp(a, word[i]) == 0)
			return i;
	}
	return -1;
}
int searchc(char a) {
	for (int i = 0;i<12;i++) {
		if (a == chr[i])
			return i;
	}
	return -1;
}

int main()
{
	while (ch != '@') {
		getsym();
		if (sym == ident)
			cout << symbol[sym] << "\t" << id << endl;
		else if (sym == number)
			cout << symbol[sym] << "\t" << num << endl;
		else
			cout << symbol[sym] << endl;
	}

	return 0;
}
