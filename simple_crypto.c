#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_crypto.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

 char* savedkey;
 int total_len;
 int *flags;
 char alhpabet[62];

char * encrypt_one_time_pad(char* etext)
{

	total_len=strlen(etext);
	int i,j;
	//int randomData = open("/dev/urandom", O_RDONLY);
	FILE * fp = fopen("/dev/urandom", "r");
	char* encrypted_text;

	encrypted_text= (char*) malloc(total_len* sizeof(char));
	savedkey= (char*) malloc(total_len* sizeof(char));
	flags= (int*) malloc(total_len* sizeof(int));
	char key[total_len];

	/*Remove special chars from input if they exist*/
	for(i=0;i<total_len;i++)
	{
		while (!(etext[i] >= 'a' && etext[i] <= 'z') && !(etext[i] >= 'A' && etext[i] <= 'Z') && !(etext[i] >= '0' && etext[i] <= '9') && !(etext[i] == '\0')) 
		{
			for(j = i; etext[j] != '\0'; ++j)
			{
				etext[j] = etext[j+1];
			}
				etext[j] = '\0';
		}
	}


	etext[i]='\0';
	//printf("New input. %s : \n",etext);

	total_len=strlen(etext);

	/*if (randomData < 0)
	{
    	printf("Error in open /dev/urandom");
    	exit(-1);
	}
	else
	{*/

    	//ssize_t result = read(randomData, key, sizeof key);
    	fread(&key, 1, total_len+1,fp);
    	while(strlen(key)<(total_len+1))
    	{
    		//printf("i am in \n");
    		fread(&key, 1, total_len+1,fp);
    	}
    	//printf("%s : %d \n", key , strlen(key));
    	/*if (result < 0)
    	{
        	printf("Error in open /dev/urandom");
    		exit(-1);
    	}*/
	//}

	for(i=0;i<total_len;i++)
	{
		if ((etext[i]>=48 && etext[i]<=57  ) ||  (etext[i]>=65 && etext[i]<=90) ||  (etext[i]>=97 && etext[i]<=122) )
		{
			encrypted_text[i] =  (char )((int)key[i]^ (int)etext[i]);

			//printf("%d : %c : %c : %d ", i,etext[i], encrypted_text[i]  , encrypted_text[i] );

			if ((int)encrypted_text[i]<-33 && ((int)encrypted_text[i]!=-127 && (int)encrypted_text[i] != -128 ))
			{
				encrypted_text[i]=abs(encrypted_text[i]);
				flags[i]=0;
			}
			else if ((int)encrypted_text[i]<0)
			{
				encrypted_text[i]=abs(encrypted_text[i])+33;
				flags[i]=1;
			}
			else if ((int)encrypted_text[i]<33)
			{
				encrypted_text[i]=encrypted_text[i]+33;
				flags[i]=2;
			}
			else if (((int)encrypted_text[i]==-127 || (int)encrypted_text[i] == -128 ))
			{
				encrypted_text[i]=abs(encrypted_text[i])-5;
				flags[i]=3;
			}
			else if (((int)encrypted_text[i]==127 || (int)encrypted_text[i] == 128 ))
			{
				encrypted_text[i]=encrypted_text[i]-5;
				flags[i]=4;
			}
			else
				flags[i]=5;

			//printf(" %c : %d  : %d \n", encrypted_text[i]  , encrypted_text[i] , flags[i]);
		}


	}

	strcpy(savedkey, key);
	//printf("%s\n%s\n",key,savedkey );
	//printf("%d\n%d\n",strlen(key),strlen(savedkey) );

	return encrypted_text;
}

