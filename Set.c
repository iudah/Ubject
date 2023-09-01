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

/** @brief Set class*/
struct Set
{
    /** @brief Keeps track of number of element in a Set.*/
    unsigned int count;
};
struct Ubject
{
    /** @brief Keeps track of number of number of time Ubject is added to a Set.*/
    unsigned int count;
    /** @brief Set Ubject is added to.*/
    struct Set *set;
};

void *new(const void *descriptor, ...)
{
    const size_t size = *(const size_t *)descriptor;
    void *p = calloc(1, size);

    assert(p);
    return p;
}

void delete(void *item_)
{
    free(item_);
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
int differ(const void *a, const void *b)
{
    return a != b;
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