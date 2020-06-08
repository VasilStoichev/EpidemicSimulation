#include "PersonController.h"

void PersonController::repelPeople()
{
	for (std::list<Person*>::iterator p1 = people.begin(); p1 != people.end(); ++p1)
	{
		std::list<Person*>::iterator p2 = p1;
		++p2;
		for (p2; p2 != people.end(); ++p2)
		{
			vec2 dir = (*p1)->getLocation() - (*p2)->getLocation();
			float distSquared = length2(dir);
			if (distSquared < REPEL_RADIUS)
			{
				float f = (REPEL_RADIUS / distSquared - 1.0f) * 0.05f;
				dir = normalize(dir) * f;
				float y = dir.y;
				(*p1)->setAcceleration((*p1)->getAcceleration() + vec2(0, y));
				(*p2)->setAcceleration((*p2)->getAcceleration() - vec2(0, y));
			}
		}
	}
}

void PersonController::spread()
{
	for (std::list<Person*>::iterator p1 = people.begin(); p1 != people.end(); ++p1)
	{
		std::list<Person*>::iterator p2 = p1;
		++p2;
		for (p2; p2 != people.end(); ++p2)
		{
			float maskReduction = 1.0f;
			vec2 dir = (*p1)->getLocation() - (*p2)->getLocation();
			float distSquared = length2(dir);
			float r = Rand::randFloat(1.0f);
			if (distSquared <= this->infectionRadius)
			{
				if ((*p1)->getState() == Infected && (*p1)->getInfectedSince() > 1 && (*p2)->getState() == Susceptible)
				{
					if ((*p1)->hasMask()) maskReduction = 1.0f - maskEffect;
					if (r < this->infectionChance * maskReduction)
					{
						this->SIRcount.infected++;
						this->SIRcount.susceptible--;
						(*p2)->setState(Infected);
					}
				}
				if ((*p1)->getState() == Susceptible && (*p2)->getInfectedSince() > 1 && (*p2)->getState() == Infected)
				{
					if ((*p2)->hasMask()) maskReduction = 1.0f - maskEffect;
					if (r < this->infectionChance * maskReduction)
					{
						this->SIRcount.infected++;
						this->SIRcount.susceptible--;
						(*p1)->setState(Infected);
					}
				}
			}
		}
	}
}

PersonController::PersonController()
{
	this->personCount = 0;
	this->infectionChance = 0;
	this->infectionDuration = 0;
}

PersonController::~PersonController()
{
	//this->people.~list();
}

void PersonController::addExam()
{
	int infectedPosition = Rand::randUint(115);
	int position = 0;
	this->personCount = 144;
	SIRGroup state;
	SIRcount.infected++;
	for (float x = 50.0f; x <= 1200.0f; x+=50.0f)
	{
		for (float y = 50.0f; y <= 300.0f; y+=50.0f)
		{
			if (position == infectedPosition)
			{
				state = Infected;
			}
			else
			{
				state = Susceptible;
			}
			this->people.push_back(new Person(vec2(x, y), state,this->simType,false));
			position++;
		}
	}
}

void PersonController::addPeople(unsigned _personCount, unsigned _infected,unsigned _masked)
{
	//Adds _personCount people, _infected of which start infected, _masked wear masks
	int leftInfected = _infected;
	SIRGroup state = Infected;
	this->personCount += _personCount;
	int leftMasked = _masked;
	
	this->SIRcount.susceptible += _personCount - _infected;
	this->SIRcount.infected += _infected;
	for (int i = 0; i < _personCount; i++)
	{
		if (leftInfected == 0) state = Susceptible;

		float x = Rand::randFloat(-20.0f, 0.0f);
		float y = Rand::randFloat(50.0f,app::getWindowHeight() / 2 - 40.0f);

		people.push_back(new Person(vec2(x, y), state,this->simType,leftMasked>0));
		leftInfected--;
		leftMasked--;
	}
}

void PersonController::init(float _infectionChance, unsigned _infectionDuration,unsigned _spreadInterval, float _maskEffect,float _infectionRadius, std::string _simType)
{
	Rand::randomize();
	this->infectionChance = _infectionChance;
	this->infectionDuration =_infectionDuration != 0 ?  _infectionDuration : INT_MAX;
	this->simType = _simType;
	this->maskEffect = _maskEffect;
	this->infectionRadius = (float)(_infectionRadius*_infectionRadius);
	this->spreadInterval = _spreadInterval;
}

void PersonController::update()
{
	if(this->simType !="Exam")this->repelPeople();
	if (app::getElapsedFrames() %(this->spreadInterval * 30) == 0) this->spread();


	for (std::list<Person*>::iterator p = this->people.begin(); p!=this->people.end();)
	{
		bool stateChangedThisUpdate = false;
		(*p)->update();
		if ((*p)->getInfectedSince() > this->infectionDuration)
		{
			(*p)->setState(Recovered);
			this->SIRcount.infected--;
			this->SIRcount.recovered++;
			stateChangedThisUpdate = true;
		}
		//Person exits the corridor
		if ((*p)->getLocation().x > app::getWindowWidth() - 20.0f)
		{
			if ((*p)->getState() == Infected && !stateChangedThisUpdate)
			{
				this->SIRcount.infected--;
				this->SIRcount.recovered++;
			}
			auto p1 = p;
			p++;
			this->people.erase(p1);
		}
		else
		{
			p++;
		}
		
	}
}

void PersonController::draw()
{
	for (auto p : people)
	{
		p->draw();
	}
}

void PersonController::reset()
{
	this->people.clear();
	this->personCount = 0;
	this->SIRcount.infected = 0;
	this->SIRcount.susceptible = 0;
	this->SIRcount.recovered = 0;
}

CountByGroup PersonController::getCount()
{
	return this->SIRcount;
}

unsigned PersonController::getPersonCount()
{
	return this->personCount;
}

CountByGroup::CountByGroup()
{
	this->susceptible = 0;
	this->infected = 0;
	this->recovered = 0;
}
