#include <stdlib.h>
#include <stdio.h>

#include "BaseClass.h"
#include "BaseInternal.r.h"
#include "BaseObject.h"

//#define TYPECLASS_EXPORTS
#include "TypeClass.h"
#define TYPECLASS_C
#include "TypeClass.r.h"

void *super_dtor(const void *class_, void *self) {
  const struct TypeClass *superclass = super(class_);
  if (!superclass) {

    UbjectError.error("%s: super class is NULL\n", descName(class_));
  }
  if (!superclass->dtor) {
    UbjectError.error("%s: %s: class destructor is NULL\n", descName(class_),
                      descName(superclass));
  }
  return superclass->dtor(self);
}

char desc[255];
const char *descName(const void *class_) {
  const struct TypeClass *class = class_;

  const void *super_class = super(class);

  if (super_class == TypeClass) {
    snprintf(desc, 255, "%sClass", class->name);
    return desc;
  }

  if (super_class == BaseClass || super_class == BaseObject)
    return "BaseClass";

  return class->name;
}

const char *className(const void *self_) { return descName(classOf(self_)); }

void *dtor(void *self_) {
  const struct TypeClass *class = classOf(self_);
  // check if self is a class descriptor
  // all class descriptor should extend TypeClass
  const void *super_class = super(class);
  if (super_class == TypeClass) {
    UbjectError.warn(
        "TypeClass: trying to destroy class (%s) descriptor? Ignored\n",
        className(self_));
    return NULL;
  }

  // TypeClass extends BaseClass
  if (super_class == BaseClass || class == BaseClass) {
    UbjectError.warn(
        "BaseClass: trying to destroy class (%s) descriptor? Ignored\n",
        className(self_));
    return NULL;
  }
  if (!class->dtor) {
    UbjectError.error("%s: class destructor is NULL\n", className(self_));
  }

  return class->dtor(self_);
}

static void *TypeClass_ctor(void *self_, va_list *arg) {
  struct TypeClass *self = super_ctor(TypeClass, self_, arg);
  typedef void (*voidf)();
  voidf selector;
  va_list args = *arg;
  while ((selector = va_arg(args, voidf))) {
    voidf method = va_arg(args, voidf);
    if (selector == (voidf)dtor)
      *(voidf *)&self->dtor = method;
    else if (selector == (voidf)className)
      *(voidf *)&self->name = method;
  }
  return self;
}

struct BaseClass typeClass = {0};
const void *TypeClass = &typeClass;
static void __attribute__((__constructor__(BASE_CTOR_PRIORITY + 4)))
initTypeClass(void) {
  base_internal_make_a_class_((void *)TypeClass, BaseClass,
                              sizeof(struct TypeClass), TypeClass_ctor);
}
