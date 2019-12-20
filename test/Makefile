COMMON = -g -w -O0 -I../core/  -I../extra/ $(Mco)
LINKLIB = -lnet-extra -lnet -L../build/

test: test.c
	g++ -o libnet-test $(COMMON) $< $(LINKLIB) -g

