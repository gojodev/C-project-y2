#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

typedef struct ship_state
{
    unsigned int *visited;
    unsigned int jumpNo;
    unsigned int allPlanets;
    double prevDist;
    double *allDists;
    unsigned int isMixerZero;
    unsigned int *candPlanets;
    unsigned int candIndex;
    unsigned int candAmt;
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
 * first check if the id of the treasure planet is 0 (you can get there is one hop) otherwise:
 * keeps jumping to the next planet if it is closer to the mixer and if there's no planet that's currently closer
 * then the ship goes back to its previously visited planets until there's one that is closer
 * if the mixer is a distance of 0 away then look through all of the current connections for the mixer
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
        state->allDists = malloc(sizeof(double) * MAX_PLANETS);
        state->isMixerZero = 0;
        state->candPlanets = malloc(sizeof(unsigned int) * 50); // 50 candidate planets
        state->candAmt = 0;
    }
    else
    {
        state = ship_state;
    }

    unsigned int next_planet = RAND_PLANET;

    state->visited[state->jumpNo] = crt_planet;
    state->allDists[state->jumpNo] = abs(distance_from_mixer);

    if (state->isMixerZero == 0)
    {
        state->isMixerZero = 1;
        return (ShipAction){0, state};
    }

    if (distance_from_mixer == 0)
    {
        state->candIndex = -1;
        // printf("\nLOOKING AROUND:");
        state->candAmt = num_connections;
        for (int i = 0; i < num_connections; i++)
        {
            state->candPlanets[i] = connections[i];
            // printf("\nlooking at: %d , index: %d", connections[i], i);
            // sleep(1);
        }

        if (state->candIndex < state->candAmt)
        {
            state->candIndex++;
            // create your own function to do this if you have to
            return (ShipAction){state->candPlanets[state->candIndex], state};
        }
    }

    for (int i = 0; i < num_connections; i++)
    {
        if (is_visited(connections[i], state) == 0 && abs(distance_from_mixer) <= abs(state->prevDist))
        {
            next_planet = connections[i];
        }
    }

    // will look back to previous planets for a new route if there's no current shorter path
    // and will do a random jump as a last resort
    if (next_planet == RAND_PLANET)
    {
        double oldDist;
        int PlanetIndex;
        for (int i = 1; i < 20; i++)
        {
            PlanetIndex = state->jumpNo - i;
            oldDist = state->allDists[PlanetIndex];

            if (PlanetIndex < 0)
            {
                break;
            }

            if (abs(oldDist) < abs(distance_from_mixer))
            {
                next_planet = state->visited[PlanetIndex];
                // printf("\nBack Tracking to: %d , index: %d", next_planet, i);
                // sleep(1);
                break;
            }
        }
    }

    state->prevDist = distance_from_mixer;

    state->jumpNo++;

    // printf("\nFrom space_explorer.c");
    // printf("\njumpNo : %u , ", state->jumpNo);
    // printf("\ncrt_planet : %u , ", crt_planet);

    // printf("\nprevDist : %u , ", state->prevDist);
    // printf("\ndistance_from_mixer : %d , ", distance_from_mixer);
    // printf("\nnum_connections : %d , ", num_connections);
    // printf("\nNearBy planets: ");
    // for (int i = 0; i < num_connections; i++)
    // {
    //     printf("%d , ", connections[i]);
    // }
    // printf("\nAll Visited planets: ");
    // for (int i = 0; i < state->jumpNo; i++)
    // {
    //     printf("%u, ", state->visited[i]);
    // }
    // printf("\n------------\n");

    return (ShipAction){next_planet, state};
}

/**
 * gcc space_explorer.c space_solution.c -lm -ospace_explorer
 * .\space_explorer.exe
 */