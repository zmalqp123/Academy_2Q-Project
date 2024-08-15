#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

enum class EnemyID {
	swordMan = 30601, 
	swordMan_solid,
	swordMan_fast,
	swordMan_hero,
	musketeer,
	musketeer_solid,
	musketeer_fast,
	musketeer_hero,
	heavyArmor,
	heavyArmor_solid,
	heavyArmor_fast,
	heavyArmor_hero,
	griffin,
	griffin_solid,
	griffin_fast,
	griffin_hero,
	bombCarrier,
	bombCarrier_solid,
	bombCarrier_fast,
	bombCarrier_hero,
	boss1,
	boss2,
};

enum class TurretID {
	crossBow0 = 30501,
	crossBow1,
	crossBow2,
	crossBow3,
	crossBow4,
	musket0 = 30511,
	musket1,
	musket2,
	musket3,
	musket4,
	cannon0 = 30521,
	cannon1,
	cannon2,
	cannon3,
	cannon4,
	superCrossBow0 = 30531,
	superCrossBow1,
	superCrossBow2,
	superCrossBow3,
	superCrossBow4,
	slow0 = 30541,
	slow1,
	slow2,
	slow3,
	slow4,
	fertilizer0 = 30551,
};


struct EnemyData {
	EnemyData() = default;
	EnemyData(int _id) : id(_id) {};
	~EnemyData() = default;

	int id;
	int eliteType;

	int resistArrow;
	int resistBullet;
	int resistBurst;
	int resistComosus;

	float hp;
	int moveSpeed;
	int attack;
	int attackRate;
	int range;

	int reward;
	int expReward;
};

struct TurretData
{	
	TurretData() = default;
	TurretData(int _id) : id(_id) {}; //id가 안들어가는 경우 오류 가능성 있음 주의.
	~TurretData() = default;
	int id;
	int cost;
	int refund;

	float burstRange;
	int damage;
	float fireRate;
	int penetration;

	int bulletType;
	float bulletSpeed;
	int slowRate;
	float slowDuration;

	std::wstring imagePath;
	std::wstring bulletImagePath;
};

struct WaveEnemyData {
	int id;
	std::wstring name;
	int count;
	float interval;
	float maxInterval;
	float startTime;
};

struct WaveData {
	WaveData() = default;
	WaveData(int _id) : id(_id) {};
	~WaveData() = default;
	int id;

	std::vector<WaveEnemyData> leftWaveData;
	std::vector<WaveEnemyData> rightWaveData;
};

class DataManager
{
private:
	DataManager()=default;
	~DataManager() {
		for (auto& enemyData : enemyDataMap) {
			delete enemyData.second;
		}
		enemyDataMap.clear();
		for (auto& turretData : turretDataMap) {
			delete turretData.second;
		}
		turretDataMap.clear();
	};
public:
	

	static DataManager& GetInstance() {
		static DataManager instance;
		return instance;
	}

	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;


	std::map<int, EnemyData*> enemyDataMap; // int = id
	std::map<int, TurretData*> turretDataMap; // int = id
	std::map<int, WaveData*> waveDataMap;

	bool LoadEnemySheetFromCSV(const wchar_t* fileName)
	{
		std::wifstream file(fileName);
		if (!file.is_open()) {
			std::cout << "파일을 열 수 없습니다." << std::endl;
			std::wcout << fileName << std::endl;
			return false;
		}
		std::wstring line;			// 한줄의 문자열	
		int DataCount = 0;			// 띄어쓰기 된 정보의 갯수
		std::getline(file, line);		// 첫번째 줄 읽기
		{
			std::getline(file, line);   // 두번째 줄 읽기 (데이터 갯수)
			std::wstringstream wss(line);
			wss >> DataCount;
		}

		for (int j = 0; j < DataCount; j++)
		{

			getline(file, line);		// 한줄 읽기
			std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
			std::wstring token;
			{
				getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리 ID
				EnemyData* Enemy = new EnemyData(_wtoi(token.c_str()));
				getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리 Name
				getline(wss, token, L',');  // wss의 내용을 ,를 기준으로 문자열을 분리 Size
				getline(wss, token, L',');  // EliteType
				Enemy->eliteType = _wtoi(token.c_str());

				getline(wss, token, L',');  // wss의 내용을 ,를 기준으로 문자열을 분리 Resist
				Enemy->resistArrow = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->resistBullet = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->resistBurst = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->resistComosus = _wtoi(token.c_str());

				getline(wss, token, L',');  // wss의 내용을 ,를 기준으로 문자열을 분리 Stat
				Enemy->hp = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->moveSpeed = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->attack = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->attackRate = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->range = _wtoi(token.c_str());

				getline(wss, token, L',');
				Enemy->reward = _wtoi(token.c_str());
				getline(wss, token, L',');
				Enemy->expReward = _wtoi(token.c_str());
				enemyDataMap.insert(std::make_pair(Enemy->id, Enemy));
			}
		}
		file.close();
		return true;
	}

