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
#include <assert.h>

#if !defined MANY || MANY < 1
#define MANY 10
#endif

static int heap[MANY];

void *new(const void *descriptor, ...)
{
    int *p;
    for (p = heap + 1; p < heap + MANY; ++p)
        if (!*p)
            break;
    assert(p < heap + MANY);
    *p = MANY;
    return p;
}

void delete(void *item_)
{
    int *item = item_;
    if (item)
    {
        assert(item > heap && item < heap + MANY);
        *item = 0;
    }
}

void *add(void *set_, const void *element_)
{
    int *set = set_;
    const int *element = element_;

    assert(set > heap && set < heap + MANY);
    assert(*set == MANY);
    assert(element > heap && element < heap + MANY);

    if (*element == MANY)
        *(int *)element = set - heap;
    else
        // each element can only be one set in this implementation
        assert(*element == set - heap);
    return (void *)element;
}

void *find(const void *set_, const void *element_)
{
    const int *set = set_;
    const int *element = element_;

    assert(set > heap && set < heap + MANY);
    assert(*set == MANY);
    assert(element > heap && element < heap + MANY);

    return *element == set - heap ? (void *)element : 0;
}

int contains(const void *set_, const void *element_)
{
    return find(set_, element_) != 0;
}

void *drop(void *set_, const void *element_)
{
    int *element = find(set_, element_);
    if (element)
        *element = MANY;
    return element;
}
int differ(const void *a, const void *b)
{
    return a != b;
}

const void *Set;
const void *Ubject;