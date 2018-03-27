#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ostringstream convert;
    char resp = 'n';
    int matrixSize = 0;

    //get number of nodes to determine the matrix size
    cout << "Enter the number of nodes: ";
    cin >> matrixSize;

    //create matrix
    int nodeMatrix[matrixSize][matrixSize];
    for(int i = 0; i < matrixSize; i++)
    {
        for(int j = 0; j < matrixSize; j++)
        {
            nodeMatrix[i][j] = 0;
        }
    }

    string nodeNames[matrixSize];

    //name the nodes
    cout << "Would you like to name the nodes? [y/n]: ";
    cin >> resp;
    if (toupper(resp) == 'Y')
    {
        for (int i = 0; i < matrixSize; i++)
        {
            cout << "Enter name for node " << i+1 << ": ";
            cin >> nodeNames[i];
        }
    }
    else
    {
        //if not naming nodes, assign them numbers
        for (int i = 0; i < matrixSize; i++)
        {
            convert.str("");
            convert << i+1;
            nodeNames[i] = convert.str();
        }
    }

    //TODO: read file for input

    //get input for relationship status of each node (except for selves i.e. node[2,2])
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (i != j)
            {
                resp = 'n';
                cout << "Can ";
                cout << nodeNames[i];
                cout << " talk to ";
                cout << nodeNames[j];
                cout << "? [y/n]: ";
                cin >> resp;
                if (toupper(resp) == 'Y')
                {
                    nodeMatrix[i][j] = 1;
                }
            }
        }
    }

    cout << "User Entered: \n";
    //cout << Matrix.ToString(nodeMatrix, nodeNames);


    //Matrix.GetLinkedNodes<int> (ref nodeMatrix, 1, 0);

    cout << "Returned: \n";
    //cout << Matrix.ToString(nodeMatrix, nodeNames);

    for (int i=0; i < matrixSize; i++)
    {
        for (int j=0; j < matrixSize; j++)
        {
            cout << nodeNames[i];
            cout << ", ";
            cout << nodeNames[j];
            cout << " = ";
            cout << nodeMatrix[i][j];
            cout << "\n";

        }
    }



    cout << "Hello world!" << endl;
    return 0;
}
