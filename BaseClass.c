#define __STDC_WANT_LIB_EXT1__ 1 // required for memcpy_s
#include <string.h>

#include "BaseObject.h"

// #define BASECLASS_EXPORTS
#include "BaseClass.h"
#define BASECLASS_C
#include "BaseClass.r.h"
#include "BaseInternal.r.h"

void *ctor(void *self_, va_list *arg) {
  const struct BaseClass *class = classOf(self_);

  if (!class->ctor) {
    UbjectError.error("init: no constructor found\n");
  }
  return class->ctor(self_, arg);
}

size_t sizeOf(const void *self_) {
  const struct BaseClass *class = classOf(self_);
  return class->size;
}

const void *super(const void *class_) {
  const struct BaseClass *class = class_;
  if (!class) {
    UbjectError.error("super: trying to access super class of NULL class\n");
  }
  if (!class->super) {
    UbjectError.error("super: super class is NULL\n");
  }
  return class->super;
}

void *super_ctor(const void *class_, void *self, va_list *arg_) {
  const struct BaseClass *superclass = super(class_);
  if (!superclass) {
    UbjectError.error("super: super class is NULL\n");
  }
  if (!superclass->ctor) {
    UbjectError.error("super: class constructor is NULL\n");
  }
  return superclass->ctor(self, arg_);
}

static void *BaseClass_ctor(void *self_, va_list *arg) {
  struct BaseClass *self = self_;

  // self->name = va_arg(*arg, char *);
  self->super = va_arg(*arg, struct BaseClass *);
  self->size = va_arg(*arg, size_t);

  if (!self->super)
    UbjectError.error("BaseClass: class has no superclass\n");

  if (self->super != BaseObject) {
    const size_t offset = offsetof(struct BaseClass, ctor);
    const size_t limit = sizeOf(self->super) - offset;
#ifdef __STDC_LIB_EXT1__
    memcpy_s((char *)self + offset, limit, (char *)self->super + offset, limit);
#else
    if (0 < (signed int)limit) {
    }
    memcpy((char *)self + offset, (char *)self->super + offset, limit);
#endif
  }

  {
    typedef void (*voidf)();
    voidf selector;
    va_list args = *arg;
    while ((selector = va_arg(args, voidf))) {
      voidf method = va_arg(args, voidf);
      if (selector == (voidf)ctor)
        *(voidf *)&self->ctor = method;
    }
  }
  return self;
}

static struct BaseClass baseObject = {.super = &baseObject,
                                      .size = sizeof(struct BaseObject)};

static struct BaseClass baseClass = {.super = &baseObject,
                                     .size = sizeof(struct BaseClass),
                                     .ctor = BaseClass_ctor};

static void
base_internal_make_a_class(void *class, const struct BaseClass *super,
                           size_t size,
                           void *(*ctor)(void *self, va_list *arg)) {
  struct BaseClass *bc = class;

  bc->super = super;
  bc->size = size;
  bc->ctor = ctor;
  base_internal_add_meta_class_(bc, BaseClass);
}

void (*base_internal_make_a_class_)(
    void *class, const struct BaseClass *super, size_t size,
    void *(*ctor)(void *self, va_list *arg)) = base_internal_make_a_class;

const static size_t class_internal_size_(const void *class) {
  return ((struct BaseClass *)class)->size;
}
const size_t (*class_internal_size)(const void *class) = class_internal_size_;

static const void *class_internal_super_(const void *class) {
  return ((struct BaseClass *)class)->super;
}
const void *(*class_internal_super)(const void *class) = class_internal_super_;

const void *BaseClass = &baseClass;
static void __attribute__((__constructor__(BASE_CTOR_PRIORITY + 2)))
initBaseClass(void) {
  base_internal_set_base_object_(&baseObject);
  base_internal_add_meta_class_(&baseObject, BaseClass);
  base_internal_add_meta_class_(&baseClass, BaseClass);
}