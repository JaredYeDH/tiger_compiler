1. `lvalue [exp]` �� `id [exp] of exp` ���ƽ���Լ��ͻ���⣺

�ڵ����µĽ���������޳�ͻ��ֻ�������﷨�����׶Σ������ɳ����﷨�Ľ׶λ��������
�����½����
���ǰ��(�к���ͻ)
<code>
	 lvalue:	ID 	
		|		lvalue DOT ID	 
		|		lvalue LBRACK exp RBRACK  

	array: 		ID LBRACK exp RBRACK OF exp </code>

�����(�޳�ͻ)
<code>
	lvalue:		ID 		
		|		lvalue DOT ID	
		|		ID LBRACK exp RBRACK  bracklist

	bracklist: 	LBRACK exp RBRACK bracklist
		| 

	array: 		ID LBRACK exp RBRACK OF exp </code>

������Ҫ���ɳ����﷨�������֮ǰ���ķ�����Ҫ��`bracklist`һ�����ͣ���������Ҫ�������͡�

�����޸�`lvalue` ��`array`�Ķ��壬��ɾ��`bracklist`���������ƽ����޺���ͻ��
<code>
	lvalue:		ID 
		|		lvalue DOT ID
		|		ID LBRACK exp RBRACK 
		|		lvalue LBRACK exp RBRACK

	array: 		ID LBRACK exp RBRACK OF exp  </code>

�޸�֮����Ȼû�н���ƽ���Լ��ͻ���⣬����֮ǰ��Ϊ�к���ͻ���޸�֮���Ϊ�޺���ͻ�����ȿ����ƽ�������Ӱ���﷨������Ҳ����Ҫ������������͡�


2. ĳЩ�ս����������ֵ����Ҫָ����������ͣ��Ӷ�ʹ$���������С�
   ���еķ��ս������Ҫָ�������ͣ�������ʼ����

3. ������� undefined reference to `A_StringExp' ��

	ԭ�� δ��makefile��������� absyn.o �����Ƶ�Ŀ���ļ���ϵͳ�޷��������ӡ� �����csapp

4. ѧϰ��makefile��ʹ��

5. �����ظ��������������Ҫ��absyn.h�м��� ifndef

6. ���������ܣ��ܴ�ӡ��һ��Դtig�ļ������ĳ����﷨��