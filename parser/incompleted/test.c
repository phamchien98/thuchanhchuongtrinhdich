#include <stdio.h>
int main(int argc, char *argv[])
{
	FILE *result,*runresult;
	result=fopen(argv[1],"r");
	runresult=fopen(argv[2],"r");

	char a,b;
	int line=0;
	do{

		fscanf(result,"%c",&a);
		fscanf(runresult,"%c",&b);
		if(a=='\n'){
			line++;
		}
		if(a!=b){
			printf("%s in line %d \n",argv[1],line );
			return 1;
		}
	}while(!feof(result)&&!feof(runresult));
	printf("ok");
	return 0;

}
