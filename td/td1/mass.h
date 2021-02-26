#pragma once

enum class MassType
{
	Constant,
	Movable
};

class Mass
{
public:
	Mass(MassType type, double x, double y, double m);
	~Mass();

	void draw() const;
	void update(double h);

	double getX() const { return x; }
	double getY() const { return y; }
	double getSpeed() const { return speed; }

	void addToFriction(double toAdd) { fric += toAdd; }

private:
	void leapFrog(double h);

private:
	double m; // mass
	double y; // position y
	double x; // position x
	double speed = 0.;
	double fric = 0.; // friction
	MassType type;
};
