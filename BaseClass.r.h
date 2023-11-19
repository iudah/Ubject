#ifndef BASECLASS_R_H
#define BASECLASS_R_H

#include <stdarg.h>
#include <stddef.h>

#include "BaseObject.r.h"

struct BaseClass {

#ifndef BASECLASS_C
  char ___[sizeof(struct BASECLASS_C_ {
#endif
    struct BaseObject _parent_struct_;
    const struct BaseClass *super;
    size_t size;
    void *(*ctor)(void *self, va_list *arg);

#ifndef BASECLASS_C
  })];
#endif
};

extern const void *BaseClass;

#endif