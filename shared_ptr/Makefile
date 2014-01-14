clean:
	rm *~ tags *.exe 

all:
	ctags -R
	g++ -g --std=c++0x *.cc -o test_shared_ptr.exe

test:all
	test_shared_ptr.exe
