all: build/imgui.a build/imgui.a deps/chibi-scheme-static/libchibi-scheme.a build/loki

deps/chibi-scheme-static/lib/imgui/imgui.c: deps/chibi-scheme-static/lib/imgui/imgui.stub
	echo "generating chibi c code from stub for ffi"
	cd deps/chibi-scheme-static; LD_LIBRARY_PATH=../chibi-scheme-dynamic PATH=../chibi-scheme-dynamic ./tools/chibi-ffi lib/imgui/imgui.stub

deps/chibi-scheme-static/lib/.stubbed:
	echo "generating chibi c code from stub for chibi libs"
	@for f in lib/chibi/process.stub lib/chibi/time.stub lib/chibi/system.stub lib/chibi/stty.stub lib/chibi/pty.stub lib/chibi/net.stub lib/chibi/io/io.stub lib/chibi/crypto/crypto.stub lib/srfi/144/math.stub lib/srfi/160/uvprims.stub lib/scheme/bytevector.stub lib/chibi/filesystem.stub; do LD_LIBRARY_PATH=deps/chibi-scheme-dynamic DYLD_LIBRARY_PATH=deps/chibi-scheme-dynamic CHIBI_IGNORE_SYSTEM_PATH=1 CHIBI_MODULE_PATH=lib deps/chibi-scheme-dynamic/chibi-scheme -A deps/chibi-scheme-dynamic/lib -Ideps/chibi-scheme-dynamic/lib -q deps/chibi-scheme-static/tools/chibi-ffi deps/chibi-scheme-static/$${f}; done
	touch deps/chibi-scheme-static/lib/.stubbed

deps/chibi-scheme-static/clibs.c: deps/chibi-scheme-static/lib/imgui/imgui.c deps/chibi-scheme-static/lib/.stubbed
	echo "building deps/chibi-scheme-static/clibs.c"
	cd deps/chibi-scheme-static; find -L lib/ | grep .sld | LD_LIBRARY_PATH=../chibi-scheme-dynamic DYLD_LIBRARY_PATH=../chibi-scheme-dynamic CHIBI_IGNORE_SYSTEM_PATH=1 CHIBI_MODULE_PATH=lib ../chibi-scheme-dynamic/chibi-scheme -q ./tools/chibi-genstatic > clibs.c

deps/chibi-scheme-static/eval.c.o: deps/chibi-scheme-static/clibs.c
	cc -c -DSEXP_USE_STATIC_LIBS -DSEXP_USE_STATIC_LIBS_NO_INCLUDE=0 -Isrc/lib/imgui/ -Ideps/cimgui/ -Ideps/imgui/ -Ideps/chibi-scheme-static/include  -DSEXP_USE_NTPGETTIME -DSEXP_USE_INTTYPES -Wall -DSEXP_USE_DL=0 -g -g3  -fPIC -o deps/chibi-scheme-static/eval.c.o deps/chibi-scheme-static/eval.c

deps/chibi-scheme-static/libchibi-scheme.a:
	echo "building chibi static"
	echo '#define sexp_so_extension "'.so'"' > deps/chibi-scheme-static/include/chibi/install.h
	echo '#define sexp_default_module_path "'/usr/local/share/chibi:/usr/local/lib/chibi:/usr/local/share/snow:/usr/local/lib/snow'"' >> deps/chibi-scheme-static/include/chibi/install.h
	echo '#define sexp_platform "'linux'"' >> deps/chibi-scheme-static/include/chibi/install.h
	echo '#define sexp_version "'0.10.0'"' >> deps/chibi-scheme-static/include/chibi/install.h
	echo '#define sexp_release_name "'`cat deps/chibi-scheme-static/RELEASE`'"' >> deps/chibi-scheme-static/include/chibi/install.h
	@for f in gc.c sexp.c bignum.c gc_heap.c opcodes.c vm.c simplify.c; do cc -c -DSEXP_USE_STATIC_LIBS -DSEXP_USE_STATIC_LIBS_NO_INCLUDE=0 -Ideps/cimgui/ -Ideps/imgui/ -Ideps/chibi-scheme-static/include  -DSEXP_USE_NTPGETTIME -DSEXP_USE_INTTYPES -Wall -DSEXP_USE_DL=0 -g -g3 -O3  -fPIC -o deps/chibi-scheme-static/$${f}.o deps/chibi-scheme-static/$${f}; done
	cd deps/chibi-scheme-static/; ar -crs libchibi-scheme.a gc.c.o sexp.c.o bignum.c.o gc_heap.c.o opcodes.c.o vm.c.o simplify.c.o


