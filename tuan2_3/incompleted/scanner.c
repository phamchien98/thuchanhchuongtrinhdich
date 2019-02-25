/* Scanner
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
#include "charcode.h"
#include "token.h"
#include "error.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

extern CharCode charCodes[];


FILE *output;

/***************************************************************/

void skipBlank() {

  // TODO
  readChar();
  if(charCodes[currentChar]==CHAR_SPACE&&currentChar!=EOF)
  {
    skipBlank();
  }
}

void skipComment() {
  // TODO
	
	while(1){
		readChar();
		if(currentChar==-1)
			error(ERR_ENDOFCOMMENT,lineNo,colNo);
		if(charCodes[currentChar]==CHAR_TIMES){
			readChar();
			if(charCodes[currentChar]==CHAR_RPAR)
				break;
		}

	}
	
}

Token* readIdentKeyword(void) {
  // TODO
	int count=0;

	Token *a=makeToken(TK_IDENT,lineNo,colNo);
	do{
		a->string[count++]=currentChar;
		readChar();
	}
	while(charCodes[currentChar]==CHAR_LETTER||charCodes[currentChar]==CHAR_DIGIT);

	a->string[count] = '\0';

  if (count > MAX_IDENT_LEN) {
    
    error(ERR_IDENTTOOLONG, lineNo, colNo - count);
  } 
  else {
    TokenType type = checkKeyword(a->string);
    if (type != TK_NONE) {
      a->tokenType = type;
    }
  }

return a;
	
}

Token* readNumber(void) {
  // TODO
	int count=0;
	Token *a=makeToken(TK_NUMBER,lineNo,colNo);
	do{

		a->string[count++]=currentChar;
		readChar();

	}
	while(charCodes[currentChar]==CHAR_DIGIT);
	a->string[count] = '\0';
	a->value = atoi(a->string);
	return a;
}

Token* readConstChar(void) {
  // TODO
	Token *a=makeToken(TK_CHAR,lineNo,colNo);
	readChar();
	if(currentChar==-1||charCodes[currentChar]==CHAR_SINGLEQUOTE){
		error(ERR_INVALIDCHARCONSTANT, lineNo,colNo);}

	a->string[0]=currentChar;a->string[1]='\0';
	readChar();
	if(currentChar==-1||charCodes[currentChar]!=CHAR_SINGLEQUOTE){
		error(ERR_INVALIDCHARCONSTANT, lineNo,colNo);}

	return a;


}

Token* getToken(void) {
  Token *token;
  int ln, cn;
//printf("%c\n",currentChar);
  if (currentChar == EOF) 
    return makeToken(TK_EOF, lineNo, colNo);

  switch (charCodes[currentChar]) {

  case CHAR_SPACE: skipBlank(); return getToken();
  case CHAR_LETTER : return readIdentKeyword();
  case CHAR_DIGIT: return readNumber();
  case CHAR_SINGLEQUOTE:
  token = readConstChar();
  readChar(); 
  return token;


/* cac thanh phan khong phan nhanh*/
  {
  case CHAR_PLUS: 
    token = makeToken(SB_PLUS, lineNo, colNo);
    readChar(); 
    return token;

	case CHAR_MINUS:
	token = makeToken(SB_MINUS, lineNo, colNo);
    readChar(); 
    return token;

	case CHAR_TIMES:
	token = makeToken(SB_TIMES, lineNo, colNo);
	readChar(); 
	return token;

    case CHAR_SLASH:
	token = makeToken(SB_TIMES, lineNo, colNo);
    readChar(); 
    return token;
    case CHAR_EQ:
   token = makeToken(SB_EQ, lineNo, colNo);
   token->string[0]='=';
	token->string[1]='\0';
    readChar(); 
    return token;
  case CHAR_COMMA:
  token = makeToken(SB_COMMA, lineNo, colNo);
    readChar(); 
    return token;


  case CHAR_PERIOD:
  token = makeToken(SB_PERIOD, lineNo, colNo);
    readChar(); 
    return token;

   case CHAR_RPAR:
  token = makeToken(SB_RPAR, lineNo, colNo);
    readChar(); 
    return token;
    case CHAR_COLON:
  token = makeToken(SB_COLON, lineNo, colNo);
    readChar(); 
    return token;
  
  case CHAR_SEMICOLON:
  token = makeToken(SB_SEMICOLON, lineNo, colNo);
    readChar(); 
    return token;

}




/*  sang thanh phan co phan nhanh */

 case CHAR_LPAR :{

    //printf("chu cai ngay sau \n",currentChar );
 	token = makeToken(TK_NONE, lineNo, colNo);

    readChar(); 
    switch(charCodes[currentChar]){
		case CHAR_TIMES:{

			skipComment();
			readChar();
			return getToken();

		}
		case CHAR_PERIOD:{
		token->tokenType = SB_LSEL;
     	 readChar();
      	return token;
		}

		default:
		token->tokenType = SB_LPAR;

    }
    return token;

 }



	case CHAR_LT:
	token = makeToken(TK_NONE, lineNo, colNo);

    readChar(); 
    if(charCodes[currentChar]==CHAR_EQ)
    	token->tokenType=SB_LE;
    return token;

   case CHAR_GT:
   token = makeToken(SB_GT, lineNo, colNo);
    readChar(); 
    if(charCodes[currentChar]==CHAR_EQ)
    	token->tokenType=SB_GE;
    return token;



   case CHAR_EXCLAIMATION:
   token = makeToken(SB_NEQ, lineNo, colNo);
    readChar(); 
    if(charCodes[currentChar]!=CHAR_EQ){
		error(ERR_INVALIDSYMBOL, token->lineNo, token->colNo);
    }
    return token;

  
  default:
    token = makeToken(TK_NONE, lineNo, colNo);
    error(ERR_INVALIDSYMBOL, lineNo, colNo);
    readChar(); 
    return token;
  }
}


