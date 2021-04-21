CSC322 Lab 3 Cache Simulation
Nathan Loucks, nloucks@oswego.edu, 804298087

ReadMe for CacheSim 

To compile:
	cc cachesim.c -o cachesim -lm
	
	Note: -lm flag sometimes necessary for Math.h to link properly.
	
To run:
	./cachesim -m <m> -s <s> -e <e> -b <b> -i <file> -r <option>
	
	where,
	
	m			address size in bits
	s			number if index bits
	e			number of line bits 
	b			size of block bits
	file		name of file containing a list of addresses
	option		method used (lfu, fifo, opt)
	
	Note: fifo and opt caching methods have not been implemented.