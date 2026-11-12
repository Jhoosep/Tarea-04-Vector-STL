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

bool insertarEn(vector<Estudiante>& v, int indice, Estudiante e) {
    if (indice < 0 || indice > (int)v.size()) return false;
    v.insert(v.begin() + indice, e);
    return true;
}

void insertarAlFinal(vector<Estudiante>& v, Estudiante e) {
    v.push_back(e);
}

bool eliminarUltimo(vector<Estudiante>& v) {
    if (v.empty()) return false;
    v.pop_back();
    return true;
}

bool eliminarEn(vector<Estudiante>& v, int indice) {
    if (v.empty()) return false;
    if (indice < 0 || indice >= (int)v.size()) return false;
    v.erase(v.begin() + indice);
    return true;
}

bool actualizarEn(vector<Estudiante>& v, int indice, Estudiante e) {
    if (indice < 0 || indice >= (int)v.size()) return false;
    v[indice] = e;
    return true;
}

bool ordenarPor(vector<Estudiante>& v, int criterio) {
    if (criterio == 1) sort(v.begin(), v.end(), porAnio);
    else if (criterio == 2) sort(v.begin(), v.end(), porGpa);
    else if (criterio == 3) sort(v.begin(), v.end(), porPresupuesto);
    else if (criterio == 4) sort(v.begin(), v.end(), porIndice);
    else return false;
    return true;
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
        insertarAlFinal(estudiantes, nuevo);
        cout << "Estudiante insertado al final.\n";
    } else if (donde == 2) {
        int indice;
        cout << "Indice (0 a " << estudiantes.size() << "): ";
        cin >> indice;
        if (insertarEn(estudiantes, indice, nuevo)) {
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
        eliminarUltimo(estudiantes);
        cout << "Ultimo estudiante eliminado.\n";
    } else if (opcion == 2) {
        int indice;
        cout << "Indice (0 a " << estudiantes.size() - 1 << "): ";
        cin >> indice;
        if (eliminarEn(estudiantes, indice)) {
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
        actualizarEn(estudiantes, indice, pedirDatos());
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

    if (ordenarPor(estudiantes, opcion)) {
        cout << "Estudiantes ordenados.\n";
    } else {
        cout << "Opcion invalida.\n";
    }
}

vector<Estudiante> crearBase() {
    vector<Estudiante> v;
    v.push_back(Estudiante("Ana",   2003, 3.8, 1000));
    v.push_back(Estudiante("Luis",  2000, 2.5, 500));
    v.push_back(Estudiante("Maria", 2001, 3.0, 3000));
    v.push_back(Estudiante("Pedro", 1999, 3.2, 100));
    return v;
}

void ejecutarPruebas() {
    vector<Estudiante> v;

    cout << "\n########## PRUEBAS DE FUNCIONAMIENTO ##########\n";
    cout << "Vector base: Ana(2003,3.8,1000) Luis(2000,2.5,500) "
         << "Maria(2001,3.0,3000) Pedro(1999,3.2,100)\n";

    cout << "\n=== PRUEBA 1: Insertar sin datos ===\n";
    cout << "Entrada: vector vacio; insertar al final un estudiante por defecto\n";
    cout << "Salida esperada: [0] NN | Anio: 0 | GPA: 0 | Presupuesto: 0 | Indice U: 0\n";
    v.clear();
    insertarAlFinal(v, Estudiante());
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 2: Insertar con datos ===\n";
    cout << "Entrada: vector base; insertar Sofia(2002,3.5,800) en el indice 1\n";
    cout << "Salida esperada: Ana, Sofia, Luis, Maria, Pedro (Sofia en [1], Indice U 400)\n";
    v = crearBase();
    insertarEn(v, 1, Estudiante("Sofia", 2002, 3.5, 800));
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 3: Eliminar el ultimo ===\n";
    cout << "Entrada: vector base; eliminar el ultimo\n";
    cout << "Salida esperada: Ana, Luis, Maria (Pedro ya no esta)\n";
    v = crearBase();
    eliminarUltimo(v);
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 4: Eliminar con indice ===\n";
    cout << "Entrada: vector base; eliminar el indice 1 (Luis)\n";
    cout << "Salida esperada: Ana, Maria, Pedro\n";
    v = crearBase();
    eliminarEn(v, 1);
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 5: No se elimina si el vector esta vacio ===\n";
    cout << "Entrada: vector vacio; intentar eliminar el ultimo\n";
    cout << "Salida esperada: no se elimina nada, el vector sigue vacio\n";
    v.clear();
    if (eliminarUltimo(v)) {
        cout << "Se elimino un estudiante (ERROR)\n";
    } else {
        cout << "No se elimino nada porque el vector esta vacio\n";
    }
    cout << "Salida obtenida:";
    imprimir(v);
    cout << "\n=== PRUEBA 6: Actualizar ===\n";
    cout << "Entrada: vector base; actualizar el indice 2 con Maria Lopez(2002,3.5,2000)\n";
    cout << "Salida esperada: Ana, Luis, Maria Lopez (Indice U 1000), Pedro\n";
    v = crearBase();
    actualizarEn(v, 2, Estudiante("Maria Lopez", 2002, 3.5, 2000));
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 7: Ordenar por anio de nacimiento ===\n";
    cout << "Entrada: vector base; ordenar por anio\n";
    cout << "Salida esperada: Pedro(1999), Luis(2000), Maria(2001), Ana(2003)\n";
    v = crearBase();
    ordenarPor(v, 1);
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 8: Ordenar por GPA ===\n";
    cout << "Entrada: vector base; ordenar por GPA\n";
    cout << "Salida esperada: Luis(2.5), Maria(3.0), Pedro(3.2), Ana(3.8)\n";
    v = crearBase();
    ordenarPor(v, 2);
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 9: Ordenar por presupuesto ===\n";
    cout << "Entrada: vector base; ordenar por presupuesto\n";
    cout << "Salida esperada: Pedro(100), Luis(500), Ana(1000), Maria(3000)\n";
    v = crearBase();
    ordenarPor(v, 3);
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n=== PRUEBA 10: Ordenar por indice universidad ===\n";
    cout << "Entrada: vector base; ordenar por indice universidad\n";
    cout << "Salida esperada: Maria(0), Pedro(20), Luis(250), Ana(800)\n";
    v = crearBase();
    ordenarPor(v, 4);
    cout << "Salida obtenida:";
    imprimir(v);

    cout << "\n########## FIN DE LAS PRUEBAS ##########\n";
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
        cout << "6. Ejecutar pruebas de funcionamiento\n";
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
        else if (opcion == 6) ejecutarPruebas();
        else if (opcion != 0) cout << "Opcion invalida.\n";

    } while (opcion != 0);

    cout << "Programa terminado.\n";
    return 0;
}