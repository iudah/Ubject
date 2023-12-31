// BaseClass.c: Implementation of the BaseClass class

// Required for memcpy_s
#define __STDC_WANT_LIB_EXT1__ 1

// Include required system headers
#include <stdarg.h>
#include <string.h>

// Include project headers
#include "BaseClass.h"
#include "BaseObject.h"
#define BASECLASS_C
#include "BaseClass.r.h"
#undef BASECLASS_C
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

// Function to call the constructor of the superclass
void *super_ctor(const void *class_, void *self, va_list *arg_) {

  // Cast class_ to the BaseClass struct
  const struct BaseClass *superclass = super(class_);

  // Check if the superclass exists
  if (!superclass) {
    UbjectError.error("super: super class is NULL\n");
  }

  // Check if the superclass has a constructor
  if (!superclass->ctor) {
    UbjectError.error("super: class constructor is NULL\n");
  }

  // Call the constructor of the superclass
  return superclass->ctor(self, arg_);
}

// Constructor for the BaseClass clas
static void *BaseClass_ctor(void *self_, va_list *arg) {
  // Cast self_ to the BaseClass struct
  struct BaseClass *self = self_;

  // Initialize members of the BaseClass struct
  self->super = va_arg(*arg, struct BaseClass *);
  self->size = va_arg(*arg, size_t);

  // Check if the superclass exists
  if (!self->super)
    UbjectError.error("BaseClass: class has no superclass\n");

  // Check if the superclass is not BaseObject
  if (self->super != BaseObject) {
    const size_t offset = offsetof(struct BaseClass, ctor);
    const size_t limit = sizeOf(self->super) - offset;

    // Copy members from the superclass
#ifdef __STDC_LIB_EXT1__
    memcpy_s((char *)self + offset, limit, (char *)self->super + offset, limit);
#else
    if (0 < (signed int)limit) {
    }
    memcpy((char *)self + offset, (char *)self->super + offset, limit);
#endif
  }

  {
    // Initialize the selector and method variables
    typedef void (*voidf)();
    voidf selector;
    va_list args = *arg;

    // Loop through the variable arguments to initialize methods
    while ((selector = va_arg(args, voidf))) {
      voidf method = va_arg(args, voidf);

      // Check if the selector is the constructor selector
      if (selector == (voidf)ctor)
        *(voidf *)&self->ctor = method;
    }
  }

  // Return the self pointer
  return self;
}

// Define the baseObject and baseClass structs
static struct BaseClass baseObject = {.super = &baseObject,
                                      .size = sizeof(struct BaseObject)};
static struct BaseClass baseClass = {.super = &baseObject,
                                     .size = sizeof(struct BaseClass),
                                     .ctor = BaseClass_ctor};

// Function to create a new class
void base_internal_make_a_class_(void *class, const struct BaseClass *super,
                                 size_t size,
                                 void *(*ctor)(void *self, va_list *arg)) {
  // Cast class to the BaseClass struct
  struct BaseClass *bc = class;

  // Set the superclass, size, and constructor for the new class
  bc->super = super;
  bc->size = size;
  bc->ctor = ctor;
  // Add the new class as a metaclass for itself and its superclass
  base_internal_add_meta_class_(bc, BaseClass);
}

// Function to get the size of a class
size_t class_internal_size(const void *class) {
  // Cast class to the BaseClass struct
  struct BaseClass *base_class = (struct BaseClass *)class;

  // Return the size of the class
  return base_class->size;
}

// Function to get the superclass of a class
const void *class_internal_super(const void *class) {
  // Cast class to the BaseClass struct
  struct BaseClass *base_class = (struct BaseClass *)class;

  // Return the superclass of the class
  return base_class->super;
}

// Function to increment the internal count of a class
int class_increment_internal_count(const void *class) {
  // Cast class to the BaseClass struct
  struct BaseClass *base_class = (struct BaseClass *)class;

  // Increment the internal count and return the updated value
  return ++base_class->instance_count;
}

// Pointer to the BaseClass class
const void *BaseClass = &baseClass;

// Function to initialize the BaseClass class
static void __attribute__((__constructor__(BASE_CTOR_PRIORITY + 2)))
initBaseClass(void) {
  // Set the base object for the BaseClass class
  base_internal_set_base_object_(&baseObject);

  // Add the BaseClass class as a metaclass for the BaseObject class
  base_internal_add_meta_class_(&baseObject, BaseClass);

  // Add the BaseClass class as a metaclass for itself
  base_internal_add_meta_class_(&baseClass, BaseClass);
}