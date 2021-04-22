# CSC322_lab3_CacheSim ###############################
#                                                    #
#    ReadMe for Lab 3 - Cache Simulation             #
#    Nathan Loucks, nloucks@oswego.edu, 804298087    #    
#                                                    #
######################################################


Full, and possibly updated, source code can be found at: https://github.com/nrloucks/CSC322_lab3_CacheSim

To compile:
	cc lab3_nloucks.c -o cachesim -lm
	
	Note: -lm flag sometimes necessary for Math.h to link properly.
	
To run:
	./cachesim -m <m> -s <s> -e <e> -b <b> -i <file> -r <option>
	
	Example: ./cachesim -m 64 -s 4 -e 0 -b 4 -i addresses.txt -r lfu
  
	Where,                                     ~ The File addresses.txt is provided 
                                               as well and contains a list of 
	m			address size in bits                   semi-random 64 bit addresses.
	s			number of index bits
	e			number of line bits 
	b			size of block bits
	file		name of file containing a list of addresses
	option		method used (lfu, fifo, opt)
	
IF SEGMENTATION FAULT OCCURS:
	Make sure you are running the program as administrator/with appropriate privelages. Otherwise it may be blocked from accessing memory and abort execution. 
  
Note: Fifo and opt caching methods have not been implemented. 
      Would like to implement using a doubly linked-list if time permitted.
      The file 'cachesimv2.c' is the incomplete linked-list version, therefore, be sure to compile 'lab3_nloucks.c' for it to run.