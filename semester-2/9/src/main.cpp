#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include <iostream>
#include <fstream>
#include <string>

#include "City.h"
#include "Service.h"
#include "RailSystem.h"

using namespace std;

// For test
bool check(Route & expected,RailSystem &rs){
    Route actual = rs.getCheapestRoute(expected.from,expected.to);
    return actual == expected;
}

int main(int argc, char* argv[]) {

    try {

        RailSystem rs("/home/maxim/University/HomeWork/Algorithms/2_semester/algo-2sem-9/src/services.txt");

        while (true) {

            cerr << "\n\nEnter a start and destination city:  ('quit' to exit)\n";

            string from, to;
            cin >> from;
            if (from == "quit") break;
            cin >> to;

            if (rs.is_valid_city(from) && rs.is_valid_city(to)) {
                rs.output_cheapest_route (from, to, cout);
            }
            else {
                cout << "Please enter valid cities\n\n";
            }

        }

        return EXIT_SUCCESS;

    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown exception caught\n";
    }

    return EXIT_FAILURE;
}
