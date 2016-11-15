# Graph-BFS

/* Task: In this program, we will use a graph to represent
 * relationships by categorizing them. 
 * I found a great video explaining about breadth first search graphs 
 * and decided to build a graph based off of the example. Here
 * is the link: 
 * https://www.youtube.com/watch?v=QRq6p9s8NVg
 *
 * Here is what I made my graph
 * look like. 
 * BFS Answers:
 *
 * BASCG
 * ABSCG
 * SACGB
 * CSAGB
 * GSACB
 *         B        0 |A|->|B|->|S|->NULL          
 *        /         1 |B|->|A|->NULL
 *       A   C      2 |S|->|A|->|C|->|G|->NULL
 *        \ /       3 |C|->|S|->NULL
 *         S        4 |G|->|S|->NULL
 *          \
 *           G
 *           Tomake it look like this, we must insert connect the nodes
 *           in the order from G to S, C to S, A to S, and B to A.
 * */
