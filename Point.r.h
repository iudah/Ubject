/**
 * @file Point.r.h
 * @brief Representation file for Point
 * @author Jude (iudah)
 */
#ifndef POINT_R_H
#define POINT_R_H

struct Point
{
    const struct Class *class;
    int x, y;
};

#define x(self) (((const struct Point *)(self))->x)
#define y(self) (((const struct Point *)(self))->y)

#endif