# Primary targets:
# gc.a - builds basic library
# libgc.a - builds library for use with g++ "-fgc-keyword" extension
# c++ - adds C++ interface to library
# cords - adds cords (heavyweight strings) to library
# test - prints porting information, then builds basic version of gc.a,
#      	 and runs some tests of collector and cords.  Does not add cords or
#	 c++ interface to gc.a
# cord/de - builds dumb editor based on cords.
CC= cc
CXX=gcc
AS=as
#  The above doesn't work with gas, which doesn't run cpp.
#  Define AS as `gcc -c -x assembler-with-cpp' instead.

CFLAGS= -O -DNO_SIGNALS -DALL_INTERIOR_POINTERS -DSILENT

# Setjmp_test may yield overly optimistic results when compiled
# without optimization.
# -DSILENT disables statistics printing, and improves performance.
# -DCHECKSUMS reports on erroneously clear dirty bits, and unexpectedly
#   altered stubborn objects, at substantial performance cost.
#   Use only for incremental collector debugging.
# -DFIND_LEAK causes the collector to assume that all inaccessible
#   objects should have been explicitly deallocated, and reports exceptions.
#   Finalization and the test program are not usable in this mode.
# -DSOLARIS_THREADS enables support for Solaris (thr_) threads.
#   (Clients should also define SOLARIS_THREADS and then include
#   gc.h before performing thr_ or dl* or GC_ operations.)
#   This is broken on nonSPARC machines.
# -DALL_INTERIOR_POINTERS allows all pointers to the interior
#   of objects to be recognized.  (See gc_priv.h for consequences.)
# -DSMALL_CONFIG tries to tune the collector for small heap sizes,
#   usually causing it to use less space in such situations.
#   Incremental collection no longer works in this case.
# -DLARGE_CONFIG tunes the collector for unusually large heaps.
#   Necessary for heaps larger than about 500 MB on most machines.
#   Recommended for heaps larger than about 64 MB.
# -DDONT_ADD_BYTE_AT_END is meaningful only with
#   -DALL_INTERIOR_POINTERS.  Normally -DALL_INTERIOR_POINTERS
#   causes all objects to be padded so that pointers just past the end of
#   an object can be recognized.  This can be expensive.  (The padding
#   is normally more than one byte due to alignment constraints.)
#   -DDONT_ADD_BYTE_AT_END disables the padding.
# -DNO_SIGNALS does not disable signals during critical parts of
#   the GC process.  This is no less correct than many malloc 
#   implementations, and it sometimes has a significant performance
#   impact.  However, it is dangerous for many not-quite-ANSI C
#   programs that call things like printf in asynchronous signal handlers.
# -DOPERATOR_NEW_ARRAY declares that the C++ compiler supports the
#   new syntax "operator new[]" for allocating and deleting arrays.
#   See gc_cpp.h for details.  No effect on the C part of the collector.
#   This is defined implicitly in a few environments.
# -DREDIRECT_MALLOC=X causes malloc, realloc, and free to be defined
#   as aliases for X, GC_realloc, and GC_free, respectively.
#   Calloc is redefined in terms of the new malloc.  X should
#   be either GC_malloc or GC_malloc_uncollectable.
#   The former is occasionally useful for working around leaks in code
#   you don't want to (or can't) look at.  It may not work for
#   existing code, but it often does.  Neither works on all platforms,
#   since some ports use malloc or calloc to obtain system memory.
#   (Probably works for UNIX, and win32.)
# -DNO_DEBUG removes GC_dump and the debugging routines it calls.
#   Reduces code size slightly at the expense of debuggability.

LIBGC_CFLAGS= -O -DNO_SIGNALS -DSILENT \
    -DREDIRECT_MALLOC=GC_malloc_uncollectable \
    -DDONT_ADD_BYTE_AT_END -DALL_INTERIOR_POINTERS
#   Flags for building libgc.a -- the last two are required.

CXXFLAGS= $(CFLAGS) 
AR= ar
RANLIB= ranlib


