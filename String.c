/**
 * @file String.c
 * @brief Implementation of to String and related functions.
 * @author Jude (iudah)
 */
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "String.h"
#include "new.h"
#include "new.r.h"

struct String
{
    /** @brief String descriptor*/
    const void *class;
    char *text;
};

static void *String_ctor(void *self_, va_list *arg)
{
    struct String *self = self_;
    const char *text = va_arg(*arg, char *);
    size_t len = strlen(text) + 1;

    self->text = malloc(len);
    assert(self->text);
    strncpy(self->text, text, len);

    return self;
}
static void *String_dtor(void *self_)
{
    struct String *self = self_;

    free(self->text);
    self->text = 0;
    return self;
}
static void *String_clone(const void *self_)
{
    const struct String *self = self_;
    return new (String, self->text);
}
static int String_differ(const void *self_, const void *b_)
{
    const struct String *self = self_;
    const struct String *b = b_;

    if (self == b)
        return 0;
    if (!b || b->class != String)
        return 1;
    return strcmp(self->text, b->text);
}

static const struct Class String_ = {
    sizeof(struct String),
    String_ctor, String_dtor,
    String_clone, String_differ};

const void *String = &String_;