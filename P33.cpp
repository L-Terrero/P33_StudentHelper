#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <functional>
#include <filesystem>
#include <cmath>
#include <P33_FUNC.h>

using namespace std;
namespace fs = filesystem;

const string CREDENCIALES_FILEPATH = "credencialesP33.txt";
const string CLASSES_FILEPATH = "classes.txt";

void CheckAndCreateFile() {
    if (!fs::exists(CREDENCIALES_FILEPATH)) {
        ofstream file(CREDENCIALES_FILEPATH);
        if (!file) {
            cout << "Error al crear el archivo de usuarios.\n";
            return;
        }
        cout << "Archivo de usuarios creado exitosamente.\n";
    }
}

void CheckAndCreateClassesFile() {
    if (!fs::exists(CLASSES_FILEPATH)) {
        ofstream file(CLASSES_FILEPATH);
        if (!file) {
            cout << "Error al crear el archivo de clases.\n";
            return;
        }
        vector<string> defaultClasses = {
            "Historia", "Quimica", "Fisica", "Ingles",
            "Matematicas", "Artes", "Atletismo", "Etica"
        };
        for (const auto& cls : defaultClasses) {
            file << cls << endl;
        }
        cout << "Archivo de clases creado exitosamente con clases predeterminadas.\n";
    }
}

vector<string> LoadClasses() {
    vector<string> classes;
    ifstream file(CLASSES_FILEPATH);
    if (!file) {
        cout << "Error al cargar las clases. Asegúrese de que 'classes.txt' exista.\n";
        return classes;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            classes.push_back(line);
        }
    }
    return classes;
}

void SaveClasses(const vector<string>& classes) {
    ofstream file(CLASSES_FILEPATH);
    if (!file) {
        cout << "Error al guardar las clases.\n";
        return;
    }

    for (const auto& cls : classes) {
        file << cls << endl;
    }
}

void hora() {
    time_t time1;
    time(&time1);
    cout << ctime(&time1);
}

void RegistrarUsuario() {
    string username, password;
    cout << "Ingrese un nombre de usuario: ";
    cin >> username;
    cout << "Ingrese una contrasena: ";
    cin >> password;

    ofstream file(CREDENCIALES_FILEPATH, ios::app);
    if (!file) {
        cout << "Error al abrir el archivo para guardar el usuario.\n";
        return;
    }
    file << username << " " << password << endl;
    cout << "Usuario registrado exitosamente.\n";
}

bool IniciarSesion() {
    string username, password;
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contrasena: ";
    cin >> password;

    ifstream file(CREDENCIALES_FILEPATH);
    if (!file) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return false;
    }

    string storedUsername, storedPassword;
    bool found = false;

    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            cout << "Inicio de sesion exitoso.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Usuario o contrasena incorrectos.\n";
        return false;
    }

    return true;
}

void CambiarNombreDeClase(vector<string>& classes) {
    int index;
    string newName;

    cout << "Ingrese el numero de la clase que desea cambiar (1-" << classes.size() << "): ";
    if (!(cin >> index)) {
        cout << "Entrada invalida. Debe ser un numero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (index < 1 || index > classes.size()) {
        cout << "Numero de clase invalido!" << endl;
        return;
    }

    cin.ignore();
    cout << "Ingrese el nuevo nombre para la clase " << classes[index - 1] << ": ";
    getline(cin, newName);

    classes[index - 1] = newName;
    cout << "Nombre de clase actualizado correctamente." << endl;

    SaveClasses(classes);
}

void AgregarClase(vector<string>& classes) {
    string newClass;
    cout << "Ingrese el nombre de la nueva clase: ";
    cin.ignore();
    getline(cin, newClass);

    classes.push_back(newClass);
    SaveClasses(classes);
    cout << "Clase agregada exitosamente: " << newClass << endl;
}

void EliminarClase(vector<string>& classes) {
    int index;

    cout << "Lista de clases:\n";
    for (int i = 0; i < classes.size(); ++i) {
        cout << i + 1 << ") " << classes[i] << endl;
    }

    cout << "Ingrese el numero de la clase que desea eliminar: ";
    if (!(cin >> index) || index < 1 || index > classes.size()) {
        cout << "Numero de clase invalido.\n";
        return;
    }

    string removedClass = classes[index - 1];
    classes.erase(classes.begin() + index - 1);

    SaveClasses(classes);

    cout << "Clase eliminada exitosamente: " << removedClass << endl;
}

void MostrarClases(const vector<string>& classes) {
    cout << "Lista de clases:\n";
    for (int i = 0; i < classes.size(); ++i) {
        cout << i + 1 << ") " << classes[i] << endl;
    }
}

void Asistencia() {
    int ClasesTotal = 8;
    int ClasesAusente;

    cout << "He faltado a : \n";
    cin >> ClasesAusente;
    if (ClasesAusente > ClasesTotal) {
        cout << "Cantidad de clases con ausencia mayor a clases en total \n";
        return;
    }

    int Total = ClasesTotal - ClasesAusente;
    cout << "Ha asistido a un total de: " << Total << " clases de 8 clases\n";

    double porciento = (static_cast<double>(Total) / ClasesTotal) * 100;
    cout << "En promedio, asiste a un total de: " << porciento << "%\n";
}

