TAGS:
	ctags -R
all:TAGS
	g++ -g *.cc -o a

test:all
	./a

ftest:all
	./a cases.txt
clean:
	rm -rf a* tags *~



