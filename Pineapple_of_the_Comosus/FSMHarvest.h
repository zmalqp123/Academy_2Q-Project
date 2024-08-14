//#pragma once
//#include "../D2DEngine/FiniteStateMachine.h"
//#include <iostream>
//
//// 기본 상태 (대기 상태)
//class TentacleDefault : public FSMState
//{
//public:
//    TentacleDefault(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Tentacle is in default state..." << std::endl;
//        // 기본 상태에서의 초기화 작업
//    }
//
//    void Update(float deltaTime) override {
//        // 기본 상태에서의 로직 처리
//        // 특정 조건이 충족되면 다음 상태로 전이
//        if () {
//            fsm->SetState("TentacleDownState");
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Exiting default state." << std::endl;
//        // 기본 상태 종료 시 처리할 코드
//    }
//};
//
//// 촉수가 내려오는 상태
//class TentacleDownState : public FSMState
//{
//public:
//    TentacleDownState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Tentacle is moving down..." << std::endl;
//        // 촉수가 내려오는 애니메이션 시작 코드
//    }
//
//    void Update(float deltaTime) override {
//        // 촉수가 내려오는 중의 로직 처리
//        if (/* 촉수가 다 내려왔다면 */) {
//            fsm->SetState("TentacleUpState");
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Tentacle has reached the pineapple." << std::endl;
//        // 상태 종료 시 처리할 코드
//    }
//};
//
//// 파인애플을 가져가는 상태
//class TentacleUpState : public FSMState
//{
//public:
//    TentacleUpState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Tentacle is moving up with the pineapple..." << std::endl;
//        // 촉수가 올라가는 애니메이션 시작 코드
//    }
//
//    void Update(float deltaTime) override {
//        // 촉수가 올라가는 중의 로직 처리
//        if (/* 촉수가 다 올라갔다면 */) {
//            // 파인애플 위치가 화면위로 사라지면 파인애플 스프라이트 삭제
//            // 모든 터렛 환불 골드 = 골드 + 환불 금액 
//            // 수확 보상 팝업 상태로 전환
//            fsm->SetState("ShowPopupState");
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Tentacle has taken the pineapple." << std::endl;
//        // 상태 종료 시 처리할 코드
//    }
//};
//
//// 팝업이 뜨는 상태
//class ShowPopupState : public FSMState
//{
//public:
//    ShowPopupState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Showing popup..." << std::endl;
//        // 팝업 표시 코드
//    }
//
//    void Update(float deltaTime) override {
//        // 팝업이 표시되는 동안의 로직 처리
//        if (/* 팝업이 다 떴다면 */) {
//            // 팝업 표시 후 다른 상태로 전환하거나 유지
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Popup has been shown." << std::endl;
//        // 상태 종료 시 처리할 코드
//    }
//};
//
//// 파인애플 가져오는 상태 
//class ShowPopupState : public FSMState
//{
//public:
//    ShowPopupState(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {}
//
//    void Enter() override {
//        std::cout << "Showing popup..." << std::endl;
//        // 팝업 표시 코드
//    }
//
//    void Update(float deltaTime) override {
//        // 팝업이 표시되는 동안의 로직 처리
//        if (/* 팝업이 다 떴다면 */) {
//            // 팝업 표시 후 다른 상태로 전환하거나 유지
//        }
//    }
//
//    void Exit() override {
//        std::cout << "Popup has been shown." << std::endl;
//        // 상태 종료 시 처리할 코드
//    }
//};
//
//// FSMHarvest 클래스 정의
//class FSMHarvest : public FSMState
//{
//public:
//    FSMHarvest(FiniteStateMachine* fsm, const std::string& name) : FSMState(fsm, name) {
//        
//    }
//
//    void Enter() override {
//        // 초기 상태로 설정
//        fsm->SetState("TentacleDefault");
//    }
//
//    void Update(float deltaTime) override {
//        if (fsm->m_pCurrState) {
//            fsm->m_pCurrState->Update(deltaTime);
//        }
//    }
//
//    void Exit() override {
//        // 상태 종료 시 처리할 코드
//    }
//};
