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
    /** @brief Implement linked list of atom*/
    struct String *next;
    unsigned count;
};

static struct String *ring = 0;

static void *String_ctor(void *self_, va_list *arg)
{
    struct String *self = self_;
    const char *text = va_arg(*arg, char *);
    size_t len = strlen(text) + 1;

    if (ring)
    {
        struct String *p = ring;
        do
        {
            if (!strcmp(p->text, text))
            {
                ++p->count;
                free(self);
                return p;
            }
        } while ((p = p->next) != ring);
    }
    else
        ring = self;
    self->next = ring->next;
    ring->next = self;
    self->count = 1;

    self->text = malloc(len);
    assert(self->text);
    strncpy(self->text, text, len);

    return self;
}
static void *String_dtor(void *self_)
{
    struct String *self = self_;

    if (--self->count > 0)
        return 0;

    assert(ring);
    if (ring == self)
        ring = self->next;
    if (ring == self)
        ring = 0;
    else
    {

        struct String *p = ring;
        while (p->next != self)
        {
            p = p->next;
            assert(p != ring);
        }
        p->next = self->next;
    }

    free(self->text);
    self->text = 0;
    return self;
}
static void *String_clone(const void *self_)
{
    struct String *self = (void *)self_;
    self->count++;
    return self;
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