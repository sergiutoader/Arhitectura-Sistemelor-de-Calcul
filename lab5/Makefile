default: build

build: loop-ordering.c constant-optimization.c bmm.c
	gcc -O0 -o loop-ordering loop-ordering.c -g
	gcc -O0 -o constant-optimization constant-optimization.c -g
	gcc -O0 -o bmm bmm.c -g

clean:
	rm loop-ordering constant-optimization bmm