IFICC = $(shell icc --version | head -c3)
$(info if_icc=$(IFICC))

MACHINE = $(shell uname -n)
$(info machine=$(MACHINE))

TYPECLANG = $(shell clang --version | head -c16)
$(info type_clang=$(TYPECLANG))

GCC = gcc
CLANG = clang
ICC = icc

ifeq ($(MACHINE),snb01)
	GCCFLAGS = -g -march=sandybridge -mavx2 -Ofast -funroll-loops -finline-functions -ftree-vectorize
	CLANGFLAGS = -g -march=sandybridge -mavx2 -Ofast -funroll-loops -finline-functions -ftree-vectorize
	ICCFLAGS = -g -xhost -mavx2 -Ofast -funroll-all-loops -finline-functions
else 
	GCCFLAGS = -g -march=native -mavx2 -Ofast -funroll-loops -finline-functions -ftree-vectorize
	CLANGFLAGS = -g -march=native -mavx2 -Ofast -funroll-loops -finline-functions -ftree-vectorize
	ICCFLAGS = -g -xhost -mavx2 -Ofast -funroll-all-loops -finline-functions
endif 

.PHONY: clean all check

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

ifeq ($(IFICC),icc)
all: gcc_nobin gcc_bin clang_nobin clang_bin icc_nobin icc_bin
else
all: gcc_nobin gcc_bin llvm_nobin llvm_bin
endif

gcc_nobin: main.c ../gene.c
	$(GCC) $(GCCFLAGS) -o $@ $^
	
gcc_bin: main_bin.c ../gene_bin.c
	$(GCC) $(GCCFLAGS) -o $@ $^

llvm_nobin: main.c ../gene.c
	$(CLANG) $(CLANGFLAGS) -o $@ $^
	
llvm_bin: main_bin.c ../gene_bin.c
	$(CLANG) $(CLANGFLAGS) -o $@ $^

clang_nobin: main.c ../gene.c
	$(CLANG) $(CLANGFLAGS) -o $@ $^
	
clang_bin: main_bin.c ../gene_bin.c
	$(CLANG) $(CLANGFLAGS) -o $@ $^

icc_nobin: main.c ../gene.c
	$(ICC) $(ICCFLAGS) -o $@ $^
	
icc_bin: main_bin.c ../gene_bin.c
	$(ICC) $(ICCFLAGS) -o $@ $^

clean :
	@rm -f *.o gcc_nobin gcc_bin clang_nobin clang_bin llvm_nobin llvm_bin icc_nobin icc_bin
