#include "encryption.h"
#include <string.h>
void exchangetable(int x[],int y[],int len){
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
	if (s == 1){
		for (int i = 0;i < len - 1;i++)
			x[i] = x[i + 1];
		x[len - 1] = x0;

	}else{
		int x1 = x[1];
		for (int i = 0;i < len - 3;i += 2){
			x[i] = x[i + 2];
			x[i + 1] = x[i + 3];
		}
		x[len - 1] = x1;
		x[len - 2] = x0;
	}
}
void Sbox_op(int x[]){
	int len = 0;
	for (int s = 0;s < 8;s++){
		int row = x[s * 6] * 2 + x[s * 6 + 5];
		int col = x[s*6+4] + x[s*6+3]*2 + x[s*6+2]*4 + x[s*6+1]*8;
		int F = tableS[s][row * 16 + col];
		for (int i = 3;i >=  0;i++){
			x[len + i] = F & 1;
			F >>= 1;
		}
	}
}
void encrypt(int plaintext[],int key[]){
	//initial translation
	int x[64];
	exchangetable(x,plaintext,Plaintextsize);
	gettable(x,plaintext,initial_transformation_table,Plaintextsize);
	//16 rounds
	for (int round = 1;round <= 16;round++){
		int L[32],R[48];
		int C[28],D[28];
		int K[48];
		int P[32];
		//break into L,R
		for (int i = 0;i < LRsize;i++){
			L[i] = plaintext[i + 32];
			R[i] = plaintext[i];
			plaintext[i + 32] = R[i];
			plaintext[i] = L[i];
		}
		//getE
		exchangetable(x,R,LRsize);
		gettable(x,R,tableE,Esize);
		//break into C,D
		for (int i =0;i < CDsize;i++){
			C[i] = key[tableC[i] - 1];
			D[i] = key[tableD[i] - 1];
		}
		//leftshit
		leftshift_op(C,CDsize,leftshift_table[round - 1]);
		leftshift_op(D,CDsize,leftshift_table[round - 1]);
		//getK
		exchangetable(x,C,CDsize);
		gettable(x,K,translation_table2,CDsize);
		exchangetable(x,D,CDsize);
		for (int i = 24;i < Ksize;i++)
			K[i] = D[translation_table2[i]];
		//XOR
		xor_op(R,K,Esize);
		//Sbox
		Sbox_op(R);
		//XOR
		xor_op(R,L,LRsize);
		//getplaintext
		for (int i = LRsize;i < Plaintextsize;i++)
			plaintext[i] = R[i - LRsize];

	}
	//inverse initial translation
	exchangetable(x,plaintext,Plaintextsize);
	gettable(x,plaintext,inverse_initial_transformation_table,Plaintextsize);
}