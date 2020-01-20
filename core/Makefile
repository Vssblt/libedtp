COMMON = -g -W -Wall -O0 -Wno-unused-variable -Wno-unused-parameter $(Mco) 

OUTFILE = ../build

O = \
	$(OUTFILE)/core.o \
	$(OUTFILE)/socket.o \
	$(OUTFILE)/packet.o \
	$(OUTFILE)/rbtree.o \
	$(OUTFILE)/thread.o \
	$(OUTFILE)/map.o \

all: checkdir libedtp

checkdir: 
	mkdir -p $(OUTFILE)

libedtp: $(OUTFILE) $(O)
	ar rcs $(OUTFILE)/libedtp.a  $(O)

$(OUTFILE)/core.o:  common.c 
	$(CXX) -c $< -o $@ $(COMMON) $(INCLUDE) 

$(OUTFILE)/socket.o:  socket.c
	$(CXX) -c $< -o $@ $(COMMON) $(INCLUDE) 

$(OUTFILE)/packet.o:  packet.c 
	$(CXX) -c $< -o $@ $(COMMON) $(INCLUDE) 

$(OUTFILE)/rbtree.o:  rbtree.c 
	$(CXX) -c $< -o $@ $(COMMON) $(INCLUDE) 

$(OUTFILE)/thread.o:  thread.c 
	$(CXX) -c $< -o $@ $(COMMON) $(INCLUDE) 

$(OUTFILE)/map.o:  map.c 
	$(CXX) -c $< -o $@ $(COMMON) $(INCLUDE) 
