#ifndef _TEXT_FIELD_H
#define _TEXT_FIELD_H

class Transform;

#include "Vector3f.h"
#include <string>

class TextField
{
private:
	Transform* mTransform;
	std::string mText;
	float mFontSize;
	float mSize;
	float mEolSpacing;

public:
	TextField();
	TextField(float x, float y, float z);
	TextField(const std::string &text);
	TextField(float x, float y, float z, const std::string &text);
	TextField(const Vector3f &position, const std::string &text);
	TextField(const TextField &rhs);
	~TextField();

	//accessors
	std::string GetText() const;
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	Vector3f GetPosition() const;
	Transform* GetTransform() const;
	float GetTextLength() const;
	float GetFontSize() const;
	float GetSize() const;
	float GetEolSpacing() const;
	bool IsEmptyText() const;

	//setters
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetPosition(float x, float y, float z);
	void SetPosition(const Vector3f &position);
	void SetFontSize(float size);
	void SetSize(float size);
	void SetEolSpacing(float eolSpacing);

	void SetText(const std::string &text);
	void AppendText(const std::string &text);
	void ClearText();

	void CopyDataFrom(const TextField& other);

private:
	void Initialize(float x, float y, float z, const std::string &text);
};

#endif