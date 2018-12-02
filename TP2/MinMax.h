#ifndef MINMAX_H
#define MINMAX_H

#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "Mapping.h"

class MinMax
{
	typedef multimap<int, string> multi;
	multi::iterator it;
	multi::reverse_iterator revIt;
	
public:
	MinMax(){};

	void getMin(Mapping mm, int nbElement, int nbMap)
	{	cout << "Les " << nbElement << " clés associées à la plus petite valeur" << endl;
		for (int i = 0; i<nbMap; i++)
		{	
			multi current = mm.getMesMultis()[i];
			// place l'itératteur du multimapp au début de la multi courante.
			it = current.begin();
			cout << mm.getTitres()[i] + "--> les clés associées à la valeur " << it->first << " sont: ";
			// boucle au nombre entré en argument à l'exécution du programme.
			for(int j = 0; j<nbElement; j++)
			{
				// affichage de la value
				cout << it->second << " ";
				// incrémente l'itérateur.
				++it;
			}
			cout << endl;
		}
	}
	
	void getMax(Mapping mm, int nbElement, int nbMap)
	{
		cout << "Les " << nbElement << " valeurs plus élevées et les clés respectives à chacune d'elle" << endl;
		for (int i = 0; i<nbMap; i++)
			{
				multi current = mm.getMesMultis()[i];
				// place le reverse_iterator à la fin.
				revIt = current.rbegin();
				cout << mm.getTitres()[i] + "--> les " << nbElement << " valeurs Max sont: ";
				// ce vector contient les valeurs maximales qui serviront à la recherche dans le multimap.
				vector<int> max;
				for(int j = 0; j<nbElement; j++)
				{
					// boucle sur n éléments, remplis le vector, affiche les valeurs maximales
					max.push_back(revIt->first);
					cout << revIt->first << " ";
					// incrémente l'itérateur.
					++revIt;
				}
				cout << endl;
				int maxSize = max.size();
				multi::iterator mmIt;
				for(int k = 0; k < maxSize; k++)
				{
					cout << mm.getTitres()[i] << " les clés associées à la valeur " << max[k] << " sont: ";
					// affiche tous les occurances de la clef trouvées avec le equal_range.
					for (mmIt = current.equal_range(max[k]).first; mmIt != current.equal_range(max[k]).second; mmIt++)
						cout  << mmIt->second << " ";
					cout << endl;
				}
			}
	}


};

#endif // MINMAX_H
