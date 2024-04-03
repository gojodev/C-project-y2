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

    unsigned int *candPlanets;
    unsigned int *candDists;
    unsigned int candIndex;
    unsigned int candConn;
} ShipState;

#define MAX_PLANETS 500 // for the sake for argument allocated space for 500 planets should be more than enough

unsigned int is_visited(unsigned int planet_id, ShipState *state)
{
    for (int i = 0; i < state->allPlanets; i++)
    {
        if (state->visited[i] == planet_id)
        {
            return 1;
            break;
        }
    }
    return 0;
}

void clearCands(ShipState *state)
{
    for (int i = 0; i < state->candConn; i++)
    {
        state->candDists[i] = 0;
        state->candPlanets[i] = 0;
    }
    state->candIndex = 0;
}

/**
 * ! algorithim
 * keeps jumping to the next planet if it is closer to the mixer
 * and will "look around" to find a planet that is closer if it runs into a deadend and if all else fails it will jump to a random planet
 * rinse and repeat
 * ? flaws: no backtracking, depends on luck
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

        state->candPlanets = malloc(sizeof(unsigned int) * num_connections);
        state->candDists = malloc(sizeof(unsigned int) * num_connections);
        state->candIndex = 0;
        state->candConn = num_connections;
    }
    else
    {
        state = (ShipState *)ship_state;
    }

    unsigned int next_planet = RAND_PLANET;

    state->visited[state->jumpNo] = crt_planet;
    crt_planet = crt_planet;

    for (int i = 0; i < num_connections; i++)
    {
        if (is_visited(connections[i], state) == 0 && abs(distance_from_mixer) < abs(state->prevDist))
        {
            printf("\nNEW PLANET");
            next_planet = connections[i];
        }
    }

    state->prevDist = distance_from_mixer;

    printf("\nFrom space_explorer.c");
    printf("\njumpNo : %u , ", state->jumpNo);
    printf("\ncrt_planet : %u , ", crt_planet);

    printf("\nprevDist : %u , ", state->prevDist);
    printf("\ndistance_from_mixer : %d , ", distance_from_mixer);
    printf("\nnum_connections : %d , ", num_connections);
    printf("\nNearBy planets: ");

    for (int i = 0; i < num_connections; i++)
    {
        printf("%d , ", connections[i]);
    }
    // printf("\nAll Visited planets: ");
    // for (int i = 0; i < state->jumpNo; i++)
    // {
    //     printf("%u, ", state->visited[i]);
    // }
    printf("\n------------\n");

    state->jumpNo++;

    return (ShipAction){next_planet, state};
}
