#ifndef _TRANS_H
#define _TRANS_H

#include "temp.h"
#include "frame.h"

typedef struct Tr_level_ *Tr_level;
typedef struct Tr_access_ *Tr_access;
typedef struct Tr_accessList_ *Tr_accessList;

struct Tr_level_ {
	Tr_level parent;
	Temp_label name;
	F_frame frame; //ΪɶҪ���????????? ----- ����ֲ�������frame����count,���ڳ���
	Tr_accessList formals;
};
struct Tr_access_ {
	Tr_level level; F_access access;
};
struct Tr_accessList_ {
	Tr_access head; Tr_accessList tail;
};

Tr_level Tr_outermost(); //���ò���...

Tr_accessList Tr_AccessList(Tr_access head, Tr_accessList tail);  //Ϊɶ���ֲ��Ǿ�̬��?
Tr_level Tr_NewLevel(Tr_level parent, Temp_label name, U_boolList formals);
Temp_label Tr_name(Tr_level l);    ///����û�����������������������
Tr_accessList Tr_formals(Tr_level l);
Tr_access Tr_allocLocal(Tr_level l, bool escape);

#endif