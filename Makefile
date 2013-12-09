TAGS:
	ctags -R
all:TAGS
	g++ -g  *.cc -o a
test:all
	./a AB#D##CE#F####
clean:
	rm -rf a* tags *~
