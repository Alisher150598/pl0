// �������м�����pl/0������

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "pl0.h"

// �ڶ��������������
void error(long n){
    long i;

    printf(" ****");
	// �����һ�οհ��ַ����������λ��ʱֹͣ
    for (i=1; i<=cc-1; i++){
		printf(" ");
    }
	// cc��ָ����λ��?
	// ������ʾ��Ϣ��'^'ָ�����λ�ã�����ʾ�������ͺ�
    printf("^%2d\n",n);
    err++;
}

// ����������ȡһ���ַ�
void getch() {
	// ll�����л��������ȣ��������һ�еĳ���
	// �����ʾ��������һ��(��ָ������г������)
    if(cc==ll){
		// feof���Ը����� stream ���ļ�������ʶ��
		if( feof(infile) ){
			// ����������ļ�ĩβ��������������
			printf("************************************\n");
			printf("      program incomplete\n");
			printf("************************************\n");
			exit(1);
		}
		// ���г��ȡ���ָ������
		ll=0; cc=0;
		// ��������ַ�����Ϊ4
		printf("%5d ", cx);
		// ��û�е���ĩʱ����������ÿһ���ַ������Ҵ洢��line(����������)ȥ��ͬʱ�г�������
		while( (!feof(infile)) && ((ch=getc(infile))!='\n') ){
			printf("%c",ch);
			ll=ll+1; line[ll]=ch;
		}
		// ����
		printf("\n");
		// ��� ��������������һ��Ԫ�� Ϊ�ո�
		ll=ll+1; line[ll]=' ';
    }
	// �ƶ��л���ָ�룬ָ������е���һ���ַ�
    cc=cc+1; ch=line[cc];
}

// ���Ĳ����ʷ�����
void getsym(){
	// ������������
    long i,j,k;

	// ��ǰ�ַ�Ϊ' '��'\t'��������ȡ��һ���ַ�
    while(ch==' '||ch=='\t'){
		getch();
    }
	// ���дʷ�����
	// ���ʶ����ĸ����ô�п����Ǳ����ֻ��ʶ��
    if( isalpha(ch) ){
		// k������������ʾ��ǰ���ʵĳ���
		k=0;
		do{
			// ������� С�� ���ı�ʶ�����ȣ����������ַ�
			if(k<al){
				// a: �����洢��ʶ�������顣a���ϴ洢��ʶ�����ַ���������������
				a[k]=ch; k=k+1;
			}
			// ������ȡ��һ���ַ�
			getch();

		// ��ʶ�����ַ��Ժ������ ��ĸ������
		} while( isalpha(ch)||isdigit(ch) );
		// ������ʵļ��� > kk(kk�����б�ʶ������󳤶ȣ���ʼΪ10)
		if(k>=kk){
			kk=k;
		}else{
		// ���� �洢��ʶ������a ��kλ����ַ� ��Ϊ�ո��������������Ƿ�ֹ��һ����ʶ������a�е�����Ӱ�쵽��ǰ��ʶ����������һ����ʶ��Ϊ��qwerty�������ڵı�ʶ��Ϊ��abcd������������λ��a�лᱣ��"abcdty"������Ȼ�Ǵ����
			do{
				kk=kk-1; a[kk]=' ';
			} while(k<kk);
		}
		// id����������� ��ʶ��

		// ���ｫa�����еı�ʶ���ַ��������Ƶ�id�����У�Ϊ�������еı����ֽ��бȽϣ���ȷ���ոն����ĵ����ǲ��� ������֮һ
		strcpy(id,a); i=0; j=norw-1;
		// ���ֲ��ұ����ֱ���j��Ϊ�����ֵ������Ŀ
		do{
			// k��Ϊ���ֲ��ҵ��м����
			k=(i+j)/2;
			// ����ǰ����С�ڻ���ڱ����ֱ��еĵ�k����������ж����ݵ����ֵ�����ô�����Ʋ���ű�/�����������飩�ǰ����ֵ��򱣴��
			if(strcmp(id,word[k])<=0){
				j=k-1;
			}
			// ����ǰ��ʶ�����ڻ���ڱ����ֱ��еĵ�k��
			if(strcmp(id,word[k])>=0){
				i=k+1;
			}
		// ���ҽ�������Ϊi>j
		} while(i<=j);

		// �ҵ���ƥ��Ĺؼ���
		if(i-1>j){
			// ���ҵ��ı��������͸���sym(��������� ��������)
			sym=wsym[k];
		}else{
		// �����ʾδ�ҵ�ƥ�䣬��sym��Ϊident���ͣ���ʾ�Ǳ�ʶ��
			sym=ident;
		}
	// ������ַ������֣���ʾ������ʿ����� ���� ����
	} else if( isdigit(ch) ) { 
		// �����k������¼���ֵ�λ��
		k=0;
		// num�������ֵ�ֵ
		num=0;
		// ����ʶ������������Ϊ����
		sym=number;
		do{
			// �������ַ�ת��Ϊ���֣���ƴ�������ӵ�num��
			num = num*10+(ch-'0');
			// k++
			k = k+1;
			// ������һ���ַ�
			getch();
		// ѭ����ֹ������������ַ���������
		} while(isdigit(ch));
		// ����������ֵ���󳤶ȣ�����31�Ŵ���
		if(k>nmax){
			error(31);
		}
	// ������ַ���':'�������жϵ��ʿ�����":="����becomes����
	} else if(ch==':'){
		// ������һ���ַ��ж��ǲ���'='
		getch();
		// �����'='��������������Ϊbecomes�������ʷ�����
		if(ch=='='){
			sym=becomes;
			getch();
		}else{
		// �������':'û�����⺬��
			sym=nul;
		}
	// ������ַ���'<'��������: <=,<,<>����Ӧ������Ϊleq, lss, neq
	} else if(ch=='<'){
		getch();
		if(ch=='='){
			sym=leq;
			getch();
		} else if(ch == '>'){
			sym=neq;
			getch();
		} else {
			sym=lss;
		}
	// ������ַ���'>'��������: >=,>����Ӧ������Ϊgeq, gtr, 
	} else if(ch=='>'){
		getch();
		if(ch=='='){
			sym=geq; getch();
		}else{
			sym=gtr;
		}
	// ����ȥASCII���Ŷ�Ӧ�ĵ������ͱ��в���
	} else{
		// ����ǿ��ת��Ϊunsigned char������Ϊ�����±�ȡ�ö�Ӧ��ֵ������+,-,*,/,nul֮��
		sym=ssym[(unsigned char)ch];
		getch();
    }
}


