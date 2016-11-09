// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"

TileList::TileList()
{
    std::vector<Tile> tileList(10);
}

TileList::~TileList()
{
    tileList.remove();
}

void TileList::addTile(Tile tile)
{
    tileList.push_back(tile);
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for (i = 0; i < tileList.size(); i++) {
        tileList[i].draw();
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    // TODO: write this member
}

void TileList::raise(int x, int y)
{
    // TODO: write this member
}

void TileList::lower(int x, int y)
{
    // TODO: write this member
}

void TileList::remove(int x, int y)
{
    // TODO: write this member
}

void TileList::removeAll(int x, int y)
{
    // TODO: write this member
}