# Redefining srcdir allows object code for the nonPCR version of the collector
# to be generated in different directories.  In this case, the destination directory
# should contain a copy of the original include directory.
srcdir = .
VPATH = $(srcdir)

OBJS= alloc.o reclaim.o allchblk.o misc.o mach_dep.o os_dep.o mark_rts.o headers.o mark.o obj_map.o blacklst.o finalize.o new_hblk.o dbg_mlc.o malloc.o stubborn.o checksums.o solaris_threads.o typd_mlc.o ptr_chck.o

CSRCS= reclaim.c allchblk.c misc.c alloc.c mach_dep.c os_dep.c mark_rts.c headers.c mark.c obj_map.c pcr_interface.c blacklst.c finalize.c new_hblk.c real_malloc.c dyn_load.c dbg_mlc.c malloc.c stubborn.c checksums.c solaris_threads.c typd_mlc.c ptr_chck.c

CORD_SRCS=  cord/cordbscs.c cord/cordxtra.c cord/cordprnt.c cord/de.c cord/cordtest.c cord/cord.h cord/ec.h cord/private/cord_pos.h cord/de_win.c cord/de_win.h cord/de_cmds.h cord/de_win.ICO cord/de_win.RC cord/SCOPTIONS.amiga cord/SMakefile.amiga

CORD_OBJS=  cord/cordbscs.o cord/cordxtra.o cord/cordprnt.o

SRCS= $(CSRCS) mips_mach_dep.s rs6000_mach_dep.s alpha_mach_dep.s \
    sparc_mach_dep.s gc.h gc_typed.h gc_hdrs.h gc_priv.h gc_private.h \
    config.h gc_mark.h include/gc_inl.h include/gc_inline.h gc.man \
    if_mach.c if_not_there.c gc_cpp.cc gc_cpp.h weakpointer.h \
    gcc_support.c $(CORD_SRCS)

OTHER_FILES= Makefile PCR-Makefile OS2_MAKEFILE NT_MAKEFILE BCC_MAKEFILE \
           README test.c test_cpp.cc setjmp_t.c SMakefile.amiga \
           SCoptions.amiga README.amiga README.win32 cord/README \
           cord/gc.h include/gc.h include/gc_typed.h include/cord.h \
           include/ec.h include/private/cord_pos.h include/private/config.h \
           include/private/gc_hdrs.h include/private/gc_priv.h \
	   include/gc_cpp.h README.rs6000 \
           include/weakpointer.h README.QUICK callprocs pc_excludes \
           barrett_diagram README.OS2 README.Mac MacProjects.sit.hqx \
           MacOS.c EMX_MAKEFILE makefile.depend README.debugging \
           include/gc_cpp.h Mac_files/datastart.c Mac_files/dataend.c \
           Mac_files/MacOS_config.h Mac_files/MacOS_Test_config.h \
           add_gc_prefix.c

CORD_INCLUDE_FILES= $(srcdir)/gc.h $(srcdir)/cord/cord.h $(srcdir)/cord/ec.h \
           $(srcdir)/cord/private/cord_pos.h

# Libraries needed for curses applications.  Only needed for de.
CURSES= -lcurses -ltermlib

# The following is irrelevant on most systems.  But a few
# versions of make otherwise fork the shell specified in
# the SHELL environment variable.
SHELL= /bin/sh

SPECIALCFLAGS = 
# Alternative flags to the C compiler for mach_dep.c.
# Mach_dep.c often doesn't like optimization, and it's
# not time-critical anyway.
# Set SPECIALCFLAGS to -q nodirect_code on Encore.

all: gc.a gctest

pcr: PCR-Makefile gc_private.h gc_hdrs.h gc.h config.h mach_dep.o $(SRCS)
	make -f PCR-Makefile depend
	make -f PCR-Makefile

$(OBJS) test.o dyn_load.o dyn_load_sunos53.o: $(srcdir)/gc_priv.h $(srcdir)/gc_hdrs.h $(srcdir)/gc.h \
    $(srcdir)/config.h $(srcdir)/gc_typed.h Makefile
