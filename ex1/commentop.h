#ifndef COMMENTOPH
#define COMMENTOPH
#include "datastruct.h"
#include <string.h>
void exchangetable(int x[],int y[],int len){
	memset(x,0,sizeof (int) * 64);
	for (int i = 0;i < len;i++)
		x[i] = y[i];
}

void gettable(int s[],int t[],int trans[],int len){
	for (int i = 0;i < len;i++)
		t[i] = s[trans[i] - 1];
}

void xor_op(int x[],int y[],int len){
	for (int i = 0;i < len;i++)
		x[i] = x[i] ^ y[i];
}

void leftshift_op(int x[],int len,int s){
	int x0 = x[0];
	for (int i = 0;i < len - 1;i++)
		x[i] = x[i + 1];
	x[len - 1] = x0;
	if (s == 2){
		x0 = x[0];
		for (int i = 0;i < len - 1;i++ )
			x[i] = x[i + 1];
		x[len - 1] = x0;
	}
}
void Sbox_op(int x[]){
	int len = 0;
	for (int s = 0;s < 8;s++){
		int row = x[s * 6] * 2 + x[s * 6 + 5];
		int col = x[s*6+4] + x[s*6+3]*2 + x[s*6+2]*4 + x[s*6+1]*8;
		int F = tableS[s][row * 16 + col];
		for (int i = 3;i >= 0;i--)
			x[len++] = F & (1 << i) ?1:0;
	}
}
void getK(int key[]){
	int x[64];
	//break into C,D
	memset(C,0,sizeof (int)*CDsize);
	memset(D,0,sizeof (int)*CDsize);
	for (int i =0;i < CDsize;i++){
		C[i] = key[tableC[i] - 1];
		D[i] = key[tableD[i] - 1];
	}

	for (int round = 1;round <= 16;round++){
		//leftshift
		leftshift_op(C,CDsize,leftshift_table[round - 1]);
		leftshift_op(D,CDsize,leftshift_table[round - 1]);
		//getK
		exchangetable(x,C,CDsize);
		gettable(x,K[round-1],translation_table2,24);
		exchangetable(x,D,CDsize);
		for (int i = 24;i < Ksize;i++)
			K[round-1][i] = D[translation_table2[i] - 1 - 28];
	}
}
void crypt(int plaintext[],int key[],int mode){
	//getK
	getK(key);
	
	int x[64];

	//initial translation
	exchangetable(x,plaintext,Plaintextsize);
	gettable(x,plaintext,initial_transformation_table,Plaintextsize);
	//for (int i = 0;i < 64;i++)
	//	printf("%d",plaintext[i]);
	
	int L[32],R[48],TEM[48];
	//break into L0,R0
	for (int i = 0;i < LRsize;i++){
		L[i] = plaintext[i];
		R[i] = plaintext[i + 32];
	}

	//16 rounds
	for (int round = 1;round <= 16;round++){
		for (int i = 0;i < LRsize;i++)
			TEM[i] = R[i];
		//getE
		exchangetable(x,R,LRsize);
		gettable(x,R,tableE,Esize);
		//XOR
		if (mode)
			xor_op(R,K[16 - round],Esize);
		else
			xor_op(R,K[round-1],Esize);
		//Sbox
		Sbox_op(R);
		//tableP
		exchangetable(x,R,LRsize);
		gettable(x,R,tableP,LRsize);
		//XOR
		xor_op(R,L,LRsize);
		//exchangeL,R
		for (int i = 0;i < LRsize;i++)
			L[i] = TEM[i];
	}
	for (int i = 0;i < LRsize;i++){
		plaintext[i] = R[i];
		plaintext[i+32] = L[i];
	}
	//inverse initial translation
	exchangetable(x,plaintext,Plaintextsize);
	gettable(x,plaintext,inverse_initial_transformation_table,Plaintextsize);
	/*puts("");
	for (int i = 0;i < 64;i++)
		printf("%d",plaintext[i]);*/

}
#endif