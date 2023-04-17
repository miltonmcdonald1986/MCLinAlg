#pragma once


#include <cassert>
#include <format>
#include <iostream>
#include <vector>

#include <Windows.h>


namespace MCLinAlg
{


	class Matrix
	{
	public:
		using Row = std::vector<double>;

		Matrix(unsigned int numRows, unsigned int numCols, const std::vector<double> &arr)
		{
			m_Rows = std::vector<Row>(numRows, Row(numCols));
			
			for (size_t i = 0; i < arr.size(); ++i)
			{
				const auto r = i / numCols;
				const auto c = i % numCols;
				m_Rows[r][c] = arr[i];
			}
		}

		Row& operator[](std::size_t i) 
		{ 
			return m_Rows[i]; 
		}

		const Row& operator[](std::size_t i) const 
		{ 
			return m_Rows[i]; 
		}

		auto Replacement(unsigned int rowToReplace, double multiplier, unsigned int rowToMultiply)
		{
			auto& row = m_Rows[rowToReplace];
			for (auto i = 0; i < row.size(); ++i)
			{
				row[i] += multiplier * m_Rows[rowToMultiply][i];
			}
		}

		auto Scaling(unsigned int rowToScale, double multiplier)
		{
			auto& row = m_Rows[rowToScale];
			for (auto i = 0; i < row.size(); ++i)
			{
				row[i] *= multiplier;
			}
		}

		auto DebugTextDump() const
		{
			OutputDebugString(L"\n");

			for (const auto row : m_Rows)
			{
				for (const auto val : row)
				{
					OutputDebugString(std::format(L"{} ", val).c_str());
				}

				OutputDebugString(L"\n");
			}
		}

	private:
		std::vector<Row> m_Rows;
	};


}