build/imgui.a:
	echo "rebuilding imgui..."
	PKG_CONFIG_PATH=$$(dirname $$(ls /nix/store/*xorgproto*/share/pkgconfig/xproto.pc)):$$PKG_CONFIG_PATH \
	$(MAKE) -C deps/imgui/examples/example_glfw_opengl3;
	ar -crs build/imgui.a \
	deps/imgui/examples/example_glfw_opengl3/imgui_demo.o \
	deps/imgui/examples/example_glfw_opengl3/imgui_draw.o \
	deps/imgui/examples/example_glfw_opengl3/imgui_impl_glfw.o \
	deps/imgui/examples/example_glfw_opengl3/imgui_impl_opengl3.o \
	deps/imgui/examples/example_glfw_opengl3/imgui.o \
	deps/imgui/examples/example_glfw_opengl3/imgui_tables.o \
	deps/imgui/examples/example_glfw_opengl3/imgui_widgets.o


build/imgui_src.o: src/lib/imgui/imgui_src.c
	gcc -c src/lib/imgui/imgui_src.c \
	-I./deps/imgui \
	-I./deps/cimgui \
	-I./deps/imgui/backends/ \
	-o build/imgui_src.o


build/linux_main.o:
	g++ -c src/linux_main.cpp \
	-I./deps/imgui \
	-I./deps/imgui/backends/ \
	-o build/linux_main.o


build/loki_main.o: src/loki_main.cpp
	g++ -c src/loki_main.cpp \
	-I./deps/imgui \
	-I./deps/imgui/backends/ \
	-I./deps/chibi-scheme-static/include \
	-o build/loki_main.o


build/loki: build/linux_main.o build/loki_main.o deps/chibi-scheme-static/libchibi-scheme.a build/imgui.a deps/chibi-scheme-static/eval.c.o ./build/imgui_src.o
	mkdir -p build
	g++ \
	./build/linux_main.o \
	./build/loki_main.o \
	./build/imgui_src.o \
	./build/imgui.a \
	./deps/chibi-scheme-static/libchibi-scheme.a \
	./deps/cimgui/cimgui.o \
	./deps/chibi-scheme-static/opcodes.c.o \
	./deps/chibi-scheme-static/eval.c.o \
	-I./deps/imgui \
	-I./deps/imgui/backends/ \
	-I./deps/chibi-scheme-static/include \
	-g -o build/loki -lGL -lglut -lglfw -ldl -lutil -lm -Wl,-export-dynamic
	rm -f imgui.ini

cleanall:
	$(MAKE) -C deps/imgui/examples/example_glfw_opengl3 clean
	rm -f build/*
	$(MAKE) -C deps/chibi-scheme-static clean; 
	rm -f deps/chibi-scheme-static/*.o
	rm -f deps/chibi-scheme-static/chibi-scheme
	rm -f deps/chibi-scheme-static/chibi-scheme-static
	rm -f deps/chibi-scheme-static/libchibi-scheme.*
	rm -f deps/chibi-scheme-static/lib/imgui/imgui.so
	rm -f deps/chibi-scheme-static/lib/imgui/imgui.c
	rm -f deps/chibi-scheme-static/lib/.stubbed

cleanloki:
	rm -f build/loki*
	rm -f build/linux_main*

cleanffi:
	rm -f deps/chibi-scheme-static/clibs.c
	rm -f deps/chibi-scheme-static/lib/imgui/imgui.c





run: all
	./build/loki










