#ifndef FIXED_ARRAY_H
#define FIXED_ARRAY_H


template<class T>
class FixedArray
{
private:
	int mCapacity;
	T* mData;

	FixedArray(int capacity);
	~FixedArray();
	bool contains(const T &data);
	int indexOf(const T &data);
	T operator[](int index);
};


template<class T>
FixedArray<T>::FixedArray(int capacity)
{
	mCapacity = capacity;
	mData = new T[capacity];
}

template<class T>
FixedArray<T>::~FixedArray()
{
	delete [] mData;
}

template<class T>
bool FixedArray<T>::contains(const T &data)
{
	bool found = false;
	for (int i = 0; i < mCapacity; i++)
	{
		if (mData[i] == data)
		{
			found = true;
			break;
		}
	}
	return found;
}

template<class T>
int FixedArray<T>::indexOf(const T &data)
{
	int index = -1;
	for (int i = 0; i < mCapacity; i++)
	{
		if (mData[i] == data)
		{
			index = i;
			break;
		}
	}
	return index;
}


template<class T>
T FixedArray<T>::operator[](int index)
{
	return mData[index];
}

#endif