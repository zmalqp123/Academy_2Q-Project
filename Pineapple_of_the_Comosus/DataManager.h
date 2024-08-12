#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct EnemyData {
	EnemyData(int _id) : id(_id) {};
	~EnemyData() = default;

	int id;
	int eliteType;

	int resistArrow;
	int resistBullet;
	int resistBurst;
	int resistComosus;

	int hp;
	int moveSpeed;
	int attack;
	int attackRate;
	int range;

	int reward;
	int expReward;
};

struct TurretData
{
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

	float angle;
};

class DataManager
{
private:
	DataManager()=default;
	~DataManager() {
		for (auto& data : enemyDataList) {
			delete data;
		}
		enemyDataList.clear();
		for (auto& data : turretDataList) {
			delete data;
		}
		turretDataList.clear();
	};
public:
	

	static DataManager& GetInstance() {
		static DataManager instance;
		return instance;
	}

	DataManager(const DataManager&) = delete;
	DataManager& operator=(const DataManager&) = delete;


	std::vector<EnemyData*> enemyDataList;
	std::vector<TurretData*> turretDataList;

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
				enemyDataList.push_back(Enemy);
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
				Turret->angle = _wtof(token.c_str());
				turretDataList.push_back(Turret);
			}
		}
		file.close();
		return true;
	}

	EnemyData* GetEnemyData(int id) {
		for (auto& data : enemyDataList) {
			if (data->id == id) {
				return data;
			}
		}
		return nullptr;
	}

	TurretData* GetTurretData(int id) {
		for (auto& data : turretDataList) {
			if (data->id == id) {
				return data;
			}
		}
		return nullptr;
	}
};