# The dependency on Makefile is needed.  Changing
# options such as -DSILENT affects the size of GC_arrays,
# invalidating all .o files that rely on gc_priv.h

mark.o typd_mlc.o finalize.o: $(srcdir)/gc_mark.h

gc.a: $(OBJS) dyn_load.o
	rm -f on_sparc_sunos5
	./if_mach SPARC SUNOS5 touch on_sparc_sunos5
	./if_mach SPARC SUNOS5 $(AR) rus gc.a $(OBJS) dyn_load.o
	./if_not_there on_sparc_sunos5 $(AR) ru gc.a $(OBJS) dyn_load.o
	./if_not_there on_sparc_sunos5 $(RANLIB) gc.a || cat /dev/null
#	ignore ranlib failure; that usually means it doesn't exist, and isn't needed

libgc.a: 
	make CFLAGS="$(LIBGC_CFLAGS)" clean gc.a gcc_support.o
	mv gc.a libgc.a
	rm -f on_sparc_sunos5
	./if_mach SPARC SUNOS5 touch on_sparc_sunos5
	./if_mach SPARC SUNOS5 $(AR) rus libgc.a gcc_support.o
	./if_not_there on_sparc_sunos5 $(AR) ru libgc.a gcc_support.o
	./if_not_there on_sparc_sunos5 $(RANLIB) libgc.a || cat /dev/null

cords: $(CORD_OBJS) cord/cordtest
	rm -f on_sparc_sunos5
	./if_mach SPARC SUNOS5 touch on_sparc_sunos5
	./if_mach SPARC SUNOS5 $(AR) rus gc.a $(CORD_OBJS)
	./if_not_there on_sparc_sunos5 $(AR) ru gc.a $(CORD_OBJS)
	./if_not_there on_sparc_sunos5 $(RANLIB) gc.a || cat /dev/null

gc_cpp.o: $(srcdir)/gc_cpp.cc $(srcdir)/gc_cpp.h $(srcdir)/gc.h Makefile
	$(CXX) -c $(CXXFLAGS) $(srcdir)/gc_cpp.cc
	
test_cpp: $(srcdir)/test_cpp.cc $(srcdir)/gc_cpp.h gc_cpp.o $(srcdir)/gc.h gc.a
	rm -f test_cpp
	./if_mach SPARC SUNOS5 $(CXX) $(CXXFLAGS) -o test_cpp $(srcdir)/test_cpp.cc gc_cpp.o gc.a -lthread -ldl
	./if_not_there test_cpp $(CXX) $(CXXFLAGS) -o test_cpp $(srcdir)/test_cpp.cc gc_cpp.o gc.a

c++: gc_cpp.o $(srcdir)/gc_cpp.h test_cpp
	rm -f on_sparc_sunos5
	./if_mach SPARC SUNOS5 touch on_sparc_sunos5
	./if_mach SPARC SUNOS5 $(AR) rus gc.a gc_cpp.o
	./if_not_there on_sparc_sunos5 $(AR) ru gc.a gc_cpp.o
	./if_not_there on_sparc_sunos5 $(RANLIB) gc.a || cat /dev/null
	./test_cpp 1

dyn_load_sunos53.o: dyn_load.c
	$(CC) $(CFLAGS) -DSUNOS53_SHARED_LIB -c $(srcdir)/dyn_load.c -o $@

# SunOS5 shared library version of the collector
libgc.so: $(OBJS) dyn_load_sunos53.o
	$(CC) -G -o libgc.so $(OBJS) dyn_load_sunos53.o -ldl

# Alpha/OSF shared library version of the collector
libalphagc.so: $(OBJS)
	ld -shared -o libalphagc.so $(OBJS) dyn_load.o -lc

# IRIX shared library version of the collector
libirixgc.so: $(OBJS) dyn_load.o
	ld -shared -o libirixgc.so $(OBJS) dyn_load.o -lc

