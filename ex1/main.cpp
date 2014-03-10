/*************************************************
Copyright:liucising
Author:liucising(Áõ×ÓÐÇ)
Date:2013-04-03
Description:
There are 5 main functions altogether.
1.completed the test a) which is one of the requirement in experiment1
2.completed the test b) which is one of the requirement in experiment1
3.encrypt a 64-bit 0-1 string
4.encrypt a 64-bit 0-1 string
5.exit the system
**************************************************/
#include <iostream>
#include <cstdio>
#include <fstream>
#include "decryption.h"
#include "encryption.h"
using namespace std;

FILE *plaintin = fopen("plaint2.in","r"); 
FILE *keyin = fopen("key2.in","r"); 
FILE *testdata = fopen("input.txt","r"); 

void inputdata(FILE* indata,int x[]){
	char c;
	int l = 0;
	while (fscanf(indata,"%c",&c)!=EOF){
		if (c >= '0' && c <= '1'){
			x[l++] = c - '0';
			if (l == 64) return;
		}
	}
}
void inputdata(int x[]){
	char c;
	int l = 0;
	while (scanf("%c",&c)!=EOF){
		if (c >= '0' && c <= '1'){
			x[l++] = c - '0';
			if (l == 64) return;
		}
	}
}
void outputdata(int x[],int len){
	for (int i = 0;i < len;i++)
		printf("%d",x[i]);
	printf("\n\n");
}

void getarray(int x[],int y[],int len){
	for (int i = 0;i < len;i++)
		x[i] = y[i];
}
int getdifferentbits(int x[],int y[],int len){
	int ret = 0;
	for (int i = 0;i < len;i++)
		if (x[i] != y[i])
			ret++;
	return ret;
}
void testa(){
	int plaintext1[64];
	int plaintext2[64];
	int ciphertext1[64];
	int ciphertext2[64];
	int key[64];
	cout << "test a)" << endl;
	cout << "input the key" << endl;
	inputdata(key);

	cout << "input the plaint1" << endl;
	inputdata(plaintext1);

	cout << "The plaintext1 after encrypt,we got ciphertext1" << endl;
	getarray(ciphertext1,plaintext1,Plaintextsize);
	encrypt(ciphertext1,key);
	outputdata(ciphertext1,Plaintextsize);

	cout << "The ciphertext1 after decrypt,we got plaintext1" << endl;
	getarray(plaintext1,ciphertext1,Plaintextsize);
	decrypt(plaintext1,key);
	outputdata(plaintext1,Plaintextsize);

	cout << "input the plaint2" << endl;
	inputdata(plaintext2);

	cout << "The plaintext2 after encrypt,we got ciphertext2" << endl;
	getarray(ciphertext2,plaintext2,Plaintextsize);
	encrypt(ciphertext2,key);
	outputdata(ciphertext2,Plaintextsize);

	cout << "The ciphertext2 after decrypt,we got plaintext2" << endl;
	getarray(plaintext2,ciphertext2,Plaintextsize);
	decrypt(plaintext2,key);
	outputdata(plaintext1,Plaintextsize);

	cout << "The number of different bits between ciphertext1 and ciphertext2: " << endl << getdifferentbits(ciphertext1,ciphertext2,Plaintextsize) << endl << endl;
}

void testb(){
	int plaintext[64];
	int ciphertext1[64];
	int ciphertext2[64];
	int key1[64];
	int key2[64];
	cout << "test b)" << endl;
	cout << "input the key1" << endl;
	inputdata(key1);

	cout << "input the key2" << endl;
	inputdata(key2);

	cout << "input the plaint" << endl;
	inputdata(plaintext);

	cout << "The plaintext encrypted by key1,we got ciphertext1" << endl;
	getarray(ciphertext1,plaintext,Plaintextsize);
	encrypt(ciphertext1,key1);
	outputdata(ciphertext1,Plaintextsize);

	cout << "The ciphertext1 decrypted by key1,we got the original plaintext" << endl;
	getarray(plaintext,ciphertext1,Plaintextsize);
	decrypt(plaintext,key1);
	outputdata(plaintext,Plaintextsize);

	cout << "The plaintext encrypted by key2,we got ciphertext2" << endl ;
	getarray(ciphertext2,plaintext,Plaintextsize);
	encrypt(ciphertext2,key2);
	outputdata(ciphertext2,Plaintextsize);

	cout << "The ciphertext2 decrypted by key2,we got the original plaintext" << endl ;
	getarray(plaintext,ciphertext2,Plaintextsize);
	decrypt(plaintext,key2);
	outputdata(plaintext,Plaintextsize);

	cout << "The number of different bits between ciphertext1 and ciphertext2: " << endl << getdifferentbits(ciphertext1,ciphertext2,Plaintextsize) << endl << endl;
}
void perform_encryption(){
	int plaintext[64];
	int ciphertext[64];
	int key[64];
	cout << "input the key" << endl;
	inputdata(key);

	cout << "input the plaint" << endl;
	inputdata(plaintext);

	cout << "The plaintext after encrypt,we got ciphertext" << endl;
	getarray(ciphertext,plaintext,Plaintextsize);
	encrypt(ciphertext,key);
	outputdata(ciphertext,Plaintextsize);
}
void perform_decryption(){
	int plaintext[64];
	int ciphertext[64];
	int key[64];

	cout << "input the key" << endl;
	inputdata(key);

	cout << "input the plaint" << endl;
	inputdata(ciphertext); 

	cout << "The ciphertext decrypted by key,we got the original plaintext" << endl;
	getarray(plaintext,ciphertext,Plaintextsize);
	decrypt(plaintext,key);
	outputdata(plaintext,Plaintextsize);
}
int main(){
	int cho;
	cout << "welcome to the simple DES system." << endl <<endl;
	while (1){
		cout << "enter a number to:" << endl;
		cout << "1.perform test a)" << endl;
		cout << "2.perform test b)" << endl;
		cout << "3.encrypt a 64-bit 0-1 string" << endl;
		cout << "4.decrypt a 64-bit 0-1 string" << endl;
		cout << "5.exit the system"<< endl;
		cin>>cho;
		switch (cho){
		case 1:testa();break;
		case 2:testb();break;
		case 3:perform_encryption();break;
		case 4:perform_decryption();break;
		default: return 0;
		}
	}
}