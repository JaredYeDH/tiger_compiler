1.
�ѽ�� else �ƽ���Լ��ͻ �� ����� `if exp then exp` �﷨

ֱ�����if then �﷨����Ȼ���ڳ�ͻ������Ϊ�޺���ͻ������Ҫ�޸ġ�

2.
%prec ��ʹ��

#### 3.
`tyassign , tyfields,args` �����Ʒ��ս����������д���
	

4.
����� a+b*c   a:=b+c �����Ƶ��ƽ���Լ��ͻ���⣬��Ҫ������Ӧ�����������ȼ�(����of do)

5.
��� `lvalue [exp]` �� `id [exp] of exp` ���ƽ���Լ��ͻ���⣺
���ǰ��
<code>
	lvalue:		ID 	
		|		lvalue DOT ID	 
		|		lvalue LBRACK exp RBRACK  

	array: 		ID LBRACK exp RBRACK OF exp </code>

�����
<code>
	lvalue:		ID 		
		|		lvalue DOT ID	
		|		ID LBRACK exp RBRACK  bracklist

	bracklist: 	LBRACK exp RBRACK bracklist
		| 

	array: 		ID LBRACK exp RBRACK OF exp </code>

#### 6.
δ��ӹ��ܣ�����ָ�

