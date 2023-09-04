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
#include "Circle.h"

struct Circle
{
    const struct Point _;
    int rad;
};

static void *Circle_ctor(void *self_, va_list *arg)
{
    struct Circle *self = super_ctor(Circle, self_, arg);
    self->rad = va_arg(*arg, int);
    return self;
}

static void Circle_draw(const void *self_)
{
    const struct Circle *self = self_;
    printf("circle at %d, %d\n", x(self), y(self));
}

const void *Circle = 0;

void initCircle()
{
    if (!Circle)
    {
        initPoint();
        Circle = new (PointClass, "Circle", Point,
                      sizeof(struct Circle),
                      ctor, Circle_ctor,
                      draw, Circle_draw,
                      0);
    }
}