COMMON = -w -O2 -I../core/ $(Mco)
LINKLIB = 
OUTFILE = ../build
LINKLIB = -lnet -L../build/

O = \
	$(OUTFILE)/httppack.o \
	$(OUTFILE)/httpunpack.o \
	$(OUTFILE)/base64.o \

all: checkdir libnet-extra

checkdir: 
	mkdir -p $(OUTFILE)

libnet-extra: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libnet-extra.a  $(O)

$(OUTFILE)/httppack.o:  httppack.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE) $(LINKLIB)

$(OUTFILE)/httpunpack.o:  httpunpack.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE) $(LINKLIB)

$(OUTFILE)/base64.o:  base64.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE) $(LINKLIB)
