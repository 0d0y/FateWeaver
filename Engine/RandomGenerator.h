#pragma once
#include <random>

/*-------------------------------------------------------
RandomGenerator
난수 생성기, 어디서나 접근하게 하고 시드 하나로 난수 생성하려고 싱글톤으로 만듬.
인스턴스로 접근해서 GetRamdomNumber 호출할 때 min, max값 지정해주면 그 범위안에서 난수 리턴 해줌.
-------------------------------------------------------*/

class RandomGenerator
{
private :
	std::random_device rd;
	std::mt19937 rng;

	static RandomGenerator* m_Instance;

private:
	RandomGenerator();

public:
	static RandomGenerator* GetInstance();

public:
	int GetRandomNumber(int min, int max);
	std::mt19937& GetRandomEngine();

public:
	RandomGenerator(const RandomGenerator&) = delete;
	RandomGenerator& operator=(const RandomGenerator&) = delete;

	void Finalize();
};

