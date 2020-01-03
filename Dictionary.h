#pragma once

#include <string>
#include <vector>

class Dictionary
{
	public:
		Dictionary(const char* filename);

		size_t size() const { return m_words.size(); }
		const std::string& operator[](size_t i) const { return m_words[i]; };

	private:
		std::vector<std::string> m_words;

};
