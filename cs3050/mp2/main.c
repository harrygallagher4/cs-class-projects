#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Harry Gallagher, Machine Problem 2
 * Reads a file describing a directed graph G as a list of edges. 
 * Calculates the out-degree sequence for G^(SCC) in increasing order.
 * 
 * First calculates G^T using the edge list by just iterating over the edges
 * and reversing each one. Then uses DFS to compute finishing times for each
 * vertex in G. ...
 * 
 * ... gonna stop documenting it here because I didn't actually implement
 * anything farther than the transposition. I'm really slacking on these
 * assignments, huh.
 */

/**
 * This is pretty useless, but whatever. 
 */
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

/**
 * Count number of lines in file
 */
int countLinesInFile(char file[]) {
    FILE *fp = fopen(file, "r");
    if (fp == NULL) {
        return -1;
    }

    // just in case someone forgets their trailing newline.
    // probably ends up allocating space for one extra Vertex
    int lines = 1;
    char c;
    while (!feof(fp)) {
        c = fgetc(fp);
        if (c == '\n') {
            lines++;
        }
    }

    fclose(fp);
    
    return lines;
}

/**
 * Read edges from file formatted with each edge on a line, with their
 * vertices separated by a space
 */
int readEdgesFromFile(char file[], Edge *edges[]) {
    FILE *fp;
    fp = fopen(file, "r");

    if (fp == NULL) {
        return 1;
    }

    for (int index = 0; !feof(fp); index++) {
        int from, to;
        fscanf(fp, "%d %d\n", &from, &to);
        Vertex *fromV, *toV;
        fromV = newVertex(from);
        toV = newVertex(to);
        Edge *e = newEdge(fromV, toV);
        edges[index] = e;
    }

    fclose(fp);

    return 0;
}

/**
 * We can easily count the number of vertices by just locating the
 * vertex with the highest ID. The format of the input file
 * specifies they're numbered from 1 to the total number
 */
int countVertices(Edge *edges[], int edgeCount) {
    int count = 0;
    for (int i = 0; i < edgeCount; i++) {
        Edge *e = edges[i];
        if (e == NULL) {
            break;
        }

        if (e->from->id > count) {
            count = e->from->id;
        }

        if (e->to->id > count) {
            count = e->to->id;
        }
    }

    return count;
}

/*
 * G^T is just G with all of the edges reversed, so since we already
 * have a list of edges we can just reverse each one to get the edges
 * in G^T
 */
void transposeEdges(Edge *transpose[], Edge *source[], int edgeCount) {
    for (int i = 0; i < edgeCount; i++) {
        Edge *e = source[i];
        if (e == NULL) {
            break;
        }

        Edge *reversedEdge = newEdge(e->to, e->from);
        transpose[i] = reversedEdge;
    }
}

void printNode(ListNode *node) {
    printf("%d: %p->%p\n", node->item->id, node, node->next);
}

/** 
 * Converts a list of G's edges into an adjacency list representation of G
 */
void getAdjacencyListFromEdges(Edge *edges[], int edgeCount,
ListNode *adjacencyList[], int vertexCount) {
    // ensure adjacency list starts empty
    for (int i = 0; i < vertexCount; i++) {
        adjacencyList[i] = NULL;
    }

    for (int i = 0; i < edgeCount; i++) {
        Edge *edge = edges[i];
        if (edge == NULL) {
            break;
        }

        Vertex *from = edge->from;
        Vertex *to = edge->to;
        int fromId = from->id;
        int toId = to->id;
        int fromIndex = fromId - 1;
        int toIndex = toId - 1;

        ListNode *toNode;

        if (adjacencyList[fromIndex] == NULL) {
            toNode = newNode(to, NULL);
        } else {
            ListNode *head = adjacencyList[fromIndex];
            toNode = newNode(to, head);
        }

        adjacencyList[fromIndex] = toNode;
    }
}

void printAdjacencyList(ListNode *adjacencyList[], int vertexCount) {
    for (int i = 0; i < vertexCount; i++) {
        ListNode *node = adjacencyList[i];
        printf("%d: ", i + 1);

        if (node == NULL) {
            printf("\n");
            continue;
        }

        printf("%d ", node->item->id);

        while ((node = node->next) != NULL) {
            printf("%d ", node->item->id);
        }

        printf("\n");
    }
}

int main(void) {
    char file[] = "edges.txt";
    int lines = countLinesInFile(file);
    printf("%d lines\n", lines);
    
    if (lines == -1) {
        printf("Could not open file %s\n", file);
        return 1;
    }

    Edge *edges[lines];    
    Edge *transpose[lines];

    if (readEdgesFromFile(file, edges) == 1) {
        printf("Could not open file %s\n", file);
        return 1;
    }

    int vertexCount = countVertices(edges, lines);
    printf("%d vertices\n", vertexCount);
    ListNode *adjacencyList[vertexCount];
    ListNode *transposedAdjacencyList[vertexCount];

    getAdjacencyListFromEdges(edges, lines, adjacencyList, vertexCount);
    transposeEdges(transpose, edges, lines);
    getAdjacencyListFromEdges(transpose, lines, transposedAdjacencyList,
                                vertexCount);

    printAdjacencyList(adjacencyList, vertexCount);
    printAdjacencyList(transposedAdjacencyList, vertexCount);

    return 0;
}