#pragma once

#include "mass.h"

enum class LinkType
{
	Constant, // Do not move
	Spring,
	Break,
	SpringBreak,
	ConditionalSpringBreak,
	Stop // Inactive after a certain threshold
};

class Link
{
public:
	Link(LinkType type, double k, // hardness
		double l, // default length
		double z, // viscosity
		double s, // threshold for conditionnal link
		double fric, // friction
		bool isActivated = true);

	~Link();

	void draw() const;
	void connect(Mass* mass1, Mass* mass2);
	void update();

private:
	void updateConstant();
	void updateSpring();
	void updateBreak();
	void updateSpringBreak();
	void updateConditionalSpringBreak();
	void updateStop();

private:
	double k; // hardness
	double l; // default length
	double z; // viscosity
	double s; // threshold for conditionnal link
	double fric; // friction
	Mass* m1 = nullptr;
	Mass* m2 = nullptr;
	bool isActivated = true;
	LinkType type = LinkType::Constant;
};

static Link ConstantLink(double force) { return Link(LinkType::Constant, 0., 0., 0., 0., force); }
static Link SpringLink(double k) { return Link(LinkType::Spring, k, 0., 0., 0., 0.); }
static Link BreakLink(double z) { return Link(LinkType::Break, 0., 0., z, 0., 0.); }
static Link SpringBreakLink(double k, double z) { return Link(LinkType::SpringBreak, k, 0., z, 0., 0.); }
static Link ConditionalSpringBreakLink(double k, double z, double s) { return Link(LinkType::ConditionalSpringBreak, k, 0., z, s, 0.); }
static Link StopLink(double k, double z, double s) { return Link(LinkType::Stop, k, 0., z, s, 0.); }
