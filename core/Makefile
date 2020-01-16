COMMON = -W -Wall -O2 $(Mco)

OUTFILE = ../build

O = \
	$(OUTFILE)/core.o \

all: checkdir libedtp

checkdir: 
	mkdir -p $(OUTFILE)

libedtp: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libedtp.a  $(O)

$(OUTFILE)/core.o:  common.c socket.c packet.c rbtree.c libedtp.c thread.c rbtree.c
	$(CXX) -c $<  -o $@ $(COMMON) $(INCLUDE)
