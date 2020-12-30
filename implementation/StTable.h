#pragma once
#include<vector>
class StTable
{
public:
	StTable(const std::vector<long>& data,bool (*fptr)(long,long));
	~StTable();
	long query(int start, int end);
private:
	long m_num;
	long m_maxLog;
	std::vector<long> m_log;
	std::vector<long> m_table;
	bool (*m_fptr)(long, long);
	
};

inline StTable::StTable(const std::vector<long>& data,bool(*fptr)(long, long)):m_num{(long)data.size()},m_maxLog(long(log2(data.size())+1)),m_table(m_num*m_maxLog,0),m_fptr{fptr},m_log(1,0)
{
	int t = 0;
	for (long i = 1; i <= m_num; i++)
	{	
		if (i == 1 << (t + 1)) t++;
		m_log.push_back(t);
	}
	for (long i = 0; i < m_num; i++)
	{
		m_table[0 * m_num + i] = data[i];
	}
	for (long i = 1; i < m_maxLog; i++)
	{
		for (long j = 0; j < m_num; j++)
		{
			long first = m_table[(i - 1) * m_num + j];
			long second = m_table[(i - 1) * m_num + j + (1 << (i - 1))];
			m_table[i * m_num + j] = m_fptr(first, second) ? first: second;
		}
	}
}

StTable::~StTable()
{
}

inline long StTable::query(int start, int end)
{
	long length = end - start + 1;
	long logLength = m_log[length];
	long first = m_table[logLength * m_num + start];
	long second = m_table[logLength * m_num+end - (1 << logLength) + 1];

	return m_fptr(first, second) ? first: second;
}
