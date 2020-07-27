#ifndef coord_HEADER
#define coord_HEADER


class coord {

	public:
	coord();
	coord(const int x_in, const int y_in);	// x-value, y-value

	coord get_pos();
	int get_x();
	int get_y();

	coord operator+ (const coord);
	coord operator- (const coord);
	const coord operator+ (const coord&) const;
	const coord operator- (const coord&) const;
	coord& operator+= (const coord&);
	coord& operator-= (const coord&);
	coord& operator= (const coord&);
	bool operator== (const coord);

	private:
	int x;	// x-coordinate of point
	int y; // y-coordinate of point
	
};


#endif