#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SpriteAnimation.h"
#include "D2DRenderer.h"
GameObject::GameObject()
{
	transform = CreateComponent<Transform>();
}
GameObject::~GameObject()
{
	for (auto c : components) {
		c->Release();
	}
	components.clear();
}

void GameObject::Init()
{

}

void GameObject::Update(float delta)
{
	for (auto c : components) {
		c->Update(delta);
	}

	transform->UpdateTrasnform();
}

void GameObject::Render(D2D1_MATRIX_3X2_F cameraMat)
{
	//if (spriteAnim) spriteAnim->Render(&D2DRenderer::getRenderTarget(), cameraMat);
	for (auto c : components) {
		c->Render(cameraMat);
	}
}

bool GameObject::AddComponent(Component* _component)
{
	for (auto c : components) {
		if (c->GetInstanceID() == _component->GetInstanceID())
			return false;
	}
	components.push_back(_component);
	return true;
}

void GameObject::RemoveComponent(Component* _component)
{
	/*for (auto c : components) {
		if (c->GetInstanceID() == _component->GetInstanceID())
		{
			c->Release();

			break;
		}
	}*/
}

void GameObject::SetActive(bool active)
{
	isActive = active;
}

void GameObject::SetOwner(Scene* scene)
{
	ownerScene = scene;
}
