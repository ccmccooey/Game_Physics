/*
class AggregateFactory 
{
public:
	virtual ~AggregateFactory() {}
	virtual MassAggregate* BuildAggregate() = 0;
};

class CubeBuilder : public AggregateFactory 
{
public:
	virtual MassAggregate* BuildAggregate() 
	{
		MassAggregate* aggregate = new MassAggregate(...);
		aggregate.addLink(...);
		aggregate.addParticle(...);
		return aggregate;
	};
};

enum 
{
	BUILD_CUBE = 0,
	BUILD_TETRA,
	BUILD_RING,
	BUILD_CLOTH,
	NUM_BUILDERS
};
AggregateFactory *kAggregates[NUM_BUILDERS] = 
{
	new CubeBuilder(...),
	new TetraBuilder(...),
	new ClothBuilder(...)
};

MassAggregate* myAggregate = kAggregates[BUILD_CUBE]->BuildAggregate();*/