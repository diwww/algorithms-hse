
#include "toyBDD.h"

#include <cmath>

////////////////////////////////////////////////////////////////////////
// Main program.
int main(int argc, char *argv [])
{
    // Initial value for BDD size.
    int sizeMaxBDD = 50; // Default: 50 MB

    // Initialize BDD package.
    {
        // 2000000 BDD nodes ~ 50 MB
        unsigned amountOfNodes  = sizeMaxBDD * 30000;
        unsigned sizeHash = (unsigned) ( log((float)amountOfNodes) / log(2.0) );
        // Initialize BDD package.
        toyBDD::init(amountOfNodes, sizeHash, sizeHash);
    }


    cout << "====================================================================================== \n";
    cout << "BDD as a string examples:\n\n";

    cout << "================ \n";
    cout << "BDD: ";
    toyBDD(0,1,1).print(cout);
    cout << " corresponds to:\n";
    cout << "    x0       \n";
    cout << "  l/  \\h     \n";
    cout << " 0      1  \n";
    cout << "================ \n";
    cout << endl;

    cout << "================ \n";
    cout << "BDD: ";
    toyBDD(0,1,0).print(cout);
    cout << " corresponds to:\n";
    cout << "    x0       \n";
    cout << "  h/  \\l     \n";
    cout << " 0      1  \n";
    cout << "================ \n";
    cout << endl;

    cout << "============================ \n";
    cout << "BDD: ";
    toyBDD(0,3,5).print(cout);
    cout << " corresponds to:  \n";
    cout << "    x0            \n";
    cout << "  l/ \\h          \n";
    cout << "  /   x1          \n";
    cout << " |  /h  \\l       \n";
    cout << " |/    x2         \n";
    cout << " |   /l   \\h     \n";
    cout << " | /       |      \n";
    cout << " |/        |      \n";
    cout << " 0         1      \n";
    cout << "============================ \n";
    cout << endl;
    cout << "====================================================================================== \n";
    cout << endl;
    cout << endl;


    cout << "====================================================================================== \n";
    cout << "Union of BDDs example:\n";
    cout << "================================== \n";
    toyBDD bdd5(0,3,5), bdd7(0,3,7);
    cout << "BDD \"5\": ";
    bdd5.print(cout);
    cout << "BDD \"7\": ";
    bdd7.print(cout);
    cout << "BDD \"5 union 7\": \n";
    cout << "Result   : ";
    toyBDD bdd57(bdd5);
    bdd57.unite(bdd7);
    bdd57.print(cout);
    cout << "Expected : (0 x0 (0 x2 1)) \n";
    cout << "====================================================================================== \n";
    cout << endl;
    cout << endl;

    cout << "====================================================================================== \n";
    cout << "Intersection of BDDs example:\n";
    cout << "================================== \n";
    cout << "BDD \"5; 7\": ";
    bdd57.print(cout);
    cout << "BDD \"7; 9\": ";
    toyBDD bdd9(0,4,9),bdd79(bdd7);
    bdd79.unite(bdd9);
    bdd79.print(cout);
    cout << "BDD \"{5;7} intersect {7;9}\": \n";
    cout << "Result   : ";
    bdd79.intersect(bdd57);
    bdd79.print(cout);
    cout << "Expected : (0 x0 (0 x1 (0 x2 1))) \n";
    cout << "====================================================================================== \n";

    cout << endl;
    cout << endl;
    cout << "====================================================================================== \n";
    cout << "Complement of a BDD with 3 variables:\n";
    cout << "================================== \n";
    toyBDD bdd1(0,3,1), bdd3(0,3,3);
    cout << "BDD \"1\": ";
    bdd1.print(cout);
    cout << "BDD \"3\": ";
    bdd3.print(cout);
    cout << "BDD \"5\": ";
    bdd5.print(cout);
    cout << "BDD \"{1;3;5}\": ";
    toyBDD bdd135(bdd1);
    bdd135.unite(bdd3);
    bdd135.unite(bdd5);
    bdd135.print(cout);
    cout << endl;
    cout << "Result   : ";
    bdd135.complement();
    bdd135.print(cout);
    cout << "Expected : ((1 x2 0) x0 ((1 x2 0) x1 1))\n";
    cout << "====================================================================================== \n";

    return 0;
};

