CFLAGS += -fPIC
LDFLAGS += -Wl,--no-undefined

main: main.o libdotproduct.so libmultiply.so
	cc -o $@ $< -L. -ldotproduct

main_shared_2: main.o libdotproduct.so libmultiply.so
	cc -o $@ $< -L. -lmultiply -ldotproduct

main_static: main.o libdotproduct.a libmultiply.a
	cc -o $@ $< -L. -ldotproduct -lmultiply

libdotproduct.a:dotproduct.o
	ar -crs $@ $<


libdotproduct.so:dotproduct.o libmultiply.so
	cc -shared $(LDFLAGS) -o $@ $< -L.

libmultiply.a:multiply.o
	ar -crs $@ $<

libmultiply.so:multiply.o
	cc -shared -o $@ $<

clean:
	rm -f *.o *.so *.a main
