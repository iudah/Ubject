/**
 * @file Ubject.r.h
 *  @brief Ubject represention
 */
#ifndef UBJECT_R_H
#define UBJECT_R_H

/**
 * @struct Ubject
 * @brief Represents a base object with class information.
 *
 * This structure contains a pointer to the class descriptor of an object.
 */
struct Ubject {
    /** Pointer to the class descriptor of the object. */
    const struct BaseClass *class;
};

/**
 * @struct TypeClass
 * @brief Represents a base class with class information.
 *
 * This structure contains information about a class, including its name and
 * destructor function.
 */
struct TypeClass {
    /** Inherited base class structure. */
    struct {
        /** Pointer to the superclass descriptor. */
        const struct BaseClass *baseclass;
    } _;

    /** Name of the class. */
    char *name;

    /** Pointer to the destructor function of the class. */
    void *(*dtor)(void *self);
};

/** @brief Class descriptor*/
extern const void *TypeClass;

/**
 * @brief Invoke the superclass constructor.
 *
 * This function invokes the superclass constructor.
 *
 * @param class_ Pointer to the class descriptor.
 * @param self Pointer to the object.
 * @param arg_ Variable argument list.
 * @return Pointer to the initialized object.
 */
void *super_ctor(const void *class_, void *self, va_list *arg_);

/**
 * @brief Invoke the superclass destructor.
 *
 * This function invokes the superclass destructor.
 *
 * @param class_ Pointer to the class descriptor.
 * @param self Pointer to the object.
 * @return Pointer to the object after destruction.
 */
void *super_dtor(const void *class_, void *self);

#endif