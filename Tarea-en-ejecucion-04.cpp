#include <iostream>
#include <vector>
#include <string>
#include <algorithm>   
#include <cmath>     
using namespace std;

class Estudiante {
public:
    string nombre;
    int anioNacimiento;
    double gpa;
    double presupuesto;

    Estudiante() {
        nombre = "NN";
        anioNacimiento = 0;
        gpa = 0;
        presupuesto = 0;
    }

    Estudiante(string n, int a, double g, double p) {
        nombre = n;
        anioNacimiento = a;
        gpa = g;
        presupuesto = p;
    }

    double indiceUniversidad() const {
        return fabs(gpa - 3) * presupuesto;
    }
};


bool porAnio(const Estudiante& a, const Estudiante& b) {
    return a.anioNacimiento < b.anioNacimiento;
}

bool porGpa(const Estudiante& a, const Estudiante& b) {
    return a.gpa < b.gpa;
}

bool porPresupuesto(const Estudiante& a, const Estudiante& b) {
    return a.presupuesto < b.presupuesto;
}

bool porIndice(const Estudiante& a, const Estudiante& b) {
    return a.indiceUniversidad() < b.indiceUniversidad();
}


Estudiante pedirDatos() {
    Estudiante e;
    cin.ignore();                       
    cout << "Nombre: ";
    getline(cin, e.nombre);
    cout << "Anio de nacimiento: ";
    cin >> e.anioNacimiento;
    cout << "Promedio (GPA): ";
    cin >> e.gpa;
    cout << "Presupuesto: ";
    cin >> e.presupuesto;
    return e;
}


void imprimir(const vector<Estudiante>& estudiantes) {
    cout << "\n--- Lista de estudiantes ---\n";
    if (estudiantes.empty()) {
        cout << "(el vector esta vacio)\n";
        return;
    }
    for (int i = 0; i < (int)estudiantes.size(); i++) {
        cout << "[" << i << "] "
             << estudiantes[i].nombre << " | "
             << "Anio: " << estudiantes[i].anioNacimiento << " | "
             << "GPA: " << estudiantes[i].gpa << " | "
             << "Presupuesto: " << estudiantes[i].presupuesto << " | "
             << "Indice U: " << estudiantes[i].indiceUniversidad() << "\n";
    }
}


void insertar(vector<Estudiante>& estudiantes) {
    int donde, tipo;

    cout << "\n1. Insertar al final\n2. Insertar en un indice\nOpcion: ";
    cin >> donde;
    cout << "1. Estudiante por defecto (NN,0,0,0)\n2. Estudiante con datos\nOpcion: ";
    cin >> tipo;

    Estudiante nuevo;                  
    if (tipo == 2) {
        nuevo = pedirDatos();
    }

    if (donde == 1) {
        estudiantes.push_back(nuevo);
        cout << "Estudiante insertado al final.\n";
    } else if (donde == 2) {
        int indice;
        cout << "Indice (0 a " << estudiantes.size() << "): ";
        cin >> indice;
        if (indice >= 0 && indice <= (int)estudiantes.size()) {
            estudiantes.insert(estudiantes.begin() + indice, nuevo);
            cout << "Estudiante insertado en el indice " << indice << ".\n";
        } else {
            cout << "Indice invalido. No se inserto nada.\n";
        }
    } else {
        cout << "Opcion invalida.\n";
    }
}

void eliminar(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "\nEl vector esta vacio. No se puede eliminar.\n";
        return;
    }

    int opcion;
    cout << "\n1. Eliminar el ultimo\n2. Eliminar por indice\nOpcion: ";
    cin >> opcion;

    if (opcion == 1) {
        estudiantes.pop_back();
        cout << "Ultimo estudiante eliminado.\n";
    } else if (opcion == 2) {
        int indice;
        cout << "Indice (0 a " << estudiantes.size() - 1 << "): ";
        cin >> indice;
        if (indice >= 0 && indice < (int)estudiantes.size()) {
            estudiantes.erase(estudiantes.begin() + indice);
            cout << "Estudiante eliminado del indice " << indice << ".\n";
        } else {
            cout << "Indice invalido. No se elimino nada.\n";
        }
    } else {
        cout << "Opcion invalida.\n";
    }
}

void actualizar(vector<Estudiante>& estudiantes) {
    if (estudiantes.empty()) {
        cout << "\nEl vector esta vacio. No hay nada que actualizar.\n";
        return;
    }

    int indice;
    cout << "\nIndice del estudiante a actualizar (0 a "
         << estudiantes.size() - 1 << "): ";
    cin >> indice;

    if (indice >= 0 && indice < (int)estudiantes.size()) {
        cout << "Ingrese los nuevos datos:\n";
        estudiantes[indice] = pedirDatos();
        cout << "Estudiante actualizado.\n";
    } else {
        cout << "Indice invalido. No se actualizo nada.\n";
    }
}

void ordenar(vector<Estudiante>& estudiantes) {
    int opcion;
    cout << "\n1. Por anio de nacimiento\n2. Por GPA\n"
         << "3. Por presupuesto\n4. Por indice universidad\nOpcion: ";
    cin >> opcion;

    if (opcion == 1) {
        sort(estudiantes.begin(), estudiantes.end(), porAnio);
    } else if (opcion == 2) {
        sort(estudiantes.begin(), estudiantes.end(), porGpa);
    } else if (opcion == 3) {
        sort(estudiantes.begin(), estudiantes.end(), porPresupuesto);
    } else if (opcion == 4) {
        sort(estudiantes.begin(), estudiantes.end(), porIndice);
    } else {
        cout << "Opcion invalida.\n";
        return;
    }
    cout << "Estudiantes ordenados.\n";
}

int main() {
    vector<Estudiante> estudiantes;    
    int opcion;

    do {
        cout << "\n===== MENU ESTUDIANTES =====\n";
        cout << "1. Ingresar estudiante\n";
        cout << "2. Eliminar estudiante\n";
        cout << "3. Actualizar estudiante\n";
        cout << "4. Ordenar\n";
        cout << "5. Imprimir\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (cin.fail()) {              
            cout << "Entrada invalida. Saliendo del programa.\n";
            break;
        }

        if (opcion == 1) insertar(estudiantes);
        else if (opcion == 2) eliminar(estudiantes);
        else if (opcion == 3) actualizar(estudiantes);
        else if (opcion == 4) ordenar(estudiantes);
        else if (opcion == 5) imprimir(estudiantes);
        else if (opcion != 0) cout << "Opcion invalida.\n";

    } while (opcion != 0);

    cout << "Programa terminado.\n";
    return 0;
}