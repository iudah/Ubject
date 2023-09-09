/**
 * @file Ubject.c
 * @brief Ubject implementation
 */

#define __STDC_WANT_LIB_EXT1__ 1 // required for memcpy_s
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void ubject_error(const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    exit(-1);
}
void ubject_warn(const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    vprintf(fmt, arg);
    va_end(arg);
    return;
}

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
    if (!self)
    {
        ubject_error("classOf: trying to access class of NULL object\n");
    }
    if (!self->class)
    {
        ubject_error("classOf: class of object is NULL\n");
    }
    return self->class;
}

void *ctor(void *self_, va_list *arg)
{
    const struct BaseClass *class = classOf(self_);

    if (!class->ctor)
    {
        ubject_error("new: no constructor found\n");
    }
    return class->ctor(self_, arg);
}

size_t sizeOf(const void *self_)
{
    const struct BaseClass *class = classOf(self_);
    return class->size;
}

const void *super(const void *class_)
{
    const struct BaseClass *class = class_;
    if (!class)
    {
        ubject_error("super: trying to access super class of NULL class\n");
    }
    if (!class->super)
    {
        ubject_error("super: super class is NULL\n");
    }
    return class->super;
}

void *super_ctor(const void *class_, void *self, va_list *arg_)
{
    const struct BaseClass *superclass = super(class_);
    if (!superclass)
    {
        ubject_error("super: super class is NULL\n");
    }
    if (!superclass->ctor)
    {
        ubject_error("super: class constructor is NULL\n");
    }
    return superclass->ctor(self, arg_);
}

static void *BaseClass_ctor(void *self_, va_list *arg)
{
    struct BaseClass *self = self_;

    // self->name = va_arg(*arg, char *);
    self->super = va_arg(*arg, struct BaseClass *);
    self->size = va_arg(*arg, size_t);

    if (!self->super)
        ubject_error("BaseClass: class has no superclass\n");

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

void *new(const void *class_, ...)
{
    const struct BaseClass *class = class_;
    struct BaseObject *object;
    va_list arg;

    if (!class)
        ubject_error("new: no class provided\n");
    if (!class->size)
        ubject_error("new: class size is invalid\n");
    object = calloc(1, class->size);
    if (!object)
        ubject_error("new: out of memory\n");
    object->class = class;
    va_start(arg, class_);
    object = ctor(object, &arg);
    va_end(arg);

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
    if (!superclass)
    {

        ubject_error("%s: super class is NULL\n", descName(class_));
    }
    if (!superclass->dtor)
    {
        ubject_error("%s: %s: class destructor is NULL\n", descName(class_), descName(superclass));
    }
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
char desc[255];
const char *descName(const void *class_)
{
    const struct TypeClass *class = class_;

    if (class == Ubject)
        return class->name;

    const void *super_class = super(class);

    if (super_class == TypeClass)
    {
        snprintf(desc, 255, "%sClass", class->name);
        return desc;
    }

    if (super_class == BaseClass || super_class == BaseObject)
        return "BaseClass";

    return class->name;
}

const char *className(const void *self_)
{
    return descName(classOf(self_));
}

void *dtor(void *self_)
{
    const struct TypeClass *class = classOf(self_);
    // check if self is a class descriptor
    // all class descriptor should extend TypeClass
    const void *super_class = super(class);
    if (super_class == TypeClass)
    {
        ubject_warn("TypeClass: trying to destroy class (%s) descriptor? Ignored\n", className(self_));
        return NULL;
    }
    // TypeClass extends BaseClass
    if (super_class == BaseClass || class == BaseClass)
    {
        ubject_warn("BaseClass: trying to destroy class (%s) descriptor? Ignored\n", className(self_));
        return NULL;
    }
    if (!class->dtor)
    {
        ubject_error("%s: class destructor is NULL\n", className(self_));
    }

    return class->dtor(self_);
}

void delete(void *self_)
{
    if (self_)
        free(dtor(self_));
}
static const struct BaseClass typeClass = {
    // struct BaseObject _; super object class
    {baseObject + 1},
    // const struct Class *super;
    baseObject + 1,
    // size_t size;
    sizeof(struct TypeClass),
    // void *(*ctor)(void *self, va_list *arg);
    TypeClass_ctor,
};
static const struct TypeClass ubject = {
    {// struct BaseObject _;
     // {&typeClass}===typeClass
     &typeClass,
     // const struct Class *super;
     baseObject,
     // size_t size;
     sizeof(struct Ubject),
     // void *(*ctor)(void *self, va_list *arg);
     BaseObject_ctor},
    "Ubject",
    Ubject_dtor};

const void *Ubject = &ubject, *TypeClass = &typeClass;