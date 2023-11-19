/**
 * @file Ubject.c
 * @brief Ubject implementation
 */
#include <stdlib.h>

#include "BaseObject.h"
#include "TypeClass.h"
#include "TypeClass.r.h"

//#define UBJECT_EXPORTS
#include "Ubject.h"
#define UBJECT_C
#include "Ubject.r.h"

static void *Ubject_ctor(void *self_, va_list *arg) { return self_; }

static void *Ubject_dtor(void *self_) { return self_; }

static int Ubject_differ(const void *self_, const void *b) {
  return self_ != b;
}

const int reference(void *self_) {
  struct Ubject *self = self_;
  if (!self) {
    UbjectError.error("reference: trying to reference NULL object\n");
  }
  return ++self->reference;
}
const int getReference(void *self_) {
  struct Ubject *self = self_;
  if (!self) {
    UbjectError.warn("reference: trying to reference NULL object\n");
  }
  return self->reference;
}

void blip(void *self_) {
  if (self_) {
    struct Ubject *self = self_;
    if (self->reference > 0)
      self->reference--;
    else
      free(dtor(self_));
  }
}

static const struct TypeClass ubject;
#if 0
= {
    {// struct BaseObject _;
     // {&typeClass}===typeClass
     &typeClass,
     // const struct Class *super;
     baseObject,
     // size_t size;
     sizeof(struct Ubject),
     // void *(*ctor)(void *self, va_list *arg);
     BaseObject_ctor},
    "Ubject",
    Ubject_dtor};
#endif
const void *Ubject = 0;

static void __attribute__((__constructor__(BASE_CTOR_PRIORITY + 6)))
initUbject(void) {
  Ubject = init(TypeClass, BaseObject, sizeof(struct Ubject), ctor, Ubject_ctor,
                dtor, Ubject_dtor, className, "Ubject", NULL);
}
