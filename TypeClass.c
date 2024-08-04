#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <mem_lk.h>

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

int super_puto(const void *class_, void *self, FILE *f) {
  const struct TypeClass *superclass = super(class_);
  if (!superclass) {

    UbjectError.error("%s: super class is NULL\n", descName(class_));
  }
  if (!superclass->puto) {
    UbjectError.error("%s: %s: class serializer is NULL\n", descName(class_),
                      descName(superclass));
  }
  return superclass->puto(self, f);
}
void *super_rollback(const void *class_, void *self, FILE *f) {
  const struct TypeClass *superclass = super(class_);
  if (!superclass) {

    UbjectError.error("%s: super class is NULL\n", descName(class_));
  }
  if (!superclass->rollb) {
    UbjectError.error("%s: %s: class deserializer is NULL\n", descName(class_),
                      descName(superclass));
  }
  return superclass->rollb(self, f);
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

static struct TypeClass **classes;
static uint64_t n_classes;
static void free_classes() { FREE(classes); }
static inline void attach(struct TypeClass *class) {

  uint64_t first = 0;
  uint64_t last = n_classes;

  n_classes++;

  if (n_classes == 1) {
    classes = MALLOC(sizeof(void *));
    classes[0] = class;

    atexit(free_classes);
  } else {
    classes = REALLOC(classes, n_classes * sizeof(void *));
    classes[last] = NULL;
    int cmp = strcmp(class->name, classes[0]->name);
    if (cmp <= 0) {
      // str1<str2
      for (uint64_t i = n_classes - 1; i > 0; i--) {
        classes[i] = classes[i - 1];
      }
      classes[0] = class;
    } else {
      // last--;
      cmp = strcmp(class->name, classes[last - 1]->name);
      if (cmp >= 0) {
        // str1>str2
        classes[last] = class;
      } else {
        first = (first + last + 1) / 2;
        uint64_t first_ = 0;
        uint64_t last_ = last--;

        while (first < last) {
          cmp = strcmp(class->name, classes[first]->name);
          if (cmp < 0) {
            last_ = last;
            last = first;
            first = (first_ + last + 1) / 2;
          } else if (cmp > 0) {
            first_ = first;
            first = (first + last + 1) / 2;
            if (first == first_)
              break;
          } else {

            first_ = first;
          }
        }

        // for(uint64_t i =first; i < (n_classes-1); i++) {
        for (uint64_t i = n_classes - 1; i > first; i--) {
          classes[i] = classes[i - 1];
        }
        classes[first] = class;
      }
    }
  }
}

int puto(const void *self_, FILE *f) {
  const struct TypeClass *class = classOf(self_);

  const void *super_class = super(class);
  if (super_class == TypeClass) {
    return 0;
  }

  // TypeClass extends BaseClass
  if (super_class == BaseClass || class == BaseClass) {
    return 0;
  }

  if (!class->puto) {
    UbjectError.error("serialize: no serializer found\n");
  }
  uint64_t len = strlen(class->name);
  fwrite(&len, 1, sizeof(len), f);
  fwrite(class->name, 1, len, f);
  return class->puto((void *)self_, f);
}

static inline void *retr_class(char *c_name, uint64_t c_name_length) {

  uint64_t first = 0;
  uint64_t last = n_classes - 1;

#define UBJ_TC_INVALID_CLASSNAME                                               \
  UbjectError.error("class '%s' not found\n", c_name);

  int cmp = strncmp(c_name, classes[0]->name, c_name_length);
  if (cmp < 0) {
    // str1<str2
    // invalid name?
    UBJ_TC_INVALID_CLASSNAME;
  } else if (!cmp) {
    return classes[0];
  } else {
    cmp = strncmp(c_name, classes[last]->name, c_name_length);
    if (cmp > 0) {
      // str1>str2
      UBJ_TC_INVALID_CLASSNAME;
    } else if (!cmp) {
      return classes[last];
    } else {
      first = (first + last + 1) / 2;
      uint64_t first_ = 0;
      uint64_t last_ = last--;

      while (first <= last) {
        cmp = strncmp(c_name, classes[first]->name, c_name_length);
        if (cmp < 0) {
          last_ = last;
          last = first;
          first = (first_ + last + 1) / 2;
        } else if (cmp > 0) {
          first_ = first;
          first = (first + last + 1) / 2;
          if (first == first_)
            break;
        } else {
          return classes[first];
        }
      }
    }
  }

#undef UBJ_TC_INVALID_CLASSNAME

  return NULL;
}

void *rollback(FILE *f) {

  // const void *super_class = super(class);
  // if (super_class == TypeClass) {
  //   return 0;
  // }

  // TypeClass extends BaseClass
  // if (super_class == BaseClass || class == BaseClass) {
  //   return 0;
  // }

  // if (!class->puto) {
  //   UbjectError.error("serialize: no serializer found\n");
  // }
  uint64_t len;
  fread(&len, 1, sizeof(len), f);
  char *c_name = CALLOC(len + 1, 1);
  fread(c_name, 1, len, f);

  const struct TypeClass *class = retr_class(c_name, len);

  FREE(c_name);

  return class->rollb(partial_init(class), f);
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
      memcpy(&self->dtor, &method, sizeof(method));
    else if (selector == (voidf)className) {
      memcpy(&self->name, &method, sizeof(method));
      attach(self);
    } else if (selector == (voidf)puto)
      memcpy(&self->puto, &method, sizeof(method));
    else if (selector == (voidf)rollback)
      memcpy(&self->rollb, &method, sizeof(method));
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