// ���ɲ�����һ���м����,x��ʾp-codeָ��, y,z��ָ�������������
void gen(enum fct x, long y, long z){
	// �����ǰ���ɴ��������cx�����������󳤶�cxmax
    if(cx > cxmax){
		// ���������Ϣ���˳�����
		printf("program too long\n");
		exit(1);
    }
	// ���û�г���,��Ŀ�����cx�洢��code������
	// instruction code[cxmax+1]�������洢�м����p-code������
    code[cx].f=x; code[cx].l=y; code[cx].a=z;
	// ����ǰp-code����������һ
    cx=cx+1;
}

// ���Ե�ǰ���ʵĺϷ��ԡ����ڴ����﷨�Ĵ���,�����Ϸ�����������ֱֵ�������Ϸ�����Ϊֹ?
void test(unsigned long s1, unsigned long s2, long n){
	// �����ǰ���Ų���s1��
    if (!(sym & s1)) {
		// ��n�Ŵ���
		error(n);
		// ��s1��ֵΪs1��s2�Ĳ���
		s1=s1|s2;
		// ���while�ı�����pass�����в��Ϸ��ķ���,�Իָ��﷨��������
		while(!(sym & s1)){
			// �����һ������
			getsym();
		}
    }
}

// ��������뵽���ű���
void enter(enum object k) {
	// tx�ǵ�ǰ���ű�ָ�룬��һ��ʾָ��һ���ձ���
    tx=tx+1;
	// �ı�tx��Ŷ�Ӧ�������
    strcpy(table[tx].name,id);	//name��¼object k��id����getsym���
    table[tx].kind=k;			// kind��¼k������,Ϊ�������
	// �������Ͳ�ͬ���в�ͬ�Ĳ���
    switch(k){
		// ������
		case constant:
			// �����������ֵ����Լ�������ֵ
			if(num>amax){
				error(31);		// ��30�Ŵ���
				num = 0;		// num��0
			}
			// val����ó�����ֵ,����Ͼ���Կ���,������������򱣴�0
			table[tx].val=num;
			break;
		// ����
		case variable:
			table[tx].level=lev;	// ��¼�������
			table[tx].addr=dx;		// ��¼�����ڵ�ǰ���е�ƫ�Ƶ�ַ
			dx=dx+1;				// ƫ����++,Ϊ�´β�����׼��?
			break;
		// ����
		case proc:
			table[tx].level=lev;	// ��¼�������
			break;
    }
}

// ���ҷ��ű�ĺ���,����idΪ��ҪѰ�ҵķ���
long position(char* id) {
    long i;
	// ��id�ŵ����ű�0��λ�ã��ڱ�?����table���±��1��ʼ����tx������
    strcpy(table[0].name,id);
	// ��i����Ϊ���ű�����һ��λ��,��Ϊ���ű���ջʽ�ṹ,��˰�����������
    i=tx;
	// �����ǰ�����name��id��ͬ
    while(strcmp(table[i].name,id)!=0){
		// ����ǰ��
		i=i-1;
    }
	// ����Ϊ0����ʾû�ҵ���>0��ʾ���ҵ�
    return i;
}

// �����������ĺ���
void constdeclaration() {
	// ������ʵ�������ident��˵���Ǳ�ʶ��
    if( sym==ident ){
		getsym();
		// �ٻ�ȡ��һ�����ʣ������ �Ⱥ� ���� ��ֵ����
		if( sym==eql || sym==becomes ){
			// ���Ǹ�ֵ���ţ���1�Ŵ���,��Ϊ����Ӧ��ʹ�õȺ�
			if(sym==becomes){
				error(1);
			}
			// �����һ������
			getsym();
			// ��� ���ʵ����� ������
			if(sym==number){
				// ����������������Ź������
				enter(constant);
				// �����һ����
				getsym();
			} else {
				// ����Ⱥź��治�� ���֣� �ͱ�2�Ŵ���
				error(2);
			}
		} else {
			// ���������ʶ��const���治�� �Ⱥ� ���� ��ֵ���ţ���3�Ŵ���
			error(3);
		}
    }
	// ������������ĵ�һ�����ʲ��Ǳ�ʶ������4�Ŵ��� (��Ȼǰ���Ѿ�ʶ����const�����Ե�һ������Ӧ���Ǳ�ʶ��)
	else {
		error(4);
    }
	// ������������
}

