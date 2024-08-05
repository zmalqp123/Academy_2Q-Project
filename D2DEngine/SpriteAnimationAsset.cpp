#include "pch.h"
#include "SpriteAnimationAsset.h"

bool SpriteAnimationAsset::LoadAnimation(std::wstring FilePath)
{
	//텍스트 파일을 열어서 csv파일 목록을 읽어온다.
	// 아래 함수로 csv파일을 처리한다.
	if (FilePath == std::wstring(L"../Resource/background.txt"))
	{
		return LoadAnimationFromCSV(0, FilePath.c_str());
	}
	if (FilePath == std::wstring(L"../Resource/midnight.txt"))
	{
		return LoadAnimationFromCSV(1, FilePath.c_str());
	}
	if (FilePath == std::wstring(L"Ken")) 
	{
		LoadAnimationFromCSV(0, L"../Resource/KenIdle.csv");
		LoadAnimationFromCSV(1, L"../Resource/KenMove.csv");
		LoadAnimationFromCSV(2, L"../Resource/KenAttack.csv");
	}
	if (FilePath == std::wstring(L"TheBullet")) {
		LoadAnimationFromCSV(0, L"../Resource/Animations/IdleDown.txt");
		LoadAnimationFromCSV(1, L"../Resource/Animations/IdleRight.txt");
		LoadAnimationFromCSV(2, L"../Resource/Animations/IdleRightUp.txt");
		LoadAnimationFromCSV(3, L"../Resource/Animations/IdleUp.txt");
		LoadAnimationFromCSV(4, L"../Resource/Animations/WalkDown.txt");
		LoadAnimationFromCSV(5, L"../Resource/Animations/WalkRight.txt");
		LoadAnimationFromCSV(6, L"../Resource/Animations/WalkRightUp.txt");
		LoadAnimationFromCSV(7, L"../Resource/Animations/WalkUp.txt");
		LoadAnimationFromCSV(8, L"../Resource/Animations/DodgeRollDown.txt");
		LoadAnimationFromCSV(9, L"../Resource/Animations/DodgeRollRight.txt");
		LoadAnimationFromCSV(10, L"../Resource/Animations/DodgeRollRightUp.txt");
		LoadAnimationFromCSV(11, L"../Resource/Animations/DodgeRollUp.txt");
	}
	return true;
}

bool SpriteAnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)
{
	std::wifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		std::wcout << fileName << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	int FrameCount = 0;			// 프레임의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_Animations[index].Frames.resize(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// 한줄 읽기
		std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			m_Animations[index].Frames[j].Source.left = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.top = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.right = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Source.bottom = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			m_Animations[index].Frames[j].Duration = (float)_wtof(token.c_str());
		}
	}

	return true;
}
