#ifndef BASEOBJECT_R_H
#define BASEOBJECT_R_H

#define BASE_CTOR_PRIORITY 6987

struct BaseObject {

#ifndef BASEOBJECT_C
  char ___[sizeof(struct BASEOBJECT_C_ {
#endif
    const struct BaseClass *class;
#ifndef BASEOBJECT_C
  })];
#endif
};

extern const void *BaseObject;

#endif