///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Main entry point
///
/// This file contains a partial implementation for the simulation. It is
/// task for students to finish this implementation.
///
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "car.h"


const int PARKING_SPOTS_PER_AISLE = 3;      ///< Determines a number of cars per an aisle
const int NUMBER_OF_AISLES = 5;             ///< Determines a number of aisls in the parking


/** \brief Defines an Aisle in some parking */
typedef std::stack<std::string> ParkAisle;

/** \brief Defines a parking containing some aisles */
typedef std::vector<ParkAisle> Parking;

/** \brief Defines a collection of cars most likely implemented as a vector of cars */
typedef std::vector<Car> Cars;


/** \brief Iterates through the vector of stacks, looking for the first stack that
 *  does not contain three cars. If all five aisles (stacks) are full, output a message 
 *  indicating such; otherwise place the license plate into the first non-full stack.
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
                    const std::string& plate);


/** \brief Locates the departing vehicle from the \a cars vector using function \a find_car() and
 *  removes the departing car's license plate from the corresponding aisle.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate);


/** \brief Returns a reference to the \a Car object stored in the vector \a cars 
 *  whose license plate equals the parameter \a plate.
 */
Car& find_car(Cars& cars, const std::string& plate);


//------------------------------------------------------------------------------


/** \brief Main entry point of the program
 *
 *  Should obtain at least 1 command line parameter, which is interpreted as the name of a 
 *  file with parking day's payload
 */
int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage:\n" << argv[0] << " data-file";
            return EXIT_FAILURE;
        }

        std::ifstream inf(argv[1]);
        if (!inf)
        {
            std::cerr << "Could not open " << argv[1];
            return EXIT_FAILURE;
        }

        Cars cars;
        Parking parking_lot(NUMBER_OF_AISLES);

        while (!inf.eof())
        {

            std::string action, plate;
            inf >> plate >> action;

            if (action == "arrives")
            {
                handle_arrival(cars, parking_lot, plate);
            }
            else if (action == "departs")
            {
                handle_departure(cars, parking_lot, plate);
            }
            else
            {
                std::cerr << "Unknown action: " << action << std::endl;
            }

        }
        inf.close();

        // Output the license plates of all the
        // cars that visited the lot, in alphabetical order
        std::cout << "\nHere are all the cars that visited the lot today:\n";
        std::sort(cars.begin(), cars.end());
        for (Car car : cars)
            std::cout << car.getPlate() << " moved " <<
                      car.getTimesMoved() << " times" << std::endl;

        return EXIT_SUCCESS;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught!" << std::endl;
    }

    return EXIT_FAILURE;
}

//------------------------------------------------------------------------------

/** 
 *  This is essentially "parking" the car. For this
 *  arriving car, also add an entry of type \a Car to the vector \a cars. In this \a Car instance, 
 *  make sure to record properly the index of the aisle where this car is parked. 
 */
void handle_arrival(Cars& cars, Parking& parking_lot,
                    const std::string& plate)
{
    // I know, that this part of code (cycle)
    // could be written in more simple way,
    // but I intended to practice iterators here
    Parking::iterator it;
    int i = 0; // number of aisle
    for (it = parking_lot.begin(); it != parking_lot.end(); ++it, ++i)
    {
        if (it->size() != PARKING_SPOTS_PER_AISLE)
        {
            it->push(plate);
            Car arrivedCar(plate, i);
            cars.push_back(arrivedCar);
            return;
        }
    }

    std::cout << "Parking is full." << std::endl;
}

//------------------------------------------------------------------------------


/** 
 *  Another stack must be used to move, temporarily, any cars that may be in front of the
 *  departing car. Record the number of times a car is moved when accommodating the
 *  departure of another car. For the departing car, display the number of times it was moved
 *  while it was parked in the lot.
 */
void handle_departure(Cars& cars, Parking& parking_lot, const std::string& plate)
{
    Car& departedCar = find_car(cars, plate);
    ParkAisle& currentAisle = parking_lot[departedCar.getAisle()];
    ParkAisle tempAisle; // an extra place for blocking cars

    while (currentAisle.top() != plate)
    {
        Car& top = find_car(cars, currentAisle.top());
        tempAisle.push(top.getPlate());
        currentAisle.pop();
        // Increasing moves count
        top.setTimesMoved(top.getTimesMoved() + 1);
    }

    // Depart a car
    currentAisle.pop();
    // Park remained cars back
    while (!tempAisle.empty())
    {
        currentAisle.push(tempAisle.top());
        tempAisle.pop();
    }

    // Display moves count
    std::cout << departedCar.getPlate() << " moved " <<
              departedCar.getTimesMoved() << " times" << std::endl;
}


//------------------------------------------------------------------------------


/** 
 *  Use the STL \a find() function to perform this task. To use the function correctly, you
 *  must supply it with three arguments. The first two arguments specify a range to search.
 *  The third argument is the value that the function attempts to find. This argument must be
 *  of type \a Car.
 *
 *  * http://www.cplusplus.com/reference/algorithm/find/
 */
Car& find_car(Cars& cars, const std::string& plate)
{
    Cars::iterator iter = std::find(cars.begin(), cars.end(), Car(plate));

    if (iter == cars.end())
        throw std::invalid_argument("Car not found.");

    return *iter;
}
