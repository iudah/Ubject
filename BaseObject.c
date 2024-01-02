// Include standard C library headers for input/output and general purpose
// functions
#include <stdio.h>
#define __STDC_WANT_LIB_EXT1__ 1 // required for memcpy_s
#include <stdlib.h>

// Include header files for the base class and base object
#include "BaseClass.h"

// Include the header file for the BaseObject module
#include "BaseObject.h"

// Define a macro to indicate that we are implementing the BaseObject module
#define BASEOBJECT_C
// Include internal header files for the BaseObject module
#include "BaseInternal.r.h"
#include "BaseObject.r.h"

// Error and Warning Handling Functions:
// These functions handle errors and warnings by printing messages to the
// console and aborting the program.
static void Ub_error(const char *fmt, ...) {
  va_list arg;
  puts("\e[0;31m");
  va_start(arg, fmt);
  vfprintf(stderr, fmt, arg);
  va_end(arg);
  puts("\e[0m");
  abort();
}
static void Ub_warn(const char *fmt, ...) {
  va_list arg;
  puts("\e[0;33m");
  va_start(arg, fmt);
  vfprintf(stderr, fmt, arg);
  va_end(arg);
  puts("\e[0m");
  return;
}

// Define the UbjectError structure for error and warning handling
const struct Ubject_err_disp__ UbjectError = {.error = Ub_error,
                                              .warn = Ub_warn};

// Base Object Class Constructor:
// This function is the constructor for the base object class. It takes a
// pointer to the object being constructed and a variable argument list, and it
// initializes the object.
static void *BaseObject_ctor(void *self_,
                             va_list __attribute__((unused)) * arg) {
  return self_;
}

// Function to Get the Class of an Object:
// This function returns the class of an object.
const void *classOf(const void *self_) {
  const struct BaseObject *self = self_;
  if (!self) {
    UbjectError.error("classOf: trying to access class of NULL object\n");
  }
  if (!self->class) {
    UbjectError.error("classOf: class of object is NULL\n");
  }
  return self->class;
}

// Function to Initialize the Base Object Class:
// This function initializes the base object class. It is called as a
// constructor with a high priority.
static void __attribute__((__constructor__(BASE_CTOR_PRIORITY)))
initBaseObject(void) {}

// Function to Add a Meta Class to a Class:
// This function adds a meta class to a class.
void base_internal_add_meta_class_(void *class, const void *meta_class) {
  struct BaseObject *bo = class;
  bo->class = (void *)meta_class;
}

// Pointer to the Base Object Class Descriptor:
// This pointer is used to access the base object class descriptor.
const void *BaseObject = 0;

// Function to Set the Base Object Descriptor:
// This function sets the base object descriptor.
void base_internal_set_base_object_(const void *base_obj_desc) {
  BaseObject = base_obj_desc;
}

// Function to Initialize an Object:
// This function initializes an object of a given class. It takes a pointer to
// the class of the object being initialized and a variable argument list, and
// it returns a pointer to the initialized object.
void *init(const void *class_, ...) {
  const struct BaseClass *class = class_;
  size_t class_size = class_internal_size(class);
  struct BaseObject *object;
  va_list arg;

  if (!class)
    UbjectError.error("init: no class provided\n");
  if (!class_size)
    UbjectError.error("init: class size is invalid\n");
  object = calloc(1, class_size);
  if (!object)
    UbjectError.error("init: out of memory\n");
  object->class = class;
  va_start(arg, class_);
  object = ctor(object, &arg);
  va_end(arg);

  object->instance_index = class_increment_internal_count(class);

  return object;
}

// Function to Get the instance index of an Object:
// This function returns the instance index of an object.
int ubjectIndex(const void *self_) {
  return ((struct BaseObject *)(self_))->instance_index;
}