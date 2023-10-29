/**
 * @file Ubject.r.h
 *  @brief Ubject represention
 */
#ifndef UBJECT_R_H
#define UBJECT_R_H

#include <stdarg.h>
#include <stddef.h>

#ifdef _WIN32

#ifdef UBJECT_EXPORTS
#define UBJECTAPI __declspec(dllexport)
#else
#define UBJECTAPI __declspec(dllimport)
#endif
#define UBJECTCALL __cdecl

#else

#define UBJECTAPI
#define UBJECTCALL

#endif

/**
 * @struct Ubject
 * @brief Represents a base object with class information.
 *
 * This structure contains a pointer to the class descriptor of an object.
 */
struct Ubject {
#ifndef UBJECT_C
  char ___[sizeof(struct _ubj_ {
#endif
    /** Pointer to the class descriptor of the object. */
    const struct BaseClass *class_;
    /** Number of time object is referenced*/
    int reference;
#ifndef UBJECT_C
  })];
#endif
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
    /** Pointer to the class descriptor. */
    const struct BaseClass *desc;
    /** Pointer to the super class. */
    const struct BaseClass *baseclass;
    size_t _size_t;
    void *(*voidf_)();
  } _;

  /** Name of the class. */
  char *name;

  /** Pointer to the destructor function of the class. */
  void *(*dtor)(void *self);
};

/** @brief Class descriptor
 * @example{
 * SomeTypeClass = new (TypeClass, TypeClass,
 *                       sizeof(struct SomeTypeClass),
 *                  ctor, SomeClass_ctor, 0);
 * SomeType = new (SomeTypeClass, SomeSuperType_to_inherit_from,
 *                   sizeof(struct SomeType),
 *                   ctor, SomeType_ctor,
 *                   dtor, SomeType_dtor,
 *                   className, "SomeType",
 *                      ...,
 *                   someFnSelector, correspondingOverloadFn,
 *                   0);
 * }
 */
extern UBJECTAPI const void *TypeClass;

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
UBJECTAPI void *super_ctor(const void *class_, void *self, va_list *arg_);

/**
 * @brief Invoke the superclass destructor.
 *
 * This function invokes the superclass destructor.
 *
 * @param class_ Pointer to the class descriptor.
 * @param self Pointer to the object.
 * @return Pointer to the object after destruction.
 */
UBJECTAPI void *super_dtor(const void *class_, void *self);

#endif