#include "translate.h" 

static Tr_access Tr_Access(Tr_level l, F_access access);
static Tr_accessList MakeFormalsAccessList(Tr_level l);


Tr_level NewLevel(Tr_level parent, Temp_label name, U_boolList formals) {
	Tr_level l = checked_malloc(sizeof(*l));
	l->parent = parent; l->name = name; 
	l->frame = F_NewFrame(name, U_BoolList(TRUE, formals));  //����һ����֡ջ,��һ��λ��Ϊ��̬����Ϊ���ݵģ�Ϊɶ��Ҫ? parent��ɶ����
	l->formals = MakeFormalsAccessList(l);      //// Tr_accessList �� ֡ջ ��ϵ ��̫�����������
	return l;
}

static Tr_level outermost = NULL;
Tr_level Tr_outermost() {
	if (!outermost) { return NewLevel(NULL, Temp_newlabel(), NULL); } 
	//Ϊɶ��Temp_newlabel()����NULL??
	return outermost;
}
Temp_label Tr_name(Tr_level l) {  //����û�У���
	return l->name;
}
Tr_accessList Tr_formals(Tr_level l) {
	return l->formals;
}

Tr_access Tr_Access(Tr_level l, F_access access) {
	Tr_access a = checked_malloc(sizeof(*a));
	a->level = l;a->access = access;
	return a;
}
Tr_accessList Tr_AccessList(Tr_access head, Tr_accessList tail) { //Ϊɶ���ֲ��Ǿ�̬��?
	Tr_accessList al = checked_malloc(sizeof(*al));
	al->head = head;al->tail = tail;
	return al;
}

Tr_accessList MakeFormalsAccessList(Tr_level l) {
	Tr_accessList head = NULL, tail = NULL;
	Tr_access a = NULL;
	F_accessList al = l->frame->formals->tail; //���Ե�һ����������̬����������Tr_accessList ������̬����///Ϊɶ����������
	while (al) {			
		a = Tr_Access(l, al->head);
		if (head) {
			tail = Tr_AccessList(a, NULL);
			tail = tail->tail;
		}
		else {
			head = Tr_AccessList(a, NULL);
			tail = head->tail;
		}
		al = al->tail;
	}
	return head;
}
Tr_access Tr_allocLocal(Tr_level l, bool escape) {
	F_access F_a = F_allocLocal(l->frame, escape);
	return Tr_Access(l, F_a);
}
