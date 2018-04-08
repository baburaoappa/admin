/*
 * main.c
 *
 *  Created on: 07-Apr-2018
 *      Author: tanvi
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 10


struct Optab
{
	char inst[SIZE];
	int mnecode;
	char type[2];
};

struct IC
{
	int add;
	char mneCode[SIZE];
	int reg;
	char operand[SIZE];
	int LoC;
};

struct symtab
{
	char sym[SIZE];
	int address;
	int length;
	char RS[1];
};

struct littab
{
	int lit;
	int add;
};

struct reg
{
	char reg[SIZE];
};
struct control
{
	char inst[10];
};

int tokenize(char temp[] , char read[][100]);
int searchreg(char temp[] , struct reg r[]);
int search(char temp[] , struct Optab o[]);
int ictabgen(char read[][100] , struct Optab o[] , struct IC ic[] , struct reg r[] , struct control c[] , struct symtab s[] , struct littab l[]);
int symtabgen(struct symtab s[] , char temp[] , int add , int len , int sym);
int searchsymtab(char temp[] , struct symtab s[]);
int littabgen(struct littab l[] , int literal  , int lit , int add);

int j = 0;
int sym = 0;
int lit = 0;

int main(void)
{
	char ch = '\0';
	int rval = 0;
	char temp[20] = {'\0'};
	char read[100][100] = {{'\0'}};
	FILE * fout = NULL;
	struct symtab s[10];
	struct littab l[10];
	struct Optab o[18] = {{"STOP" , 0 , "IS"} , {"ADD" , 1 , "IS"} , {"SUB" , 2 , "IS"} , {"MULT" , 3 , "IS"} ,
				             {"DIV" , 8 , "IS"} , {"MOVER" , 4 , "IS"} , {"MOVEM" , 5 , "IS"} , {"COMP" , 6 , "IS"} ,
							 {"BC" , 7 , "IS"} , {"READ" , 9 , "IS"} , {"PRINT" , 10 , "IS"} , {"DC" , 1 , "DL"} ,
							 {"DS" , 2 , "DL"} , {"START" , 1 , "AD"} , {"END" , 2 , "AD"} , {"ORIGIN" , 3 , "AD"} ,
							 {"EQU" , 4 , "AD"} , {"LTORG" , 5 , "AD"}};

	struct reg r[] = {{"AREG"} , {"BREG"} , {"CREG"}};
	struct control c[] = {{"LT"} , {"LE"} , {"GT"} , {"GE"} , {"EE"} , {"ANY"}};
	struct IC ic[50];
	fout = fopen("/home/tanvi/input.txt" , "r");
	if(fout != NULL)
	{
		/*printf("\n\tThe input assembly program is:\n\n");
		ch = fgetc(fout);
		while(ch != EOF)
		{
			printf("%c" , ch);
			ch = fgetc(fout);
		}*/
		fclose(fout);
		fout = NULL;

		rval = tokenize(temp , read);
		rval = ictabgen(read , o , ic , r , c , s , l);

	}
	else
	{
		printf("\n\tFile opening error.");
	}

	return 0;
}

int tokenize(char temp[] , char read[][100])
{

	int rval = 0;
	int i = 0;

	int y = 0;
	int z = 0;
	char ch = '\0';
	char prev = '\0';
	FILE *fout = NULL;
	fout = fopen("/home/tanvi/input.txt" , "r");
	if(fout != NULL)
	{

		ch = fgetc(fout);
		while(ch != EOF)
		{
			if(ch >= 'A' && ch <= 'Z')
			{
				temp[i] = ch;
				temp[i+1] = '\0';
				i++;
				prev = ch;
				ch = fgetc(fout);
			}
			else if(ch == ' ' || ch == '\n' || ch == ',')
			{
				if(ch == ' ')
				{
					if(prev != ',')
					{
						strcpy(read[j] , temp);
						j++;
						i = 0;
						do
						{
							prev = ch;
							ch = fgetc(fout);
						}while(ch == ' ');
					}
					else
					{
						prev = ch;
						ch = fgetc(fout);
					}
				}
				else if(ch == '\n')
				{
					strcpy(read[j] , temp);
					j++;
					i = 0;
					while(ch == '\n')
					{
						prev = ch;
						ch = fgetc(fout);
						if(ch == '\n')
						{
							temp[i] = ch;
							temp[i+1] = '\0';
							i++;
							strcpy(read[j] , temp);
							j++;
							i = 0;
						}
					}
				}
				else if(ch == ',')
				{
					prev = ch;
					ch = fgetc(fout);
					temp[i] = prev;
					temp[i+1] = '\0';
					i++;
					strcpy(read[j] , temp);
					j++;
					i = 0;
				}
			}
			else if(ch >= '0' && ch <= '9')
			{
				temp[i] = ch;
				temp[i+1] = '\0';
				i++;
				prev = ch;
				ch = fgetc(fout);
			}
			else if(ch == ':')
			{
				strcpy(read[j] , temp); //store value before :
				j++;
				i = 0;
				temp[i] = ch;
				temp[i+1] = '\0';
				i++;
				prev = ch;
				ch = fgetc(fout);
			}
			else if(ch == '=')
			{
				temp[i] = ch;
				temp[i+1] = '\0';
				i++;
				strcpy(read[j] , temp);
				j++;
				i = 0;
				ch = fgetc(fout);
				if(ch == '\'')
				{
					ch = fgetc(fout);
					do
					{
						temp[i] = ch;
						temp[i+1] = '\0';
						i++;
						ch = fgetc(fout);
					}while(ch != '\'');
					/*strcpy(read[j] , temp);
					j++;
					i = 0;*/
				}
			}
			else
			{
				ch = fgetc(fout);
			}

		}
		fclose(fout);
		fout = NULL;

	}

	/*for(y = 0 ; y < j ; y++)
	{
		printf("\n\t%s" , read[y]);
	}
	int add = 0;
	add = atoi(read[1]);

	printf("\n\tAddress is: %d" , add);
*/
	return rval;

}

