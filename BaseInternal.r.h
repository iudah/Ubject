#ifndef BASEINTERNAL_R_H
#define BASEINTERNAL_R_H

#include <stdarg.h>
#include <stddef.h>

#include "BaseClass.r.h"

extern void (*base_internal_make_a_class_)(
    void *class, const struct BaseClass *super, size_t size,
    void *(*ctor)(void *self, va_list *arg));
extern void (*base_internal_add_meta_class_)(void *class,
                                             const void *meta_class);
extern void (*base_internal_set_base_object_)(const void *class);
extern const size_t (*class_internal_size)(const void *class);
extern const void *(*class_internal_super)(const void *class);
#endif