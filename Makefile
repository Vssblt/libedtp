Mco = $(M)
export Mco 

all: checkdir
	make -C core
	make -C extra
	make -C test
	
	cp ./core/*.h ./build/include/
	cp ./extra/*.h ./build/include/extra/

clean:
	rm -rf build
#	make -C core clean
#	make -C test clean
#	make -C extra clean

checkdir: 
	mkdir -p build	
	mkdir -p build/include/
	mkdir -p build/include/extra/
