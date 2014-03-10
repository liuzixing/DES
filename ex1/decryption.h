#ifndef DECRYPTIONH
#define DECRYPTIONH
#include "commentop.h"
void decrypt(int plaintext[],int key[]){
	crypt(plaintext,key,1);
}
#endif