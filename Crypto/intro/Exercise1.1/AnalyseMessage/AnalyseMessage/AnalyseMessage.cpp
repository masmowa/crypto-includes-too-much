// AnalyseMessage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <list>
#include <vector>

#include <standard-include.h>
#include "EnCharFrequency.h"
#include "CharPtFreqCtFreq.h"
#include "CharFreqNode.h"
#include "MessageInfo.h"

using namespace std;

typedef std::map<char, int> CharCount;
typedef std::map<char, CharPtFreqCtFreq> CharFreqMap;

std::string ReadInput(std::string const& input)
{
	efs::path inpath(input.c_str());
	if (Verbose())
	{
		std::cout << input << std::endl;
		//std::cout << "CWD: " << efs::current_path() << std::endl;
		demo_exists(inpath);
	}
	if (!get_exists(inpath))
	{
		std::cout << "File: " << input.c_str() << " not found" << std::endl;
	}
	// get problem name
	std::ifstream fin(inpath);
	std::string line;
	std::getline(fin, line);
	string problemName = line;
	// get input ciphertext
	std::getline(fin, line);
	vector<string> intoks = tokenize(line, ':');
	for (size_t i = 0; i < intoks.size(); ++i)
	{
		cout << intoks[i] << std::endl;
	}


	return intoks[1];
}
void ProcessInput(std::string const& input)
{
#if 0
	efs::path inpath(input.c_str());
	if (Verbose())
	{
		std::cout << input << std::endl;
		//std::cout << "CWD: " << efs::current_path() << std::endl;
		demo_exists(inpath);
	}
	if (!get_exists(inpath))
	{
		std::cout << "File: " << input.c_str() << " not found" << std::endl;
	}
	// get problem name
	std::ifstream fin(inpath);
	std::string line;
	std::getline(fin, line);
	string problemName = line;
	// get input ciphertext
	std::getline(fin, line);
	vector<string> intoks = tokenize(line, ':');
	for (size_t i = 0; i < intoks.size(); ++i)
	{
		cout << intoks[i] << std::endl;
	}


	CharCount ctCountmap;
	CharCount::iterator cci;
	std::list<CharFreqNode> ctCFList;
	string ct = intoks[1];
	for (size_t i = 0; i < ct.size(); ++i)
	{
		cci = ccmap.find(ct[i]);
		if (cci != ccmap.end())
		{
			cci->second++;
		}
		else
		{
			ccmap.insert(std::pair<char, int>(ct[i], 1));
		}
	}

	cout << "Letter Count " << std::endl;
	for (CharCount::iterator t = ccmap.begin(); t != ccmap.end(); ++t)
	{
		cout << t->first << " " << t->second << std::endl;
	}

	CipherTextFreqCountMap ctfMap;
	PTCharFrequency encf;
	FreqToCharMap ctf2c;

	size_t ctcount = ct.size();
	size_t fcnt = 0;
	size_t afcnt = 0;
	cout.precision(4);
	CharFreqNode* fcnHead = NULL;
	// ********
	// create map with freq as key
	// ********
	CharFreqCountMap::iterator ipt;
	CharFreqMap charPtCtFreqMap;

	// ****************
	// find the frequency of each char in the cipher text
	// ****************
	typedef map<char, double> CipherTextFreqCountMap;
	typedef map<char, double> CharFreqCountMap;
	typedef map<double, char> FreqToCharMap;


	for (auto itccm = ccmap.begin(), ipt = encf.english_freq.begin(); itccm != ccmap.end(); ++itccm)
	{
		double freq = static_cast<double>(itccm->second) / static_cast<double>(ctcount);
		ipt = encf.ptF2C.find(itccm->first);
		ctfMap.insert(pair<char, double>(itccm->first, freq));
		if (ipt != encf.ptF2C.end())
		{
			CharPtFreqCtFreq t(itccm->first, ipt->second, freq);
			charPtCtFreqMap.insert(itccm->first, t);
		}
		if (' ' != itccm->first) {
			cout << setw(2) << fcnt << "  ";
			cout << "F[" << freq << "] C[" << itccm->first << "]" << std::endl;
			ctf2c.insert(pair<double, char>(freq, itccm->first));
			fcnt++;
			// note: there are frequencies that are equal 
			// so I need a a container with multiple entries with the same key and different value

			afcnt++;
		}
		cout << "ctf2c size: " << ctf2c.size() << " afcnt " << afcnt << " fcnt " << fcnt << std::endl;

		for (CipherTextFreqCountMap::iterator t = ctfMap.begin(); t != ctfMap.end(); ++t)
		{
			cout << t->first << " " << t->second << std::endl;
		}

		// ********
		// print map with freq as key
		// ********
		FreqToCharMap::iterator ict;
		CharFreqNode* w;
		size_t cnt = 0;
		cout.precision(4);
		for (cnt = 0, ict = ctf2c.begin(), ipt = encf.ptF2C.begin(), w = fcnHead; (ict != ctf2c.end() || ipt != encf.ptF2C.end()) && w != NULL; ++cnt, w = w->next)
		{
			cout << setw(2) << cnt << "  ";
			if (ipt != encf.ptF2C.end()) {
				cout << "PT[" << ipt->first << ", " << ipt->second << "] ";
				++ipt;
			}
			if (ict != ctf2c.end()) {
				cout << "CT[" << ict->first << ", " << ict->second << "]";
				++ict;
			}
			if (w) {
				w->Print();
			}
			cout << std::endl;
		}
	}
#endif
	string ct = ReadInput(input);
	MessageInfo msgInfo(ct);

	msgInfo.printCharCount();
	msgInfo.printWordCount();
	msgInfo.CalcCharPercent();
	msgInfo.CalcWordPercent();
	std::cout << "Percent " << std::endl;
	msgInfo.printCharPercent();
	msgInfo.printWordPercent();

}
int main()
{
    std::cout << "Hello World!\n";
	for (auto& p : efs::directory_iterator("input"))
	{
		string ps = p.path().string();
		ProcessInput(ps);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
