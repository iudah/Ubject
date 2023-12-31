/**
 * @file BaseObject.r.h
 * @brief Header file for the BaseObject struct.
 */
#ifndef BASEOBJECT_R_H
#define BASEOBJECT_R_H

/**
 * @def BASE_CTOR_PRIORITY
 * @brief Constant used to set the priority of library constructor for
 * BaseObject.
 */
#define BASE_CTOR_PRIORITY 6987

/**
 * @struct BaseObject
 * @brief Base class for objects in the codebase.
 */
struct BaseObject {

#ifndef BASEOBJECT_C
  /**
   * Placeholder field used to calculate the size of the BASEOBJECT_C_ struct.
   */
  char ___[sizeof(struct BASEOBJECT_C_ {
#endif
    /**
     * Pointer to the BaseClass struct associated with this object.
     */
    const struct BaseClass *class;

    /**
     * Integer used to uniquely identify instances of objects.
     */
    int instance_index;
#ifndef BASEOBJECT_C
  })];
#endif
};

/**
 * @var BaseObject
 * @brief External variable representing the BaseObject struct.
 */
extern const void *BaseObject;

#endif