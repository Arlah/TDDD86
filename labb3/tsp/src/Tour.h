/*
 * Tobias Fellegi, tobfe318
 * Thomas Annerfeldt,
 *
 * A class aimed at solving the famous "Traveling Salesman Problem" (TSP).
 * This variant stores "cities" as nodes using a linked list.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    /*
     * Creates a new empty tour where the first point is a nullpointer.
     */
    Tour();

    /*
     * Clears memory used by the linked list and
     * returns the first pointer to a nullpointer.
     */
    ~Tour();

    /*
     * Outputs the nodes in the tour to text.
     */
    void show();

    /*
     * Draws the nodes in the linked list on a graphic interface.
     */
    void draw(QGraphicsScene* scene);

    /*
     * Returns the number of nodes in the tour.
     */
    int size();

    /*
     * Returns the length of the tour.
     */
    double distance();

    /*
     * An algorithm that reads the next node "x" and adds it to the tour
     * directly behind the node which "x" is closest to.
     */
    void insertNearest(Point p);

    /*
     * An algorithm that reads the next node "x" and adds it to the tour
     * behind the node where "x" affects the tour length as little as possible.
     */
    void insertSmallest(Point p);

private:

    Node* startNode = nullptr;             // Pointer to the first node in the tour

};

#endif // TOUR_H
