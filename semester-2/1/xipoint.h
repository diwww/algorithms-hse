////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     xi Point class definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      14.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Implementations for the methods declared in the classes below must be put
/// in corresponding module named xipoint.cpp.
/// 
////////////////////////////////////////////////////////////////////////////////




#ifndef XI_POINT_H_       // pay attention for this #define-style guard
#define	XI_POINT_H_


/// Namespaces are used to enclose definitions in order to prevent name collisions
/// Often, there is no indentation inside namespaces in C++
/// <b style='color:orange'>Students must use the same namespace in the corresponding .cpp module</b>
namespace xi {


/** \brief Declares a two integral coordinate  point object
 *
 *  Since there are reverse links presented, a list can be traversed both
 *  in direct and reverse direction.
 *
 */
class Point {
public:
    /// Constructor initialize a point object with two coordinates  
    Point(int x = 0 , int y = 0);


public:                             // no special need for this line, it used only as 
                                    // a separator for improving  reading

    /// Shifts coordinates by adding given value shf to both coordinates
    void shift(int shf);

    /// Shifts coordinates by adding given values of corresponding coordinates
    void shift(int xSh, int ySh);

    /// Shifts coordinates by adding given values of corresponding coordinates
    /// of the give point pt
    void shift(const Point& pt);

public:
    //-----<Setters/getters section>-----

    int getX () const;              ///< Gets x-coordinate
    int getY () const;              ///< Gets y-coordinate
    void setX(int x);     ///< Sets x-coordinate
    void setY(int y);     ///< Sets y-coordinate

protected:
    int _x , _y;                    ///< Fields for storing coordinates

}; // class Point


/** \brief Class declares a array-style collection of Point objects
 *
 *  Since the class is not generic and explicitly declares using Point objects,
 *  this is the only object types that can be managed by this array
 */
class PointArray {

public:
    typedef unsigned int Uint;

public:
    //-----<Constructors and destructor section>-----

    /** \brief Default constructor (a constructor with no arguments) 
     *
     *  It should create an array with size 0. 
     */
    PointArray();

    // Point array called points and an int called size 
    // as its arguments. It should initialize a PointArray with the 
    // specified size, copying the values from points. You will need 
    // to dynamically allocate the PointArray’s internal array to the 
    // specified size. 

    /** \brief Initialiaze an object with c-style array
     *
     *  The costructor initialized an object with a given c-style
     *  array points and its size (n). 
     *  One need to allocate dynamically the internal array to the size of a given array.
     *  Note that const Point points[] clause is equal to const Point* points
     */
    PointArray(const Point points[], const Uint n);

    /// Constructor creates a copy of a given PointArray
    PointArray(const PointArray& pv);

    /// Destructor that deletes the internal array of the PointArray (frees the allocated memory)
    ~PointArray();

public:

    /// Adds a Point to the end of the array 
    void append(const Point& pt);


    /** \brief Inserts a Point at a given position of the array, shifting the 
     *  elements past pos to the right.
     *
     *  If pos == 0, inserts a point into the beginning of the array.
     *  If pos is bigger then the number of elements, put the point to the end.
     */
    void insert(const Point& pt, Uint pos);


    /** \brief Removes a Point at a given position of the array, shifting the 
     *  remaining elements to the left .
     *
     *  If pos is bigger then the number of elements, does nothing.
     *  If the removed element is the last one, no more underlying array is presented 
     *  after removing.
     */
    void remove(const Uint pos);

    /// Removes all elements from the array and sets its size to 0 
    void clear();

public:

    /// Gets the size of the array 
    const Uint getSize() const;


    /** \brief Gets a pointer to the element at a given position of the array
     *
     *  If the array contains no given element, returns nullptr
     */
    Point* get(Uint pos);

    /// Const overloaded version of get() method
    const Point* get(Uint pos) const;

public:
    /// Returns a raw pointer to the underlying array. Can be user only in RHV position
    /// The method is implemented as highly-effective inline function
    const Point* getRawPtr() const { return _arr; };

protected:

    /// Allocates a new array of size n, copies the first min (previous array
    /// size, n) existing elements into it, and deallocates the old array.
    void resize(Uint n);

    Point* _arr;                ///< Pointer to a c-style  array
    Uint _size;                 ///< The actual size of the ^^^
};

} // namespace xi

#endif	// XI_POINT_H_

