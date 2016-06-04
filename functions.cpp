/* This file holds all of the implemented functions.  
 */
#include "functions.h"
using namespace std;

/* Constructor
 * Task: Initializes the members, and is implicitly
 * invoked whenver a client creates an object of the
 * class.
 * Input: Nothing. 
 * Output: Nothing. */
fileEntry::fileEntry(void)
{
    name = NULL;
}

/* Destructor
 * Task: Implicitly deallocates the memory when the * lifetime of a class object is over(end of block
 * in which it is defined).
 * Input: Nothing.
 * Output: Nothing. */
fileEntry::~fileEntry(void)
{
    if(name)
    {
        delete [] name;
        name = NULL;
    }
}

/* createFile
 * Task: This function deep copies the char pointer
 * Input: aName is a pointer to a char.
 * Output: Returns a 1 for success, a zero for fail. */
int fileEntry::createFile(char * aName)
{
    if(!aName) return 0;
    if(name) delete [] name;
    name = new char[strlen(aName)+1];
    strcpy(name, aName);
    return 1;
}

/* copyEntry 
 * Task: This function deep copies whatever temporary object of studyGuide
 * gets passed in.
 * Input: object of studyGuide 
 * Output: Returns a 1 for success; or a zero for fail. */
int fileEntry::copyEntry(const fileEntry & aNewEntry)
{
    if(!aNewEntry.name) return 0;
    if(name) delete [] name;
    name = new char[strlen(aNewEntry.name)+1];
    strcpy(name, aNewEntry.name);
    return 1;
}

/* compare
 * Task: This function checks if the existing vertice's name matches 
 * the argument.
 * Input: isItAMatch is a pointer to a char.
 * Output: Returns a true for success, a false for fail. */
bool fileEntry::compare(char * isItAMatch)
{
    if(!isItAMatch || !name) return false;
    if(strcmp(name, isItAMatch) == 0)
        return true;
    return false; 
}

/* compare
 * Task: This function checks if the existing vertice's name matches 
 * the argument.
 * Input: isItAMatch is a pointer to a char.
 * Output: Returns a true for success, a false for fail. */
int fileEntry::display(void) const
{
    if(!name) return 0;
    cout << name; 
    return 1;
}

/* getName
 * Task: Returns the char * name.
 * Input:Nothing.
 * Output: Returns the char * name. */
char * fileEntry::getName()const
{
    return name;
}
/* Constructor
 * Task: Initializes the members, and is implicitly
 * invoked whenver a client creates an object of the
 * class.
 * Input: Nothing. 
 * Output: Nothing. */
queue::queue(void)
{
    rear = NULL;
}


/* Destructor
 * Task: Implicitly deallocates the memory when the 
 * lifetime of a class object is over(end of block
 * in which it is defined).
 * Input: Nothing.
 * Output: Nothing. */
queue::~queue(void)
{
    if(rear)
    {
        qnode * temp = rear;
        while(temp->next != rear)
        {
            qnode * end = temp;
            temp = temp->next;
            delete end;
        }
        delete temp;
        rear = NULL;
    }
}

/* enqueue
 * Task: Adds a new node at the rear
 * Input: const fileEntry & toRear
 * Output: A non-zero for success, a zero for fail. */
int queue::enqueue(const fileEntry & toRear)
{
    if(!rear)
    {
        rear = new qnode;
        rear->next = rear;
        rear->qEntry.copyEntry(toRear);
        return 1;
    }
    else
    {
        qnode * temp = new qnode;
        temp->next = rear->next;
        rear->next = temp;
        rear = temp;
        rear->qEntry.copyEntry(toRear);
        temp = NULL;
        return 1;
    }
    return 0;
}

/* dequeue
 * Task: Dequeues at the front(rear->next) of the linked list.
 * Input: Nothing.
 * Output: A non-zero for success, a zero for fail*/
char * queue::dequeue()
{
    char * name;
    if(!rear) return NULL;
    if(rear->next == rear)
    {
        name = new char[strlen(rear->qEntry.getName())+1];
        strcpy(name, rear->qEntry.getName());
        delete rear;
        rear = NULL;
    }
    else
    {
        qnode * temp = rear->next;
        name = new char[strlen(temp->qEntry.getName())+1];
        strcpy(name, temp->qEntry.getName());
        rear->next = temp->next;
        delete temp;
    }
    return name;
}

