#include "ParticleContactResolver.h"
#include "ParticleContact.h"


ParticleContactResolver::ParticleContactResolver()
{

}
ParticleContactResolver::~ParticleContactResolver()
{

}

void ParticleContactResolver::MultiPassResolveContacts(ParticleContact **contacts, int num_contacts, float duration)
{
	int processed = 0;
	while (processed < mPasses) 
	{
		float min_separating_velocity = std::numeric_limits<float>::max();
		int candidate = 0;
		for (int x = 0; x < num_contacts; ++x) 
		{
			// Find the collision with greatest velocity
			float separating_velocity = contacts[x]->SeparatingVelocity();

			if (separating_velocity <= min_separating_velocity &&
				(separating_velocity < 0.0f || contacts[x]->GetPenetrationDepth() > 0)) 
			{
				min_separating_velocity = separating_velocity;
				candidate = x;
			}
		}

		// No collision found
		if (min_separating_velocity > 0.0f) 
		{
			break;
		}

		Particle *actor_a = contacts[candidate]->GetActorA();
		Particle *actor_b = contacts[candidate]->GetActorB();

		//Vector3f const & move_a = contacts[candidate]->actor_A_displacement();
		//Vector3f const & move_b = contacts[candidate]->actor_B_displacement();

		Vector3f const & move_a = contacts[candidate]->GetActorADisplacement();
		Vector3f const & move_b = contacts[candidate]->GetActorBDisplacement();

		// Process the best candidate
		contacts[candidate]->Resolve(duration);

		// Update all of the other collisions
		for (int x = 0; x < num_contacts; ++x) 
		{
			// Note - this loop includes the contact that was just resolved!
			ParticleContact *contact = contacts[x];
			if (contact->GetActorA() == actor_a)
			{
				contact->SetPenetrationDepth(contact->GetPenetrationDepth() - Vector3f::DotProduct(move_a, contact->GetContactNormal()));
			}
			if (contact->GetActorA() == actor_b)
			{
				contact->SetPenetrationDepth(contact->GetPenetrationDepth() - Vector3f::DotProduct(move_b, contact->GetContactNormal()));
			}

			if (contact->GetActorB()) 
			{
				if (contact->GetActorB() == actor_a) 
				{
					contact->SetPenetrationDepth(contact->GetPenetrationDepth() + Vector3f::DotProduct(move_a, contact->GetContactNormal()));
				}
				if (contact->GetActorB() == actor_b)
				{
					contact->SetPenetrationDepth(contact->GetPenetrationDepth() + Vector3f::DotProduct(move_b, contact->GetContactNormal()));
				}
			}
			++processed;
		}
	}
}