	bool LoadTurretSheetFromCSV(const wchar_t* fileName) {
		std::wifstream file(fileName);
		if (!file.is_open()) {
			std::cout << "파일을 열 수 없습니다." << std::endl;
			std::wcout << fileName << std::endl;
			return false;
		}
		std::wstring line;			// 한줄의 문자열	
		int DataCount = 0;			// 띄어쓰기 된 정보의 갯수
		for (int i = 0; i < 6; i++) { // 6번째 줄 까지 흘려보내기.
			std::getline(file, line);
		}

		{
			std::getline(file, line);   // 7번째 줄 읽기 (데이터 갯수)
			std::wstringstream wss(line);
			std::wstring token;
			getline(wss, token, L',');
			while (_wtoi(token.c_str()) == 0) {
				getline(wss, token, L',');
				if (_wtoi(token.c_str()) != 0) break;
			}
			DataCount = _wtoi(token.c_str());
		}

		for (int j = 0; j < DataCount; j++)
		{

			getline(file, line);		// 한줄 읽기
			std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
			std::wstring token;
			{
				while (_wtoi(token.c_str()) == 0) {
					getline(wss, token, L',');
					if (_wtoi(token.c_str()) != 0) break;
				}
				TurretData* Turret = new TurretData(_wtoi(token.c_str()));
				getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리 Name
				getline(wss, token, L',');  // wss의 내용을 ,를 기준으로 문자열을 분리 Size

				getline(wss, token, L',');  // wss의 내용을 ,를 기준으로 문자열을 분리 Cost
				Turret->cost = _wtoi(token.c_str());
				getline(wss, token, L',');  // Refund
				Turret->refund = _wtoi(token.c_str());

				getline(wss, token, L',');  // wss의 내용을 ,를 기준으로 문자열을 분리 Stat
				Turret->burstRange = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->damage = _wtoi(token.c_str());
				getline(wss, token, L',');
				Turret->fireRate = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->penetration = _wtoi(token.c_str());

				getline(wss, token, L',');
				Turret->bulletType = _wtoi(token.c_str());//투사체 타입
				getline(wss, token, L',');
				Turret->bulletSpeed = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->slowRate = _wtof(token.c_str());
				getline(wss, token, L',');
				Turret->slowDuration = _wtof(token.c_str());

				getline(wss, token, L',');
				//Turret->angle = _wtof(token.c_str());
				Turret->imagePath = (L"../Resource/" + token).c_str();
				getline(wss, token, L',');
				//Turret->angle = _wtof(token.c_str());
				Turret->bulletImagePath = (L"../Resource/" + token).c_str();
				turretDataMap.insert(std::make_pair(Turret->id, Turret));
			}
		}
		file.close();
		return true;
	}

	bool LoadWaveSheetFromCSV(const wchar_t* fileName) {
		std::wstring fileBase = fileName;
		int count = 1;
		std::wstring extension = L".csv";

		while (true) {
			std::wstring newPath = fileBase + std::to_wstring(count) + extension;
			std::wifstream file(newPath);
			if (!file.is_open()) {
				std::cout << "파일을 열 수 없습니다." << std::endl;
				std::wcout << newPath << std::endl;
				break;
			}
			std::wstring line;			// 한줄의 문자열	
			WaveData* wave = new WaveData(count);
			getline(file, line);
			for(int i = 0; i < 22; i++)
			{
				getline(file, line);		// 한줄 읽기
				std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장
				std::wstring token;
				{
					WaveEnemyData leftData;
					getline(wss, token, L',');
					leftData.id = _wtoi(token.c_str());
					getline(wss, token, L',');
					leftData.name = token.c_str();
					getline(wss, token, L',');
					leftData.count = _wtoi(token.c_str());
					getline(wss, token, L',');
					float interval = _wtof(token.c_str());
					leftData.interval = interval;
					leftData.maxInterval = interval;
					getline(wss, token, L',');
					leftData.startTime = _wtof(token.c_str());

					wave->leftWaveData.push_back(leftData);

					getline(wss, token, L',');
					getline(wss, token, L',');
					getline(wss, token, L',');

					WaveEnemyData rightData;
					rightData.id = _wtoi(token.c_str());
					getline(wss, token, L',');
					rightData.name = token.c_str();
					getline(wss, token, L',');
					rightData.count = _wtoi(token.c_str());
					getline(wss, token, L',');
					float interval2 = _wtof(token.c_str());
					rightData.interval = interval2;
					rightData.maxInterval = interval2;
					getline(wss, token, L',');
					rightData.startTime = _wtof(token.c_str());

					wave->rightWaveData.push_back(rightData);
				}
			}
			waveDataMap.insert(std::make_pair(count, wave));
			file.close();


			count++;
		}



		
		return true;
	}

	EnemyData* GetEnemyData(int id) {
		
		return enemyDataMap[id];
	}

	TurretData* GetTurretData(int id) {
		
		return turretDataMap[id];
	}

	WaveData* GetWaveData(int number) {
		return waveDataMap[number];
	}
};

