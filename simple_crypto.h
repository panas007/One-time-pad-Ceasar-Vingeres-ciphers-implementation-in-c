		if (ch1 >= '0' && ch1 <= '9'){
			
			int flag;
			a= ch-'9'+'A'-1;

			b=ch;
			//printf("%d : %d \n",a,b );


			if( (abs(ch) > '9' ) && (a <='Z'))
			{
				ch = ch-'9'+'A'-1;
				flag=1;
			}

			a=ch-'9'+'A';
			b=ch-'9'+'A'-'Z'+'a'-2;
			//printf("%d : %d \n",a,b );

			if((a > 'Z') && b<='a')
			{
				ch = ch-'9'+'A'-'Z'+'a'-2;
				flag=2;
			}

			a=ch-'9'+'A'-'Z'+'a';
			b=ch-'9'+'A'-'Z'+'a'-'z'+'0'-3;
			
			if( (b >= '0'))
			{
				ch = ch-'9'+'A'-'Z'+'a'-'z'+'0'-3;
				flag=3;
			}

			//printf("\nEncrypted message: %d flag :%d \n", ch,flag);

		}
		else if(ch1 >= 'a' && ch1 <= 'z'){
			int flag;
			a= ch-'z'+'0'-1;

			b=ch;
			//printf("%d : %d \n",a,b );


			if( (abs(ch) > 'z' ) && (a <='9'))
			{
				ch = ch-'z'+'0'-1;
				flag=1;
			}

			a=ch-'z'+'0';
			b=ch-'z'+'0'-'9'+'A'-2;
			//printf("%d : %d \n",a,b );

			if((a > '9') && b<='Z')
			{
				ch = ch-'z'+'0'-'9'+'A'-2;
				flag=2;
			}

			a=ch-'z'+'0'-'9'+'A';
			b=ch-'z'+'0'-'9'+'A'-'Z'+'a'-3;
			
			if( (b >= 'a'))
			{
				ch = ch-'z'+'0'-'9'+'A'-'Z'+'a'-3;
				flag=3;
			}


			//printf("\nEncrypted message: %d flag :%d \n", ch,flag);
		}
	    else if(ch >= 'A' && ch <= 'Z'){
	    	int flag;
			a= ch-'Z'+'a'-1;

			b=ch;
			//printf("%d : %d \n",a,b );


			if( (abs(ch) > 'a' ) && (a <='z'))
			{
				ch = ch-'Z'+'a'-1;
				flag=1;
			}

			a=ch-'Z'+'a';
			b=ch-'Z'+'a'-'z'+'0'-2;
			//printf("%d : %d \n",a,b );

			if((a > 'z') && b<='9')
			{
				ch = ch-'Z'+'a'-'z'+'0'-2;
				flag=2;
			}

			a=ch-'Z'+'a'-'z'+'0';
			b=ch-'Z'+'a'-'z'+'0'-'Z'+'a'-'z'+'A'-3;
			
			if( (b >= 'A'))
			{
				ch = ch-'Z'+'a'-'z'+'0'-'Z'+'a'-'z'+'A'-3;
				flag=3;
			}

				
			//ch = ch + key;	
		}