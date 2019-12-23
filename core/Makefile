COMMON = -W -Wall -O2 $(Mco)

OUTFILE = ../build/

O = \
	$(OUTFILE)/common.o \

all: checkdir libedtp

checkdir: 
	mkdir -p $(OUTFILE)

libedtp: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libedtp.a  $(O)

$(OUTFILE)/common.o:  common.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE)
