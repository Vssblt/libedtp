COMMON = -g -std=c99 -w -O0 -I../core/  -I../extra/ $(Mco)
LINKLIB = -lpthread -lnet-extra -L../build/

test: test.c
	g++ -o libnet-test $(COMMON) $< $(LINKLIB) -g

clean:
