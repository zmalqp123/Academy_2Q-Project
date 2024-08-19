#include "pch.h"
#include "FiniteStateMachine.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (auto& state : m_pStates)
	{
		//statd.second안에 Transition들도 삭제해야함. class만들고 삭제.
		delete state.second;
	}
	m_pStates.clear();
}

void FiniteStateMachine::Update(float deltaTime)
{
	if (m_pCurrState != m_pNextState)
	{
		if (m_pCurrState != nullptr)
		{
			m_pCurrState->Exit();
		}
		m_pCurrState = m_pNextState;
		m_pCurrState->Enter();
	}
	else
	{
		m_pCurrState->Update(deltaTime);
	}
}

void FiniteStateMachine::SetFloatParam(const std::string stateName, float value)
{
	m_pParams[stateName]->SetFloat(value);
}

void FiniteStateMachine::SetIntParam(const std::string stateName, int value)
{
	m_pParams[stateName]->SetInt(value);
}

void FiniteStateMachine::SetTriggerParam(const std::string stateName)
{
	m_pParams[stateName]->SetTrigger();
}

void FiniteStateMachine::SetBoolParam(const std::string stateName, bool value)
{
	m_pParams[stateName]->SetBool(value);
}

void FiniteStateMachine::SetState(const std::string stateName)
{
	m_pNextState = m_pStates[stateName];
}


void FSMParameter::SetFloat(float value)
{
	m_param.floatValue = value;
}

void FSMParameter::SetInt(int value)
{
	m_param.intValue = value;
}

void FSMParameter::SetTrigger()
{
	// trigger!
}

void FSMParameter::SetBool(bool value)
{
	m_param.boolValue = value;
}
