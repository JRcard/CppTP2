#ifndef TP2_H
#define TP2_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "Mapping.h"
#include "MinMax.h"
#include "Compare.h"

using namespace std;

class Process
{
	typedef map<string, int> map;
	typedef multimap<int, string> multi;
	typedef const pair<string, int> paireSint;
	
public:
		Process(){};

		Process(int argc, char** argv)
		{
			// nombre d'élément à afficher. Valeur a entrer à l'exécution sinon valeur par défaut = 5
			int nbElement;
			if(argc == 1)
				nbElement = 5;
			else nbElement = atoi(argv[1]);
			
			/* création d'un vector avec le chemin du fichier. 
			 * Ce vector sera envoyé à l'objet mapping*/
			vector<string> lesLivres;
			lesLivres.push_back("fic_depart/arlequin.txt");
			lesLivres.push_back("fic_depart/camelias.txt");
			lesLivres.push_back("fic_depart/germinal.txt");
			lesLivres.push_back("fic_depart/ptprince.txt");
			
			// La création de cet objet génère une map et une multimap à l'aide des fichiers donnés en argument.
			Mapping mapping(lesLivres);
			// retourne le nombre de map (les 4 fichiers + global).
			int nbMap = mapping.getSize();
			
			/* Pour les opérations 1 & 2, puisque les mappes se classent automatiquement en ordre croissant, 
			 * nous n'avons qu'à afficher avec le bon itérateur.*/
			
			// OPÉRATION 1:
			cout << "Le Maximum dans chacun des 4 fichiers et globalement\n";
			// Pour chaque map.
			for (int i = 0; i<nbMap; i++)
			{
				// on attrape les mappes à tour de rôle.
				multi current = mapping.getMesMultis()[i];
				/* affichage du titre à l'aide du titre du fichier 
				 * affichage des données grâce à l'intérateur qui commence par la fin*/ 
				cout << mapping.getTitres()[i] + "--> " <<  current.rbegin()->second << " " << current.rbegin()->first << endl;
			}
			// OPÉRATION 2:
			cout << "Le Minimum dans chacun des 4 fichiers et globalement\n";
			for (int i = 0; i<nbMap; i++)
			{
				// même principe que l'opération 1 mais en commençant par le début.
				multi current = mapping.getMesMultis()[i];
				cout << mapping.getTitres()[i] + "--> " <<  current.begin()->second << " " << current.begin()->first << endl;
			}
			
			// OPÉRATION 3:
			MinMax minMax;
			minMax.getMin(mapping, nbElement, nbMap);
			
			// OPÉRATION 4:
			minMax.getMax(mapping, nbElement, nbMap);
			
			// OPÉRATION 5-6:
			cout << "Se trouve dans l'un mais pas dans l'autre, tests croisés avec tous les fichiers" << endl;
			cout << "Se trouve dans l'un et dans l'autre, tests croisés avec tous les fichiers" << endl;
			Compare compOp5(lesLivres, mapping);
		}

};


#endif // TP2_H
