/**
 * @file new.r.h
 * @brief Private representation file for managing class description
 * @author Jude (iudah)
 */
#ifndef NEW_R_H
#define NEW_R_H

/** @brief Type description*/
struct Class
{
    /** @brief size of type class*/
    size_t size;
    /** @brief Constructor of type class*/
    void *(*ctor)(void *self, va_list *arg);
    /** @brief Destructor of type class*/
    void *(*dtor)(void *self);
    /** @brief Display an instance */
    void (*draw)(const void *self);
};

#endif