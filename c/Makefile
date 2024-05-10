.PHONY: all ifiss

# $(info Before assignment: PETSC_DIR=$(PETSC_DIR))
ifeq ($(PETSC_DIR), )
    PETSC_DIR := $(HOME)/projects/ip-hdg/petsc
    # $(info After assignment: PETSC_DIR=$(PETSC_DIR))
endif
ifeq ($(PETSC_ARCH), )
	PETSC_ARCH := arch-moose
endif

ifiss_CXXFLAGS := -I$(PETSC_DIR)/include -I$(PETSC_DIR)/$(PETSC_ARCH)/include
ifiss_LDFLAGS := -Wl,-rpath -Wl,$(PETSC_DIR)/$(PETSC_ARCH)/lib -L$(PETSC_DIR)/$(PETSC_ARCH)/lib -lpetsc

ifneq ($(GPERF_DIR), )
    ifiss_CXXFLAGS += -DHAVE_GPERFTOOLS -I$(GPERF_DIR)/include
    ifiss_LDFLAGS += -L$(GPERF_DIR)/lib -Wl,-rpath,$(GPERF_DIR)/lib -ltcmalloc_and_profiler
endif

ifneq ($(DEBUG), )
	ifiss_CXXFLAGS += -O0
endif

all: ifiss

ifiss: solve-ifiss-mat

solve-ifiss-mat: solve-ifiss-mat.c
	mpicxx -Werror -Wall -g -O2 $(ifiss_CXXFLAGS) solve-ifiss-mat.c -o solve-ifiss-mat $(ifiss_LDFLAGS)

clean: solve-ifiss-mat
	rm solve-ifiss-mat

serial_run: ifiss
	./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is -ksp_monitor $(PETSC_OPTIONS)

run: ifiss
	mpiexec -np 2 ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is -ksp_monitor $(PETSC_OPTIONS)

serial_valgrind: ifiss
	valgrind ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is -ksp_monitor $(PETSC_OPTIONS)

valgrind: ifiss
	mpiexec -np 2 valgrind ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is -ksp_monitor $(PETSC_OPTIONS)

profile: ifiss
	PROFILE_BASE=test mpiexec -np 2 ./solve-ifiss-mat -fAnst Anst.mat -fBst Bst.mat -fQ Q.mat -fbound bound.is -ksp_monitor $(PETSC_OPTIONS)
