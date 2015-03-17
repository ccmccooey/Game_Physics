#ifndef _MASS_AGGREGATE_MODELS_H
#define _MASS_AGGREGATE_MODELS_H

class Model;

//this struct contains all the graphical models used to represent each of the different physics links and the particle
struct MassAggregateModels
{
public:
	Model* modelParticle;
	Model* modelRod;
	Model* modelCable;
	Model* modelSpring;
	Model* modelBungee;

private:
	bool mBad;

public:
	MassAggregateModels();
	MassAggregateModels(Model* particle, Model* rod, Model* cable, Model* spring, Model* bungee);
	MassAggregateModels(const MassAggregateModels &rhs);
	~MassAggregateModels();

	//accessors
	bool IsBad() const;
};

#endif
