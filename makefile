dict: $(wildcard *.c)
	gcc -o $@ $^