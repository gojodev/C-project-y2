#include "space_explorer.h"
#include <stdlib.h>

typedef struct
{
    unsigned int *visited;
    int num_visited;
    int capacity;
} ShipState;

ShipState *init_ship_state()
{
    ShipState *state = malloc(sizeof(ShipState));
    state->capacity = 10; // Initial capacity
    state->visited = malloc(sizeof(unsigned int) * state->capacity);
    state->num_visited = 0;
    return state;
}

int is_visited(ShipState *state, unsigned int planet_id)
{
    for (int i = 0; i < state->num_visited; ++i)
    {
        if (state->visited[i] == planet_id)
            return 1;
    }
    return 0;
}

void add_visited(ShipState *state, unsigned int planet_id)
{
    if (state->num_visited == state->capacity)
    {
        state->capacity *= 2;
        state->visited = realloc(state->visited, sizeof(unsigned int) * state->capacity);
    }
    state->visited[state->num_visited++] = planet_id;
}

ShipAction space_hop(unsigned int crt_planet, unsigned int *connections, int num_connections, double distance_from_mixer, void *ship_state)
{
    ShipState *state;
    if (ship_state == NULL)
    {
        state = init_ship_state();
    }
    else
    {
        state = (ShipState *)ship_state;
    }

    add_visited(state, crt_planet);

    unsigned int next_planet = crt_planet; // Stay on current planet if no unvisited connection is closer
    double min_distance = distance_from_mixer;

    // The game should ideally recognize the treasure planet as found when distance_from_mixer is zero.
    // Ensure the game's logic checks for this condition correctly.
    if (distance_from_mixer == 0)
    {
        // Logic to handle finding the treasure planet
        // This could involve setting a specific next_planet value or triggering a game win condition
        ShipAction action;
        action.next_planet = crt_planet;
        action.ship_state = state;
        return action;
    }

    for (int i = 0; i < num_connections; ++i)
    {
        if (!is_visited(state, connections[i]))
        {
            // Since we're hypothesizing about the distances from these connections to the mixer,
            // and we don't have direct access to these distances, we use the given logic to check:
            // Assume a function or logic here to estimate distance; since we can't do that directly,
            // the actual implementation needs to be based on the game's provided mechanisms.

            // If a connection has a distance of 0 (hypothetically, if we could check it),
            // that would indicate the treasure planet is found. This is a placeholder for such logic.
            // Without direct access to each planet's distance to the mixer, we're limited in implementation.
            next_planet = connections[i]; // Placeholder, assume we set next_planet based on some condition
        }
    }

    // Further logic here as needed...

    ShipAction action;
    action.next_planet = next_planet;
    action.ship_state = state;
    return action;
}
