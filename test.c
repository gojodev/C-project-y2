#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define RAND_PLANET 111

#define DIST_THRESHOLD 1
#define AREA_SIZE 10
#define POINT_DENSITY 3

#ifndef srand48
#define srand48(X) (srand(X))
#endif
#ifndef drand48
#define drand48() (rand() * ((double)1 / RAND_MAX))
#endif

unsigned int permuteQPR(unsigned int x)
{
    static const unsigned int prime = 4294967291u;
    if (x >= prime)
        return x; // The 5 integers out of range are mapped to themselves.
    unsigned int residue = ((unsigned long long)x * x) % prime;
    return (x <= prime / 2) ? residue : prime - residue;
}

unsigned int gen_planet_id(unsigned int id, unsigned int intOffset)
{
    unsigned int planet_id = RAND_PLANET;
    while (planet_id == RAND_PLANET)
    {
        planet_id = permuteQPR((permuteQPR(id) + intOffset) ^ 0x5bf03635);
    }
    return planet_id;
}

// trying to figure out what a valid planet id is
void main()
{
    printf("%d", gen_planet_id(1, 1));
}