#ifndef ENCRYPTIONH
#define ENCRYPTIONH
#include "commentop.h"
void encrypt(int plaintext[],int key[]){
	crypt(plaintext,key,0);
}
#endif