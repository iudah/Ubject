TITLE         := Ubject
OUT           := $(TITLE)

CC            := gcc
CFLAGS        :=-c -std=c17 -fPIC
CLDFLAGS      :=-Lbin #-lyhunk
CBUILD        := build/
CSRC          := BaseClass.c BaseObject.c TypeClass.c Ubject.c
CHDR          := $(CSRC:%.c=%.h)
COBJ          := $(CSRC:%.c=$(CBUILD)%.o)
EXT           := so

IFLAGS        :=-I.
GFLAGS        :=-g -fno-omit-frame-pointer -fsanitize=address 

COBJEXTRAFLAG :=
CAPPEXTRAFLAG :=
CDEFINES      :=

ifeq ($(host),  windows)
endif

ifeq (target, windows)
COBJEXTRAFLAG +=-s -Wl,--subsystem,windows,--out-implib,bin/lib$(OUT)-0.a
CAPPEXTRAFLAG +=-l$(OUT)-0
CDEFINES      +=-DBASECLASS_EXPORTS -DBASEOBJECT_EXPORTS -DTYPECLASS_EXPORTS -DUBJECT_EXPORTS
endif

ALL: PREBUILD APP POSTBUILD
ifeq ($(host), $(target))
ifeq ($(host),  termux)
	ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) $$HOME/$(OUT)
else
ifeq ($(host),  windows)
		bin/$(OUT).exe
else
	bin/$(OUT)
endif
endif
endif

PREBUILD:build

build:
	mkdir $@
	mkdir bin

APP: $(CBUILD)main.o bin/lib$(OUT).$(EXT)
	$(CC) $(CLDFLAGS) $(GFLAGS) -l$(OUT)  $< -o bin/$(OUT) $(CAPPEXTRAFLAG)	

$(CBUILD)main.o: test.c
	$(CC) $(CFLAGS) $(GFLAGS) -g $< -o $@ 

bin/lib$(OUT).$(EXT): $(COBJ)
	$(CC) $(GFLAGS) -shared -fPIC $(GFLAGS) -o $@ $^ $(COBJEXTRAFLAG)
$(CBUILD)%.o:%.c %.h %.r.h
	$(CC) $(CFLAGS) $(GFLAGS) $< -o $@  $(CDEFINES)

POSTBUILD:
ifeq ($(host), $(target))
ifeq ($(host),  termux)
	cp -r bin $$HOME
	for FILE in $$HOME/bin/*;do echo $$FILE; chmod +x $$FILE; mv $$FILE $$HOME; done;
endif
endif
	@echo Finished building!

clean: remove_all ALL

remove_all:
	@rm -r build
	@rm -r bin
	@echo build cleaned
	@echo


