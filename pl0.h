#include <stdio.h>

/*
no.		����	��Ŀ
max.	����	���


pl/0 ���е��﷨:
	�������͡���������
		const var procedure

	����ṹ
		begin end
		if then
		while do
		call procedure
	
*/

// �궨�� 

// atl
#define norw       20             // �����ֵ���Ŀ

#define txmax      100            // ���ű�ĳ���
#define nmax       14             // ���ֵ���󳤶�
#define al         10             // ��ʶ������󳤶�
#define amax       2047           // ��Ե�ַ�����ֵ0-2048
#define levmax     3              // ���Ƕ�ײ���
#define cxmax      2000           // ����Ŀ�����p-code�������󳤶�

#define nul	   0x1					// ASCII�ַ�Ĭ�ϵ�symbol���ͣ�˵��������������ַ�/�ַ���������?
#define ident      0x2				// ��ĸ��ͷ�����ִ�
#define number     0x4				// �޷�����������ʵ���������С����ǰ���зǿ����ִ�����ʽ

/* ��һ����һЩ�궨�壬����symbol���� */
// �����
#define plus       0x8				// +
#define minus      0x10				// -
#define times      0x20				// *

// atl
#define divsym     0x30				// div
#define modsym	   0x50				// mod

#define slash      0x40				// /
#define eql        0x100			// =
#define neq        0x200			// <>
#define lss        0x400			// <
#define leq        0x800			// <=
#define gtr        0x1000			// >
#define geq        0x2000			// >=

// atl
#define true 	   0x300			// true
#define false 	   0x500			// false
#define and		   0x3000			// and
#define or		   0x5000			// or
#define not	 	   0x7000			// not

#define lparen     0x4000			// (
#define rparen     0x8000			// )
#define comma      0x10000			// ,
#define semicolon  0x20000			// ;
#define period     0x40000			// .

#define becomes    0x80000			// := ��ֵ����

// ������ 11 �� ��Ӧwsym����
#define beginsym   0x100000			// begin
#define endsym     0x200000			// end
#define ifsym      0x400000			// if

// atl
#define elsesym    0x800000 		// else


#define oddsym     0x80				// ���ú���odd()��Ҳ����������
#define thensym    0x800000			// then
#define whilesym   0x1000000		// while
#define dosym      0x2000000		// do
#define callsym    0x4000000		// call
#define constsym   0x8000000		// const
#define varsym     0x10000000		// var
#define procsym    0x20000000		// procedure

// atl
#define exitsym    0x40000000		// exit


// ��������Ͱ������֣�����������������
enum object {
    constant, variable, proc, integer, real, Boolean
};


// �м����p-code��ָ�����ͣ��� 8 ��
enum fct {
    lit, 
	opr, 
	lod, 
	sto, 
	cal, 
	Int, 
	jmp, 
	jpc, 
	/*
	red, 
	wrt
	*/
};

// �������p-codeָ��Ľṹ��
typedef struct{
    enum fct f;		// ������ (fct�е�һ��)
    long l; 		// Ƕ�ײ�� (��ʶ�����ò��ȥ�����)
    long a; 		// ƫ�Ƶ�ַ/... ����ͬ��ָ��岻ͬ��
} instruction;


