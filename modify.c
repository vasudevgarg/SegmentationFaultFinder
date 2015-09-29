int check_main(FILE *fp)
{
	char str[]={'a','i','n','('};
	int i,flag=0;
	char x;
	for(i=0;i<4;i++)
	{
		x=fgetc(fp);
		if(x==str[i])
			continue;
		else
		{
			flag=1;
		}
	}
	if(flag==1)
	{
		fseek(fp,-4,SEEK_CUR);
		return -1;
	}
	else
	{
		return 1;	
	}
}
void modify(FILE *fp)
{
	FILE *ft;
	ft=fopen("copy.c","w");
	char ch;
	int count=1,flag=0,no=0;
	fputs("#include<stdio.h>\n#include<signal.h>\n#include<stdlib.h>\n",ft);
	fputs("int ABCDEF=0;\n",ft);
	fprintf(ft,"void sig_handler(int signum){\n");
	fprintf(ft,"printf(\"Segmentation fault arrived at line=");
	fputs("%d\\n\",ABCDEF);\n",ft);
	fputs("exit(0);\n}\n",ft);
	while((ch=fgetc(fp))!=EOF)
	{
		if(ch=='{')
			no++;
		if(ch=='}'&&no>0)
			no--;
		if(ch=='m')
		{
			int ret=check_main(fp);
			if(ret==1)
			{
				fputs("main(",ft);
				while((ch=fgetc(fp))!='{')
				{
					if(ch=='\n')
						count++;
					fputc(ch,ft);
				}
				if(ch=='{')
					no++;
				fputc(ch,ft);
				fputs("signal(SIGSEGV,sig_handler);",ft);
				continue;
			}	
		}
		
		if(ch=='\n')
		{	count++;
			//printf("count=%d\n",count);
			fseek(fp,-2,SEEK_CUR);
			ch=fgetc(fp);
			if(ch==')'||ch=='>'||ch=='}')
				flag=1;
			ch=fgetc(fp);
			if(!flag&&no>0)
				fprintf(ft,"\nABCDEF=%d;\n",count);
			flag=0;
		}
		fputc(ch,ft);
	}
	fclose(ft);
//	fseek(ft,5,SEEK_SET);
//	printf("%c\n",fgetc(ft));
//	while(fgetc(ft)!='{')
//	;
//	fputs("signal(SIGSEGV,sig_handler);",ft);
/*	fscanf(ft,"%s",temp);
	printf("%s\n",temp);
	char str[]="int main()";
	int i=10;
	while(i--)
	{
		if(strcmp(temp,str)==0)
		{
			printf("sdjf\n");
			fputs("hello",ft);
			break;
		}
		fscanf(fp,"%s",temp);
		printf("%s\n",temp);	
	}

*/
	
}