int search(char temp[] , struct Optab o[])
{
	int rval = -1;
	int i = 0;
	for(i = 0 ; i < 18 ; i++)
	{
		if(strcmp(temp , o[i].inst) == 0)
		{
			rval = i;
		}
	}
	return rval;
}

int searchreg(char temp[] , struct reg r[])
{
	int rval = -1;
	int i = 0;

	for(i = 0 ; i < 3 ; i++)
	{
		if((strcmp(temp , r[i].reg) == 0))
		{
			rval = i;
		}
	}

	return rval;
}

int searchcontrol(char temp[] , struct control r[])
{
	int rval = -1;
	int i = 0;

	for(i = 0 ; i < 6 ; i++)
	{
		if((strcmp(temp , r[i].inst) == 0))
		{
			rval = i;
		}
	}

	return rval;
}

int searchsymtab(char temp[] , struct symtab s[])
{
	int rval = -1;
	int i = 0;

	for(i = 0 ; i < sym ; i++)
	{
		if(strcmp(temp , s[i].sym) == 0)
		{
			rval = i;
		}
	}

	return rval;
}

int searchlittab(int literal , struct littab l[])
{
	int rval = -1;
	int i = 0;

	for(i = 0 ; i < lit ; i++)
	{
		if(literal == l[i].lit)
		{
			rval = i;
		}
	}

	return rval;
}

