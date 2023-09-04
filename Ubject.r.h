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
    const struct Ubject _;
    const char *name;
    const struct Class *super;
    size_t size;
    void *(*ctor)(void *self, va_list *arg);
    void *(*dtor)(void *self);
    int (*differ)(const void *self, const void *b);
    int (*puto)(const void *self, FILE *f);
};

void *super_ctor(const void *class_, void *self, va_list *arg_);
void *super_dtor(const void *class_, void *self);
int super_differ(const void *class_, void *self, void *b);
int super_puto(const void *class_, void *self, FILE *f);

#endif