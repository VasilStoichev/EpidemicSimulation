#include "Person.h"
#include "cinder/svg/Svg.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

void Person::correctOutOfBounds()
{
	float x = this->location.x;
	float y = this->location.y;

	//change direction if near top or bottom wall
	if ((y < 50.0f && y < 0.0f) || (y > app::getWindowHeight() / 2.0f - 50.0f && y > 0.0f))
	{
		this->velocity.y = (this->velocity.y * -1.0f);
	}
}

void Person::correctSpeed()
{
	float velocityLengthSqared = length2(this->velocity);
	vec2 velocityNormalized = normalize(this->velocity);

	if (velocityLengthSqared > MAX_SPEED * MAX_SPEED)
	{
		this->velocity = velocityNormalized *this->speedVariation* MAX_SPEED;
	}
	if (velocityLengthSqared < MIN_SPEED * MIN_SPEED)
	{
		this->velocity = velocityNormalized * this->speedVariation * MIN_SPEED;
	}

	//make sure Person is moving forward every second
	if (app::getElapsedFrames() % 30 == 0)
	{
		if (this->velocity.x < 0.3f)
		{
			this->velocity.x = Rand::randFloat(0.3f, 0.5f);
		}
		if (this->velocity.x > 0.9f)
		{
			this->velocity.x = Rand::randFloat(0.7f, 0.9f);
		}
		if (this->velocity.y < -0.6f)
		{
			this->velocity.y = Rand::randFloat(-0.6f, -0.0f);
		}
		if (this->velocity.y > 0.6f)
		{
			this->velocity.y = Rand::randFloat(0.0f, 0.6f);
		}
	}
}

Person::Person(vec2 _location, SIRGroup _state,std::string _simType,bool _mask)
{
	this->location = _location;
	this->state = _state;
	this->simType = _simType;
	this->mask = _mask;

	float x = Rand::randFloat(0.3f, 0.9f);
	float y = Rand::randFloat(-0.6f, 0.6f);
	this->velocity = vec2(x, y);

	this->radius = PERSON_RADIUS;
	this->infectedSince = (_state == Infected);
	this->acceleration = vec2(0, 0);
	this->speedVariation = Rand::randFloat(0.5f, 0.8f);
}

void Person::update()
{
	if (this->simType != "Exam")
	{
		this->acceleration += vec2(0.05, 0);
		this->velocity += this->acceleration;
		this->correctSpeed();

		this->location += this->velocity;
		this->correctOutOfBounds();

		this->acceleration = { 0, 0 };
	}
	if (this->infectedSince > 0 && app::getElapsedFrames() % 30 == 0)
	{
		this->infectedSince++;
	}
}

void Person::draw()
{
	
	if (state == Infected)
	{
		gl::color(Color(1, 0, 0));
	}
	else if (state == Recovered)
	{
		gl::color(Color(0.4, 0.4, 0.4));
	}
	else
	{
		gl::color(Color(1, 1, 1));
	}
	
	gl::drawSolidCircle(this->location, this->radius);
	if(mask)
	{
		gl::color(Color(0.50, 0.91, 0.75));
		gl::lineWidth(4);
		gl::drawLine(vec2(this->location.x - this->radius, this->location.y), vec2(this->location.x + this->radius, this->location.y));
	}
}

vec2 Person::getLocation()
{
	return this->location;
}

vec2 Person::getAcceleration()
{
	return this->acceleration;
}

vec2 Person::getVelocity()
{
	return this->velocity;
}

SIRGroup Person::getState()
{
	return this->state;
}

unsigned Person::getInfectedSince()
{
	return this->infectedSince;
}

bool Person::hasMask()
{
	return this->mask;
}

void Person::setLocation(vec2 _location)
{
	this->location = _location;
}

void Person::setAcceleration(vec2 _acceleration)
{
	this->acceleration = _acceleration;
}

void Person::setVelocity(vec2 _velocity)
{
	this->velocity = _velocity;
}

void Person::setState(SIRGroup _state)
{
	if (_state == Infected) this->infectedSince = 1;
	if (_state == Recovered) this->infectedSince = 0;
	this->state = _state;
}
