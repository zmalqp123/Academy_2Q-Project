#include "GameScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "GameScene.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/Camera.h"
#include "../D2DEngine/SoundManager.h"
#include "../D2DEngine/InputManager.h"
#include <iostream>
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/SpriteRenderer.h"
#include"../D2DEngine/ImageUIRenderer.h"
#include "../D2DEngine/Button.h"
#include"../D2DEngine/SceneManager.h"

GameScene::GameScene() {
    std::cout << "GameScene Constructor" << std::endl;
}

GameScene::~GameScene() {
    std::cout << "GameScene Destructor" << std::endl;
}

void GameScene::Start() {
    std::cout << "Entering GameScene" << std::endl;

    auto camera = CreateGameObject<GameObject>();
    auto pCam = camera->CreateComponent<Camera>();
    SetMainCamera(pCam);

    // ���� �ʱ�ȭ �� �ε�
    SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3");
    SoundManager::GetInstance().SetVolume(L"backgroundMusic", 0.5f);
    SoundManager::GetInstance().PlaySoundW(L"backgroundMusic", true);

    // ��� �̹���
    auto bgObj = CreateGameObject<GameObject>();
    auto bgSpr = bgObj->CreateComponent<SpriteRenderer>();
    bgSpr->LoadTexture(L"../Resource/morningBG.png");

    // �޴���
    auto uiObj = CreateGameObject<GameObject>();
    auto uiImage = uiObj->CreateComponent<ImageUIRenderer>();
    uiObj->transform->type = Type::Ui;
    uiObj->transform->pos.rectposition = { {180,0} ,{1560 + 180,200} };
    uiImage->LoadTexture(L"../Resource/BG/BG.png");

    // ���̺� �ý���
    auto waveObj = CreateGameObject<GameObject>();
    waveSystem = waveObj->CreateComponent<WaveSystem>();
    waveSystem->scene = this;

    // DayNightCycleComponent ���� �� ���� ������Ʈ�� �߰�
    auto nightObj = CreateGameObject<GameObject>();
    nightSystem = nightObj->CreateComponent<DayNightCycle>();

    // ���� ������Ʈ ������ �ּ� ����
    nightSystem->waveSystem = waveSystem;


    // �ͷ� UI
    float spacing = 20.0f;
    float startX = 0.f;
    float width = 120.f;

    for (size_t i = 0; i < 6; i++) {
        auto turretUI = CreateGameObject<GameObject>();
        auto turretImage = turretUI->CreateComponent<Button>();
        startX = i * (spacing + width);
        turretUI->transform->SetParent(uiObj->transform);
        turretUI->transform->type = Type::Ui;
        turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };
        turretImage->LoadTexture(L"../Resource/turret.png");
    }

    // HP �� MP �� UI

    auto hpBarObj = CreateGameObject<GameObject>();
    auto hpBarImage = hpBarObj->CreateComponent<ImageUIRenderer>();
    hpBarObj->transform->SetParent(uiObj->transform);
    hpBarObj->transform->type = Type::Ui;
    hpBarObj->transform->pos.rectposition = { {20.f,0.f} ,{20.f + 820.f,20.f} };
    hpBarUi = hpBarObj->CreateComponent<Hpbar>();
    hpBarUi->ImageRender = hpBarImage;
    hpBarImage->LoadTexture(L"../Resource/Hpbar.png");


    auto mpBarObj = CreateGameObject<GameObject>();
    auto mpBarImage = mpBarObj->CreateComponent<ImageUIRenderer>();
    mpBarObj->transform->SetParent(uiObj->transform);
    mpBarObj->transform->type = Type::Ui;
    mpBarObj->transform->pos.rectposition = { {20.f,20.f} ,{20.f + 820.f,40.f} };
    mpBarUi = mpBarObj->CreateComponent<Mpbar>();
    mpBarUi->ImageRender = mpBarImage;
    mpBarImage->LoadTexture(L"../Resource/Mpbar.png");

    /*auto turretUI = CreateGameObject<GameObject>();
    auto turretImage = turretUI->CreateComponent<Button>();
    startX = i * (spacing + width);
    turretUI->transform->SetParent(uiObj->transform);
    turretUI->transform->type = Type::Ui;
    turretUI->transform->pos.rectposition = { {startX + spacing, 60.f} ,{120.f + startX + spacing, 180.f} };
    turretImage->LoadTexture(L"../Resource/turret.png");*/

    // ��� ������ Ui
    auto GoldObj = CreateGameObject<GameObject>();
    auto GoldImage = GoldObj->CreateComponent<Button>();
    GoldObj->transform->SetParent(uiObj->transform);
    GoldObj->transform->type = Type::Ui;
    GoldObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,40.f} ,{20.f + 820.f + spacing + 270.f, (200.f - spacing)} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/
    GoldImage->LoadTexture(L"../Resource/upgradeButton.png");

    // ��ȭ ��ư 
    auto UpgradeObj = CreateGameObject<GameObject>();
    auto UpgradeImage = UpgradeObj->CreateComponent<Button>();
    UpgradeObj->transform->SetParent(uiObj->transform);
    UpgradeObj->transform->type = Type::Ui;
    UpgradeObj->transform->pos.rectposition = { {20.f + 820.f + spacing ,10.f} ,{20.f + 820.f + spacing + 270.f, (200.f - spacing) / 2} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/
    UpgradeImage->LoadTexture(L"../Resource/button.png");

    // ��Ȯ ��ư -> �̰� �ϼ� 500 * 500
    auto Harvestobj = CreateGameObject<GameObject>();
    auto HarvestbtnImage = Harvestobj->CreateComponent<Button>();
    Harvestobj->transform->SetParent(uiObj->transform);
    Harvestobj->transform->type = Type::Ui;
    Harvestobj->transform->pos.rectposition = { {20.f + 820.f + spacing + 270.f + spacing,10.f} ,{20.f + 820.f + spacing + 270.f + spacing + 180.f, 200.f - spacing} };
    /*harvestUi = Harvestobj->CreateComponent<HarvestButton>();
    harvestUi->ImageRender = HarvestbtnImage;*/
    HarvestbtnImage->LoadTexture(L"../Resource/harvest.png");
}

