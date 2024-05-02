#include "pch.h"
#include "RandomGenerator.h"

RandomGenerator* RandomGenerator::m_Instance = nullptr;

RandomGenerator::RandomGenerator()
    : rng(rd())
{
}

RandomGenerator* RandomGenerator::GetInstance()
{
	if (m_Instance == nullptr)
		m_Instance = new RandomGenerator;

	return m_Instance;
}

int RandomGenerator::GetRandomNumber(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(rng);
}

std::mt19937& RandomGenerator::GetRandomEngine()
{
	return rng;
}

void RandomGenerator::Finalize()
{
	SAFE_DELETE(m_Instance);
}