mach_dep.o: $(srcdir)/mach_dep.c $(srcdir)/mips_mach_dep.s $(srcdir)/rs6000_mach_dep.s if_mach if_not_there
	rm -f mach_dep.o
	./if_mach MIPS "" $(AS) -o mach_dep.o $(srcdir)/mips_mach_dep.s
	./if_mach RS6000 "" $(AS) -o mach_dep.o $(srcdir)/rs6000_mach_dep.s
	./if_mach ALPHA "" $(AS) -o mach_dep.o $(srcdir)/alpha_mach_dep.s
	./if_mach SPARC SUNOS5 $(AS) -o mach_dep.o $(srcdir)/sparc_mach_dep.s
	./if_not_there mach_dep.o $(CC) -c $(SPECIALCFLAGS) $(srcdir)/mach_dep.c

mark_rts.o: $(srcdir)/mark_rts.c if_mach if_not_there
	rm -f mark_rts.o
	-./if_mach ALPHA "" $(CC) -c $(CFLAGS) -Wo,-notail $(srcdir)/mark_rts.c
	./if_not_there mark_rts.o $(CC) -c $(CFLAGS) $(srcdir)/mark_rts.c
#	Work-around for DEC optimizer tail recursion elimination bug.
#  The ALPHA-specific line should be removed if gcc is used.

cord/cordbscs.o: $(srcdir)/cord/cordbscs.c $(CORD_INCLUDE_FILES)
	$(CC) $(CFLAGS) -c $(srcdir)/cord/cordbscs.c
	mv cordbscs.o cord/cordbscs.o
#  not all compilers understand -o filename

cord/cordxtra.o: $(srcdir)/cord/cordxtra.c $(CORD_INCLUDE_FILES)
	$(CC) $(CFLAGS) -c $(srcdir)/cord/cordxtra.c
	mv cordxtra.o cord/cordxtra.o

cord/cordprnt.o: $(srcdir)/cord/cordprnt.c $(CORD_INCLUDE_FILES)
	$(CC) $(CFLAGS) -c $(srcdir)/cord/cordprnt.c
	mv cordprnt.o cord/cordprnt.o

cord/cordtest: $(srcdir)/cord/cordtest.c $(CORD_OBJS) gc.a
	rm -f cord/cordtest
	./if_mach SPARC SUNOS5 $(CC) $(CFLAGS) -o cord/cordtest $(srcdir)/cord/cordtest.c $(CORD_OBJS) gc.a -lthread -ldl
	./if_mach SPARC DRSNX $(CC) $(CFLAGS) -o cord/cordtest $(srcdir)/cord/cordtest.c $(CORD_OBJS) gc.a -lucb
	./if_not_there cord/cordtest $(CC) $(CFLAGS) -o cord/cordtest $(srcdir)/cord/cordtest.c $(CORD_OBJS) gc.a

cord/de: $(srcdir)/cord/de.c cord/cordbscs.o cord/cordxtra.o gc.a
	rm -f cord/de
	./if_mach SPARC SUNOS5 $(CC) $(CFLAGS) -o cord/de $(srcdir)/cord/de.c cord/cordbscs.o cord/cordxtra.o gc.a $(CURSES) -lthread -ldl
	./if_mach SPARC DRSNX $(CC) $(CFLAGS) -o cord/de $(srcdir)/cord/de.c cord/cordbscs.o cord/cordxtra.o gc.a $(CURSES) -lucb
	./if_mach RS6000 "" $(CC) $(CFLAGS) -o cord/de $(srcdir)/cord/de.c cord/cordbscs.o cord/cordxtra.o gc.a -lcurses
	./if_mach I386 LINUX $(CC) $(CFLAGS) -o cord/de $(srcdir)/cord/de.c cord/cordbscs.o cord/cordxtra.o gc.a -lcurses
	./if_not_there cord/de $(CC) $(CFLAGS) -o cord/de $(srcdir)/cord/de.c cord/cordbscs.o cord/cordxtra.o gc.a $(CURSES)

