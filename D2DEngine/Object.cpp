#include "pch.h"
#include "Object.h"

static unsigned int instance = 0;

Object::Object() {
	instanceID = instance++;
}

Object::~Object() {

}

unsigned int Object::GetInstanceID() {
	return instanceID;
}