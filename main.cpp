#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define A4 440

std::vector<std::string> notes = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
std::vector<int> vfreq, vdur;

int toInt(char c)
{
	return (int)c - '0';
}

int noteNum(std::string s)
{
	return std::distance(notes.begin(), std::find(notes.begin(), notes.end(), s)) + 1;
}

int dist(int n, int oct)
{
	return 12 * oct + n - 58;
}

int freq(std::string s)
{
	if (s[1] == '#')
		return A4 * pow(2, dist(noteNum(s.substr(0, 2)), toInt(s[2])) / 12.0);
	return A4 * pow(2, dist(noteNum(s.substr(0, 1)), toInt(s[1])) / 12.0);
}

int main()
{
	std::ifstream fin;
	std::ofstream fout;
	fin.open("m.txt");
	fout.open("out.txt");
	
	for (std::string line; std::getline(fin, line); )
	{
		std::stringstream ss;
		std::string bs;
		int bi;

		ss << line;
		ss >> bs;
		if (bs == "0") 
			vfreq.push_back(0);
		else 
			vfreq.push_back(freq(bs));
		ss >> bi;
		vdur.push_back(bi);
	}

	fout << "int len = " << vfreq.size() << ";\nint freq[] = {";
	for (int i = 0; i < vfreq.size() - 1; i++)
		fout << vfreq[i] << ", ";

	fout << vfreq[vfreq.size()-1] << "};\nint dur[] = {";
	
	for (int i = 0; i < vdur.size() - 1; i++)
		fout << vdur[i] << ", ";

	fout << vdur[vdur.size() - 1] << "};\n";

	return 0;
}