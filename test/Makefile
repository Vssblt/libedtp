COMMON = -g -w -O0 -I../core/  -I../extra/ $(Mco)
LINKLIB = -ledtp-extra -ledtp -L../build -lpthread

test: test.c
	g++ -o libedtp-test $(COMMON) $< $(LINKLIB) -g

