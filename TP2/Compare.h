#ifndef COMPARE_H
#define COMPARE_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <string>
#include <algorithm>
#include "Mapping.h"

class Compare
{
	typedef multimap<int, string> multi;
	typedef map<string, int> map;
	ofstream diff, inter;
	vector<string> nomDiff, nomInter;
	// int filesNameSize;
	string prefixe, middle;
	
public:
	Compare(vector<string> filesName, Mapping mm)
	{
		getNameFiles(filesName);
		opt5_Opt6(mm);
	}

	void getNameFiles(vector<string>& f)
	{
		int fSize = f.size();
		for (int i = 0; i < fSize; i++)
		{
			this->prefixe = f[i].substr(11, 3);
			for (int j = 0; j < fSize; j++)
			{
				this->middle = f[j].substr(11, 3);
				if (this->prefixe != this->middle)
				{
					this->nomDiff.push_back(this->prefixe + this->middle + "diff.txt");
					this->nomInter.push_back(this->prefixe + this->middle + "inter.txt");
				}
			}
		}
	}

	void opt5_Opt6(Mapping& mm)
	{
		map m1, m2;
		int mmSize = mm.getSize();
		int nomDiffSize = nomDiff.size();
		int f = 0;
		while (f < nomDiffSize) 
		{
			for (int i = 0; i < mmSize - 1; i++)
			{	
				m1 = mm.getMesMappes()[i];
				for (int j = 0; j < mmSize - 1; j++)
				{
					m2 = mm.getMesMappes()[j];
					if (m1 != m2)
					{
						inter.open("option6/" + nomInter[f]);
						diff.open("option5/" + nomDiff[f]);
						if(diff.is_open() && inter.is_open())
						{
							for (auto e : m1)
							{
								if (m2.find(e.first) != m2.end())
									inter << e.first << " " <<  e.second << endl;
									
								else diff << e.first << " " <<  e.second << endl;
							}
							diff.close();
							inter.close();
							f++;
						}
						else cerr << "file not created\n";
					}
				}
			}
		} 
	}
};

#endif // COMPARE_H