/* isEmpty
 * Task: Checks if the queue is empty. 
 * Input: Nothing.
 * Output: Returns a true if queue is empty, a false if not.*/ 
bool queue::isEmpty()
{
    if(!rear)
        return true;
    return false;
}

/* Constructor
 * Task: Initializes the members, and is implicitly
 * invoked whenver a client creates an object of the
 * class.
 * Input: Nothing. 
 * Output: Nothing. */
table::table(int numVertices)
{
    adjacencyList = new vertex[numVertices]();
    for(int i=0; i<numVertices; ++i)
    {
        adjacencyList[i].head = NULL;
    }
    count = 0;
    this->numVertices = numVertices;
    visited = new bool[numVertices];
    for(int j=0; j<numVertices; ++j)
    {
        visited[j] = false;
    }
}

/* Destructor
 * Task: Implicitly deallocates the memory when the 
 * lifetime of a class object is over(end of block
 * in which it is defined).
 * Input: Nothing.
 * Output: Nothing. */
table::~table()
{
    if(adjacencyList) 
    {
        for(int i=0; i<numVertices; ++i)
        {
            if(adjacencyList[i].head)
            {
                node * temp = adjacencyList[i].head;
                while(temp)
                {
                    adjacencyList[i].head = adjacencyList[i].head->next;
                    delete temp;
                    temp = adjacencyList[i].head;
                }
                temp = NULL;
            }
        }
        delete [] adjacencyList;
        adjacencyList = NULL;
    }
    if(visited)
    {
        delete [] visited;
        visited = NULL;
    }
}

/*  Read in 
 * Task:This function reads in from an external file "study.txt"
 * and stores in the data into a temporary object of struct airport,
 * and passes in that object to add to the LLL. 
 * Input: Nothing.
 * Output: A non-zero for success, a zero for fail, */
int table::readIn()
{
    //fileEntry tempFile;
    char temp1[SIZE_CHAR];
    ifstream file;
    file.open("files.txt");
    if(file)
    {
        while(!file.eof() && file.peek() != EOF)
        {
            file.get(temp1,SIZE_CHAR,'\n'); file.ignore(100,'\n');
            insertVertex(temp1);
        }
    }
    file.close();
    return 1;
}

/* insertVertex 
 * Task: This function inserts the char into the first empty adjacencyList
 * element. 
 * Input: A char pointer.
 * Output: Returns less than a 0 for fails, returns 0 or greater
 * for success. */
int table::insertVertex(char * toAdd)
{
    //Go through the whole adjacencyList and 
    //compare the argument for a match. 
    //If it's already in the adjacencyList, 
    //return -1. 
    for(int i=0; i<numVertices; ++i)
    {
        if(adjacencyList[i].entry.compare(toAdd)==true)
            return -1;
    }
    //Outside of the array
    if(count == numVertices)
        return -1;
    adjacencyList[count].entry.createFile(toAdd);
    ++count;
    //Return where it was added.
    return count-1;
}

/* insertEdge 
 * Task: This function creates the edges, which are represented as the two int 
 * variables, from and to, which will pass into the connectEdges function.
 * Input: Two char pointers.
 * Output: Returns greater than 0 for any fails, returns a 0 for success. */
int table::insertEdge(char * currentVertex, char * toAttach)
{
    int from = retrieveList(currentVertex);
    int to = retrieveList(toAttach);
    //Prevents connecting to itself.
    if(from == to)
        return 2;
    //Using pointers to check for duplicates befdore connecting edges.
    node * current = adjacencyList[from].head;
    node * checker = adjacencyList[to].head;
    while(current)
    {
        //Checks for duplicate addresses.
        if(current->adjacent->head == checker)
            return 3;
        current = current->next;
    }
    //As long as there were no duplicates, we can connect the edges.
    connectEdges(from, to);
    return 0;
}

/* connectEdges 
 * Task: Connects the edges by inserting in the beginning of head at the 
 * connected indexes.
 * Input: Two int variables.
 * Output: Returns a 0 for success. */
