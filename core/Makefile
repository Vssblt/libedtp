COMMON = -W -Wall -O2 $(Mco)

OUTFILE = ../build/

O = \
	$(OUTFILE)/common.o \

all: checkdir libw

checkdir: 
	mkdir -p $(OUTFILE)

libw: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libw.a  $(O)

$(OUTFILE)/common.o:  common.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE)
