#include "pch.h"
#include "Button.h"
#include "Transform.h"
#include "GameObject.h"
#include "Texture.h"
#include "AABB.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "PublicData.h"

Button::~Button()
{
    if (m_pTexture) {
        ResourceManager::GetInstance().ReleaseAnimationAsset(m_strTextureFilePath);
        m_pTexture = nullptr;
    }
}

AABB Button::GetBound()
{
    AABB ab;
    /*ab.m_Center = { (gameObject->transform->pos.rectposition.rightTop.x + gameObject->transform->pos.rectposition.leftBottom.x) * 0.5f,
        (gameObject->transform->pos.rectposition.rightTop.y + gameObject->transform->pos.rectposition.leftBottom.y) * 0.5f
    };
    ab.m_Extent = { (gameObject->transform->pos.rectposition.rightTop.x - gameObject->transform->pos.rectposition.leftBottom.x) * 0.5f,
        (gameObject->transform->pos.rectposition.rightTop.y - gameObject->transform->pos.rectposition.leftBottom.y) * 0.5f
    };*/
    return ab;
}

void Button::Render(D2D1_MATRIX_3X2_F cameraMat)
{
    if (gameObject->isActive == false || (gameObject->transform->m_pParentScene != nullptr && gameObject->transform->m_pParentScene->gameObject->isActive == false))
        return;
    auto pRenderTarget = &D2DRenderer::getRenderTarget();

    D2D1_MATRIX_3X2_F m_ScreenTransform =
        D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
        D2D1::Matrix3x2F::Translation(0, PublicData::GetInstance().GetScreenSize().y);
    D2D1_MATRIX_3X2_F Transform =
        D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * m_ImageTransform
        * gameObject->transform->m_WorldTransform
        //* cameraMat
        * m_ScreenTransform;
    ;// * D2DRenderer::m_CameraTransform;
    pRenderTarget->SetTransform(Transform);
    auto tmp = m_SrcRect.right;
    auto srcTmp = m_SrcRect;
    srcTmp.right = tmp;

    auto dstmp = m_DstRect.right;
    auto dstTmp = m_DstRect;
    dstTmp.right = dstmp;

    pRenderTarget->DrawBitmap(m_pTexture->m_pD2DBitmap, dstTmp, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcTmp);
}

void Button::OnClick()
{
    std::cout << "ClickDown!" << std::endl;
    if (events != nullptr) events();
}

void Button::OffClick()
{
    std::cout << "ClickUp!" << std::endl;
    // 영역내에서 클릭업했는지 체크해야함
}

void Button::AddListener(std::function<void()> func)
{
     events = func;
}

bool Button::isCollide(Collider* collider, Vector2& resolution)
{
    return false;
}

bool Button::isCollide(const Vector2& point)
{
    float x = gameObject->transform->m_WorldTransform.dx;
    float y = gameObject->transform->m_WorldTransform.dy;
    float dx = gameObject->transform->pos.rectposition.rightTop.x - gameObject->transform->pos.rectposition.leftBottom.x;
    float dy = gameObject->transform->pos.rectposition.rightTop.y - gameObject->transform->pos.rectposition.leftBottom.y;
    bool result = (x <= point.x &&
        x + dx >= point.x &&
        y <= point.y &&
        y + dy >= point.y);
    return result;
}

void Button::LoadTexture(const std::wstring strFilePath)
{
    m_strTextureFilePath = strFilePath;

    if (ResourceManager::GetInstance().CreateTextureFromFile(m_strTextureFilePath, &m_pTexture))
    {
        auto size = m_pTexture->m_pD2DBitmap->GetSize();
        /*m_DstRect.left = 0.f;
        m_DstRect.top = 0.f;
        m_DstRect.right = size.width;
        m_DstRect.bottom = size.height;
        m_SrcRect = m_DstRect;*/
        m_DstRect.left = 0.f;
        m_DstRect.top = 0.f;
        m_DstRect.right = gameObject->transform->pos.rectposition.rightTop.x - gameObject->transform->pos.rectposition.leftBottom.x;
        m_DstRect.bottom = gameObject->transform->pos.rectposition.rightTop.y - gameObject->transform->pos.rectposition.leftBottom.y;
        m_SrcRect = m_DstRect;

        m_SrcRect.left = 0.f;
        m_SrcRect.top = 0.f;
        m_SrcRect.right = size.width;
        m_SrcRect.bottom = size.height;

        m_ImageTransform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0, 0)) *
            D2D1::Matrix3x2F::Translation(0.f, m_DstRect.bottom);
    }
}

void Button::Update(float deltaTime)
{
    if (isMouseOn == false) return;
    if (!InputManager::GetInstance().GetPrevMouseState().left && InputManager::GetInstance().GetMouseState().left) {
        if (isClicked == false) {
            OnClick();
        }
        isClicked = true;
    }
    else if(InputManager::GetInstance().GetPrevMouseState().left && !InputManager::GetInstance().GetMouseState().left){
        if (isClicked == true) {
            OffClick();
        }
        isClicked = false;
    }
}

void Button::Render(ID2D1HwndRenderTarget* pRenderTarget, D2D1_MATRIX_3X2_F cameraMat)
{
    
}

void Button::IPointerEnter()
{
    isMouseOn = true;
    //std::cout << "enterButton" << std::endl;
}

void Button::IPointerStay()
{
}

void Button::IPointerExit()
{
    isMouseOn = false;
    //std::cout << "exitButton" << std::endl;
    isClicked = false;
}
