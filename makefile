FLAGS := -g

dict: $(wildcard *.c)
	gcc -o $@ $^ $(FLAGS)