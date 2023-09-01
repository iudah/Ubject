/**
 * @file Set.c
 * @brief Implementation for the ADTs (Set, and Ubject),
 * and memory management.
 *
 * This single file coming to represent all 3 concept is
 * due to the current simplicity of these concepts and
 * their requirement
 * @author Jude (iudah)
 */
#include <stdlib.h>
#include <assert.h>

/** @brief Type description*/
struct Class
{
    /** @brief size of type class*/
    size_t size;
    /** @brief Constructor of type class*/
    void *(*ctor)(void *self, ...);
    /** @brief Destructor of type class*/
    void *(*dtor)(void *self);
    /** @brief */
    void *(*clone)(const void *self);
    /**
     * @brief Compares instances of type.
     * @param a an instance
     * @param b an instance
     * @return 1 if a and b are different, else 0
     */
    int (*differ)(const void *a, const void *b);
};
struct String
{
    /** @brief String descriptor*/
    const void *class;
    char *text;
};
/** @brief Set class*/
struct Set
{
    /** Set class descriptor*/
    const void *class;
    /** @brief Keeps track of number of element in a Set.*/
    unsigned int count;
};
struct Ubject
{
    /** Set class descriptor*/
    const void *class;
    /** @brief Keeps track of number of number of time Ubject is added to a Set.*/
    unsigned int count;
    /** @brief Set Ubject is added to.*/
    struct Set *set;
};

void *new(const void *descriptor, ...)
{
    const struct Class *class = descriptor;
    void *p = calloc(1, class->size);

    assert(p);
    *(const struct Class **)p = class;

    if (class->ctor)
    {
        va_list arg;
    }
    return p;
}

void delete(void *self)
{
    const struct Class **class = self;

    if (self && *class && (*class)->dtor)
        self = (*class)->dtor(self);
    free(self);
}

void *add(void *set_, const void *element_)
{
    struct Set *set = set_;
    struct Ubject *element = (void *)element_;

    assert(set);
    assert(element);

    if (!element->set)
        element->set = set;
    else
        assert(element->set == set); // one set per object
    element->set->count++;
    element->count++;

    return (void *)element;
}

void *find(const void *set_, const void *element_)
{
    const struct Ubject *element = element_;

    assert(set_);
    assert(element);

    return element->set == set_ ? (void *)element : 0;
}

int contains(const void *set_, const void *element_)
{
    return find(set_, element_) != 0;
}

void *drop(void *set_, const void *element_)
{
    struct Set *set = set_;
    struct Ubject *element = find(set_, element_);
    if (element)
    {
        element->set->count--;
        element->count--;
    }
    return element;
}
int differ(const void *self, const void *b)
{
    struct Class *const *class = self;
    assert(self && *class && (*class)->differ);
    return (*class)->differ(self, b);
}
/** @brief Get size of created instance
 * @param self pointer to item originally created by @ref new
 * @return size of self
 */
size_t sizeOf(const void *self)
{
    const struct Class *const *class = self;

    assert(self && class);
    return (*class)->size;
}
unsigned int count(const void *set_)
{
    const struct Set *set = set_;
    assert(set);
    return set->count;
}
static const size_t Set_ = sizeof(struct Set);
static const size_t Ubject_ = sizeof(struct Ubject);

const void *Set = &Set_;
const void *Ubject = &Ubject_;