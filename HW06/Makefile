CFLAGS+=  -pedantic -Wall -std=c99 -O3
HW=hw06-b0b36prp

$(HW): main.c 
	$(CC) $(CFLAGS) main.c -o $(HW)

zip:
	zip $(HW)-brute.zip main.c

clean:
	rm -f *.o
	rm -f $(HW)
	rm -f $(HW)-brute.zip

.PHONY: clear zip
