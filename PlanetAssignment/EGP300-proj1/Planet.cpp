#include "Model.h"
#include "Planet.h"
#include "Transform.h"

//constructor
Planet::Planet(Model* model)
	:DisplayObject3D(model)
{
	mRigidBody = new Rigidbody(mTransform);
	mName = "no name";
	mLabel = new TextField(mTransform->GetPosition(), mName);

}
Planet::~Planet()
{
	delete mRigidBody;
	mRigidBody = nullptr;

	delete mLabel;
	mLabel = nullptr;
}


void Planet::FixedUpdate(double t) const
{
	mRigidBody->FixedUpdate(t);
}
void Planet::FinishUpdate() const
{
	mRigidBody->FinishUpdate();
	mLabel->SetPosition(mTransform->GetPosition() - (Vector3f::unitX * 0.75f) + (Vector3f::unitY * 2.0f));
}
void Planet::SetGravity(float gravity)
{
	mGravity = gravity;
}

//accessors
Rigidbody* Planet::GetRigidBody() const
{
	return mRigidBody;
}
std::string Planet::GetName() const
{
	return mName;
}
float Planet::GetGravity() const
{
	return mGravity;
}
TextField* Planet::GetTextField() const
{
	return mLabel;
}

//setters
void Planet::SetName(const std::string &name)
{
	mName = name;
	mLabel->SetText(name);
}

//drawing text and planet
void Planet::DrawAll(DrawData* drawData)
{
	this->Draw(drawData);
	drawData->textRenderer->DrawTextField(mLabel, *drawData->frustum, *drawData->view);
}
