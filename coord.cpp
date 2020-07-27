#include "coord.h"

// constructors
coord::coord() {

	x = 0; 
	y = 0;
}
coord::coord(const int x_in, const int y_in) {

	x = x_in;
	y = y_in;
}

// member functions
coord coord::get_pos() {
	return *this;
}

// setter and getter
int coord::get_x() {
	return x;
}
int coord::get_y() {
	return y;
}

// overloaded operators
coord coord::operator+ (const coord rhs) {
	
	return coord(x + rhs.x, y + rhs.y);
}
coord coord::operator- (const coord rhs) {
	
	return coord(x - rhs.x, y - rhs.y);
}
const coord coord::operator+ (const coord& rhs) const {

	return coord(x + rhs.x, y + rhs.y);
}
const coord coord::operator- (const coord& rhs) const {

	return coord(x - rhs.x, y - rhs.y);
}

coord& coord::operator+= (const coord& rhs) {

	x += rhs.x;
	y += rhs.y;
	return *this;
}
coord& coord::operator-= (const coord& rhs) {

	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
coord& coord::operator= (const coord& rhs) {

	x = rhs.x;
	y = rhs.y;
	return *this;
}
bool coord::operator== (const coord rhs) {

	return ( (x == rhs.x) && (y == rhs.y) );
}