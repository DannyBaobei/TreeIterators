TAGS:
	ctags -R
all:TAGS
	g++ -g *.cc -o a

test:all
#A--B--NULL
#    --D
#   C--E--NULL
#       --F
# pre   ,  in   , post
# ADBCEF, BDAEFC, DBFECA
	./a AB#D##CE#F####

clean:
	rm -rf a* tags *~



