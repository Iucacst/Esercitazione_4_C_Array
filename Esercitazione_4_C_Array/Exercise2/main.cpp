#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <iomanip>

using namespace std;

array<double, 8> partiziona_S(const array<double, 8>& w, double S);
double calcola_V(const array<double, 8>& s_partizionato, const array<double, 8>& r);
double percentuale_di_ritorno(double S, double V);

int main()
{
	string nome, valore, riga;
	double S, V = 0.0;
	int n, i = 0;
	
	array <double, 8> s_part;
	
	ifstream file("data.txt");
	
	if (!file) {
        cerr << "Errore nell'apertura del file" << endl;
        return 1;
    }
    
    getline(file, riga); // Leggo la prima riga, dove c'è il valore di S
    istringstream ss(riga);
    getline(ss, nome, ';') && getline(ss, valore);
    S = stod(valore);
    
    getline(file, riga); // Leggo la seconda riga, dove c'è il valore di n
    istringstream ss2(riga);
    getline(ss2, nome, ';') && getline(ss2, valore);
    n = stoi(valore);
    
    array <double, 8> w;
	array <double, 8> r;
    
    getline(file, riga); // Butto via questa riga perchè w ed r sono i nomi delle liste
    
    string wi, ri;
    
    while(getline(file, riga)){
		istringstream ssi(riga);
		getline(ssi, wi, ';') && getline(ssi, ri);
		
		w[i] = stod(wi);
		r[i] = stod(ri);
		i++;
    }    
    
    s_part = partiziona_S(w, S);
    V = calcola_V(s_part, r);
    double perc = percentuale_di_ritorno(S, V);
    
    ofstream out("result.txt"); // Scrivo su file
    
    if (!out) {
        cerr << "Errore apertura file di output." << endl;
        return 1;
    }
    
    out << fixed << setprecision(2);
    out << "S = " << S << ", n = " << n << "\n";

    out << "w = [ ";
    for (int i = 0; i < n; i++) out << w[i] << " ";
    out << "]\n";

    out << "r = [ ";
    for (int i = 0; i < n; i++) out << r[i] << " ";
    out << "]\n";

    out << setprecision(4);
    out << "Rate of return of the portfolio: " << perc << "\n";

    out << setprecision(2);
    out << "V: " << V << "\n";

    out.close();
    
        
    return 0;
}

array<double, 8> partiziona_S(const array<double, 8>& w, double S){
	array<double, 8> s_partizionato;
	for (unsigned int i = 0; i < w.size(); i++){
		s_partizionato[i] = S*w[i];
	}
	return s_partizionato;
}

double calcola_V(const array<double, 8>& s_partizionato, const array<double, 8>& r){
	double V = 0.0;
	for (unsigned int i = 0; i < s_partizionato.size(); i++){
		V += s_partizionato[i]*(1 + r[i]);
	}
	return V;
}

double percentuale_di_ritorno(double S, double V){
	return(V/S - 1);
}