// ������������ĺ���
void vardeclaration() {
	// �����������﷨�ȳ����������﷨Ҫ��һ�㣬����ֱ��var a������ֻҪʶ�����������������ĵ����Ǳ�ʶ���Ϳ����ˡ�
    if( sym==ident ){
		// ������ʵ������� ��ʶ�����򽫸ñ������뵽���ű���
		enter(variable); 
		// �����һ������
		getsym();
    } else {
		// �����������������ĵ��ʲ��Ǳ�ʶ������4�Ŵ���
		error(4);
    }
	// ������������
}

// �г��м����p-code�ĺ��� list code generated for this block
void listcode(long cx0) {
    long i;
	// ��ʽ�����,�ֱ�������,p-codeָ������Ƿ�,���,��ַ.ʵ�ʵ����Ч��������ʵ�ʵ�p-code��ͬ
    for(i=cx0; i<=cx-1; i++){
		printf("%10d%5s%3d%5d\n", i, mnemonic[code[i].f], code[i].l, code[i].a);
    }
}

// 
void expression(unsigned long);

// �������ӵĳ���(������������������)
void factor(unsigned long fsys){
	// �������
    long i;
	// ���Ե��ʵĺϷ���,�б�ǰsym�Ƿ���facbegsys��,������main�ж���,������ڱ�24�Ŵ���˵����������?
	// facbegsys=ident|number|lparen���� ��ʶ�������֡������� ��ʼ
    test(facbegsys,fsys,24);
	
	// ѭ����������
    while(sym & facbegsys){
		// ���ʶ�𵽱�ʶ��
		if(sym==ident){
			// ���,��¼���ڷ��ű��е�λ��,������i
			i=position(id);
			// �������ֵΪ0�����ʾ���ű��в�����������ֵı�ʶ������11�Ŵ�
			if(i==0){
				error(11);
			} else {
				// ����ڷ��ű����ҵ��˶�Ӧ�ķ��������ݲ�ͬ�ķ������ͽ����м����Ĳ���
				switch( table[i].kind ) {
					// ����ǳ�������,����litָ��,������Ϊ0,val
					case constant:
						gen(lit,0,table[i].val);
						break;
					case variable:
					// ����Ǳ�������,����lodָ��,������Ϊlev-level,addr
						gen(lod,lev-table[i].level,table[i].addr);
						break;
					// ������Ӵ�����ʶ���˹��̱�ʶ��,��21�Ŵ���?
					case proc:
						error(21);
						break;
				}
			}
			// ��ȡ��һ������
			getsym();
		} else if(sym==number) {
		// ���ʶ������
			if(num>amax){
				// �б������Ƿ񳬹��涨����,��������,��31�Ŵ���
				error(31);
				// ����������Ϊ0
				num=0;
			}
			// ����litָ��,��num��ֵ�ŵ�ջ��
			gen(lit,0,num);
			// ��ȡ��һ������
			getsym();

		// ���ʶ��������
		} else if( sym==lparen ){
			// ��ȡ��һ������
			getsym();
			// ���ñ��ʽ�Ĵ������������,�ݹ��½��ӳ��򷽷�
			expression(rparen|fsys);
			// ���ʶ��������
			if(sym==rparen){
				// ��ȡ��һ������
				getsym();
			} else {
				// ����22�Ŵ���
				error(22);
			}
		}
		// ���Խ���Ƿ���fsys��,������,�׳�23�Ŵ���?
		test(fsys,lparen,23);
    }
}

// ��ķ�������* /���������Ҿ���* /�Ǹ���һ��ı��ʽ��
void term(unsigned long fsys){
	// ��ķ������̿�ʼ multiply operator
    unsigned long mulop;
	// ��ĵ�һ������Ӧ��������,�������ӷ�������
    factor(fsys|times|slash);
	// ������Ӻ����ǳ�/����
    while( sym==times||sym==slash ){
		// ʹ��mulop���浱ǰ�������
		mulop=sym;
		// ��ȡ��һ������
		getsym();
		// �������ӷ����������������������
		factor(fsys|times|slash);
		// ���������ǳ˺�
		if( mulop==times ){
			// ����oprָ��,�˷�ָ��
			gen(opr,0,4);
		} else {
			// ����oprָ��,����ָ��
			gen(opr,0,5);
		}
    }
}

