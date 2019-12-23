COMMON = -w -O2 -I../core/ $(Mco)
LINKLIB = 
OUTFILE = ../build
LINKLIB = -ledtp -L../build/

O = \
	$(OUTFILE)/httppack.o \
	$(OUTFILE)/httpunpack.o \
	$(OUTFILE)/base64.o \

all: checkdir libedtp-extra

checkdir: 
	mkdir -p $(OUTFILE)

libedtp-extra: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libedtp-extra.a  $(O)

$(OUTFILE)/httppack.o:  httppack.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE) $(LINKLIB)

$(OUTFILE)/httpunpack.o:  httpunpack.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE) $(LINKLIB)

$(OUTFILE)/base64.o:  base64.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE) $(LINKLIB)