int table::connectEdges(int from, int to)
{   
    //Create a pointer to the 'from' index of the list.

    node * current = new node;
    current->next = adjacencyList[from].head;
    adjacencyList[from].head = current;

    current->adjacent = &adjacencyList[to];

    node * temp = new node;
    temp->next = adjacencyList[to].head;
    adjacencyList[to].head = temp;
    temp->adjacent = &adjacencyList[from];
    return 0;
}

/* retrieveList 
 * Task: Retrieves the index where the key is found in the adjacencyList.
 * Input: A pointer to char. 
 * Output: Returns a number 0 or greater if the key is found; and returns
 * less than a 0 for fails.*/
int table::retrieveList(char * key)
{
    if(!key) return -2;
    for(int i=0; i<numVertices; ++i)
    {
        if(adjacencyList[i].entry.compare(key)==true)
            return i;
    }
    return -1;
}

 /*        B        0 |A|->|B|->|S|->NULL          
 *        /         1 |B|->|A|->NULL
 *       A   C      2 |S|->|A|->|C|->|G|->NULL
 *        \ /       3 |C|->|S|->NULL
 *         S        4 |G|->|S|->NULL
 *          \
 *           G
 */
/* displayAll 
 * Task: I built this function to visually check that I have the graph
 * implemented correctly.
 * Input: Nothing.
 * Output: Returns a 0 for success, a 1 for failure. */
int table::displayAll()
{
    if(!adjacencyList) return 0;
    for(int i=0; i< numVertices; ++i)
    {
        cout << i << " |" << adjacencyList[i].entry.getName() << "|->"; 
        node * current = adjacencyList[i].head;
        while(current)
        {
            cout << "|" << current->adjacent->entry.getName() << "|->"; 
            current = current->next;
        }
        cout << "NULL\n";
    }
    return 1;
}


/* displayAdjacent 
 * Task:This function is a wrapper function to the breadth first search 
 * function.
 * Input:
 * Output:  */
int table::displayAdjacent(char * key)
{
    //Vertx will represent the starting adjacencyList index to start our BFS.
    int vertx = retrieveList(key);
    //If vertx is not in the table, return 1.
    if(vertx < 0) return 1;
    //Pass that node and index for the visited flag.
    bfs(adjacencyList[vertx].head, vertx);
    return 0;
}

/* markVisit
 * Task: Marks the desired vertice's to true for visited.
 * Input: An int representing the index.
 * Output: Returns a 0 for success. */
int table::markVisit(int vertx) 
{
    visited[vertx] = true;    
    return 0;
}


/* allVisited 
 * Task: Checks if all of the vertices have been visited.
 * Input: Nothing.
 * Output: A true if all vertices have already been flagged true. */
bool table::allVisited()
{
    for(int i=0; i<numVertices; ++i)
    {
        if(visited[i]==false)
            return false;
    }
    return true;
}

/* bfs (breadth first search)
 * Task:Breadth first traverses based off the node passed in. 
 * Input: A node pointer and an int.
 * Output: Returns an int 1 if head is empty, a 0 if all nodes
 * have been visited, and a 2 if the queue is empty.*/
int table::bfs(node * head, int vertx)
{
    if(!head) return 1;
    //Start of the adjacencyList
    if(allVisited() == true)
        return 0;
    if(visited[vertx]==false)
    {
        adjacencyList[vertx].entry.display();
        markVisit(vertx);
    }
    node * current = head;
    while(current)
    {
        //int check will pass the current's name into retrieveList, returning
        //the index where it already exists.
        int check = retrieveList(current->adjacent->entry.getName());
        
        if(check >= 0)
        {
        //Enqueue unvisited nodes and mark as visit
            if(visited[check]==false)
            {
                q.enqueue(current->adjacent->entry);
            }
        }
        //Go to the next node in the list and repeat.
        current = current->next;
    }
    //recursive return to the index where the last data that was dequeued. 
    if(q.isEmpty()==false)
    {
        //dequeue returns the char * of the qnode dequeued.
        char * remove = q.dequeue();
        int adj = retrieveList(remove);
        bfs(adjacencyList[adj].head, adj);
        if(remove)
            delete [] remove;
    }
    else if(q.isEmpty()==true) 
        return 2;
}

