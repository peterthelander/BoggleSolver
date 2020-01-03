
#include "StdAfx.h"
#include "Dictionary.h"
#include <iostream>
#include <fstream>
using namespace std;

Dictionary::Dictionary(const char *filename)
{
	cout << "Reading dictionary file " << filename << endl;

	ifstream inputFile(filename);

	// words of less than three characters are not allowed
	const int minChars = 3;

	while (inputFile.good())
	{
		const streamsize bufSize = 256;
		char buffer[bufSize];
		inputFile.getline(buffer, bufSize);
		if (inputFile.good())
		{
			string bufStr(buffer);

			if (bufStr.size() >= minChars)
			{
				for (size_t t=0; t<bufStr.size(); t++)
				{
					bufStr[t] = toupper(bufStr[t]);
				}
				m_words.push_back(bufStr);
			}
		}
	};

	cout << "Finished reading, got " << m_words.size() 
		<< " words of at least " << minChars << " characters" << endl << endl;

	if (m_words.size() == 0)
	{
		cerr << "ERROR: Invalid dictionary file " << filename << endl;
	}
}

