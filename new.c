/**
 * @file new.c
 * @brief Implementation of memory managing functions.
 * @author Jude (iudah)
 */

#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "new.r.h"

void *new(const void *descriptor, ...)
{
    const struct Class *class = descriptor;
    void *p = calloc(1, class->size);

    assert(p);
    *(const struct Class **)p = class;

    if (class->ctor)
    {
        va_list arg;
        va_start(arg, descriptor);
        p = class->ctor(p, &arg);
        va_end(arg);
    }
    return p;
}

void delete(void *self)
{
    const struct Class **class = self;

    if (self && *class && (*class)->dtor)
        self = (*class)->dtor(self);
    free(self);
}

void *clone(const void *self)
{
    struct Class *const *class = self;
    assert(self && *class && (*class)->clone);
    return (*class)->clone(self);
}

int differ(const void *self, const void *b)
{
    struct Class *const *class = self;
    assert(self && *class && (*class)->differ);
    return (*class)->differ(self, b);
}

size_t sizeOf(const void *self)
{
    const struct Class *const *class = self;

    assert(self && class);
    return (*class)->size;
}
