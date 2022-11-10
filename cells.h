#ifndef SFML_CELLULAR_CELLS_H
#define SFML_CELLULAR_CELLS_H

#include <vector>

#include "variables.h"

extern int cell_types_count;

extern int worlds[2][world_w][world_h][4];
extern int world_type;

std::vector<int> count_neighbors(int x, int y, int r);

bool void_cell_update(int x, int y); //returns 1 if changed the cell

bool conway_cell_update(int x, int y);

bool diffusion_cell_update(int x, int y);

void update_cell(int x, int y);

void update_world();

#endif //SFML_CELLULAR_CELLS_H