// ���ʽ�ķ������� (+ -����) ��+ -�Ǽ򵥵ı��ʽ��
void expression(unsigned long fsys){
	// addop: add operator
    unsigned long addop;
	// ������ʽ�ĵ�һ��������+/-����
    if( sym==plus || sym==minus ){
		// ���浱ǰ����(�����)
		addop=sym;
		// ��һ������
		getsym();
		// �����ź������,������ķ�������
		term(fsys|plus|minus);
		// ������ſ�ͷ������-mul1*mul2
		if(addop==minus) {
			// ����oprָ��,���ȡ������
			gen(opr,0,1);
		}
    } else {
		// ������Ƿ��ſ�ͷ,ֱ�ӵ�����ķ�������
		term(fsys|plus|minus);
    }
	// �������Խ����ɸ�term,ʹ�ò�����+-����,��˴˴���while
    while(sym==plus||sym==minus) {
		// ��¼���������
		addop=sym;
		// ��ȡ��һ��sym����
		getsym();
		// ������ķ�������
		term(fsys|plus|minus);
		if(addop==plus){
			// ����oprָ��,��ɼӷ�����
			gen(opr,0,2);
		} else {
			// �������ɼ���ָ��
			gen(opr,0,3);
		}
    }
}

// ������������ relop: relational operator
void condition(unsigned long fsys){
	// ��ϵ�����������relop��
    unsigned long relop;

    // �����������Ϊ odd 
    if( sym==oddsym ){
    	// ��ȡ��һ������
		getsym();
		// odd������Խ��ܱ��ʽ�����Ե��ñ��ʽ��������
		expression(fsys);
		// ����opr 6��ָ��,�����ż�ж�����
		gen(opr,0,6);

	// �������odd������ñ��ʽ�������̶Ա��ʽ���м���
    } else {
    	// ���ñ��ʽ���������Ա��ʽ���м���
		expression(fsys|eql|neq|lss|gtr|leq|geq);

		// ������ڹ�ϵ���������֮��ķ���
		if( !(sym & (eql|neq|lss|gtr|leq|geq)) ){
			// ��20�Ŵ���
			error(20);
		} else {
			// ��¼��ǰ��ϵ�����������
			relop=sym;
			// ��ȡ��һ�����ʣ���ϵ�����������Ŀ϶��Ǳ��ʽ
			getsym();
			// ���ñ��ʽ�������̶Ա��ʽ���з���
			expression(fsys);
			// ���ݵ�ǰ�������Ͳ�ͬ��ɲ�ͬ�Ĳ���
			switch(relop){
				// ����ǵȺ�,����opr 8��ָ��,�ж��Ƿ����
				case eql:
					gen(opr,0,8);
					break;
				// ����ǲ��Ⱥ�,����opr 9��ָ��,�ж��Ƿ񲻵�
				case neq:
					gen(opr,0,9);
					break;
				// �����С�ں�,����opr10��ָ��,�ж��Ƿ�С��
				case lss:
					gen(opr,0,10);
					break;
				// ����Ǵ��ڵ��ں�,����opr11��ָ��,�ж��Ƿ���ڵ���
				case geq:
					gen(opr,0,11);
					break;
				// ����Ǵ��ں�,����opr12��ָ��,�ж��Ƿ����
				case gtr:
					gen(opr,0,12);
					break;
				// �����С�ڵ��ں�,����opr13��ָ��,�ж��Ƿ�С�ڵ���
				case leq:
					gen(opr,0,13);
					break;
			}
		}
    }
}

