#include<stdio.h>
#include<unistd.h>
#include<string.h>

typedef struct ic{
	char address[10];
	char mnemonics[10];
	char operand1[10];
	char operand2[10];
}ic;

typedef struct symbol{
	int serial_no;
	char symbol_name[10];
	int address;
	int length;
	int value;
}symbol;

typedef struct litral{
	int serial_no;
	char litral_name[10];
	char address[10];
}litral;

typedef struct target{
	char address[10];
	char mnemonics[10];
	char operand1[10];
	char operand2[10];
}target;

int search_in_ST(int serial_no){
	symbol sym; 
	int flag,position;
	FILE *fsym;
	flag=position=-1;
	fsym = fopen("symboltable.txt","r");
	fscanf(fsym,"%4d %10s %4d %4d %4d",&sym.serial_no,sym.symbol_name,&sym.address,&sym.length,&sym.value);
	while(!feof(fsym)){
		if(serial_no==sym.serial_no){
			flag=1;
			position=sym.address;
			break;
		}
		fscanf(fsym,"%4d %10s %4d %4d %4d",&sym.serial_no,sym.symbol_name,&sym.address,&sym.length,&sym.value);
	}
	fclose(fsym);
	if(flag==1){
		return position;
	}
	else{
		return -1;
	}
}
int search_in_LT(int serial_no){
	litral l;
	int flag,position;
	FILE *flt;
	flag=position=-1;
	flt = fopen("literal.txt","r");
	fscanf(flt,"%4d %10s %10s",&l.serial_no,l.litral_name,&l.address);
	while(!feof(flt)){
		if(serial_no==l.serial_no){
			flag=1;
			position=atoi(l.address);
			break;
		}
		fscanf(flt,"%4d %10s %10s",&l.serial_no,l.litral_name,&l.address);
	}
	fclose(flt);
	if(flag==1){
		return position;
	}
	else{
		return -1;
	}
}

void main()
{
	ic i;
	symbol s;
	litral l;
	target t;
	int flag=0,symbol_position,symbol_positionl,address_of_sym,x;
	char s1[10],s2[10],str[10],opstr[10],s3[10],s4[10],opstr1[10],s5[10],s6[10],s7[10],s8[10],var[10];
	FILE *fic,*fsym,*flit,*ftar;
	ftar=fopen("targetcode.txt","w+");
	fic=fopen("ic.txt","r");
	//fsym=fopen("symboltable.txt","r");
	//flit=fopen("literal.txt","r");
	fscanf(fic,"%s %s %s %s",i.address,i.mnemonics,i.operand1,i.operand2);
	
	while(!feof(fic))
		{
			
			if(strcmp(i.address,"*")==0)
				{
					
					flag=1;
					//break;
					
				}
				
			else
			{	
				
				
				strcpy(str,i.mnemonics);
				if(str[0]=='=')                                 //LITERAL Condition
				   {
				    fprintf(ftar,"%s %s * *\n",i.address,i.mnemonics);
			           }//LITERAL
			           
			        else if(str[1]=='D')
			        	{
			        		
				    		fprintf(ftar,"%s 00 00 00\n",i.address);
			        		
			        	}  
	

				else
			      {
				
				strcpy(s1,strtok(str,",")); //string tokenization , is the partition element tyachya left cha sagla milta
				strcpy(s2,strtok(NULL,")")); //the string already exists in the heap so we pass NULL
				strcpy(opstr,i.operand1); //single operand instrn tar 1st opnd is compulsory symbol if there are 2 opnds 1st is reg and 2nd is lit or symbol
//example of single operand is read A 
				strcpy(opstr1,i.operand2);
				
				if(opstr[1]=='S')
				{	
				
				  strcpy(s3,strtok(opstr,","));
				  strcpy(s4,strtok(NULL,")"));
				  x=atoi(s4);
				  symbol_position = search_in_ST(x);
				  fprintf(ftar,"%s %s %d *\n",i.address,s2,symbol_position);
				}
			       else if(opstr[1]=='R')
			             {
			             
			               strcpy(s3,strtok(opstr,","));
				       strcpy(s4,strtok(NULL,")"));
			               if(opstr1[1]=='S')
			                  {
			                   
			                    strcpy(s5,strtok(opstr1,","));
				            strcpy(s6,strtok(NULL,")"));
				            x=atoi(s6);
				            symbol_position = search_in_ST(x);
			                    fprintf(ftar,"%s %s %s %d\n",i.address,s2,s4,symbol_position);
			                  }//if
			                else
			                 {
			                  
			                   strcpy(s5,strtok(opstr1,","));
				           strcpy(s6,strtok(NULL,")"));
				           x=atoi(s6);
				           symbol_positionl = search_in_LT(x);
				    //printf("%d",symbol_positionl);
				           fprintf(ftar,"%s %s %s %d\n",i.address,s2,s4,symbol_positionl);    
			                 }//else  
			             }//elseifR
			       else if(opstr[0]=='*') //no opnd1 instruction like stop
			              fprintf(ftar,"%s %s * *\n",i.address,s2);
			              
			       else if(opstr[1]=='c')
			          {
			              
			               strcpy(s3,strtok(opstr,","));
				       strcpy(s4,strtok(NULL,")"));
				       fprintf(ftar,"%s %s %s *\n",i.address,s2,s4);
			          }   
			          
			         /* else{		                                //Conditional Check
			                
					 var[0]=opstr[1];
					 var[1]=opstr[2];
					 var[2]='\0';	
					 
					     if(opstr1[1]=='S')
			                  {
			                   
			                    strcpy(s5,strtok(opstr1,","));
				            strcpy(s6,strtok(NULL,")"));
				            x=atoi(s6);
				            symbol_position = search_in_ST(x);
			                    fprintf(ftar,"%s %s %s %d\n",i.address,s2,var,symbol_position);
			                  }//if
			                else
			                 {
			                   strcpy(s5,strtok(opstr1,","));
				           strcpy(s6,strtok(NULL,")"));
				           x=atoi(s6);
				           symbol_positionl = search_in_LT(x);
	               		           fprintf(ftar,"%s %s %s %d\n",i.address,s2,var,symbol_positionl);    
			                 }//else  
			             }//elseifR					          
			          	 
			             */	
                           }//else	  
	           }//else
	fscanf(fic,"%s %s %s %s",i.address,i.mnemonics,i.operand1,i.operand2);		
	//flag=0;
	}//while				
        fclose(fic);
	fclose(ftar);
	//fclose(flit);
	//fclose(fsym);
	printf("\nTarget Code Generated");
}//main
