all: format265alt

format265alt: format265alt.o formatter.o 
	    gcc format265alt.c formatter.c -o format265alt 

driver:	    driver.o formatter.o
	    gcc driver.c formatter.c -o driver

clean:
	    rm *o format265alt

