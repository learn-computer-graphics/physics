#include "mass.h"

Mass::Mass(MassType type, double x, double y, double m)
	: type(type), x(x), y(y), m(m)
{
}

Mass::~Mass()
{
}

void Mass::leapFrog(double h)
{
	speed += h * fric / m;
	y += h * speed;
	fric = 0;
}

void Mass::draw() const
{
	
}

void Mass::update(double h)
{
	switch (type)
	{
	case MassType::Constant:
		fric = 0;
		speed = 0;
		break;
	case MassType::Movable:
		leapFrog(h);
		break;
	default:
		break;
	}
}
