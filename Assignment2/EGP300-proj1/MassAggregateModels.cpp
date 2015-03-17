#include "MassAggregateModels.h"
#include "Model.h"

MassAggregateModels::MassAggregateModels()
{
	mBad = true;
}
MassAggregateModels::MassAggregateModels(Model* particle, Model* rod, Model* cable, Model* spring, Model* bungee)
{
	modelParticle = particle;
	modelRod = rod;
	modelCable = cable;
	modelSpring = spring;
	modelBungee = bungee;

	mBad = (modelParticle == nullptr || modelRod == nullptr || modelCable == nullptr || modelSpring == nullptr || modelBungee == nullptr);
}
MassAggregateModels::MassAggregateModels(const MassAggregateModels &rhs)
{
	modelParticle = rhs.modelParticle;
	modelRod = rhs.modelRod;
	modelCable = rhs.modelCable;
	modelSpring = rhs.modelSpring;
	modelBungee = rhs.modelBungee;

	mBad = (modelParticle == nullptr || modelRod == nullptr || modelCable == nullptr || modelSpring == nullptr || modelBungee == nullptr);
}
MassAggregateModels::~MassAggregateModels()
{

}

//accessors
bool MassAggregateModels::IsBad() const
{
	return mBad;
}