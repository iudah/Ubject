/**
 * @file Ubject.c
 * @brief Ubject implementation
 */

#define __STDC_WANT_LIB_EXT1__ 1 // required for memcpy_s
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BaseObject
{
    const struct BaseClass *class;
};
struct BaseClass
{
    struct BaseObject _;
    const struct BaseClass *super;
    size_t size;
    void *(*ctor)(void *self, va_list *arg);
};

static void *BaseObject_ctor(void *self_, va_list *arg)
{
    return self_;
}

const void *classOf(const void *self_)
{
    const struct BaseObject *self = self_;
    assert(self && self->class);
    return self->class;
}

void *ctor(void *self_, va_list *arg)
{
    const struct BaseClass *class = classOf(self_);

    assert(class->ctor);
    return class->ctor(self_, arg);
}

size_t sizeOf(const void *self_)
{
    const struct BaseClass *class = classOf(self_);
    return class->size;
}

const void *super(const void *self_)
{
    const struct BaseClass *self = self_;
    assert(self && self->super);
    return self->super;
}

void *super_ctor(const void *class_, void *self, va_list *arg_)
{
    const struct BaseClass *superclass = super(class_);
    assert(self && superclass->ctor);
    return superclass->ctor(self, arg_);
}

static void *BaseClass_ctor(void *self_, va_list *arg)
{
    struct BaseClass *self = self_;

    // self->name = va_arg(*arg, char *);
    self->super = va_arg(*arg, struct BaseClass *);
    self->size = va_arg(*arg, size_t);

    assert(self->super);

    const size_t offset = offsetof(struct BaseClass, ctor);
    const size_t limit = sizeOf(self->super) - offset;
#ifdef __STDC_LIB_EXT1__
    memcpy_s((char *)self + offset, limit, (char *)self->super + offset, limit);
#else
    memcpy((char *)self + offset, (char *)self->super + offset, limit);
#endif

    {
        typedef void (*voidf)();
        voidf selector;
        va_list args = *arg;
        while ((selector = va_arg(args, voidf)))
        {
            voidf method = va_arg(args, voidf);
            if (selector == (voidf)ctor)
                *(voidf *)&self->ctor = method;
        }
    }
    return self;
}

static const struct BaseClass baseObject[] = {
    {// BaseObject class
     {baseObject + 1},
     baseObject,
     sizeof(struct BaseObject),
     BaseObject_ctor},
    {// BaseObject class
     {baseObject + 1},
     baseObject,
     sizeof(struct BaseClass),
     BaseClass_ctor}};

const void *BaseObject = baseObject;
const void *BaseClass = baseObject + 1;

size_t mem_used = 0;

void *new(const void *class_, ...)
{
    const struct BaseClass *class = class_;
    struct BaseObject *object;
    va_list arg;

    assert(class && class->size);
    mem_used += class->size;
    object = calloc(1, class->size);
    assert(object);
    object->class = class;
    va_start(arg, class_);
    object = ctor(object, &arg);
    va_end(arg);

    printf("Used %uB\n", mem_used);

    return object;
}

#include "Ubject.h"
#include "Ubject.r.h"

static void *Ubject_dtor(void *self_)
{
    return self_;
}

static int Ubject_differ(const void *self_, const void *b)
{
    return self_ != b;
}

void *super_dtor(const void *class_, void *self)
{
    const struct TypeClass *superclass = super(class_);
    assert(self && superclass->dtor);
    return superclass->dtor(self);
}

static void *TypeClass_ctor(void *self_, va_list *arg)
{
    struct TypeClass *self = super_ctor(TypeClass, self_, arg);
    typedef void (*voidf)();
    voidf selector;
    va_list args = *arg;
    while ((selector = va_arg(args, voidf)))
    {
        voidf method = va_arg(args, voidf);
        if (selector == (voidf)dtor)
            *(voidf *)&self->dtor = method;
        else if (selector == (voidf)className)
            *(voidf *)&self->name = method;
    }
    return self;
}

const char *className(const void *self_)
{
    const struct TypeClass *class = classOf(self_);
    return class->name;
}

void *dtor(void *self_)
{
    const struct TypeClass *class = classOf(self_);

    assert(class->dtor);
    return class->dtor(self_);
}

void delete(void *self_)
{
    if (self_)
        free(dtor(self_));
}
static const struct BaseClass typeClass = {
    // struct BaseObject _;
    {baseObject + 1},
    // const struct Class *super;
    baseObject + 1,
    // size_t size;
    sizeof(struct TypeClass),
    // void *(*ctor)(void *self, va_list *arg);
    TypeClass_ctor,
};
static const struct TypeClass ubject = {
    {// struct BaseObject super;
     // ===
     // const struct Class *class;
     &typeClass,
     // const struct Class *super;
     baseObject + 1,
     // size_t size;
     sizeof(struct Ubject),
     // void *(*ctor)(void *self, va_list *arg);
     BaseObject_ctor},
    "Ubject",
    Ubject_dtor};

const void *Ubject = &ubject, *TypeClass = &typeClass;