/* 
	lit 0, a : ȡ����a�ŵ�����ջջ��
    opr 0, a : ִ�����㣬a��ʾִ�к�������(+ - * /)
    lod l, a : ȡ�����ŵ�����ջջ��(��Ե�ַΪa,��β�Ϊl)
    sto l, a : ������ջջ�����ݴ������(��Ե�ַΪa,��β�Ϊl)
    cal l, a : ���ù���(���ָ���ַΪa,��β�Ϊl)
    Int 0, a : ����ջջ��ָ������a
    jmp 0, a : ������ת�Ƶ�ָ���ַa
    jpc 0, a : ����ת�Ƶ�ָ���ַa
	red l, a : �����ݲ����������
    wrt 0, 0 : ��ջ���������
	
	opr 0, 0 : ���̵��ý�����,���ص��õ㲢��ջ
	opr 0, 1 : ջ��Ԫ��ȡ�� (~)
	opr 0, 2 : ��ջ����ջ����ӣ�������ջԪ�أ����ֵ��ջ (�൱��+?)
	opr 0, 3 : ��ջ����ȥջ����������ջԪ�أ����ֵ��ջ (-)
	opr 0, 4 : ��ջ������ջ����������ջԪ�أ����ֵ��ջ (*)
	opr 0, 5 : ��ջ������ջ����������ջԪ�أ����ֵ��ջ (/)
	opr 0, 6 : ջ��Ԫ�ص���ż�жϣ����ֵ��ջ�� (odd())
	opr 0, 7 : 
	opr 0, 8 : ��ջ����ջ���Ƿ���ȣ�������ջԪ�أ����ֵ��ջ (==)
	opr 0, 9 : ��ջ����ջ���Ƿ񲻵ȣ�������ջԪ�أ����ֵ��ջ (!=)
	opr 0, 10 : ��ջ���Ƿ�С��ջ����������ջԪ�أ����ֵ��ջ (<)
	opr 0, 11 : ��ջ���Ƿ���ڵ���ջ����������ջԪ�أ����ֵ��ջ (>=)
	opr 0, 12 : ��ջ���Ƿ����ջ����������ջԪ�أ����ֵ��ջ (>)
	opr 0, 13 : ��ջ���Ƿ�С�ڵ���ջ����������ջԪ�أ����ֵ��ջ (<=)

	opr 0, 14 : ջ��ֵ�������Ļ
	opr 0, 15 : ��Ļ�������
	opr 0, 16 : �������ж���һ����������ջ��
*/

// ȫ�ֱ�������
char ch;               // ��������� һ���ַ�
unsigned long sym;     // ��������� ����symbol/���� ������
char id[al+1];         // ��������� ��ʶ��
long num;              // ��������� ����
long cc;               // �л���ָ��(index)
long ll;               // �л���������(length)
long kk, err;		   // ���ڴ����������ı���( err�������; kk��/��������ʶ���ʶ�����ȴ���10�ȳ������? ) 
long cx;               // �м����ָ��(��index������)?

char line[81];				// ����һ�д���
char a[al+1];				// �����洢��ʶ��������
instruction code[cxmax+1];	// �����洢�м����p-code�����飬�������Ϊ cxmax+1
char word[norw][al+1];		// �洢�����ʵ��ַ������飬��һάΪ�ؼ��ʵ��ַ����飬�ڶ�ά��Ϊ�ַ�������

unsigned long wsym[norw];	// �����ֱ���ÿ�������ֶ�Ӧ��symbol����
unsigned long ssym[256];	// ASCII���Ŷ�Ӧ��symbol����?


// mnemonic [ni'm��nik] p-codeָ������Ƿ�����
char mnemonic[8][3+1];

// ���� ������ʼ����俪ʼ���ʼ(���ʽ) �ķ��ż���
unsigned long declbegsys, statbegsys, facbegsys;

// ���ű�����
struct{
    char name[al+1];	// ����Ԫ�ص�����
    enum object kind;	// ���ݷ���symbol�����ͱ�����Ӧ����Ϣ
    long val;			// ����ǳ�����val�б��泣����ֵ
    long level;			// ����Ǳ�������̣������Ų����� ���м���룩��ʼ��ַ��ƫ�Ƶ�ַ
    long addr;
} table[txmax+1];

// pl0�ļ���·��
char infilename[80];
// pl0�ļ�ָ��
FILE* infile;

// �﷨�������õ��ı���
long dx;		// ���ݵ�ַ����
long lev;		// �﷨�������ڲ��
long tx;		// tx�ǵ�ǰ���ű�ָ�루������

// Ϊ���ͳ��� Ԥ�� �ռ䣨һ������ջ��
#define stacksize 50000
long s[stacksize];	// datastore