// ��䴦��
void statement(unsigned long fsys){
    
    long i,cx1,cx2;

    // ����Ա�ʶ����ʼ
    if(sym==ident) {
    	// ���ݱ�ʶ������position�������ڷ��ű��е�λ��
		i=position(id);
		// ���i=0����ʾû���ҵ�����11�Ŵ���
		if(i==0){
		    error(11);
		// ����ڷ��ű����ҵ��˸÷���,���÷��ŵ����Ͳ��Ǳ���,��ô���ڵĲ������ڸ��Ǳ�����ֵ����12�Ŵ��󣬽����ű���i����
		} else if(table[i].kind != variable) {
		    error(12);
		    i=0;
		}
		// ��ȡ��һ������
		getsym();
		// ������������Ǹ�ֵ���ţ���������Ĳ��Ǹ�ֵ����,��13�Ŵ���
		if(sym==becomes){
			// ��ȡ��һ������
		    getsym();
		} else {
		    error(13);
		}
		// ��ֵ����:=�ĺ�����Ը����ʽ,��˵��ñ��ʽ�����ӳ���
		expression(fsys);
		// ������ű����ҵ��˺Ϸ��ķ���
		if(i!=0){
			// ����һ��stoָ�����������ʽ��ֵд�뵽��Ӧ�����ĵ�ַ
		    gen(sto,lev-table[i].level,table[i].addr);
		}

	// ��������ķ�����call�ؼ���
    } else if(sym==callsym) {
    	// ��ȡ��һ������
		getsym();
		// ���call����ĵ��ʲ��� ��ʶ������14�Ŵ���
		if(sym!=ident) {
		    error(14);
		} else {
		// call����Ǳ�ʶ����ͨ����ʶ���������ڷ��ű��н��в��ң�����������ظ�i
		    i=position(id);
		    // ���i=0����ʾû���ҵ�����11�Ŵ���
		    if(i==0) {
				error(11);
			// ����ҵ��˶�Ӧ�ķ������������������ proc���������ǹ��̵ı�ʶ��
		    } else if(table[i].kind==proc){
		    	// ����calָ����ʵ��call����
				gen(cal,lev-table[i].level,table[i].addr);
		    } else {
		    	// ������಻Ϊ��������,��15�Ŵ���
				error(15);
	    	}
	    	// ��ȡ��һ������
	    	getsym();
		}
	// ��������ķ�����if�ؼ���	
    } else if( sym==ifsym ) {
		getsym();
		// if�������Ӧ�����������,����������������
		condition(fsys|thensym|dosym);
		// ������������������then�ؼ���
		if(sym==thensym) {
	    	// ��ȡ��һ������
		    getsym();
		} else {
			// �������������ӵĲ���then,��16�Ŵ���
		    error(16);
		}
		// code index���м�������������¼��ǰ�����ɴ���λ�õ�cx1
		cx1=cx;
		// ����������תָ��,��תλ������0
		gen(jpc,0,0);
		// ����then�ؼ��ֺ�������
		statement(fsys);
		// ��֮ǰ��¼�Ĵ����λ�Ƶ�ַ��д�����ڵ����ɴ���λ��?
		code[cx1].a=cx;	

	// �������ĵ���Ϊbegin�ؼ���
    } else if(sym==beginsym) {
    	// ��ȡ��һ������
		getsym();
		// begin����Ĭ�Ͻ����,��������������
		statement(fsys|semicolon|endsym);
		// �����ǰ�ĵ����Ƿֺţ�������һ����䣬��������
		while( sym==semicolon || (sym&statbegsys) ){
			// ��������Ƿֺ�
		    if(sym==semicolon){
		    	// ��ȡ��һ������
				getsym();
		    } else {
		    	// ����10�Ŵ���
				error(10);
		    }
		    // �����������ķ���
		    statement(fsys|semicolon|endsym);
		}
		// �����ǰ�ĵ�����end�ؼ���
		if(sym==endsym){
			// ��ȡ��һ������
		    getsym();
		}else{
			// ���statement�﷨�鲻����end��������17�Ŵ���
		    error(17);
		}
	// �����ǰ�ĵ�����while�ؼ���
    } else if(sym==whilesym) {
    	// ��¼����while��ʼʱ��ǰ���ɴ����λ��
		cx1=cx;
		// ��ȡ��һ������
		getsym();
		// while�������Ĭ����ѭ����������Ҫ�����������ķ�������(while... do...)
		condition(fsys|dosym);
		// ��¼�ڷ���������֮������ɴ����λ��,Ҳ��do��ʼ��λ��
		cx2=cx;
		// ����һ��������תָ��,������תλ��(a)����?
		gen(jpc,0,0);
		// ������Ӧ�ý�do�ؼ��֣�����18�Ŵ���
		if(sym==dosym) {
			// ��ȡ��һ������
		    getsym();
		} else {
		    error(18);
		}
		// ��������ѭ�����ֵ����
		statement(fsys);
		// ִ����һ��ѭ��������Ҫ��ת��ѭ�����������жϣ�������Ҫ������������תָ��
		gen(jmp,0,cx1);
		// ��֮ǰ���ɵ���תָ���趨��ת��λ��Ϊ��ǰλ��?
		code[cx2].a=cx;
    }
    // ���Ե�ǰ�ַ��Ƿ�Ϸ�,���û�г�����fsys��,��19�Ŵ�
    test(fsys,0,19);
}
		
