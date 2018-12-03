#ifndef MAPPING_H
#define MAPPING_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Mapping
{
	typedef map<string, int> map;
	typedef multimap<int, string> multi;
	map arlequin, camelias, germinal, ptprince, mappeGlobal;
	multi multiArlequin, multiCamelias, multiGerminal, multiPtprince, multiMappeGlobal;
	vector<map> mesMappes;
	vector<multi> mesMultis;
	vector<string> titres;

public:
	
	Mapping(vector<string> lesLivres)
	{
		// place les mappes dans leur vector respectif.
		mesMappes.push_back(arlequin);
		mesMappes.push_back(camelias);
		mesMappes.push_back(germinal);
		mesMappes.push_back(ptprince);
		
		mesMultis.push_back(multiArlequin);
		mesMultis.push_back(multiCamelias);
		mesMultis.push_back(multiGerminal);
		mesMultis.push_back(multiPtprince);
		
		// déclaration d'une variable de type fichier de lecture.
		ifstream livre;
		int grandeurLivres = lesLivres.size();
		for (int i = 0; i < grandeurLivres; i++)
		{
			string mot;
			livre.open(lesLivres[i]);
			if (livre.is_open())
			{
			// attrappe chaque mot du fichier, le met en minuscule et l'insert dans la map.
				while(!livre.eof())
				{
					getline(livre, mot);
					for_each(mot.begin(), mot.end(), [](char & c) {c = ::tolower(c);});
					if (!mot.empty())
					{
						insert(mappeGlobal, mot); // attrape tous les mots pour le "5e fichier"
						insert(mesMappes[i], mot);
					}
				}
				livre.close();
			}
			else cerr << "file not found\n";
			
			//récupere le nom du fichier pour affichage plus tard.
			titres.push_back(lesLivres[i].substr(11));
			// remplissage de la multimap avec les int comme clef.
			for(auto const &kv : mesMappes[i])
				mesMultis[i].insert(make_pair(kv.second, kv.first));
		}
		// ajoute le string pour afficher le résultat global
		titres.push_back("les 4 fichiers");
		
		/* ajoute la mappe global au vector de map permettant l'utilisation 
		 * dans les boucles avec les autres livres.*/
		mesMappes.push_back(mappeGlobal);
		// remplissage de la multimap global avec les int comme clef.
		for(auto const &kv : mappeGlobal)
			multiMappeGlobal.insert(make_pair(kv.second, kv.first));

		mesMultis.push_back(multiMappeGlobal);
	}
	/* Fonction insert qui permet de compter les occurences du même mot
	 * si il n'est pas déjà dans la mappes, la clef est créer avec a valeur 1.*/
	void insert(map &theMap, string mot)
	{
		if(theMap.find(mot) != theMap.end())
			theMap[mot]++;
		else theMap.insert(pair<string, int>(mot, 1));
	}

/* getters */

	vector<map> getMesMappes()
	{
		return mesMappes;
	}
	
	vector<multi> getMesMultis()
	{
		return mesMultis;
	}
	
	vector<string> getTitres()
	{
		return titres;
	}
	
	int getSize()
	{
		return mesMappes.size();
	}
};

#endif // MAPPING_H
