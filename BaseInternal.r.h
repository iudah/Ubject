#ifndef BASEINTERNAL_R_H
#define BASEINTERNAL_R_H

#include <stdarg.h>
#include <stddef.h>

#include "BaseClass.r.h"

void base_internal_make_a_class_(void *class, const struct BaseClass *super,
                                 size_t size,
                                 void *(*ctor)(void *self, va_list *arg));
void base_internal_add_meta_class_(void *class, const void *meta_class);
void base_internal_set_base_object_(const void *class);
size_t class_internal_size(const void *class);
const void *class_internal_super(const void *class);
int class_increment_internal_count(const void *class);
#endif