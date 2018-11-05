#include "network.h"
#include "random.h"
#include <iostream>


bool Network::add_link	(const size_t & a,const size_t & b ) {
	
	
	if ((a==b) or (a>= (size()) ) or (b>= ( size() ) ) ) { return false; }
	
	for (auto itr = links.begin(); itr != links.end(); itr++)   {  
        if (((itr -> first == a) and (itr -> second == b)) and ((itr -> first == b) and (itr -> second == a)) )
        { return false; }
	}
             
	links.insert({a,b} ) ; 
	links.insert({b,a} );
	return true; 

}


size_t Network::degree	(const size_t & _n)	const {
	
	
	return links.count(_n);
}


std::vector<size_t> Network::neighbors	(const size_t & a )const {
	std::vector<size_t> v;
	v.clear();
	for (auto itr = links.begin(); itr != links.end(); itr++)   {  
        if ((itr -> first == a)) { v.push_back(itr -> second); } // on parcourt la multimap: pour chaque a (key) trouvé on ajoute
        // dans un tableau l'indice qui lui est associé ( = son voisin)
	}
	return v;
}


size_t Network::random_connect	(const double &  mean_deg)	{

	links.clear();
	size_t deg(0);
	std::vector<int> tab_uniform(1);
	size_t compteur(0);
	
	/*std::random_device rd{};
	std::mt19937 generator(rd());
	std::uniform_int_distribution<>uniform(0, size()-1); */
	
	for (size_t i(0) ; i< size() -1 ; ++i) { // -1
		
	deg = RNG.poisson(mean_deg);
		
		// if (deg > values.size() -1) { 
			//throw (std::runtime_error("Network::random_connect : degré supérieur au nombre de liens qu'on peut créer") ) ; } //
			
		//else { 
			//int link(deg - degree(i) );  //POURQUOI
			for (size_t j(0); j< deg ; ++j) {
			
			do {
				 RNG.uniform_int(tab_uniform, 0, size() -1 ) ; // peut prendre des valeurs entre 0 et size() -1 (indices du
				 // tableau de values)
				
				 }
			
			 while (not add_link(i, tab_uniform[0]) ) ;   // uniform(generator)//continue
			 // on accède au premier élément du tableau de taille 1 car la fonction de random, uniform_int remplit un tableau de
			 // int par une distribution uniforme et ne retourne pas simplement un int. C'est pourquoi on doit utiliser un tableau
			 ++compteur;
			 
	 }
 }
	 
	 return compteur;
	 
}




void Network::resize(const size_t & new_size) {
	if( new_size > 0) { values.clear() ;
		values.resize(new_size) ; }
		
	RNG.normal(values, 0, 1); 
	
}


size_t Network::set_values	(const std::vector< double > & v) {
	

	if (v.size() <= values.size() ) {
		for (size_t i(0); i< v.size() ; ++i) {
		values[i] = v[i];
		}
		return v.size(); 
		
	}
	
	if (v.size() > values.size() ) {
		for (size_t i(0); i< values.size() ; ++i) {
		values[i] = v[i]; }
		return values.size(); 
	}
	
	return 0;
} 
	
	


size_t Network::size()	const {
	return values.size(); 
}

	

std::vector<double> Network::sorted_values() const {	
		
		
std::vector<double> sorted_tab(values);
std::sort (std::begin(sorted_tab) , std::end(sorted_tab) ); // ordre croissant
std::reverse (std::begin(sorted_tab) , std::end(sorted_tab) ); // on reverse pour avoir l'ordre décroissant
return sorted_tab;

 }


double Network::value(const size_t & n	) const {
	if (n < values.size() ) {
	return values[n]; } // vérifier que le numero est bien dans la size du tableau
}

