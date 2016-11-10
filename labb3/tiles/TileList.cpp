/*
 * Tobias Fellegi, tobfe318
 * Thomas Annerfeldt,
 *
 * Implementation of the TileList class
 */

#include "TileList.h"

TileList::TileList()
{

}

TileList::~TileList()
{
    delete[] tileList;
}

void TileList::addTile(Tile tile)
{
    if (cur_size == cur_cap) {
        Tile* tempTileList = new Tile[cur_cap * 2];

        for (int i = 0; i < cur_size; i++) {
            tempTileList[i] = tileList[i];
        }
        delete[] tileList;
        tileList = tempTileList;
        cur_cap *= 2;
    }

    tileList[cur_size] = tile;
    cur_size++;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for (int i = 0; i < cur_size; i++) {
        tileList[i].draw(scene);
    }
}

int TileList::indexOfTopTile(const int x, const int y)
{
    for (int i = cur_size - 1; i >= 0; i--) {
        if (tileList[i].contains(x, y)) {
            return i;
        }
    }
    return -1;
}
/* Funkar...
void TileList::raise(const int x, const int y){
    bool found = false;
    Tile temp;
    Tile* tempArray = new Tile[cur_cap];
    for (int i = cur_size - 1; i >= 0; i--) {
        if(!found && tileList[i].contains(x, y)){
            temp = tileList[i];
            found = true;
        }
        else if(!found){
            tempArray[i - 1] = tileList[i];
        }
        else if(found){
            tempArray[i] = tileList[i];
        }
    }
    if(found){
        tempArray[cur_size - 1] = temp;
        delete[] tileList;
        tileList = tempArray;
    }
}
*/

// Funkar inte...
void TileList::raise(const int x, const int y)
{
    int topTileIndex = indexOfTopTile(x, y);

    if (!(topTileIndex == -1)) {
        Tile topTile = tileList[topTileIndex];
        Tile* tempTileList = tileList;

        for (int i = topTileIndex; i < cur_size; i++) {
            tempTileList[i-1] = tempTileList[i];
        }
        tempTileList[cur_size - 1] = topTile;
        delete[] tileList;
        tileList = tempTileList;
    }
}

void TileList::lower(const int x, const int y)
{
    int topTileIndex = indexOfTopTile(x, y);

    if (topTileIndex != -1) {
        Tile topTile = tileList[topTileIndex];

        for (int i = topTileIndex; i > 0; i--){
            tileList[i] = tileList[i-1];
        }
        tileList[0] = topTile;
    }
}

void TileList::remove(const int x, const int y)
{
    int topTileIndex = indexOfTopTile(x, y);

    if (topTileIndex != -1) {
        for (int i = topTileIndex; i < cur_size; i ++) {
            tileList[i] = tileList[i + 1];
        }
        cur_size--;
    }
}

void TileList::removeAll(const int x, const int y)
{
    while (indexOfTopTile(x, y) != -1) {
        remove(x, y);
    }
}
