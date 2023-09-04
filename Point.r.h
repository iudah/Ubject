/**
 * @file Point.r.h
 * @brief Representation file for Point
 * @author Jude (iudah)
 */
#ifndef POINT_R_H
#define POINT_R_H

#include "Ubject.r.h"

struct Point
{
    const struct Ubject _;
    int x, y;
};

#define x(self) (((const struct Point *)(self))->x)
#define y(self) (((const struct Point *)(self))->y)

void super_draw(const void *class, const void *self);

struct PointClass
{
    const struct Class _;
    void (*draw)(const void *self);
};
#endif