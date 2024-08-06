#include "WinApp2.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/SpriteAnimationAsset.h"
#include "../D2DEngine/SpriteAnimation.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SpriteRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/PublicData.h"
#include "../D2DEngine/InputManager.h"
#include "../D2DEngine/TextRenderer.h"
#include "../D2DEngine/SoundManager.h"  // SoundManager 헤더 파일 포함
#include "../D2DEngine/ImageUIRenderer.h"
#include "WaveSystem.h"
#include "testChar.h"

void WinApp2::Initialize(HINSTANCE hInstance, int nCmdShow, float x, float y)
{
    // 기본 초기화 + 카메라 생성
    __super::Initialize(hInstance, nCmdShow, x, y);

    scene = new Scene();
    auto camera = scene->CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    scene->SetMainCamera(pCam);

    // 사운드 초기화 및 로드
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");

    soundVolume = 0.5f;
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", soundVolume);

    // 사운드를 재생하도록 호출
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true); // true로 설정하면 루프 재생

    // 메뉴바 
    auto obj = scene->CreateGameObject<GameObject>();
    auto spr = obj->CreateComponent<SpriteRenderer>();
    spr->LoadTexture(L"../Resource/BG/BG.png");

    auto UI = scene->CreateGameObject<GameObject>();
    auto Image = UI->CreateComponent<ImageUIRenderer>();
    UI->transform->type = Type::Ui;
    UI->transform->pos.rectposition = { {1920 - 1560,0} ,{1560,200} };
    Image->LoadTexture(L"../Resource/BG/BG.png");



    // 몬스터 테스트 
    /*auto monsterObj = scene->CreateGameObject<GameObject>();
    auto monsterSpr = monsterObj->CreateComponent<SpriteRenderer>();
    monsterSpr->LoadTexture(L"../Resource/ken.png");*/
   
    // 테스트
    auto spwan = scene->CreateGameObject<GameObject>();
    auto wave = spwan->CreateComponent<WaveSystem>();

    wave->scene = scene;
    // 몬스터 테스트 
    // auto monSpawn = scene->CreateGameObject<GameObject>();
    // auto monsterpool = monSpawn->CreateComponent<testChar>();

    // 웨이브 오브젝트 vector push_back
    // wave->m_Monster.push_back(monsterpool);
    
    //// 터렛 Ui
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");

    //// 경험치 게이지 바 Ui
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");

    //// Hp 게이지 바 Ui
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");

    //// 골드 보유량 Ui
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");

    //// 강화 버튼 
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");

    //// 수확 버튼
    //auto obj = scene->CreateGameObject<GameObject>();
    //auto spr = obj->CreateComponent<SpriteRenderer>();
    //spr->LoadTexture(L"../Resource/BG/BG.png");

    //auto UI = scene->CreateGameObject<GameObject>();
    //auto Image = UI->CreateComponent<ImageUIRenderer>();
    //UI->transform->type = Type::Ui;
    //UI->transform->pos.rectposition = { {0,0} ,{1560,200} };
    //Image->LoadTexture(L"../Resource/BG/BG.png");

}

void WinApp2::Update(float deltaTime)
{
    __super::Update(deltaTime);

    scene->Update(deltaTime);
   // scene->cam->transform->m_RelativeLocation += Vector2(-1.f,0.f) * 100.f * deltaTime;
    // 사운드 업데이트
    SoundManager::GetInstance().Update();
}

void WinApp2::Render(D2DRenderer* _render)
{
    __super::Render(_render);
    scene->Render(_render);
}

void WinApp2::Uninitialize()
{
    // 사운드 종료
    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
    __super::Uninitialize();
}
