/**
 * @file BaseClass.r.h
 *
 * @brief Header file for the BaseClass struct.
 *
 * This header file defines the BaseClass struct, which is a base class for
 * other classes in the program. It contains common members and methods that can
 * be inherited by derived classes.
 */
#ifndef BASECLASS_R_H
#define BASECLASS_R_H

#include <stdarg.h>
#include <stddef.h>

#include "BaseObject.r.h"

struct BaseClass {

#ifndef BASECLASS_C
  char ___[sizeof(struct BASECLASS_C_ {
#endif
    /**
     * @brief **Pointer to the parent struct.**
     *
     * This pointer points to the parent struct of the BaseClass struct.
     * It is used for inheritance and polymorphism.
     */
    struct BaseObject _parent_struct_;
    /**
     * @brief Pointer to the superclass.
     *
     * This pointer points to the superclass of the BaseClass struct.
     * It is used for inheritance and polymorphism.
     */
    const struct BaseClass *super;
    /**
     * @brief **Size of the BaseClass struct.**
     *
     * This member stores the size of the BaseClass struct in bytes.
     * It is used for memory management and object allocation.
     */
    size_t size;

    /**
     * @brief **Count of objects of this class.**
     *
     * This member stores the count of objects of this class that have been
     * created. It is used for tracking the number of objects of this class that
     * are currently in use.
     */
    int instance_count;

    /**
     * @brief **Constructor function for the BaseClass struct.**
     *
     * This function is called to construct a new object of the BaseClass
     * struct. It takes a pointer to the object as its first argument and a
     * variable argument list as its second argument. The variable argument list
     * contains the arguments that are passed to the constructor.
     *
     * @param self Pointer to the object being constructed.
     * @param arg Variable argument list containing the arguments passed to the
     * constructor.
     *
     * @return Pointer to the newly constructed object.
     */
    void *(*ctor)(void *self, va_list *arg);
#ifndef BASECLASS_C
  })];
#endif
};

extern const void *BaseClass;

#endif