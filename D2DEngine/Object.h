#pragma once
#include "ReferenceCounter.h"

class Object : public ReferenceCounter
{
private:
	unsigned int instanceID;

public:
	Object();
	virtual ~Object();

	unsigned int GetInstanceID();
};

