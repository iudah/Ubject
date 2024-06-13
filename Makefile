OUT         := Ubject
SRCDIR		:= ./ $(filter-out build/%, $(wildcard */ */*/ */*/*/))
OBJDIR		:= $(addprefix build/, $(SRCDIR))
#get all c source files but exclude test.c
CSRC		:= $(filter-out %/test.c, $(wildcard $(addsuffix *.c, $(SRCDIR))))
OBJS		:= $(patsubst %.c, %.o, $(addprefix build/,$(CSRC)))
DEPS		:= $(patsubst %.o, %.o.d, $(OBJS))
BIN			:= 

CFLAGS		:= -fPIC -ggdb3 -O0 -fno-omit-frame-pointer -fsanitize=address
CXXFLAGS	:= -fPIC
CPPFLAGS	:= -I../Ubject -I../mem_lk
LDFLAGS		:= -L$$HOME -L$$HOME/libbacktrace/.libs/
LDLIBS		:= -lmem_lk 


ifeq ($(check),leaks)
CPPFLAGS	:= $(CPPFLAGS) -DIU_MEM_LK
endif

vpath $(OUT) build/
vpath lib$(OUT).so build/

.PHONY: all run clean

all : lib$(OUT).so $(OUT);

lib$(OUT).so : $(OBJS)
ifeq ($(check), leaks)
	@echo checking leaks
endif
	@echo building $@
	@$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -shared -o $$HOME/$@ $^
	@cp  $$HOME/$@ build/
	@echo $@ built

$(OUT): test.c
	@echo building $@
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -l$(OUT)   -o $$HOME/$@ $<
	@cp  $$HOME/$@ build/
	@echo $@ built

build/%.o : %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< 
	@echo $@ built

build/%.o.d : %.c | build
	@set -e;\
	rm -f $@;\
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
	sed 's,\(.*\.o\)[:]*,build/$*.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

build:
	@mkdir -p build $(OBJDIR)

run : all
	ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=$(shell which llvm-symbolizer) $$HOME/$(OUT)

clean:
	@$(RM) -r build
	@echo build removed

include $(DEPS)
