CC := gcc-5
CXX := g++-5

AUTOMAKE_OPTIONS = subdir-objects

include $(srcdir)/Makefile.files

# in future need remove -Wno-switch
SHARED_CXXFLAGS = -fPIC -fno-rtti -O2 -pipe -ffast-math -Wall -Wextra \
-std=gnu++1y -Wc++14-compat \
-Wno-literal-suffix -Wno-switch \
-I$(shell $(CC) -print-file-name=plugin)/include

SHARED_LDFLAGS = -avoid-version -lgcc_s

if ENABLE_SANITIZE
#skip -fsanitize=alignment
SHARED_CXXFLAGS += -fsanitize=address \
-fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable \
-fsanitize=vla-bound -fsanitize=null -fsanitize=return \
-fsanitize=signed-integer-overflow -fsanitize=bounds \
-fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
-fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool \
-fsanitize=enum -fsanitize=vptr
SHARED_LDFLAGS += -lasan -lubsan -fsanitize=address \
-fsanitize=shift -fsanitize=integer-divide-by-zero -fsanitize=unreachable \
-fsanitize=vla-bound -fsanitize=null -fsanitize=return \
-fsanitize=signed-integer-overflow -fsanitize=bounds \
-fsanitize=object-size -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
-fsanitize=nonnull-attribute -fsanitize=returns-nonnull-attribute -fsanitize=bool \
-fsanitize=enum -fsanitize=vptr
endif

if ENABLE_GPROF
SHARED_CXXFLAGS += "-pg"
endif

lib_LTLIBRARIES = libparanucker.la libcxxparanucker.la
libparanucker_la_SOURCES = ${SRC}
libparanucker_la_LDFLAGS = ${SHARED_LDFLAGS}
libparanucker_la_CXXFLAGS = ${SHARED_CXXFLAGS}

libcxxparanucker_la_SOURCES = ${SRC} custom/fixed-cp-tree.h
libcxxparanucker_la_LDFLAGS = ${SHARED_LDFLAGS}
libcxxparanucker_la_CXXFLAGS = ${SHARED_CXXFLAGS} -DENABLE_CXXLANG

all-local: libparanucker.la libcxxparanucker.la
	echo done
