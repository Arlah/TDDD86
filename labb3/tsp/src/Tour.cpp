/*
 * Tobias Fellegi, tobfe318
 * Thomas Annerfeldt,
 *
 * Implementation of the Tour class
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{

}

Tour::~Tour()
{
    delete[] tour;
}

void Tour::show()
{
    Node* curNode = startNode;

    do {
        cout << curNode -> point.toString() << endl;
        curNode = curNode -> next;
    } while (curNode != startNode);
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* curNode = startNode;

    do {
        curNode -> point.draw(scene);
        curNode -> point.drawTo(curNode -> next -> point, scene);
        curNode = curNode -> next;
    } while (curNode != startNode);
}

int Tour::size()
{
    Node* curNode = startNode;
    int size = 0;

    do {
        size++;
        curNode = curNode -> next;
    } while (curNode != startNode);

    return size;
}

double Tour::distance()
{
    Node* curNode = startNode;
    double distance = 0;

    do {
        Point nextNode = curNode -> next -> point;
        distance += curNode -> point.distanceTo(nextNode);
        curNode = curNode -> next;
    } while (curNode != startNode);

    return distance;
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
