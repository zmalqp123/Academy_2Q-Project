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
	if (FilePath == std::wstring(L"Comosus"))
	{
		LoadAnimationFromCSV(0, L"../Resource/KrakenDefault.txt");
		LoadAnimationFromCSV(1, L"../Resource/kraken.txt");
	}
	if (FilePath == std::wstring(L"BombcartMove"))
	{
		LoadAnimationFromCSV(0, L"../Resource/bomcart.txt");
	}
	if (FilePath == std::wstring(L"swordmanMove"))
	{
		LoadAnimationFromCSV(0, L"../Resource/swordman.txt");
	}
	if (FilePath == std::wstring(L"musketshooterMove"))
	{
		LoadAnimationFromCSV(0, L"../Resource/musketshooter.txt");
	}
	if (FilePath == std::wstring(L"heavyknightMove"))
	{
		LoadAnimationFromCSV(0, L"../Resource/heavyknight.txt");
	}
	if (FilePath == std::wstring(L"griffinMove"))
	{
		LoadAnimationFromCSV(0, L"../Resource/griffin.txt");
	}
	// turret bullet
	if (FilePath == std::wstring(L"30306"))
	{
		LoadAnimationFromCSV(0, L"../Resource/30306.txt");
	}
	if (FilePath == std::wstring(L"30307"))
	{
		LoadAnimationFromCSV(0, L"../Resource/30307.txt");
	}
	if (FilePath == std::wstring(L"30308"))
	{
		LoadAnimationFromCSV(0, L"../Resource/30308.txt");
	}
	if (FilePath == std::wstring(L"30309"))
	{
		LoadAnimationFromCSV(0, L"../Resource/30309.txt");
	}
	if (FilePath == std::wstring(L"30318")) 
	{
		LoadAnimationFromCSV(0, L"../Resource/30318.txt");
		LoadAnimationFromCSV(1, L"../Resource/30318-1.txt");
	}
	if (FilePath == std::wstring(L"30501"))
	{
		LoadAnimationFromCSV(0, L"../Resource/Turret/30501.txt");
		LoadAnimationFromCSV(1, L"../Resource/Turret/30502.txt");
		LoadAnimationFromCSV(2, L"../Resource/Turret/30503.txt");
		LoadAnimationFromCSV(3, L"../Resource/Turret/30504.txt");
		LoadAnimationFromCSV(4, L"../Resource/Turret/30505.txt");
	}
	if (FilePath == std::wstring(L"30511"))
	{
		LoadAnimationFromCSV(0, L"../Resource/Turret/30511.txt");
		LoadAnimationFromCSV(1, L"../Resource/Turret/30512.txt");
		LoadAnimationFromCSV(2, L"../Resource/Turret/30513.txt");
		LoadAnimationFromCSV(3, L"../Resource/Turret/30514.txt");
		LoadAnimationFromCSV(4, L"../Resource/Turret/30515.txt");
	}
	if (FilePath == std::wstring(L"30521"))
	{
		LoadAnimationFromCSV(0, L"../Resource/Turret/30521.txt");
		LoadAnimationFromCSV(1, L"../Resource/Turret/30522.txt");
		LoadAnimationFromCSV(2, L"../Resource/Turret/30523.txt");
		LoadAnimationFromCSV(3, L"../Resource/Turret/30524.txt");
		LoadAnimationFromCSV(4, L"../Resource/Turret/30525.txt");
	}
	if (FilePath == std::wstring(L"30541"))
	{
		LoadAnimationFromCSV(0, L"../Resource/Turret/30541.txt");
		LoadAnimationFromCSV(1, L"../Resource/Turret/30542.txt");
		LoadAnimationFromCSV(2, L"../Resource/Turret/30543.txt");
		LoadAnimationFromCSV(3, L"../Resource/Turret/30544.txt");
		LoadAnimationFromCSV(4, L"../Resource/Turret/30545.txt");
	}
	if (FilePath == std::wstring(L"griffinMove"))
	{
		LoadAnimationFromCSV(0, L"../Resource/griffin.txt");
	}
	if (FilePath == std::wstring(L"ComosusLight"))
	{
		LoadAnimationFromCSV(0, L"../Resource/ComosusLightDefault.txt");
		LoadAnimationFromCSV(1, L"../Resource/ComosusLight.txt");
		LoadAnimationFromCSV(2, L"../Resource/ComosusLightRe.txt");
	}
	if (FilePath == std::wstring(L"cutton_10301"))
	{
		LoadAnimationFromCSV(0, L"../Resource/10301.txt");
		LoadAnimationFromCSV(1, L"../Resource/empty.txt");
	}
	if (FilePath == std::wstring(L"cutton_10302"))
	{
		LoadAnimationFromCSV(0, L"../Resource/10302.txt");
		LoadAnimationFromCSV(1, L"../Resource/empty.txt");
	}
	if (FilePath == std::wstring(L"cutton_10301close"))
	{
		LoadAnimationFromCSV(0, L"../Resource/10301close.txt");
		LoadAnimationFromCSV(1, L"../Resource/empty.txt");
	}
	if (FilePath == std::wstring(L"cutton_10302close"))
	{
		LoadAnimationFromCSV(0, L"../Resource/10302close.txt");
		LoadAnimationFromCSV(1, L"../Resource/empty.txt");
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