/******************************************************************/

void printToken(Token *token) {

  printf("%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case TK_NONE: printf("TK_NONE\n"); break;
  case TK_IDENT: printf("TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: printf("TK_NUMBER(%s)\n", token->string); break;
  case TK_CHAR: printf("TK_CHAR(\'%s\')\n", token->string); break;
  case TK_EOF: printf("TK_EOF\n"); break;

  case KW_PROGRAM: printf("KW_PROGRAM\n"); break;
  case KW_CONST: printf("KW_CONST\n"); break;
  case KW_TYPE: printf("KW_TYPE\n"); break;
  case KW_VAR: printf("KW_VAR\n"); break;
  case KW_INTEGER: printf("KW_INTEGER\n"); break;
  case KW_CHAR: printf("KW_CHAR\n"); break;
  case KW_ARRAY: printf("KW_ARRAY\n"); break;
  case KW_OF: printf("KW_OF\n"); break;
  case KW_FUNCTION: printf("KW_FUNCTION\n"); break;
  case KW_PROCEDURE: printf("KW_PROCEDURE\n"); break;
  case KW_BEGIN: printf("KW_BEGIN\n"); break;
  case KW_END: printf("KW_END\n"); break;
  case KW_CALL: printf("KW_CALL\n"); break;
  case KW_IF: printf("KW_IF\n"); break;
  case KW_THEN: printf("KW_THEN\n"); break;
  case KW_ELSE: printf("KW_ELSE\n"); break;
  case KW_WHILE: printf("KW_WHILE\n"); break;
  case KW_DO: printf("KW_DO\n"); break;
  case KW_FOR: printf("KW_FOR\n"); break;
  case KW_TO: printf("KW_TO\n"); break;

  case SB_SEMICOLON: printf("SB_SEMICOLON\n"); break;
  case SB_COLON: printf("SB_COLON\n"); break;
  case SB_PERIOD: printf("SB_PERIOD\n"); break;
  case SB_COMMA: printf("SB_COMMA\n"); break;
  case SB_ASSIGN: printf("SB_ASSIGN\n"); break;
  case SB_EQ: printf("SB_EQ\n"); break;
  case SB_NEQ: printf("SB_NEQ\n"); break;
  case SB_LT: printf("SB_LT\n"); break;
  case SB_LE: printf("SB_LE\n"); break;
  case SB_GT: printf("SB_GT\n"); break;
  case SB_GE: printf("SB_GE\n"); break;
  case SB_PLUS: printf("SB_PLUS\n"); break;
  case SB_MINUS: printf("SB_MINUS\n"); break;
  case SB_TIMES: printf("SB_TIMES\n"); break;
  case SB_SLASH: printf("SB_SLASH\n"); break;
  case SB_LPAR: printf("SB_LPAR\n"); break;
  case SB_RPAR: printf("SB_RPAR\n"); break;
  case SB_LSEL: printf("SB_LSEL\n"); break;
  case SB_RSEL: printf("SB_RSEL\n"); break;
  }
}

void fprintToken(Token *token) {

  fprintf(output,"%d-%d:", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case TK_NONE: fprintf(output,"TK_NONE\n"); break;
  case TK_IDENT: fprintf(output,"TK_IDENT(%s)\n", token->string); break;
  case TK_NUMBER: fprintf(output,"TK_NUMBER(%s)\n", token->string); break;
  case TK_CHAR: fprintf(output,"TK_CHAR(\'%s\')\n", token->string); break;
  case TK_EOF: fprintf(output,"TK_EOF\n"); break;

  case KW_PROGRAM: fprintf(output,"KW_PROGRAM\n"); break;
  case KW_CONST: fprintf(output,"KW_CONST\n"); break;
  case KW_TYPE: fprintf(output,"KW_TYPE\n"); break;
  case KW_VAR: fprintf(output,"KW_VAR\n"); break;
  case KW_INTEGER: fprintf(output,"KW_INTEGER\n"); break;
  case KW_CHAR: fprintf(output,"KW_CHAR\n"); break;
  case KW_ARRAY: fprintf(output,"KW_ARRAY\n"); break;
  case KW_OF: fprintf(output,"KW_OF\n"); break;
  case KW_FUNCTION: fprintf(output,"KW_FUNCTION\n"); break;
  case KW_PROCEDURE: fprintf(output,"KW_PROCEDURE\n"); break;
  case KW_BEGIN: fprintf(output,"KW_BEGIN\n"); break;
  case KW_END: fprintf(output,"KW_END\n"); break;
  case KW_CALL: fprintf(output,"KW_CALL\n"); break;
  case KW_IF: fprintf(output,"KW_IF\n"); break;
  case KW_THEN: fprintf(output,"KW_THEN\n"); break;
  case KW_ELSE: fprintf(output,"KW_ELSE\n"); break;
  case KW_WHILE: fprintf(output,"KW_WHILE\n"); break;
  case KW_DO: fprintf(output,"KW_DO\n"); break;
  case KW_FOR: fprintf(output,"KW_FOR\n"); break;
  case KW_TO: fprintf(output,"KW_TO\n"); break;

  case SB_SEMICOLON: fprintf(output,"SB_SEMICOLON\n"); break;
  case SB_COLON: fprintf(output,"SB_COLON\n"); break;
  case SB_PERIOD: fprintf(output,"SB_PERIOD\n"); break;
  case SB_COMMA: fprintf(output,"SB_COMMA\n"); break;
  case SB_ASSIGN: fprintf(output,"SB_ASSIGN\n"); break;
  case SB_EQ: fprintf(output,"SB_EQ\n"); break;
  case SB_NEQ: fprintf(output,"SB_NEQ\n"); break;
  case SB_LT: fprintf(output,"SB_LT\n"); break;
  case SB_LE: fprintf(output,"SB_LE\n"); break;
  case SB_GT: fprintf(output,"SB_GT\n"); break;
  case SB_GE: fprintf(output,"SB_GE\n"); break;
  case SB_PLUS: fprintf(output,"SB_PLUS\n"); break;
  case SB_MINUS: fprintf(output,"SB_MINUS\n"); break;
  case SB_TIMES: fprintf(output,"SB_TIMES\n"); break;
  case SB_SLASH: fprintf(output,"SB_SLASH\n"); break;
  case SB_LPAR: fprintf(output,"SB_LPAR\n"); break;
  case SB_RPAR: fprintf(output,"SB_RPAR\n"); break;
  case SB_LSEL: fprintf(output,"SB_LSEL\n"); break;
  case SB_RSEL: fprintf(output,"SB_RSEL\n"); break;
  }
}

int scan(char *fileName) {
  Token *token;

  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;

  token = getToken();
  while (token->tokenType != TK_EOF) {
    //fprintToken(token);
    printToken(token);
    free(token);
    token = getToken();
  }

  free(token);
  closeInputStream();
  return IO_SUCCESS;
}

/******************************************************************/

int main(int argc, char *argv[]) {
	output=fopen(argv[2],"w");
  if (argc <= 1) {
    printf("scanner: no input file.\n");
    return -1;
  }

  if (scan(argv[1]) == IO_ERROR) {
    printf("Can\'t read input file!\n");
    return -1;
  }
    
  return 0;
}

