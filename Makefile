TAGS:
	ctags -R
all:TAGS
	g++ -g *.cc -o a

test:all
	./a

ftest:all
	./a cases.txt >result.txt
clean:
	rm -rf a* tags *~ result.txt



