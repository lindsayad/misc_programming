.PHONY: all ifiss

PETSC_DIR ?= $(HOME)/petsc
PETSC_ARCH ?= arch-linux-c-debug

ifiss_CXXFLAGS := -I$(PETSC_DIR)/include -I$(PETSC_DIR)/$(PETSC_ARCH)/include
ifiss_LDFLAGS := -Wl,-rpath -Wl,$(PETSC_DIR)/$(PETSC_ARCH)/lib -L$(PETSC_DIR)/$(PETSC_ARCH)/lib -lpetsc

ifneq ($(GPERF_DIR), )
    ifiss_CXXFLAGS += -DHAVE_GPERFTOOLS -I$(GPERF_DIR)/include
    ifiss_LDFLAGS += -L$(GPERF_DIR)/lib -Wl,-rpath,$(GPERF_DIR)/lib -ltcmalloc_and_profiler
endif

PETSC_OPTIONS ?= -ksp_monitor

all: ifiss

ifiss: solve-ifiss-mat

solve-ifiss-mat: solve-ifiss-mat.c
	mpicxx -Werror -Wall -g -O2 $(ifiss_CXXFLAGS) solve-ifiss-mat.c -o solve-ifiss-mat $(ifiss_LDFLAGS)

clean: solve-ifiss-mat
	rm solve-ifiss-mat

dbg:
	mpicxx -Werror -Wall -g -O0 $(ifiss_CXXFLAGS) solve-ifiss-mat.c -o solve-ifiss-mat $(ifiss_LDFLAGS)

gdb : dbg
	OMP_NUM_THREADS=1 gdb --args ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)

opt:
	mpicxx -Werror -Wall -g -O2 $(ifiss_CXXFLAGS) solve-ifiss-mat.c -o solve-ifiss-mat $(ifiss_LDFLAGS)

serial_run: ifiss
	OMP_NUM_THREADS=1 ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)

run: ifiss
	OMP_NUM_THREADS=1 mpiexec -np 2 ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)

serial_valgrind: ifiss
	OMP_NUM_THREADS=1 valgrind $(VALGRIND_OPTIONS) ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)

valgrind: ifiss
	OMP_NUM_THREADS=1 mpiexec -np 2 valgrind $(VALGRIND_OPTIONS) ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)

profile: ifiss
	OMP_NUM_THREADS=1 PROFILE_BASE=test mpiexec -np 2 ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)

serial_profile: ifiss
	OMP_NUM_THREADS=1 PROFILE_BASE=test ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is $(PETSC_OPTIONS)
