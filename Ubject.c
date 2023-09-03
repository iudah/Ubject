/**
 * @file Ubject.c
 * @brief Ubject implementation
 */
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "Ubject.h"
#include "Ubject.r.h"

void *new(const void *class_, ...)
{
    const struct Class *class = class_;
    struct Ubject *ubject;
    va_list arg;

    assert(class && class->size);
    ubject = calloc(1, class->size);
    assert(ubject);
    ubject->class = class;
    va_start(arg, class_);
    ubject = ctor(ubject, &arg);
    va_end(arg);
    return ubject;
}

void delete(void *self_)
{
    if (self_)
        free(dtor(self_));
}

static void *Ubject_ctor(void *self_, va_list *arg)
{
    return self_;
}

static void *Ubject_dtor(void *self_)
{
    return self_;
}

static int Ubject_differ(const void *self_, const void *b)
{
    return self_ != b;
}

static int Ubject_puto(const void *self_, FILE *f)
{
    const struct Class *class = classOf(self_);
    return fprintf(f, "<%s %x>\n", class->name, class);
}

const void *classOf(const void *self_)
{
    const struct Ubject *self = self_;
    assert(self && self->class);
    return self->class;
}

void *ctor(void *self_, va_list *arg)
{
    const struct Class *class = classOf(self_);

    assert(class->ctor);
    return class->ctor(self_, arg);
}

void *dtor(void *self_)
{
    const struct Class *class = classOf(self_);

    assert(class->dtor);
    return class->dtor(self_);
}

int differ(const void *self_, const void *b)
{
    const struct Class *class = classOf(self_);

    assert(class->differ);
    return class->differ(self_, b);
}
int puto(const void *self_, FILE *f)
{
    const struct Class *class = classOf(self_);

    assert(class->puto);
    return class->puto(self_, f);
}

static void *Class_ctor(void *self_, va_list *arg)
{
    struct Class *self = self_;

    self->name = va_arg(*arg, char *);
    self->super = va_arg(*arg, struct Class *);
    self->size = va_arg(*arg, size_t);

    assert(self->super);

    const size_t offset = offsetof(struct Class, ctor);
    memcpy((char *)self + offset, (char *)self->super + offset, sizeOf(self->super) - offset);

    {
        typedef void (*voidf)();
        voidf selector;
        va_list args = *arg;
        while ((selector = va_arg(args, voidf)))
        {
            voidf method = va_arg(args, voidf);
            if (selector == (voidf)ctor)
                *(voidf *)&self->ctor = method;
            else if (selector == (voidf)dtor)
                *(voidf *)&self->dtor = method;
            else if (selector == (voidf)differ)
                *(voidf *)&self->differ = method;
            else if (selector == (voidf)puto)
                *(voidf *)&self->puto = method;
        }
    }
    return self;
}

static void *Class_dtor(void *self_)
{
    struct Class *self = self_;
    fprintf(stderr, "%s: cannot destroy class\n", self->name);
    return 0;
}

size_t sizeOf(const void *self_)
{
    const struct Class *class = classOf(self_);
    return class->size;
}

const void *super(const void *self_)
{
    const struct Class *self = self_;
    assert(self && self->super);
    return self->super;
}

static const struct Class ubject[] = {
    {// Ubject class
     {ubject + 1},
     "Ubject",
     ubject,
     sizeof(struct Ubject),
     Ubject_ctor,
     Ubject_dtor,
     Ubject_differ,
     Ubject_puto},
    {// Class class
     {ubject + 1},
     "Class",
     ubject,
     sizeof(struct Class),
     Class_ctor,
     Class_dtor,
     Ubject_differ,
     Ubject_puto}};

const void *Ubject = ubject;
const void *Class = ubject + 1;