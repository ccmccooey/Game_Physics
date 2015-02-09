#include "TextField.h"
#include "Transform.h"

//constructors
TextField::TextField()
{
	Initialize(0.0f, 0.0f, 0.0f, "");
}
TextField::TextField(float x, float y, float z)
{
	Initialize(x, y, z, "");
}
TextField::TextField(const std::string &text)
{
	Initialize(0.0f, 0.0f, 0.0f, text);
}
TextField::TextField(float x, float y, float z, const std::string &text)
{
	Initialize(x, y, z, "");
}
TextField::TextField(const Vector3f &position, const std::string &text)
{
	Initialize(position.x, position.y, position.z, text);
}
TextField::TextField(const TextField &rhs)
{
	CopyDataFrom(rhs);
}
TextField::~TextField()
{
	delete mTransform;
}

void TextField::Initialize(float x, float y, float z, const std::string &text)
{
	mTransform = new Transform(Vector3f(x, y, z));
	mText = text;
	mFontSize = 16;
}

//accessors
std::string TextField::GetText() const
{
	return mText;
}
float TextField::GetX() const
{
	return mTransform->GetPosition().x;
}
float TextField::GetY() const
{
	return mTransform->GetPosition().y;
}
float TextField::GetZ() const
{
	return mTransform->GetPosition().z;
}
Vector3f TextField::GetPosition() const
{
	return mTransform->GetPosition();
}
Transform* TextField::GetTransform() const
{
	return mTransform;
}
float TextField::GetTextLength() const
{
	return (float)mText.length() * mFontSize;
}
float TextField::GetFontSize() const
{
	return mFontSize;
}

//setters
void TextField::SetX(float x)
{
	mTransform->SetX(x);
}
void TextField::SetY(float y)
{
	mTransform->SetY(y);
}
void TextField::SetZ(float z)
{
	mTransform->SetZ(z);
}
void TextField::SetPosition(float x, float y, float z)
{
	mTransform->SetPosition(x, y, z);
}
void TextField::SetPosition(const Vector3f &position)
{
	mTransform->SetPosition(position);
}
void TextField::SetText(const std::string &text)
{
	mText = text;
}
void TextField::AppendText(const std::string &text)
{
	mText += text;
}
void TextField::ClearText()
{
	mText = "";
}
void TextField::SetFontSize(float size)
{
	mFontSize = size;
}
void TextField::CopyDataFrom(const TextField& other)
{
	mTransform->CopyTransformData(*other.mTransform);
	mText = other.mText;
	mFontSize = other.mFontSize;
}


	