#include "link.h"


Link::Link(LinkType type, double k, double l, double z, double s, double fric, bool isActivated)
	:type(type), k(k), l(l), z(z), s(s), fric(fric), isActivated(isActivated)
{}

Link::~Link()
{
}

void Link::draw() const
{
}

void Link::connect(Mass* mass1, Mass* mass2)
{
	m1 = mass1;
	m2 = mass2;
	if (mass1 == nullptr || mass2 == nullptr)
		return;

	l = m2->getY() - m1->getY();
}

void Link::update()
{
	switch (type)
	{
	case LinkType::Constant: updateConstant(); break;
	case LinkType::Spring: updateSpring(); break;
	case LinkType::Break: updateBreak();  break;
	case LinkType::SpringBreak: updateSpringBreak();  break;
	case LinkType::ConditionalSpringBreak: updateConditionalSpringBreak(); break;
	case LinkType::Stop: updateStop();  break;
	default:
		break;
	}
}

void Link::updateConstant()
{
	Mass* mass = m1 != nullptr ? m1 : m2;
	mass->addToFriction(fric);
}

void Link::updateSpring()
{
	const double d = m2->getY() - m1->getY();
	const double f = k * (d - l);
	m1->addToFriction(f);
	m2->addToFriction(-f);
}

void Link::updateBreak()
{
	const double f = z * (m2->getSpeed() - m1->getSpeed());
	m1->addToFriction(f);
	m2->addToFriction(-f);
}

void Link::updateSpringBreak()
{
	const double d = m2->getY() - m1->getY();
	const double f = k * (d - l) + z * (m2->getSpeed() - m1->getSpeed());
	m1->addToFriction(f);
	m2->addToFriction(-f);
}

void Link::updateConditionalSpringBreak()
{
	// Link already broken
	if (!isActivated)
		return;

	const double d = m2->getY() - m1->getY();

	// Break link
	if (d > s)
	{
		isActivated = false;
		return;
	}

	const double f = k * (d - l) + z * (m2->getSpeed() - m1->getSpeed());
	m1->addToFriction(f);
	m2->addToFriction(-f);
}

void Link::updateStop()
{
	const double d = m2->getY() - m1->getY();
	if (d > s)
		return;

	const double f = k * (d - l) + z * (m2->getSpeed() - m1->getSpeed());
	m1->addToFriction(f);
	m2->addToFriction(-f);
}
