#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int  isdauphancach(char c,char* dauphancach){
  int i=0;
  for(i=0;i<20;i++){
    if(c==dauphancach[i])
      return 1;
   
  }
  return 0;
}
typedef struct treenode{
  struct treenode *left;
  struct treenode *right;
  char * key;
  int tongsoluong;
  int mangcacdong[100];
  int tongsodong;
}treenode;

void duyetcay(treenode *root){
  if(root!=NULL)
    {
       duyetcay(root->left);
      
       printf("%s %d ",(char *)root->key,(root->tongsoluong));
       for(int i=0;i<root->tongsodong;i++)
	{
	
	  printf("%d ", (root->mangcacdong)[i]);
	  }
      printf("\n");
      duyetcay(root->right);
    }
}
void inserttotree(treenode **root,char *key,int donghientai){
  if((*root)==NULL){
    int a=0;
    
    *root=(treenode *)malloc(sizeof(treenode));
    (*root)->key=(char *)malloc(sizeof(char)*(strlen(key)+1));
    strcpy((*root)->key,key);
    // printf("%d %s\n",sizeof(char)*strlen(key),key);
  
    ((*root)->mangcacdong)[0]=donghientai;
    (*root)->tongsodong=1;
    (*root)->tongsoluong=1;
    (*root)->left=NULL; 
    (*root)->right=NULL;
   
  }
  else{
    int c=strcmp((char *)(*root)->key,key);
    if(c==0){
      int checktotai=0;
      for(int i=0;i<(*root)->tongsodong;i++)
	{
	  if(donghientai==((*root)->mangcacdong)[i])
	    checktotai=1;

	}
      if(checktotai==0)
	{
	  ((*root)->mangcacdong)[(*root)->tongsodong]=donghientai;
	  (*root)->tongsodong++;

	}
     
      (*root)->tongsoluong++;
    }
    else
      if(c>0){
	inserttotree(&((*root)->left),key,donghientai);
      }
      else{
	inserttotree(&((*root)->right),key,donghientai);
      }
  
  }
}

int main(){
  // dinh nghia cac input cho chuong trinh
  FILE *fstopw = fopen("stopw.txt", "r");
  FILE *fvanban = fopen("vanban.txt", "r");
  char dauphancach[] = {' ','\n','\t','.',',',';',':','\'','1','2','3','4','5','6','7','8','9','0','(',')',EOF};


  // xu li du lieu tho

  char stopw[50][30];
  int stopwlen=0;
  while(1){
    if(feof(fstopw))break;
    fscanf(fstopw,"%s%*[\n]",stopw[stopwlen]);
    stopwlen++;
   
  }
  stopwlen--;



// tao hash table

treenode * tree=NULL;

int i=0;
char c;
int ketthuccau=0;
int donghientai=1;
char word[100];
char f=' ';
char* strtemp;
while(!feof(fvanban)){
ketthuccau=0;
//bo qua cac ky hieu, lưu lại xem co dau cham hay khong+
//luu so dong hien tai+luu lai ky tu chu dau tien
if(f=='.'||f=='!'||f=='?') ketthuccau=1;
if(f=='\n') donghientai++;
do{c=fgetc(fvanban);
     
// printf("%c ", c);
if(c=='.'||c=='!'||c=='?')
  ketthuccau=1;
if(c=='\n') donghientai++;
if(c==EOF) break;
      
}
 while(isdauphancach(c,dauphancach));

if(c==EOF) break;
//doc het tu + luu ky tu phan cach dau tien lai
//printf("%c %d %d\n",c,ketthuccau,donghientai);
word[0]=c;
i=0;
do{
f=fgetc(fvanban);

if(!isdauphancach(f,dauphancach))
  {//printf("%d\n", f);
word[++i]=f;}
 else break;
}
 while(1);
word[++i]='\0';

//kiemtra co phai ten rieng hay khong
//printf("%s\n",(word));
 if(word[0]!='\0')
   if( ketthuccau==1||(word[0]>='a' && word[0]<='z'))
     {// neu khong phai thi them vao cay nhi phan

       for(int i=0;i<sizeof(word);i++)
	 {
	   word[i]=tolower(word[i]);
	 }
       inserttotree(&tree,word,donghientai);
       //printf("insert %s %d\n",word,donghientai); 

     }
 }
a:;
duyetcay(tree);
  return 0;
}
