/*
 * Tobias Fellegi, tobfe318
 * Thomas Annerfeldt, thoan578
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
    if (startNode == nullptr) {
        startNode = newNode(p);
        startNode -> next = startNode;
    }
    else {
        Node* curNode = startNode;
        Node* nearNode = startNode;
        double nearDist = curNode->point.distanceTo(p);

        while (curNode -> next != startNode) {
            if (p.distanceTo(curNodecurNode -> next -> point) < nearDist) {
                nearDist = p.distanceTo(curNodecurNode -> next -> point);
                nearNode = curNode -> next;
            }
        }
    }
}

void Tour::insertSmallest(Point p)
{

}
