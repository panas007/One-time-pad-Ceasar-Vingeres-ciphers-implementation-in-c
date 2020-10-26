#include <stdio.h>
#include <stdlib.h>
#include "simple_crypto.h"
#include <string.h>

char *readString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}





void main( int argc , char * argv [])
{


	/*************One-time pad Cipher **************/
	//char ptext[100];
	char *ptext;
	char * encrypted_data;
	char * decrypted_data;

	printf("[OTP] input: ");
	//fgets(ptext, 100, stdin);
	ptext=readString(stdin,100);

	int ln = strlen(ptext)-1;
	if (ptext[ln] == '\n')
    	ptext[ln] = '\0';

	encrypted_data = encrypt_one_time_pad(ptext);
	decrypted_data = decrypt_one_time_pad(encrypted_data);


	printf("[OTP] encrypted: %s\n", encrypted_data);
	printf("[OTP] decrypted: %s\n", decrypted_data);

	free(ptext);


	/***********Caesars] Cipher **************/
	//char   ctext[100];
	char   *ctext;
	char * encrypted_data_c;
	char * decrypted_data_c;
	int key_c;

	printf("[Caesars] input: ");
	//fgets(ctext, 100, stdin);
	ctext=readString(stdin,100);

	ln = strlen(ctext)-1;
	if (ctext[ln] == '\n')
    	ctext[ln] == '\0';

    printf("[Caesars] key: ");
	scanf("%d",&key_c);
	getchar();

	encrypted_data_c = encrypt_Caesars(ctext,key_c);
	decrypted_data_c = decrypt_Caesars(encrypted_data_c,key_c);

	printf("[Caesars] encrypted: %s\n", encrypted_data_c);
	printf("[Caesars] decrypted: %s\n", decrypted_data_c);
	
	free(ctext);

	/*********** Vigeneres Cipher demo **************/
	//char newtext[100];
	//char key_v[100];

	char *newtext;
	char *key_v;

	printf("[Vigenere] input: ");
	//fflush(stdin);
	//fgets(newtext, 100, stdin);
	newtext=readString(stdin,10);

	ln = strlen(newtext)-1;
	if (newtext[ln] == '\n')
    	newtext[ln] = '\0';

	printf("[Vigenere] key: ");
	//fgets(key_v, 100, stdin);
	key_v=readString(stdin,10);

	ln = strlen(key_v)-1;
	if (key_v[ln] == '\n')
    	key_v[ln] = '\0';

	//printf("%s  :  %d",kk,strlen(kk));
	char * encr ;
	char * decr ;

	encr = encrypt_Vigeneres(newtext,key_v);
	decr = decrypt_Vigeneres(encr,key_v);


	printf("[Vigenere] encrypted: %s\n", encr);
	printf("[Vigenere] decrypted: %s\n", decr);

	free(newtext);
	free(key_v);

}