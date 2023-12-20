include $(SBCL_SRC)/src/runtime/sbcl.mk

.PHONY: all clean

all: app

libhello.dll: hello.c hello.h libhello.core
	$(CC) -fPIC -c $(CPPFLAGS) $(filter-out -fno-pie,$(CFLAGS)) hello.c -o hello.o 
	gcc -shared -o libhello.dll hello.o -Wl,--allow-multiple-definition -Wl,--whole-archive $(SBCL_SRC)/src/runtime/libsbcl.a -Wl,--no-whole-archive -Wl,--export-all-symbols -Wl,$(SBCL_SRC)/src/runtime/mswin64.def $(LIBS)

app: app.c libhello.dll
	$(CC) -fPIC -c $(CPPFLAGS) $(filter-out -fno-pie,$(CFLAGS)) app.c -o app.o 
	$(CC) $(LINKFLAGS) -o app app.o -L. -lhello -Wl,--allow-multiple-definition

libhello.core: *.lisp
	$(SBCL_SRC)/run-sbcl.sh --script "script.lisp"

clean:
	rm -f app *.core *.dll *.o