void Calificaciones() {
    double NotaMatematicas, NotaQuimica, NotaFisica, NotaIngles, NotaHistoria, NotaArtes, NotaEtica, NotaAtletismo;
    cout << "Ingrese sus calificaciones :\n";
    cout << "Matematicas: "; cin >> NotaMatematicas;
    cout << "Quimica: "; cin >> NotaQuimica;
    cout << "Fisica: "; cin >> NotaFisica;
    cout << "Ingles: "; cin >> NotaIngles;
    cout << "Historia: "; cin >> NotaHistoria;
    cout << "Artes: "; cin >> NotaArtes;
    cout << "Etica: "; cin >> NotaEtica;
    cout << "Atletismo: "; cin >> NotaAtletismo;

    double NotaPromedio = (NotaMatematicas +
        NotaArtes +
        NotaAtletismo +
        NotaQuimica +
        NotaHistoria +
        NotaIngles +
        NotaEtica +
        NotaFisica) / 8;

    cout << "Promedio: " << NotaPromedio << endl;
    if (NotaPromedio > 100 || NotaPromedio < 0) {
        cout << "Promedio imposible. Por favor ingresar calificaciones nuevamente\n";
    }
}

void HoraHastaSalida() {
    time_t now;
    struct tm Hora_Salida = {};

    time(&now);
    struct tm* Hora_Actual = localtime(&now);

    int HoraElegida;
    int MinutosElegidos;

    do {
        cout << "Ingrese su hora de salida: ";
        cin >> HoraElegida;
    } while (HoraElegida > 24 || HoraElegida < 0);

    do {
        cout << "Ingrese su minuto de salida: ";
        cin >> MinutosElegidos;
    } while (MinutosElegidos > 60 || MinutosElegidos < 0);


    Hora_Salida = *Hora_Actual;
    Hora_Salida.tm_hour = HoraElegida;
    Hora_Salida.tm_min = MinutosElegidos;
    Hora_Salida.tm_sec = 0;

    time_t Hora_Salida1 = mktime(&Hora_Salida);

    if (difftime(Hora_Salida1, now) < 0) {
        Hora_Salida.tm_mday += 1;
        Hora_Salida1 = mktime(&Hora_Salida);
    }

    double seconds_left = difftime(Hora_Salida1, now);
    int hours_left = seconds_left / 3600;
    int minutes_left = (seconds_left - hours_left * 3600) / 60;
    int seconds_left_int = seconds_left - (hours_left * 3600 + minutes_left * 60);

    cout << "Tiempo restante hasta su hora de salida: "
         << hours_left << " horas, "
         << minutes_left << " minutos, "
         << seconds_left_int << " segundos.\n";
}

bool SwitchReset() {
    char choice;
    while (true) {
        cout << "\nDesea volver al menu principal? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            return true;
        } else if (choice == 'N' || choice == 'n') {
            return false;
        } else {
            cout << "Entrada invalida. Por favor, ingrese 'Y' o 'N'.\n";
        }
    }
}

int main() {

vector<string> classes = LoadClasses();

    int opcion;
    bool opc = false;
    bool loggedIn = false;

    CheckAndCreateFile();

    cout << "Fecha y hora actual: ";
    hora();

    do {
        if (!loggedIn) {
            cout << "\nElija una opcion:\n";
            cout << "1) Iniciar sesion\n";
            cout << "2) Registrar usuario\n";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    loggedIn = IniciarSesion();
                    break;
                case 2:
                    RegistrarUsuario();
                    loggedIn = true;
                    break;
                default:
                    cout << "Opcion no valida" << endl;
                    break;
            }

            if (loggedIn) {
                cout << "\nSesion iniciada exitosamente.\n";
            }

        } else {
            cout << "\nElija una opcion:\n";
            cout << "1) Medir asistencia\n";
            cout << "2) Mostrar clases\n";
            cout << "3) Promedio\n";
            cout << "4) Hora hasta salida\n";
            cout << "5) Cambiar nombre de clase\n";
            cout << "6) Agregar clase\n";
            cout << "7) Eliminar clase\n";
            cout << "0) Salir\n";
            cout << "Decision:  "; cin >> opcion;

            switch (opcion) {
                case 1: Asistencia(); break;

                case 2: MostrarClases(classes); break;

                case 3: Calificaciones(); break;

                case 4: HoraHastaSalida(); break;

                case 5: CambiarNombreDeClase(classes); break;

                case 6: AgregarClase(classes); break;

                case 7: EliminarClase(classes); break;

                case 0: loggedIn = false; cout << "Sesion cerrada.\n"; break;

                default: cout << "Opcion no valida" << endl; break;
            }
        }

        if (loggedIn) {
    opc = SwitchReset();
        } else {
            opc = false;
        }

    } while (opc);

}