// 	�����﷨������������,lev��ʾ�﷨�������ڲ��,tx�ǵ�ǰ���ű�ָ��,fsys�������ָ�����ĵ��ʼ���
/*
long dx;		// ���ݵ�ַ����
long lev;		// �﷨�������ڲ��
long tx;		// tx�ǵ�ǰ���ű�ָ��
*/
void block(unsigned long fsys){
    long tx0;		// ��ʼ���ű�����
    long cx0; 		// ��ʼ�м��������
    long tx1;		// �ڴ���Ƕ�׵Ĺ���ʱ����Ҫ���浱ǰ���ű������
    long dx1;		// ���ݵ�ַ����

	// ��¼����ջ�ռ��ջ��λ��,����Ϊ3����Ϊ��ҪԤ��SL,DL,RA�Ŀռ䣨3���Ĵ�����
    dx=3;
	// ��¼��ǰ���ű��ջ��λ��
	tx0=tx;
	// ���ű�ǰλ�õ�ƫ�Ƶ�ַ��¼��һ�����ɴ��뿪ʼ��λ��
	table[tx].addr=cx;
	// ����һ��jmp���͵���������תָ��,��תλ��δ֪?
	gen(jmp,0,0);
	// ������������Ĳ�δ�����������Ƕ�ײ�Σ���32�Ŵ���
    if(lev>levmax){
		error(32);
    }
	// ѭ����ʼ���ȴ���������
    do{
		// �������������const����������
		if(sym == constsym){
			// ��ȡ��һ������
			getsym();
			// ѭ����ʼ
			do{
				// ��const����Ҫ����������
				constdeclaration();
				// ���������������ӵ��Ƕ��ţ�˵����������û�н�����������һѭ����ֱ��������Ĳ���','
				while( sym==comma ) {
					getsym();
					constdeclaration();
				}
				// ��������˷ֺ�,˵�����������Ѿ�������
				if(sym==semicolon){
					getsym();
				} else {
				// ���û�зֺţ�˵���������û��������������5�Ŵ��� 
					error(5);
				}
			// ѭ��ֱ��������һ������ ��ʶ��
			} while(sym==ident);
		}
	
		// ��� ����������var������
		if( sym==varsym ){
			// ��ȡ��һ������
		    getsym();
			// ѭ����ʼ��������һvar��������еı�������
		    do{
				// ��var�󣬴����������
				vardeclaration();
				// ��������˶���,˵������δ����,����ѭ����ֱ��������ĵ������Ͳ���','
				while( sym==comma ) {
					// ��ȡ��һ������
					getsym();
					// �����������
					vardeclaration();
				}
				// ��������˷ֺ�,˵�����������Ѿ�������
				if(sym==semicolon) {
					getsym();
				} else {
				// ���û�зֺţ�˵���������û��������������5�Ŵ��� 
					error(5);
				}
			// ѭ��ֱ��������һ������ ��ʶ��
		    } while(sym==ident);
		}
		
		// ��� ����������procedure������
		while( sym==procsym ){
			// ��ȡ��һ������
		    getsym();
			// ��һ������Ӧ���Ǳ�ʶ�����ͣ���������̵ı�ʶ��
		    if(sym==ident) {
				// ���÷���¼����ű�,����Ϊ����,��Ϊ����proc�����һ���ǹ�����
				enter(proc);
				// ��ȡ��һ������
				getsym();
		    } else {
				// �����һ�����Ų��Ǳ�ʶ������,��4�Ŵ���
				error(4);
		    }
			// ��������˷ֺ�,˵�� ������������
		    if(sym==semicolon){
				// ��ȡ��һ����
				getsym();
		    } else {
				// �����������֮��û�и��ֺ�,���û����������,��5�Ŵ���
				error(5);
		    }
			// ִ�зֳ���ķ������̣��﷨�������ڲ��lev++��ʾ������һ�㣻tx1���ڴ���Ƕ�׵Ĺ���ʱ����Ҫ���浱ǰ���ű������
		    lev=lev+1; tx1=tx; dx1=dx;
			// ִ�зֳ���ķ�������
		    block(fsys|semicolon);
		    // �ݹ鷵�غ󣬸��������ָ�ԭ����ֵ
		    lev=lev-1; tx=tx1; dx=dx1;
			
			// ??? ��û����
		    // �ݹ���÷��غ�Ӧ�ýӷֺš�����Ƿֺ�
		    if(sym == semicolon) {
		    	// ��ȡ��һ������
				getsym();
				// ���Ե�ǰ���ʵĺϷ��ԡ����ڴ����﷨�Ĵ���6�Ŵ���
				test(statbegsys|ident|procsym,fsys,6);
		    } else {
		    	// ����ӵĲ��Ƿֺţ���5�Ŵ���
				error(5);
		    }
		}
		// ���Ե�ǰ��sym�Ƿ�Ϸ�����7�Ŵ���
		test(statbegsys|ident,declbegsys,7);
		
	// һֱѭ����sym�����������ż���Ϊֹ
    } while(sym & declbegsys);

    // ��֮ǰ������������תָ���Ŀ���ַָ��ǰλ��
    code[table[tx0].addr].a=cx;
    // ��¼��ǰ����ķ��俪ʼ����
    table[tx0].addr=cx;
    // ��¼��ǰ�������ĵ�ַ
    cx0=cx;
    // ����intָ��,����dx���ռ�
    gen(Int,0,dx);
    // �����﷨��������
    statement(fsys|semicolon|endsym);
    // ����0��opr����,��ɷ��ز���
    gen(opr,0,0);
    // ���Ե�ǰ״̬�Ƿ�Ϸ�,�����ⱨ8�Ŵ���
    test(fsys,0,8);
    // �г���block�����ɵ�p-code
    listcode(cx0);
}

// �������ַ�ĺ���
long base(long b, long l){
	// ������������
    long b1;
	// ��¼��ǰ��Ļ���ַ
    b1=b;
	// �������l����0,��Ѱ�ҵĲ��Ǳ���
    while (l>0) {
		// ��¼��ǰ�����ݻ�ַ������
		b1=s[b1];
		// l--
		l=l-1;
    }
	// ���ҵ��Ļ���ַ����
    return b1;
}

