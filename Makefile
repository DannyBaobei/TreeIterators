TAGS:
	ctags -R
all:TAGS
	g++ --std=c++0x -g *.cc vczh/*.cpp -o a

test:all
	./a

ftest:all
	./a cases.txt >result.txt
clean:
	rm -rf a* tags *~ result.txt



