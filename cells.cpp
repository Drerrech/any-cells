#include <iostream>

#include "cells.h"

int cell_types_count = 3;

int worlds[2][world_w][world_h][4];// [world_type] [x] [y] [id, (RGB 3 values)]
int world_type = 0;


std::vector<int> count_neighbors(int x, int y, int r){
    std::vector<int> neighbors; for (int i = 0; i < cell_types_count; ++i) neighbors.push_back(0);

    for (int _x = x-r/2; _x < x+r/2 + 1; ++_x) {
        for (int _y = y-r/2; _y < y+r/2 + 1; ++_y) {

            //std::cout << "_x & _y:" << _x << " " << _y << std::endl;

            if (!(_x == x && _y == y)) {
                int neg_cell_type = worlds[world_type][(_x + world_w) % world_w][(_y + world_h) % world_h][0];

                neighbors[neg_cell_type]++;
            }
        }
    }

    return neighbors;
}

//CELLS:
//VOID
bool void_cell_update(int x, int y){ //returns true if changed the cell
    int *our_cell = worlds[world_type][x][y];

    //void_cell
    if (our_cell[0] == 0) return false; // cell will not do anything while lives

    //conway_cell
    if (our_cell[0] == 1) {
        //count neighbors
        std::vector<int> neighbors = count_neighbors(x, y, 3);
        //decide if it can grow here
        int conway_neighbors = neighbors[1];

//        std::cout << "void: " << neighbors[0] << " " << neighbors[1] << std::endl;

        if (conway_neighbors < 2 || conway_neighbors > 3) {
            //set world2
            worlds[!world_type][x][y][0] = 0;
            for (int i = 1; i < 4; ++i) worlds[!world_type][x][y][i] = 0;

            return true;
        }
    }

    return false; //technically this should not be possible. Or you forgot to add conditions for some cells
}

//CONWAY
bool conway_cell_update(int x, int y){ //returns true if changed the cell
    int *our_cell = worlds[world_type][x][y];

    //void_cell
    if (our_cell[0] == 0) {
        //count neighbors
        std::vector<int> neighbors = count_neighbors(x, y, 3);
        //decide if it can grow here
        int conway_neighbors = neighbors[1];

//        std::cout << "conway: " << neighbors[0] << " " << neighbors[1] << std::endl;
//        std::cout << "c_neg: " << conway_neighbors << std::endl;

        if (conway_neighbors == 3) {
            //set world2
            worlds[!world_type][x][y][0] = 1;
            for (int i = 1; i < 4; ++i) worlds[!world_type][x][y][i] = 255;

            return true;
        }
    }

    //conway_cell
    if (our_cell[0] == 1) return false; // cell will not do anything while lives

    return false; //technically this should not be possible. Or you forgot to add conditions for some cells
}


//DIFFUSION
bool diffusion_cell_update(int x, int y){ //returns true if changed the cell
    int *our_cell = worlds[world_type][x][y];

    // cell will not do something while lives
    if (our_cell[0] == 2) {
        //count color
        int col[3]; for (int &i : col) i = 0;

        for (int _x = x+1; _x < x+1 + 1; ++_x) {
            for (int _y = y-1; _y < y+1 + 1; ++_y) {
                if (!(_x == x && _y == y)) {
                    int *neg_cell = worlds[world_type][(_x + world_w) % world_w][(_y + world_h) % world_h];

                    col[0] += neg_cell[1];
                    col[1] += neg_cell[2];
                    col[2] += neg_cell[3];
                }
            }
        }

        // divide
        col[0] /= 3;
        col[1] /= 3;
        col[2] /= 3;

        //set world2
        worlds[!world_type][x][y][0] = 2;
        for (int i = 1; i < 4; ++i) worlds[!world_type][x][y][i] = col[i-1];

        return true;

    }

    return false; //technically this should not be possible. Or you forgot to add conditions for some cells
}


void update_cell(int x, int y){ //this will only affect world2
    void_cell_update(x, y);
    conway_cell_update(x, y);
    diffusion_cell_update(x, y);
}

void update_world(){
    //std::cout << worlds[0][0][0][0] << std::endl;

    for (int x = 0; x < world_w; ++x) {
        for (int y = 0; y < world_h; ++y) {
            update_cell(x, y);
        }
    }

    //flipping worlds may be a good idea, but let's go for the shitty solution
    for (int x = 0; x < world_w; ++x) {
        for (int y = 0; y < world_h; ++y) {
            for (int i = 0; i < 4; ++i) worlds[0][x][y][i] = worlds[1][x][y][i];
        }
    }
}