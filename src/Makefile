minic: mini.tab.o lex.yy.o main.o tree.o SymbolTable.o TypeCheck.o CodeGen.o weed.o pretty.o
	gcc -g pretty.o weed.o CodeGen.o TypeCheck.o SymbolTable.o tree.o lex.yy.o mini.tab.o main.o -o minic -ll
lex.yy.c: mini.l mini.tab.h
	flex mini.l
mini.tab.c mini.tab.h: mini.y
	bison -d -v mini.y
tree.o: tree.c tree.h
	gcc -c -g tree.c
pretty.o: pretty.c pretty.h
	gcc -c -g pretty.c
SymbolTable.o: SymbolTable.c SymbolTable.h
	gcc -c -g SymbolTable.c
TypeCheck.o: TypeCheck.c TypeCheck.h
	gcc -c -g TypeCheck.c
CodeGen.o: CodeGen.c CodeGen.h
	gcc -c -g CodeGen.c
weed.o: weed.c weed.h
	gcc -c -g weed.c
clean:
	rm -f lex.yy.* main.o mini.tab.* minic mini.output *.o y.tab.c y.tab.h