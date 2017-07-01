///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains implementation of \a Car class
///
/// Car module should not normally be altered
///
///////////////////////////////////////////////////////////////////////////////
#include "car.h"

Car::Car(const std::string& plate) :
    _licensePlate(plate),
    _moved(0),
    _aisle(-1) 
{
}

Car::Car(const std::string& plate, int aisle) :
    _licensePlate(plate),
    _moved(0), 
    _aisle(aisle)
{
}

int Car::getTimesMoved(void) const 
{

    return _moved;
}

void Car::setTimesMoved(int m) 
{

    _moved = m;
}

int Car::getAisle(void) const 
{

    return _aisle;
}

const std::string& Car::getPlate(void) const 
{

    return _licensePlate;
}

bool Car::operator < (const Car& rhs) const 
{
    
    return this->getPlate() < rhs.getPlate();
}

bool Car::operator == (const Car& rhs) const
{
    
    return this->getPlate() == rhs.getPlate();
}
