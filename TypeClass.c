#include <stdio.h>
#include <stdlib.h>

#include "BaseClass.h"
#include "BaseClass.r.h"
#include "BaseInternal.r.h"
#include "BaseObject.h"

#include "TypeClass.h"
#define TYPECLASS_C
#include "TypeClass.r.h"

// This function is used to call the destructor of the superclass of a given
// class. Handles potential errors related to NULL superclass or missing
// destructor.
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

// This array is used to store the name of the class.
char desc[255];
// This function is used to get the name of a class. Handles different scenarios
// such as TypeClass, BaseClass, or custom classes.
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

// This function is used to get the name of the class of an object.
const char *className(const void *self_) { return descName(classOf(self_)); }

// This function is used to call the destructor of an object. Handles errors
// related to NULL destructors and inappropriate destruction of class
// descriptors.
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

// Constructor for the TypeClass, initializes its methods such as dtor and
// className. Used during class initialization.
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

// Declaration and initialization of the global TypeClass.
struct BaseClass typeClass = {0};
const void *TypeClass = &typeClass;

// A constructor to initialize TypeClass during program startup.
static void __attribute__((__constructor__(BASE_CTOR_PRIORITY + 4)))
initTypeClass(void) {
  if (!BaseClass)
    UbjectError.error("(?)\n");
  base_internal_make_a_class_((void *)TypeClass, BaseClass,
                              sizeof(struct TypeClass), TypeClass_ctor);
}
