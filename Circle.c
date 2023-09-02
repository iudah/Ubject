/**
 * @file Circle.c
 * @brief Implementation of Circle ADT.
 *
 * This implements Circle which inherits from Point
 * @author Jude (iudah)
 */
#include <stdarg.h>
#include <stdio.h>

#include "Point.h"
#include "Point.r.h"
#include "new.h"
#include "new.r.h"

struct Circle
{
    const struct Point _;
    int rad;
};

static void *Circle_ctor(void *self_, va_list *arg)
{
    struct Circle *self = ((const struct Class *)Point)->ctor(self_, arg);
    self->rad = va_arg(*arg, int);
    return self;
}

static void Circle_draw(const void *self_)
{
    const struct Circle *self = self_;
    printf("circle at %d, %d\n", x(self), y(self));
}

static const struct Class Circle_ = {
    sizeof(struct Circle), Circle_ctor, 0, Circle_draw};

const void *Circle = &Circle_;