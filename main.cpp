#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

class AUTOMATA_DFA {
public:
    AUTOMATA_DFA(const set<int>& estados, 
                 const set<char>& alfabeto,
                 const map<int, map<char, int>>& f_transicion, 
                 const int& est_inicial, 
                 const set<int>& est_final)
        : estado(est_inicial), estados(estados), alfabeto(alfabeto), f_transicion(f_transicion), est_inicial(est_inicial), est_final(est_final) {}

      void transicion(char simbolo) {
        if (alfabeto.find(simbolo) != alfabeto.end()) {
            estado = f_transicion.at(estado).at(simbolo);
        } else {
            cout << "Simbolo de entrada '" << simbolo << " no pertenece al alfabeto :( " << endl;
        }
    }

    bool aceptacion(const string& cadena_unica) {
        estado = est_inicial;
        for (char simbolo : cadena_unica) {
            transicion(simbolo);
        }
        return est_final.find(estado) != est_final.end();
    }

    void minimizacion() {
        paso1();
        paso2();
        paso3();
        
        for (int i = 0; i < estados.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (!tabla[i][j])
                    cout << "(" << j << ", " << i << ") ";
            }
        }
        cout << endl;
    }

private:
    int estado;
    set<int> estados;
    set<char> alfabeto;
    map<int, map<char, int>> f_transicion;
    int est_inicial;
    set<int> est_final;
    vector<vector<bool>> tabla;

    void paso1() {
        //Inicializacion de la tabla de parejas
        int size = estados.size();
        tabla.resize(size, vector<bool>(size, false));
    }

    bool verificar(int estado1, int estado2) {
        //Esta función verifica, si dado un caracter del alfabeto desde los estados, se dirija a un estado final
        for (char simbolo : alfabeto) {
            estado1 = f_transicion.at(estado1).at(simbolo);
            estado2 = f_transicion.at(estado2).at(simbolo);

            if (estado1 != estado2) {
                if (estado1 >= 0 && estado2 >= 0 && estado1 < tabla.size() && estado2 < tabla[estado1].size()) {
                    if (estado1 > estado2 && tabla[estado1][estado2])
                        return true;
                    else if (estado1 < estado2 && tabla[estado2][estado1])
                        return true;
                }
            }
        }
        return false;
    }

    void paso2() {
        for (int i = 0; i < estados.size(); i++) {
            for (int j = 0; j < i; j++) {
                //validar que no exita un out of border
                bool i_es_final = (est_final.find(i) != est_final.end());
                bool j_es_final = (est_final.find(j) != est_final.end());

                //si son diferente, es decir, alguno pertenece a F, se marca 
                if (i_es_final != j_es_final) {
                    tabla[i][j] = true;
                } else if (verificar(j, i)) {
                    tabla[i][j] = true;
                }
            }
        }
    }

    void paso3() {
        bool marca = true;
        //Se recorre la tabla, buscando generar marcas sobre las casillas no marcadas, hasta que no se generen nuevas
        while (marca) {
            marca = false;
            for (int i = 1; i < estados.size(); i++) {
                for (int j = 0; j < i; j++) {
                    if (!tabla[i][j] && verificar(i, j))
                        tabla[i][j] = true;
                }
            }
        }
    }
};

int main() {
    int t;
    cin >> t;
    for(int r = 0; r < t; r++){
        int n;
        cin >> n;
    
        string alf, finales;
        int est_inicial = 0;
        set<int> estados;
        set<int> est_final;
        set<char> alfabeto;
        map<int, map<char, int>> f_transicion;
    
        cin.ignore();
        getline(cin, alf);
        for (int i = 0; i < alf.length(); i += 2) {
            alfabeto.insert(alf[i]);
        }
    
        getline(cin, finales);
        for (int i = 0; i < finales.length(); i += 2) {
            est_final.insert(finales[i] - '0');
        }
    
        for (int i = 0; i < n; i++) {
            int estado_actual, estado_siguiente;
            cin >> estado_actual;
            estados.insert(estado_actual);
            for(char simbolo : alfabeto){
                cin >> estado_siguiente;
                f_transicion[estado_actual][simbolo] = estado_siguiente;
            }
        }
    
        AUTOMATA_DFA automata_dfa(estados, alfabeto, f_transicion, est_inicial, est_final);
        automata_dfa.minimizacion();
    }
}
