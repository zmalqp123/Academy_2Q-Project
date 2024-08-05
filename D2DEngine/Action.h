#pragma once
#include <vector>
template<typename T>
class Action
{
private:
	std::vector<T*> objs;
	std::vector<void(T::*)()> functions;
public:
	void AddAction(T* obj, void(T::*func)()) {
		objs.push_back(obj);
		functions.push_back(func);
	}

	void Excute() {
		int num = objs.size();
		for (int i = 0; i < num; i++) {
			(*(objs[i]).*(functions[i]))();
		}
	}

	void RemoveActionIndex(int index) {
		
	}

};

template<typename T, typename P1>
class ActionWithParam {
	std::vector<T*> objs;
	std::vector<void(T::*)(P1)> functions;
public:
	void AddAction(T* obj, void(T::* func)(P1)) {
		objs.push_back(obj);
		functions.push_back(func);
	}

	void Excute(P1 param) {
		int num = objs.size();
		for (int i = 0; i < num; i++) {
			(*(objs[i]).*(functions[i]))(param);
		}
	}

	void RemoveActionIndex(int index) {

	}
};

