TAGS:
	ctags -R
all:TAGS
	clang++ -g -std=c++11 *.cc -o a
test:all
	./a AB#D##CE#F####
clean:
	rm -rf a* tags
