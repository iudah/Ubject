
#include <stdio.h>
#define __STDC_WANT_LIB_EXT1__ 1 // required for memcpy_s
#include <stdlib.h>

#include "BaseClass.h"

// #define BASEOBJECT_EXPORTS
#include "BaseObject.h"

#define BASEOBJECT_C
#include "BaseInternal.r.h"
#include "BaseObject.r.h"

static void Ub_error(const char *fmt, ...) {
  va_list arg;
  puts("\e[0;31m");
  va_start(arg, fmt);
  vfprintf(stderr, fmt, arg);
  va_end(arg);
  puts("\e[0m");
  exit(-1);
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

const struct Ubject_err_disp__ UbjectError = {Ub_error, Ub_warn};

static void *BaseObject_ctor(void *self_, va_list *arg) { return self_; }

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

static void __attribute__((__constructor__(BASE_CTOR_PRIORITY)))
initBaseObject(void) {}

static void base_internal_add_meta_class(void *class, const void *meta_class) {
  struct BaseObject *bo = class;
  bo->class = (void *)meta_class;
}

void (*base_internal_add_meta_class_)(void *class, const void *meta_class) =
    base_internal_add_meta_class;

const void *BaseObject = 0;

static void setBaseObjectDesc(const void *base_obj_desc) {
  BaseObject = base_obj_desc;
}
void (*base_internal_set_base_object_)(const void *class) = setBaseObjectDesc;

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

  return object;
}
