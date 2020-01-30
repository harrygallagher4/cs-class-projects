#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** 
 *
 * runs in constant time O(n) (n edges)
 * creates an array of linked lists containing vertices that the node
 * (represented by the index in the array) is adjacent to. 
 * then creates a new list at each index by iterating over the old lists
 * in decreasing order and shifting connected vertices onto the head of
 * the list. 
 *
 * i.e.
 * if we have 4-1 3-1 2-1, shift 4 onto 1's list, then 3, then 2 so the
 * final result is [1]: 2->3->4
 *
 **/

typedef struct vertex {
    int id;
} Vertex;

typedef struct edge {
    struct vertex *from, *to;
} Edge;

typedef struct listNode {
    struct vertex *item;
    struct listNode *next;
} ListNode;

// whoops... didn't implement this.
int readEdgesFromFile(char file[], Edge *edges[]) {
    /*
    FILE *fp;
    fp = fopen(file, "r");
    */
    return 1;
}

Vertex *newVertex(int id) {
    Vertex *v = malloc(sizeof(Vertex));
    v->id = id;

    return v;
}

Edge *newEdge(Vertex *from, Vertex *to) {
    Edge *e = malloc(sizeof(Edge));
    e->from = from;
    e->to = to;

    return e;
}

ListNode *newNode(Vertex *item, ListNode *next) {
    ListNode *n = malloc(sizeof(ListNode));
    n->item = item;
    n->next = next;

    return n;
}


void convertToAdjacencyList(Edge *edges, int edgeCount,
                            Vertex *vertices, int vertexCount,
                            ListNode **adjacencyList) {
    int i;
    for(i = 0; i < vertexCount; i++) {
        Vertex v = vertices[i];
        adjacencyList[i] = NULL;
    }

    for(i = 0; i < edgeCount; i++) {
        Edge e = edges[i];

        // create vertices to store in list based on each end of our edge
        Vertex from = *(e.from);
        Vertex to = *(e.to);

        // store current node at [from] and [to] in array
        ListNode *fromHead = adjacencyList[from.id - 1];
        ListNode *toHead = adjacencyList[to.id - 1];
        // create new nodes pointing to those old list heads
        ListNode *fromNewHead = newNode(&to, fromHead);
        ListNode *toNewHead = newNode(&from, toHead);

        // replace old list head with new node
        adjacencyList[from.id - 1] = fromNewHead;
        adjacencyList[to.id - 1] = toNewHead;
    }
}

int main(void) {
    Vertex *one = newVertex(1);
    Vertex *two = newVertex(2);
    Vertex *three = newVertex(3);
    Vertex *four = newVertex(4);

    Vertex vertices[] = { *one, *two, *three, *four };

    Edge *oneTwo = newEdge(one, two);
    Edge *twoThree = newEdge(two, three);
    Edge *threeOne = newEdge(three, one);
    Edge *fourOne = newEdge(four, one);
    Edge *twoFour = newEdge(two, four);
    Edge *fourThree = newEdge(four, three);

    Edge edges[] = { *oneTwo, *twoThree, *threeOne, *fourOne, *twoFour, *fourThree };

    ListNode *adjacencyList[4];

    convertToAdjacencyList(edges, 6, vertices, 4, adjacencyList);

    for (int i = 0; i < 4; i++) {
        printf("%d: ", i + 1);
        ListNode *node = (adjacencyList[i]);

        while (node != NULL) {
            printf("%d ", node->item->id);
            printf("%p ", node->next);
            node = node->next;
        }
        printf("\n");
    }
    
    return 1;
}