int ictabgen(char read[][100] , struct Optab o[] , struct IC ic[] , struct reg r[] , struct control c[] , struct symtab s[] , struct littab l[])
{
	int rval = -1;
	int rval1 = -1;
	int rval2 = -1;
	int rvalsymtab = -1;
	int i = 0;
	int z = 0;
	int add = 0;
	int rval6 = -1;
	add = atoi(read[1]);
	char tempadd[10] = {'\0'};


	for(i = 0 ; i < j ; i++)
	{
		rval = search(read[i] , o);
		rval1 = searchreg(read[i] , r);
		if(rval >= 0)
		{


			if(strcmp(o[rval].type , "AD") == 0)
			{
				int x = 0;
				strcpy(ic[z].mneCode , "AD , 0");
				sprintf(tempadd, "%d", o[rval].mnecode);
				strcat(ic[z].mneCode , tempadd);
				strcpy(ic[z].operand , "C , ");
				sprintf(tempadd, "%d", add);
				strcat(ic[z].operand , tempadd);
				if((strcmp(o[rval].inst , "START") != 0) || (strcmp(o[rval].inst , "END") != 0))
				{
					ic[z].add = add;
					ic[z].LoC = add;

				}
				if((strcmp(o[rval].inst , "END") == 0))
				{
					ic[z].add = add;
					int a = 0;

					for(a = x+1 ; a < lit ; a++)
					{
						l[a].add = add;
						add++;
					}
				}

				if((strcmp(o[rval].inst , "START") == 0))
				{
					ic[z].LoC = add;
				}

				ic[z].reg = 0;
			//	add++;
				if((strcmp(o[rval].inst , "LTORG") == 0))
				{

					printf("\n\tLIT = %d" , lit);
					for(x = 0 ; x < lit ; x++)
					{
						l[x].add = add;
						add++;
					}

				}

				z++;
			}
			else if(strcmp(o[rval].type , "IS") == 0)
			{
				ic[z].add = add;
				strcpy(ic[z].mneCode , "IS , 0");
				sprintf(tempadd, "%d", o[rval].mnecode);
				strcat(ic[z].mneCode , tempadd);
				if((strcmp(o[rval].inst , "READ") == 0) || (strcmp(o[rval].inst , "PRINT") == 0) || (strcmp(o[rval].inst , "BC") == 0))
				{
					if((strcmp(o[rval].inst , "BC") == 0))
					{
						rval2 = searchcontrol(read[i+1] , c);
						if(rval2>=0)
						{
							ic[z].reg = rval2+1;
						}
						else
						{
							ic[z].reg = 0;
						}
					}
					/*strcpy(ic[z].operand , read[i+3]);*/
					rval6 = searchsymtab(read[i+3] , s);
					if(rval6 < 0)
					{
						rvalsymtab = symtabgen( s , read[i+3] , 0 , 1 , sym);
						strcpy(ic[z].operand , "S , 0");
						sprintf(tempadd, "%d", rvalsymtab);
						strcat(ic[z].operand , tempadd);
						sym++;

					}
					else
					{
							strcpy(ic[z].operand , "S , 0");
							sprintf(tempadd, "%d", rval6);
							strcat(ic[z].operand , tempadd);
					}

					add++;
					ic[z].LoC = add;
				}
				else
				{
					rval1 = searchreg(read[i+1] , r);
					if(rval1>=0)
					{
						ic[z].reg = rval1+1;
					}
					else
					{
						ic[z].reg = 0;
					}

					rval6 = searchsymtab(read[i+3] , s);
					if(rval6 < 0)
					{
						rvalsymtab = symtabgen( s , read[i+3] , 0 , 1 , sym);
						strcpy(ic[z].operand , "S , 0");
						sprintf(tempadd, "%d", rvalsymtab);
						strcat(ic[z].operand , tempadd);
						sym++;

					}
					else
					{
							strcpy(ic[z].operand , "S , 0");
							sprintf(tempadd, "%d", rval);
							strcat(ic[z].operand , tempadd);
					}

					add++;
					ic[z].LoC = add;
				}

				z++;
			}
			else if(strcmp(o[rval].type , "DL") == 0)
			{
				ic[z].add = add;
				strcpy(ic[z].mneCode , "DL , 0");
				sprintf(tempadd, "%d", o[rval].mnecode);
				strcat(ic[z].mneCode , tempadd);
				ic[z].reg = 0;


				if((strcmp(o[rval].inst , "DC") == 0))
				{
					strcpy(ic[z].operand , read[i+1]);
					rval6 = searchsymtab(read[i-1] , s);
					if(rval6 >= 0)
					{
						symtabgen(s , read[i-1] , add , 1 , rval6);
					}
					add = add+1;
				}
				else
				{
					strcpy(ic[z].operand , read[i+1]);
					rval6 = searchsymtab(read[i-1] , s);
					if(rval6 >= 0)
					{
						symtabgen(s , read[i-1] , add , atoi(read[i+1]) , rval6);
					}
					add = add + atoi(read[i+1]);
				}


				ic[z].LoC = add;
				z++;
			}


		}
		else
		{
			if(strcmp(read[i] , "=") == 0)
			{
				int x = atoi(read[i+1]);
				rval6 = littabgen(l , x , lit , 0);
				lit++;
			}
			else if(strcmp(read[i+1] , ":") == 0)
			{
				rval = searchsymtab(read[i] , s);
				if(rval < 0)
				{
					rvalsymtab = symtabgen( s , read[i] , add , 0 , sym);
					sym++;
				}
				else
				{
					s[rval].address = add;	//for already added labels
				}


			}
		}
	}

	int k = 0;
	for(k = 0 ; k < z ; k++)
	{
		printf("\n\t%d\t%s\t%d\t%s\t%d" , ic[k].add , ic[k].mneCode , ic[k].reg , ic[k].operand , ic[k].LoC);
	}

	printf("\n\t SYMTAB");
	for(i = 0 ; i < sym ; i++)
	{
		printf("\n\t%s \t %d \t %d \t %s" , s[i].sym , s[i].address , s[i].length , s[i].RS);
	}

	printf("\n\tLITTAB");
	printf("\n\tHere lit is: %d" , lit);
	for(i = 0 ; i < lit ; i++)
	{
		printf("\n\t%d \t %d" , l[i].lit , l[i].add);
	}
	return rval;


}

int symtabgen(struct symtab s[] , char temp[] , int add , int len , int sym)
{
	int rval = 0;


	strcpy(s[sym].sym , temp);
	s[sym].address = add;
	s[sym].length = len;
	strcpy(s[sym].RS , "R");
	rval = sym;



	return rval;
}

int littabgen(struct littab l[] , int literal  , int lit , int add)
{
	int rval = 0;

	l[lit].lit = literal;
	l[lit].add = add;

	return rval;
}















