#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct ship_state
{
    unsigned int *visited;
    unsigned int jumpNo;
    unsigned int allPlanets;
    double prevDist;
    double *allDists;
} ShipState;

#define MAX_PLANETS 500 // for the sake for argument allocated space for 500 planets should be more than enough

unsigned int is_visited(unsigned int planet_id, ShipState *state)
{
    for (int i = 0; i < state->jumpNo; i++)
    {
        if (state->visited[i] == planet_id)
        {
            return 1;
            break;
        }
    }
    return 0;
}

/**
 * ! algorithim
 * keeps jumping to the next planet if it is closer to the mixer and if there's no planet that's currently closer
 * then the ship goes back to its previously vistsed planets until there's one that is closer
 * if all else fails then a random jump will be made
 */
ShipAction space_hop(unsigned int crt_planet, unsigned int *connections, int num_connections, double distance_from_mixer, void *ship_state)
{
    ShipState *state;
    if (ship_state == NULL)
    {
        state = malloc(sizeof(ShipState)); // will only be storing one ShipState at a time everytime this method is run
        state->visited = malloc(sizeof(unsigned int) * MAX_PLANETS);
        state->jumpNo = 0;
        state->allPlanets = MAX_PLANETS;
        state->prevDist = distance_from_mixer;
        state->allDists = malloc(sizeof(unsigned int) * MAX_PLANETS);
    }
    else
    {
        state = ship_state;
    }

    unsigned int next_planet = RAND_PLANET;

    state->visited[state->jumpNo] = crt_planet;
    state->allDists[state->jumpNo] = distance_from_mixer;

    for (int i = 0; i < num_connections; i++)
    {
        if (is_visited(connections[i], state) == 0 && abs(distance_from_mixer) < abs(state->prevDist))
        {
            next_planet = connections[i];
            break;
        }
    }

    // will look back to previous planets for a new route if there's no current shorter path
    // and will do a random jump as a last resort
    if (next_planet == RAND_PLANET)
    {
        double oldDist;
        int PlanetIndex;
        for (int i = 1; i < state->jumpNo; i++)
        {
            PlanetIndex = state->jumpNo - i;
            oldDist = state->allDists[PlanetIndex];
            if (abs(oldDist) < abs(distance_from_mixer))
            {
                next_planet = state->visited[PlanetIndex];
                break;
            }
        }
    }

    state->prevDist = distance_from_mixer;

    state->jumpNo++;

    return (ShipAction){next_planet, state};
}