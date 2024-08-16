#ifndef TYPECLASS_R_H
#define TYPECLASS_R_H

#ifdef _WIN32

#ifdef TYPECLASS_EXPORTS
#define TYPECLASSAPI __declspec(dllexport)
#else
#define TYPECLASSAPI __declspec(dllimport)
#endif
#define TYPECLASSCALL __cdecl

#else

#define TYPECLASSAPI
#define TYPECLASSCALL

#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "BaseClass.r.h"
#include "BaseObject.r.h"

#define UBJECT_TYPECLASS_PRIORITY (UBJECT_BASECLASS_PRIORITY + 2)

/**
 * @struct TypeClass
 * @brief Represents a base class with class information.
 *
 * This structure contains information about a class, including its name and
 * destructor function.
 */
struct TypeClass {

#ifndef TYPECLASS_C
  char ___[sizeof(struct TYPECLASS_C_ {
#endif
    /** Inherited base class structure. */
    struct BaseClass _parent_struct_;
    /** Name of the class. */
    char *name;

    /** Pointer to the destructor function of the class. */
    void *(*dtor)(void *self);

    int (*puto)(void *self, FILE *f);

    void *(*rollb)(void *self, FILE *f);

#ifndef TYPECLASS_C
  })];
#endif
};

/** @brief Class descriptor
 * @example{
 * SomeTypeClass = init (TypeClass, TypeClass,
 *                       sizeof(struct SomeTypeClass),
 *                  ctor, SomeClass_ctor, 0);
 * SomeType = init (SomeTypeClass, SomeSuperType_to_inherit_from,
 *                   sizeof(struct SomeType),
 *                   ctor, SomeType_ctor,
 *                   dtor, SomeType_dtor,
 *                   className, "SomeType",
 *                      ...,
 *                   someFnSelector, correspondingOverloadFn,
 *                   0);
 * }
 */
extern TYPECLASSAPI const void *TypeClass;

/**
 * @brief Invoke the superclass destructor.
 *
 * This function invokes the superclass destructor.
 *
 * @param class_ Pointer to the class descriptor.
 * @param self Pointer to the object.
 * @return Pointer to the object after destruction.
 */
TYPECLASSAPI void *super_dtor(const void *class_, void *self);

TYPECLASSAPI int super_puto(const void *class_, void *self, FILE *f);
TYPECLASSAPI void *super_rollback(const void *class_, void *self, FILE *f);
#endif