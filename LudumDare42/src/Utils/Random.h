#pragma once

#include <random>
#include <ctime>

namespace Utils
{
	class Random
	{
		public:
			Random(int seed = std::time(nullptr)) : m_generator(seed)
			{
			}

			int getNumberInRange(int min, int max)
			{
				std::uniform_int_distribution<int> dist(min, max);
				return dist(m_generator);
			}

		private:
			std::mt19937 m_generator;
	};
}