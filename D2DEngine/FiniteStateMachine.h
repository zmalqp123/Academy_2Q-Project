#pragma once
#include "Component.h"
#include "Action.h"
#include <string>
#include <map>
class FSMState;
class FSMTransition;
class FSMParameter;

class FiniteStateMachine : public Component
{
public:
	FiniteStateMachine() = default;
	virtual ~FiniteStateMachine();

public:
	FSMState* m_pCurrState = nullptr;  // 현재 상태	
	FSMState* m_pNextState = nullptr;	// 다음 상태

	std::map<std::string, FSMState*> m_pStates;
	std::map<std::string, FSMParameter*> m_pParams;

	virtual void Update(float deltaTime);
	void SetFloatParam(const std::string stateName, float value);
	void SetIntParam(const std::string stateName, int value);
	void SetTriggerParam(const std::string stateName);
	void SetBoolParam(const std::string stateName, bool value);
	void SetState(const std::string stateName);

	template<typename T>
	void CreateParameter(const std::string paramName, FSMState* From, FSMState* to) {
		T* pParam = new T(this, paramName);
		m_pParams.insert(std::make_pair(pParam->GetName(), pParam));
	}

	template<typename T>
	T* CreateState(const std::string stateName) {
		T* pState = new T(this, stateName);
		m_pStates.insert(std::make_pair(pState->GetName(), pState));
		return pState;
	}

	template<typename T>
	void CreateTransition(const FSMState* from, const FSMState* to) {
		T* pTransition = new T(from, to);
	}
};

class FSMState
{
protected:
	FiniteStateMachine* fsm;
	std::string name;
	std::vector<FSMTransition*> transitions;
public:
	FSMState(FiniteStateMachine* _fsm, std::string _name) {
		fsm = _fsm;
		name = _name;
	}
	virtual ~FSMState() { }

	virtual void Enter() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Exit() = 0;

	std::string GetName() { return name; }
};

class FSMTransition
{
	FSMState* fromState;
	FSMState* toState;
public:
	FSMTransition(FSMState* from, FSMState* to) : fromState(from), toState(to) {}
};

class FSMParameter
{
	union param
	{
		int intValue;
		float floatValue;
		bool boolValue;
	};

	param m_param = { 0 };
	std::string m_name;
	FiniteStateMachine* fsm;
public:
	FSMParameter(FiniteStateMachine* _fsm, std::string _name)
	{
		fsm = _fsm;
		m_name = _name;
	}

	void SetFloat(float value);
	void SetInt(int value);
	void SetTrigger();
	void SetBool(bool value);
};
