CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm 

all: parser

parser: main.o parser.o scanner.o reader.o charcode.o token.o error.o
	${CC} main.o parser.o scanner.o reader.o charcode.o token.o error.o -o parser

main.o: main.c
	${CC} ${CFLAGS} main.c

scanner.o: scanner.c
	${CC} ${CFLAGS} scanner.c

parser.o: parser.c
	${CC} ${CFLAGS} parser.c

reader.o: reader.c
	${CC} ${CFLAGS} reader.c

charcode.o: charcode.c
	${CC} ${CFLAGS} charcode.c

token.o: token.c
	${CC} ${CFLAGS} token.c

error.o: error.c
	${CC} ${CFLAGS} error.c
run:
	./parser ../test/example2.kpl ../test/runresult2.txt
	./parser ../test/example3.kpl ../test/runresult3.txt
	./parser ../test/example4.kpl ../test/runresult4.txt
	./parser ../test/example5.kpl ../test/runresult5.txt
	./parser ../test/example6.kpl ../test/runresult6.txt
	./parser ../test/example7.kpl ../test/runresult7.txt
testprogram:
	./test.out ../test/runresult2.txt ../test/result2.txt 
	./test.out ../test/runresult3.txt ../test/result3.txt 
	./test.out ../test/runresult4.txt ../test/result4.txt 
	./test.out ../test/runresult5.txt ../test/result5.txt 
	./test.out ../test/runresult6.txt ../test/result6.txt 
	./test.out ../test/runresult7.txt ../test/result7.txt 
clean:
	rm -f *.o *~