if_mach: $(srcdir)/if_mach.c $(srcdir)/config.h
	$(CC) $(CFLAGS) -o if_mach $(srcdir)/if_mach.c

if_not_there: $(srcdir)/if_not_there.c
	$(CC) $(CFLAGS) -o if_not_there $(srcdir)/if_not_there.c

clean: 
	rm -f gc.a *.o gctest gctest_dyn_link test_cpp \
	      setjmp_test  mon.out gmon.out a.out core if_not_there if_mach \
	      $(CORD_OBJS) cord/cordtest cord/de
	-rm -f *~

gctest: test.o gc.a if_mach if_not_there
	rm -f gctest
	./if_mach SPARC SUNOS5 $(CC) $(CFLAGS) -o gctest  test.o gc.a -lthread -ldl
	./if_mach SPARC DRSNX $(CC) $(CFLAGS) -o gctest  test.o gc.a -lucb
	./if_not_there gctest $(CC) $(CFLAGS) -o gctest test.o gc.a

# If an optimized setjmp_test generates a segmentation fault,
# odds are your compiler is broken.  Gctest may still work.
# Try compiling setjmp_t.c unoptimized.
setjmp_test: $(srcdir)/setjmp_t.c $(srcdir)/gc.h if_mach if_not_there
	$(CC) $(CFLAGS) -o setjmp_test $(srcdir)/setjmp_t.c

test:  KandRtest cord/cordtest
	cord/cordtest

# Those tests that work even with a K&R C compiler:
KandRtest: setjmp_test gctest
	./setjmp_test
	./gctest

add_gc_prefix: add_gc_prefix.c
	$(CC) -o add_gc_prefix add_gc_prefix.c
	
gc.tar: $(SRCS) $(OTHER_FILES) add_gc_prefix
	tar cvfh gc.tar `add_gc_prefix $(SRCS) $(OTHER_FILES)`
	
pc_gc.tar: $(SRCS) $(OTHER_FILES)
	tar cvfX pc_gc.tar pc_excludes $(SRCS) $(OTHER_FILES)

floppy: pc_gc.tar
	-mmd a:/cord
	-mmd a:/cord/private
	-mmd a:/include
	-mmd a:/include/private
	mkdir /tmp/pc_gc
	cat pc_gc.tar | (cd /tmp/pc_gc; tar xvf -)
	-mcopy -tmn /tmp/pc_gc/* a:
	-mcopy -tmn /tmp/pc_gc/cord/* a:/cord
	-mcopy -mn /tmp/pc_gc/cord/de_win.ICO a:/cord
	-mcopy -tmn /tmp/pc_gc/cord/private/* a:/cord/private
	-mcopy -tmn /tmp/pc_gc/include/* a:/include
	-mcopy -tmn /tmp/pc_gc/include/private/* a:/include/private
	rm -r /tmp/pc_gc

gc.tar.Z: gc.tar
	compress gc.tar

gc.tar.gz: gc.tar
	gzip gc.tar

lint: $(CSRCS) test.c
	lint -DLINT $(CSRCS) test.c | egrep -v "possible pointer alignment problem|abort|exit|sbrk|mprotect|syscall"
	
# BTL: added to test shared library version of collector.
# Currently works only under SunOS5.  Requires GC_INIT call from statically
# loaded client code.
ABSDIR = `pwd`
gctest_dyn_link: test.o libgc.so
	$(CC) -L$(ABSDIR) -R$(ABSDIR) -o gctest_dyn_link test.o -lgc -ldl -lthread

gctest_irix_dyn_link: test.o libirixgc.so
	$(CC) -L$(ABSDIR) -o gctest_irix_dyn_link test.o -lirixgc

reserved_namespace: $(SRCS)
	for file in $(SRCS) test.c test_cpp.cc; do \
		sed s/GC_/_GC_/g < $$file > tmp; \
		cp tmp $$file; \
		done

user_namespace: $(SRCS)
	for file in $(SRCS) test.c test_cpp.cc; do \
		sed s/_GC_/GC_/g < $$file > tmp; \
		cp tmp $$file; \
		done