// ����ִ�г���
void interpret(){
	// ���������Ĵ���,�ֱ��¼��һ��ָ��,��ַ��ַ��ջ��ָ��
    long p,b,t;
    // ָ��Ĵ���,����Ϊinstruction,Ϊ�˴�ŵ�ǰָ��
    instruction i;

    // �������ʼ���е���ʾ���
    printf("start PL/0\n");
    // ��ָ��Ĵ������㣻����ַ��ַ��Ϊ1����ջ��ָ�����㣻
    p=0; b=1; t=0; 

    // ������ջ�ĵ�һ������,��ӦSL
    s[1]=0;
    // ������ջ�ĵڶ�������,��ӦDL
    s[2]=0;
    // ������ջ�ĵ���������,��ӦRA
    s[3]=0;

    // ��ʼ����ִ��
    do{
    	// ��ȡ��ǰ��Ҫִ�еĴ���
		i=code[p];
		// ��ָ��Ĵ���+1,��ָ����һ��ָ��
		p=p+1;
		// ��Ե�ǰָ��� ����������� ִ�в�ͬ����
		switch(i.f){
			// lit
		    case lit:
		    	// ջ��ָ���1����a��������ֵ����ջ��
				t=t+1; s[t]=i.a;
				break;
			// ���opr���͵�ָ��
		    case opr:
				switch(i.a){
			    	// 0��Ӧreturn����
				    case 0:
						// tȡ���ò�����ջSL-1��λ��,��ζ�Ž��ò������ջȫ�����
						t=b-1;
						// ��ָ��ָ��ָ��RA��ֵ,�����return address
						p=s[t+3];
						// ����ַָ��ָ��DL��ֵ,�������return֮��Ļ�ַ,��Ϊ�����ò�ε�DLָ����ò�εĻ�ַ
						b=s[t+2];
						break;

					// 1��Ӧȡ������
				    case 1:
						s[t]=-s[t];
						break;

					// 2��Ӧ��Ͳ���
				    case 2:
					    // ջ��ָ����һ�񣬽�ջ���ʹ�ջ���е���ֵ��ͷ����µ�ջ��,ע��������ջ�����½�һ���,��������������
						t=t-1; s[t]=s[t]+s[t+1];
						break;

					// 3��Ӧ������
				    case 3:
						t=t-1; s[t]=s[t]-s[t+1];
						break;

					// 4��Ӧ�˻�����
				    case 4:
						t=t-1; s[t]=s[t]*s[t+1];
						break;
					// 5��Ӧ���
				    case 5:
						t=t-1; s[t]=s[t]/s[t+1];
						break;
					// 6��Ӧ�ж��Ƿ�ջ����ֵΪ����
				    case 6:
						s[t]=s[t]%2;
						break;
					
					// 8�Ŷ�Ӧ��ֵ�ж�
				    case 8:
						t=t-1; s[t]=(s[t]==s[t+1]);
						break;

					// 9�Ŷ�Ӧ�����ж�
				    case 9:
						t=t-1; s[t]=(s[t]!=s[t+1]);
						break;
				    
				    // 10�Ŷ�ӦС���ж�
				    case 10:
						t=t-1; s[t]=(s[t]<s[t+1]);
						break;
				    
					// 11�Ŷ�Ӧ���ڵ����ж�
				    case 11:
						t=t-1; s[t]=(s[t]>=s[t+1]);
						break;
				    
					// 12�Ŷ�Ӧ�Ŵ����ж�
				    case 12:
						t=t-1; s[t]=(s[t]>s[t+1]);
						break;
				    
					// 13�Ŷ�Ӧ��С�ڵ����ж�
				    case 13:
						t=t-1; s[t]=(s[t]<=s[t+1]);
				}
				break;
		    
			// �����lodָ��
		    case lod:
			    // ջ��ָ��ָ����ջ
				t=t+1;
				// ���뵱ǰ���ݲ��β�Ϊl,����ƫ��Ϊa��ջ�е����ݴ浽ջ��
				s[t]=s[base(b,i.l)+i.a];
				break;

			// stoָ��
		    case sto:
		    	// ����ǰջ�������ݱ��浽�뵱ǰ����Ϊl,����ƫ��Ϊa������ջ��
				s[base(b,i.l)+i.a]=s[t];
				printf("%10d\n", s[t]); t=t-1;
				break;

			// generate new block mark
		    case cal:
		    	// ����Ҫ�����µ�block,���ջ��ѹ��SL��ֵ
				s[t+1]=base(b,i.l);
				// ��SL֮��ѹ�뵱ǰ�������Ļ�ַ,��ΪDL
				s[t+2]=b;
				// ��DL֮��ѹ��ָ��ָ��,����ָ��Ķϵ�,��ΪRA
				s[t+3]=p;
				// �ѵ�ǰ����������ַָ���µ�SL
				b=t+1;
				// ��a��λ�ü���ִ�г���,a����instruction�ṹ��
				p=i.a;
				break;

			// 	��Intָ��,��ջ��ָ������a��λ��
		    case Int:
				t=t+i.a;
				break;

			// ��jmpָ��,��ָ��ָ��ָ��a
		    case jmp:
				p=i.a;
				break;

			// ����jpcָ��
		    case jpc:
		    	// ���ջ������Ϊ�㣬��ָ��ָ��ָ��a
				if(s[t]==0){
				    p=i.a;
				}
				// ջ�������ƶ�
				t=t-1;
		}
    } while (p!=0);

    // p-codeִ�н���
    printf("end PL/0\n");
}