void GameScene::Clear() {
    __super::Clear();
    std::cout << "Exiting GameScene" << std::endl;
    // ���� �۾�
    SoundManager::GetInstance().ReleaseSound(L"backgroundMusic");
}

void GameScene::Update(float deltaTime) {
    __super::Update(deltaTime);

    if (InputManager::GetInstance().IsKeyDown('1')) {
        hpBarUi->takeDamage(10.f);
        hpBarUi->ImageRender->slideBar = hpBarUi->getBarWidth();
        std::cout << hpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << hpBarUi->getBarWidth() << std::endl;
    }

    if (InputManager::GetInstance().IsKeyDown('2')) {
        mpBarUi->takeMp(10.f);
        mpBarUi->ImageRender->slideBar = mpBarUi->getBarWidth();
        std::cout << mpBarUi->ImageRender->m_DstRect.right << std::endl;
        std::cout << mpBarUi->getBarWidth() << std::endl;
    }

    // ���� �� ��ȯ �׽�Ʈ
    if (InputManager::GetInstance().IsKeyDown('3')) {
        SceneManager::GetInstance().ChangeScene("StartScene");
    }

    // ���� ���� �׽�Ʈ 
    if (InputManager::GetInstance().IsKeyDown('5')) {
        // 5���� Ŭ���� �� ���� SoundManager::GetInstance().LoadSound(L"backgroundMusic", L"../Media/hello.mp3"); ���尡 
        // ������ ����� �״�� ��µǰ� �� ���尡 �ߺ����� ��µǰ� �Ϸ��� �ϴµ�, ��� �ϸ� ������?
         // ���ο� ���� �̸����� ���� �ε�
        std::wstring soundName = L"gimicSuccess";
        SoundManager::GetInstance().LoadSound(soundName, L"../Media/gimicSuccess.mp3");

        // �ε�� ���带 ���
        SoundManager::GetInstance().PlaySoundW(soundName, true);
    }

    SoundManager::GetInstance().Update();
}

void GameScene::Render(D2DRenderer* _render) {
    __super::Render(_render);
}
