/**
 * @file Ubject.c
 * @brief Ubject implementation
 */
#include <stdio.h>
#include <stdlib.h>

#include "BaseClass.h"
#include "BaseObject.h"
#include "BaseObject.r.h"
#include "TypeClass.h"
#include "TypeClass.r.h"

// #define UBJECT_EXPORTS
#include "Ubject.h"
#define UBJECT_C
#include "Ubject.r.h"

// Ubject constructor.
// This function serves as the constructor for Ubject instances. It initializes
// the object and returns a pointer to itself.
static void *Ubject_ctor(void *self_, va_list __attribute__((unused)) * arg) {
  return self_;
}

// Ubject destructor.
// This function is the destructor for Ubject instances. It performs any
// necessary cleanup and returns a pointer to itself.
static void *Ubject_dtor(void *self_) { return self_; }

// Check if two Ubject objects are different.
// This function compares two Ubject objects and returns 1 if they are
// different, 0 if they are the same.
static int Ubject_differ(const void *self_, const void *b) {
  return self_ != b;
}

// Increment reference count of Ubject object. This function increments the
// reference counter of the given Ubject object.
int reference(void *self_) {
  struct Ubject *self = self_;
  if (!self) {
    UbjectError.error("reference: trying to reference NULL object\n");
  }
  return ++self->reference;
}

// Get reference count of Ubject object. This function gets the reference count
// of the given Ubject object.
int getReference(void *self_) {
  struct Ubject *self = self_;
  if (!self) {
    UbjectError.warn("reference: trying to reference NULL object\n");
  }
  return self->reference;
}

// Decrease the reference count of Ubject object.
// This function decreases the reference count of the given Ubject object. If
// the reference count reaches zero, the object is deallocated.
void blip(void *self_) {
  if (self_) {
    struct Ubject *self = self_;
    if (self->reference > 0)
      self->reference--;
    else
      free(dtor(self_));
  }
}

// Get the object's name. This function retrieves the name of the Ubject object
// and stores it in the provided buffer.
int objectName(const void *self, char *buff, int buf_len) {
  return snprintf(buff, buf_len, "%s_%i", className(self), ubjectIndex(self));
}

const void *Ubject = 0;

// Ubject descriptor initialization. This function initializes the Ubject
// descriptor during program startup.
static void __attribute__((__constructor__(UBJECT_PRIORITY))) initUbject(void) {
  Ubject =
      init(TypeClass, BaseObject, sizeof(struct Ubject), ctor, Ubject_ctor,
           dtor, Ubject_dtor, className, "Ubject", differ, Ubject_differ, NULL);
}
