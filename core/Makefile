COMMON = -W -Wall -O2 $(Mco)

OUTFILE = ../build

O = \
	$(OUTFILE)/common.o \
	$(OUTFILE)/socket.o \
	$(OUTFILE)/packet.o \

all: checkdir libedtp

checkdir: 
	mkdir -p $(OUTFILE)

libedtp: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libedtp.a  $(O)

$(OUTFILE)/common.o:  common.c socket.c packet.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE)
