#include "Model.h"
#include "Planet.h"
#include "Transform.h"

//constructor
Planet::Planet(Model* model)
	:DisplayObject3D(model)
{
	mRigidBody = new Rigidbody(mTransform);
	mOriginalData = new Rigidbody(mTransform, *mRigidBody);
	mName = "no name";
	mLabel = new TextField(mTransform->GetPosition(), mName);
}
Planet::~Planet()
{
	delete mRigidBody;
	mRigidBody = nullptr;

	delete mOriginalData;
	mOriginalData = nullptr;

	delete mLabel;
	mLabel = nullptr;
}

//update functions
void Planet::FixedUpdate(double t) const
{
	mRigidBody->FixedUpdate(t);
}
void Planet::FinishUpdate() const
{
	//mRigidBody->FinishUpdate();
	mLabel->SetPosition(mTransform->GetPosition() - (Vector3f::unitX * 0.75f) + (Vector3f::unitY * mTransform->GetScale().Average() + Vector3f::unitY));
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
void Planet::GetDebugInfo(std::string &out) const
{
	out = mName + " Debug Information\n"
		+ "Position: " + mRigidBody->GetPosition().ToString() + "km\n"
		+ "Velocity: " + mRigidBody->GetVelocity().ToString() + "km/s\n"
		+ "Acceleration: " +mRigidBody->GetVelocity().ToString() + "km/s^2\n"
		+ "Mass: " +std::to_string(mRigidBody->GetMass()) +"kg";
}

//setters
void Planet::SetName(const std::string &name)
{
	mName = name;
	mLabel->SetText(name);
}
void Planet::Reset()
{
	mRigidBody->CopyDataFrom(*mOriginalData);
	mLabel->SetPosition(mTransform->GetPosition() - (Vector3f::unitX * 0.75f) + (Vector3f::unitY * 2.0f));
}
void Planet::SetOriginalDataToCurrent()
{
	mOriginalData->CopyDataFrom(*mRigidBody);
}
void Planet::SetGravity(float gravity)
{
	mGravity = gravity;
}

//drawing text and planet
void Planet::DrawAll(DrawData* drawData)
{
	this->Draw(drawData);
	drawData->textRenderer->DrawTextField(mLabel, *drawData->frustum, *drawData->view);
}
