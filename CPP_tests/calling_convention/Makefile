LDFLAGS += -L.
all:main
test:all
	./main

libfrmn.so:frmn.f
	gfortran -shared -fPIC $(LDFLAGS) $^ -o $@
rmn.o:rmn.c
	gcc $< -c -fPIC -o $@ -Wno-format

librmn.so:rmn.o libfrmn.so
	gcc -dynamiclib $(LDFLAGS) -o $@ $< -lfrmn 

main.o:main.cpp
	g++ -c -o $@ $<  -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk

main:main.o librmn.so
	g++ -o  $@ $< -Wl,-search_paths_first -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk -Wl,-headerpad_max_install_names $(LDFLAGS) -l rmn -l frmn

clean:
	rm -f libfrmn.so librmn.so main *.o
