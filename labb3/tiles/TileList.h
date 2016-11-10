
#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    TileList();
    ~TileList();

    /*
     * Adds a tile to the end of the tileList
     */
    void addTile(Tile tile);

    /*
     * Calls the draw function for each element in tileList
     */
    void drawAll(QGraphicsScene* scene);

    /*
     * Returns the index of the top tile at a position (x,y)
     */
    int indexOfTopTile(int x, int y);

    /*
     * Moves the top tile at position (x,y) to the front of the list
     */
    void lower(int x, int y);

    /*
     * Moves the top tile at position (x,y) to the end of the list
     */
    void raise(int x, int y);

    /*
     * Removes the top tile at position (x,y)
     */
    void remove(int x, int y);

    /*
     * Removes all tiles
     */
    void removeAll(int x, int y);

private:
    int cur_cap = 10;                       // Max capacity of the array
    int cur_size = 0;                       // Currently used space in the array
    Tile* tileList = new Tile[cur_cap];     // Constructs the base tileList with defaulted values

};

#endif // TILELIST_H
