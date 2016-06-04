/* Task: In this program, we will use a graph to represent
 * relationships by categorizing them. Here is what I made my graph
 * look like. 
 *
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
#include "functions.h"
using namespace std;

const int KEYWORD = 20;

int main()
{
    //Call class table which represents 
    //I only have 5 total vertices, hence calling the initializing
    //the table constructor to 5.  
    table myFile(5);
    myFile.readIn();
    char from[KEYWORD];
    char to[KEYWORD];
    
    /*
    do
    {
        myFile.displayAll();
        cout << "Enter:";
        cin.get(from,KEYWORD,'\n'); cin.ignore(100,'\n'); 
        cout << "Enter:";
        cin.get(to,KEYWORD,'\n'); cin.ignore(100,'\n'); 
        myFile.insertEdge(to, from);
    }while(again());
    */
    myFile.insertEdge("G", "S");
    myFile.insertEdge("C", "S");
    myFile.insertEdge("A", "S");
    myFile.insertEdge("B", "A");
     
    myFile.displayAll(); 

    char temp[KEYWORD];
    
    cout << "Display the other vertices that are related to this topic:\n";
    cin.get(temp,KEYWORD,'\n'); cin.ignore(100,'\n');
    if(myFile.displayAdjacent(temp) == -1) 
        cout << "\nThere is no such DATA.";
    
    return 0;
}

/* again 
 * Task: Prompts the user to re-run the program. 
 * Input: Nothing. 
 * Output: Returns a true for 'Y' or 'y' and returns a false for 'N' or 'n'. */
bool again()
{
    char answer;
    cout << "\nAgain? (Y/N)";
    cin >> answer;
    cin.ignore(100, '\n');
    answer = toupper(answer);
    if(answer == 'Y')
        return true;
    else if(answer == 'N')
        return false;
    return again();
}
