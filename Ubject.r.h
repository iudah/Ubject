/**
 * @file Ubject.r.h
 *  @brief Ubject represention
 */
#ifndef UBJECT_R_H
#define UBJECT_R_H

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

#define UBJECT_PRIORITY (6993)

/**
 * @struct Ubject
 * @brief Represents a base object with class information.
 *
 * This structure contains a pointer to the class descriptor of an object.
 */
struct Ubject {
#ifndef UBJECT_C
  char ___[sizeof(struct UBJECT_C_ {
#endif
    /** Pointer to the class descriptor of the object. */
    const struct BaseClass *class_;
    /** Number of time object is referenced*/
    int reference;
#ifndef UBJECT_C
  })];
#endif
};

#endif