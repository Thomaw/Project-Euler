struct point {
	int x;
	int y;

	bool operator== (const point& p) const
	{
		return (x == p.x && y == p.y);
	}
};

...

bool is_right_triangle(point &p1, point &p2, point &p3)
{
	int sidea = (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
	int sideb = (p1.x-p3.x)*(p1.x-p3.x) + (p1.y-p3.y)*(p1.y-p3.y);
	int sidec = (p2.x-p3.x)*(p2.x-p3.x) + (p2.y-p3.y)*(p2.y-p3.y);

	return (sidea + sideb == sidec) || (sidea + sidec == sideb) || (sideb + sidec == sidea);
}

...

// and then four nested loops