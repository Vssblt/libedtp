COMMON = -W -Wall -O2 $(Mco)

OUTFILE = ../build/

O = \
	$(OUTFILE)/common.o \

all: checkdir libnet

checkdir: 
	mkdir -p $(OUTFILE)

libnet: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libnet.a  $(O)

$(OUTFILE)/common.o:  common.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE)
