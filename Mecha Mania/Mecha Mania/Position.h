#pragma once

struct TPosition
{
	int m_iX;
	int m_iY;

	bool operator==(const TPosition& other) const
	{
		return m_iX == other.m_iX && m_iY == other.m_iY;
	}
	bool operator!=(const TPosition& other) const
	{
		return !(*this == other);
	}
};