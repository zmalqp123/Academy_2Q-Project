#include "pch.h"
#include "Renderer.h"

void Renderer::SetSortingLayer(int value)
{
	sortingLayer = value;
}

int Renderer::GetSortingLayer()
{
	return sortingLayer;
}
