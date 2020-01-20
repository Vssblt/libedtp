COMMON = -W -Wall -O2 -Wno-unused-variable -Wno-unused-parameter $(Mco) 

OUTFILE = ../build

O = \
	$(OUTFILE)/core.o \

all: checkdir libedtp

checkdir: 
	mkdir -p $(OUTFILE)

libedtp: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libedtp.a  $(O)

$(OUTFILE)/core.o:  common.c socket.c packet.c rbtree.c libedtp.c thread.c map.c
	$(CXX) $^ -o $@ $(COMMON) $(INCLUDE) 