// ��һ�����ȿ�һ��main�����������˽�������еĹ���
main(){
	// i����ASCII���ֵ: 0~255
    long i;
	// Ϊÿ��ASCII�ַ���ֵ��ֵ��ָ�ַ���Ӧ�� symbol���ͣ�����ssym['+']=plus;
	// ��һ�仰�е�symbol���ͣ�����Ϊ�� һЩ�����ASCII�ַ���ʾ�������ԵĶ���������Ӽ��˳�������û�����⺬���ASCII�ַ������ǵ�symbol���ͣ��͸�ֵΪnul
    for(i=0; i<256; i++){
		// nul��ʾ����ַ��������⺬�壬������ȫ����ֵΪnul��֮���ٽ�����������
		ssym[i]=nul;
    }
	
	
	// word[norw][al+1];
	// ��һ�δ����ʼ������ ���������飬�洢����Ӧ�� ������ (11��)
    strcpy(word[0],  "begin     ");
    strcpy(word[1],  "call      ");
    strcpy(word[2],  "const     ");
    strcpy(word[3],  "do        ");
    strcpy(word[4],  "end       ");
    strcpy(word[5],  "if        ");
    strcpy(word[6],  "odd       ");
    strcpy(word[7],  "procedure ");
    strcpy(word[8],  "then      ");
    strcpy(word[9],  "var       ");
    strcpy(word[10], "while     ");
	
	// �����ֱ���ÿ�������ֶ�Ӧ��symbol���� (������)
    wsym[0]=beginsym;
    wsym[1]=callsym;
    wsym[2]=constsym;
    wsym[3]=dosym;
    wsym[4]=endsym;
    wsym[5]=ifsym;
    wsym[6]=oddsym;
    wsym[7]=procsym;
    wsym[8]=thensym;
    wsym[9]=varsym;
    wsym[10]=whilesym;
	
	// ssym[256]
	// һЩ����ASCII�ַ���Ӧ��symbol������Ҫ�޸ģ�+-*/()=,.;
    ssym['+']=plus;
    ssym['-']=minus;
    ssym['*']=times;
    ssym['/']=slash;
    ssym['(']=lparen;
    ssym[')']=rparen;
    ssym['=']=eql;
    ssym[',']=comma;
    ssym['.']=period;
    ssym[';']=semicolon;
	
	// char mnemonic[8][3+1]
	// ��ʼ��p-codeָ�����Ƿ�����
    strcpy(mnemonic[lit],"lit");
    strcpy(mnemonic[opr],"opr");
    strcpy(mnemonic[lod],"lod");
    strcpy(mnemonic[sto],"sto");
    strcpy(mnemonic[cal],"cal");
    strcpy(mnemonic[Int],"int");
    strcpy(mnemonic[jmp],"jmp");
    strcpy(mnemonic[jpc],"jpc");
	
	// ������ʼ ���ʽ��ʼ �ʼ �ķ��ż���
	// �����|�������ִ�а�λ�����㣬ֻҪ������һ�����л����㲻Ϊ0��������������������ĳ���﷨Ԫ�صĿ�ʼ
	// �� const��var��procedure ��ʼ
    declbegsys=constsym|varsym|procsym;
	// �� begin��call��if��while ��ʼ
    statbegsys=beginsym|callsym|ifsym|whilesym;
	// �� ��ʶ�������֡������� ��ʼ
    facbegsys=ident|number|lparen;


	/* ������������ʼִ�У�ǰ����һЩ��ʼ�� */

	// ��ʾ�û�����Դ��ĵ�ַ
    printf("please input source program file name: ");
	// �����û�������ļ�·���� infilename
    scanf("%s",infilename);
	// ���뻻�з�\n
    printf("\n");
	
	// fopen: ����ļ��򿪳ɹ�����һ�� FILE ָ�롣���򷵻� NULL��������ȫ�ֱ��� errno ����ʶ����
    if( (infile = fopen(infilename,"r")) == NULL ){
		printf("File %s can't be opened.\n", infilename);
		exit(1);
    }
    
	// ��ʼ����ǰ��׼����������ʱ�Ѿ�����Դ�ļ��ˣ�������ǰ��˵�ĳ�ʼ�����̲�һ����
    err=0;		// ���������Ϊ0
    cc=0;		// �л���ָ��ָ��0
	cx=0;		// �м�����������Ϊ0
	ll=0;		// �ʷ������л������������� (������ַ���?)
	ch=' ';		// ��ǰ������ַ���Ϊ' '
	kk=al;		// kk��ֵ��ʼ��Ϊal������10
	
	// �ʷ��������򣬽��ַ���ת��Ϊ ���ʣ�������
	getsym();

    lev=0;		// �﷨�������ڲ��
	tx=0;		// tx��ָ��ǰ���ű�ָ��(index����������������)
	
	// �﷨�������� (��)
    block(declbegsys|statbegsys|period);
	
	// ������Ų��Ǿ�ţ�����9�Ŵ��󣬼������������'.'����
    if(sym != period) {
		error(9);
    }
	// ���errΪ0��ʾû�д��󣬾ͽ�����һ��
    if(err==0) {
		// ���ͳ���,��ʼ����ִ�����ɵ�p-code����
		interpret();
    }
	else {
		// ����pl/0�������д��󣬱���
		printf("errors in PL/0 program\n");
    }
	// ����������ر��ļ�
    fclose(infile);
}