char * decrypt_one_time_pad(char* dtext)
{
	int i,ans;
	char *plaintext= (char*) malloc(total_len* sizeof(char));
	//printf("%s\n", savedkey);

	for(i=0;i<total_len;i++)
	{
		//printf("3. %c : %d \n", dtext[i]  , dtext[i] );
		if (flags[i]==0)
		{
			//printf("%d.. %d : ",i,flags[i]);
			plaintext[i] =  (char )savedkey[i]^((-1)*(int)dtext[i]);
			ans=((-1)*(int)dtext[i]);
			//printf("Decrypt :  %c : %c : %d : %d \n", dtext[i]  ,plaintext[i],savedkey[i], ans);
		}
		else if (flags[i]==1)
		{
			//printf("%d.. %d : ",i,flags[i]);
			plaintext[i] =  (char )savedkey[i]^((-1)*((int)dtext[i]-33));
			ans=((-1)*((int)dtext[i]-33));
			//printf("Decrypt :  %c : %c : %d : %d \n", dtext[i]  ,plaintext[i],savedkey[i], ans);
		}
		else if (flags[i]==2)
		{
			//printf("%d.. %d : ",i,flags[i]);
			plaintext[i] =  (char )savedkey[i]^((int)dtext[i]-33);
			ans=((int)dtext[i]-33);
			//printf("Decrypt :  %c : %c : %d : %d \n", dtext[i]  ,plaintext[i],savedkey[i], ans);
		}
		else if (flags[i]==3)
		{
			//printf("%d.. %d : ",i,flags[i]);
			plaintext[i] =  (char )savedkey[i]^((-1)*((int)dtext[i]+5));
			ans=((int)dtext[i]+5);
			//printf("Decrypt :  %c : %c : %d : %d \n", dtext[i]  ,plaintext[i],savedkey[i], ans);
		}
		else if (flags[i]==4)
		{
			//printf("%d.. %d : ",i,flags[i]);
			plaintext[i] =  (char )savedkey[i]^(((int)dtext[i]+5));
			ans=((int)dtext[i]+5);
			//printf("Decrypt :  %c : %c : %d : %d \n", dtext[i]  ,plaintext[i],savedkey[i], ans);
		}
		else if (flags[i]==5)
		{
			//printf("%d.. %d : ",i,flags[i]);
			plaintext[i] =  (char )savedkey[i]^(dtext[i]);
			ans=dtext[i];
			//printf("Decrypt :  %c : %c : %d : %d \n", dtext[i]  ,plaintext[i],savedkey[i], ans);
		}
		//printf("Decrypt :  %c : %c : %d \n", dtext[i]  ,plaintext[i], dtext[i]);

	}

	return plaintext;
}


char * encrypt_Caesars(char* etext,int shift)
{
	total_len=strlen(etext);
	int i,j=48;
	char* encrypted_text;
	shift=shift % 62;
	int total_shift;
	encrypted_text= (char*) malloc(total_len* sizeof(char));

	for ( i=0;i<10;i++) 
	{
    	alhpabet[i]=(char)j;
    	j++;
	}
	j=65;
	for ( i=10;i<36;i++) 
	{
    	alhpabet[i]=(char)j;
    	j++;
    	//printf("%c",alhpabet[i]);
	}
	j=97;
	for ( i=36;i<62;i++) 
	{
    	alhpabet[i]=(char)j;
    	j++;
	}


	for ( i=0;i<total_len;i++) 
    { 

    	for ( j=0;j<62;j++) 
    	{ 
    		if (alhpabet[j]==etext[i])
    			break;
    	}
    	//printf("\n%c",alhpabet[j]);
    	total_shift=j+shift;
    	if (total_shift	<62)
    		encrypted_text[i]=(char)alhpabet[total_shift];
    	else
    		encrypted_text[i]=(char)alhpabet[total_shift-62];
    } 
  
    // Return the resulting string 
    return encrypted_text; 
} 



char * decrypt_Caesars(char* dtext,int shift)
{
	total_len=strlen(dtext);
	int i,j;
	char* plaintext;
	shift=shift % 62;
	int total_shift;
	plaintext= (char*) malloc(total_len* sizeof(char));


	for ( i=0;i<total_len;i++) 
    { 

    	for ( j=0;j<62;j++) 
    	{ 
    		if (alhpabet[j]==dtext[i])
    			break;
    	}
    	//printf("\n%c",alhpabet[j]);
    	total_shift=j-shift;
    	if (total_shift	>=0)
    		plaintext[i]=(char)alhpabet[total_shift];
    	else
    		plaintext[i]=(char)alhpabet[62+total_shift];
    } 
  
    // Return the resulting string 
    return plaintext; 
} 


char * encrypt_Vigeneres(char* etext,char * key)
{
	total_len=strlen(etext);
	int key_len  = strlen(key);
	int i,j=0;
	char* encrypted_text;

	//printf("1");
	encrypted_text= (char*) malloc(total_len* sizeof(char));
	char * newKey =(char*) malloc(total_len* sizeof(char));
	//printf("2");
	for(i = 0; i < total_len; i++){
        if(j == key_len)
            j = 0;
 
        newKey[i] = key[j];
        j++;
    }
    newKey[i] = '\0';

    for(i = 0; i < total_len; i++)
        encrypted_text[i] = ((etext[i] + newKey[i]) % 26) + 'A';
 
    encrypted_text[i] = '\0';

	return encrypted_text;
}


char * decrypt_Vigeneres(char* dtext,char * key)
{
	total_len=strlen(dtext);
	int key_len  = strlen(key);
	int i,j=0;
	char* plaintext;

	plaintext= (char*) malloc(total_len* sizeof(char));

	char * newKey =(char*) malloc(total_len* sizeof(char));

	for(i = 0; i < total_len; i++){
        if(j == key_len)
            j = 0;
 
        newKey[i] = key[j];
        j++;
    }
    //i++;

    newKey[i] = '\0';

	for(i = 0; i < total_len; i++)
        plaintext[i] = (((dtext[i] - newKey[i]) + 26) % 26) + 'A';
    //etext[i]i++;
 
    plaintext[i] = '\0';

    return plaintext; 
}