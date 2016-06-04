 /* functions.h
 * This file holds the classes, #includes, and prototype functions. 
 */
#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <iomanip>
using namespace std;

const int SIZE_CHAR = 50;

//class fileEntry manages the name. 
class fileEntry 
{ 
    public:
        fileEntry(void);
        ~fileEntry(void);
        int createFile(char * name);
        int copyEntry(const fileEntry & aNewEntry);
        int retrieve(char * name, fileEntry & found) const;
        int retrieve(fileEntry & found) const;
        bool compare(char * isItAMatch);
        int display(void) const;
        char * getName()const; 
    private:
        char * name;
};

//struct vertex holds an object to fileEntry and a head
//pointer to node. 
struct vertex
{
    fileEntry entry;
    struct node * head;
};

//struct node holds a pointer to struct vertex and a pointer
//to itself.
struct node 
{
    vertex * adjacent;
    node * next;
};

//struct qnode holds an object to fileEntry and a
//pointer to itself.
struct qnode
{
    fileEntry qEntry;
    qnode * next;
};

//class queue is responsible for the CLL data structure.
class queue
{
    public:
        queue(void);
        ~queue(void);
        int enqueue(const fileEntry & toAdd);
        char * dequeue();
        bool isEmpty();
    private:
        qnode * rear;
};

//class table is responsible for the graph data structure.
class table
{
    public:
        table(int numVertices);
        ~table();
        int readIn();
        int connectEdges(int from, int to);
        int insertVertex(char * toAdd);
        int insertEdge(char * currentVertex, char * toAttach);
        int retrieveList(char * key);
        int displayAll();
        int displayAdjacent(char * key);
        bool allVisited();
    private:
        vertex * adjacencyList;
        queue q;
        int bfs(node * head, int vertx);
        int markVisit(int vertx);
        int count;
        int numVertices;
        bool * visited;
};

bool again();
