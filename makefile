main: main.c mainFunction.c
	gcc -o main main.c mainFunction.c -I.
clean:
	rm -rf *.o
	rm -rf main
run:
	./main