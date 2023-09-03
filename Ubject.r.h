/**
 * @file Ubject.r.h
 *  @brief Ubject represention
 */
#ifndef UBJECT_R_H
#define UBJECT_R_H

/** Ubject base class*/
struct Ubject
{
    /** Ubject description  */
    const struct Class *class;
};

/** Class base class*/
struct Class
{
    /** @extends Ubject */
    const struct Ubject *class;
    const char *name;
    const struct Class *super;
    size_t size;
    void *(*ctor)(void *self, va_list *arg);
    void *(*dtor)(void *self);
    int (*differ)(const void *self, const void *b);
    int (*puto)(const void *self, FILE *f);
};

#endif