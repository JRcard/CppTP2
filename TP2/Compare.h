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
	string prefixe, middle;
	
public:
	Compare(vector<string> filesName, Mapping mm)
	{
		getNameFiles(filesName);
		opt5_Opt6(mm);
	}

	// génère les nom de fichier pour les opérations 5-6.
	void getNameFiles(vector<string>& f)
	{
		int fSize = f.size();
		for (int i = 0; i < fSize; i++)
		{
			prefixe = f[i].substr(11, 3); // capture le préfixe pour le nom de fichier
			for (int j = 0; j < fSize; j++)
			{
				middle = f[j].substr(11, 3); // capture le milieu pour le nom de fichier
				if (prefixe != middle) // si les noms sont différent.
				{
					// ajoute les noms aux bons vectors.
					nomDiff.push_back(prefixe + middle + "diff.txt");
					nomInter.push_back(prefixe + middle + "inter.txt");
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
		// pendant que f est plus petit que le vector des nom de fichier.
		while (f < nomDiffSize) 
		{
			for (int i = 0; i < mmSize - 1; i++)
			{	
				m1 = mm.getMesMappes()[i]; // attrape une map
				for (int j = 0; j < mmSize - 1; j++)
				{
					m2 = mm.getMesMappes()[j]; // attrape une seconde map.
					if (m1 != m2) // si ce n'est pas les mêmes.
					{
						/* ouvrture des fichiers:
						 * comme les vectors de nom de fichier a été fait de la même manière
						 * que la récupération des mappes, l'ordre des comparaisons sera la même.*/
						inter.open("option6/" + nomInter[f]);
						diff.open("option5/" + nomDiff[f]);
						// si les deux fichier sont bien ouvert, on procède.
						if(diff.is_open() && inter.is_open()) 
						{
							// pour tous les éléments "e" de la mappe 1.
							for (auto e : m1) 
							{
								// si, dans la mappe 2, la clef correspondant à la clef de l'élément "e" courant est trouvée,
								if (m2.find(e.first) != m2.end())
									// on l'inscrit dans le fichier qui recense les éléments semblables.
									inter << e.first << " " <<  e.second << endl;
								/* si il ne le trouve pas cela signifie que l'élément n'est pas commun au deux listes.
								 * il est donc inscrit dans le fichier qui recense les différences.*/
								else diff << e.first << " " <<  e.second << endl;
							}
							// fermeture des fichiers
							diff.close();
							inter.close();
							// incrémente la liste des nom de fichier.
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
