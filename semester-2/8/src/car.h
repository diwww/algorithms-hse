///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains definition of \a Car class
///
/// Car module should not normally be altered
///
///////////////////////////////////////////////////////////////////////////////

#ifndef XI_ENHPARKINGLOT_CAR_H_
#define XI_ENHPARKINGLOT_CAR_H_

#include <iostream>
#include <string>



/** \brief Replresents a record about a car in a parking
 *
 *  Acts like a descriptor of a car, containing information about its plate id
 *  and moving during staying in a parking
 */
class Car 
{
public:

    /** \brief Initialize with a plate number */
    Car(const std::string& plate);
    
    /** \brief Initialize with a plate number and an aisle number*/
    Car(const std::string& plate, int aisle);

    /** \brief Returns a number of moving the car during its staying the parking */
    int getTimesMoved(void) const;
    
    /** \brief Sets a number of moving the car during its staying the parking */
    void setTimesMoved(int);
    
    /** \brief Returns car's plate */
    const std::string& getPlate(void) const;
    
    /** \brief Returns the aisle the car is parking in */
    int getAisle(void) const;

    /** \brief Implemented for sorsing: a car is "less" if its plate is less */
    bool operator < (const Car& rhs) const;
    
    /** \brief Equality of two cars is defined as equality their plates */
    bool operator == (const Car& rhs) const;

private:
    int _moved;                     ///< Stores a number of movings
    std::string _licensePlate;      ///< Stores a license plate
    int _aisle;                     ///< Stores an aisle the car is parked in
}; // class Car 


#endif // XI_ENHPARKINGLOT_CAR_H_
