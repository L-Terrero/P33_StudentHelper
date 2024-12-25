#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <functional>
#include <filesystem>
#include <cmath>

using namespace std;
namespace fs = std::filesystem;

const string FILE_PATH = "credencialesP33.txt";

void CheckAndCreateFile() {
    if (!fs::exists(FILE_PATH)) {
        ofstream file(FILE_PATH);
        if (!file) {
            cout << "Error al crear el archivo de usuarios.\n";
            return;
        }
        cout << "Archivo de usuarios creado exitosamente.\n";
    }
}

void hora() {
    time_t time1;
    time(&time1);
    cout << ctime(&time1);
}

vector<string> clases = {
    "Historia",
    "Quimica",
    "Fisica",
    "Ingles",
    "Matematicas",
    "Artes",
    "Atletismo",
    "Etica" };

void RegistrarUsuario() {
    string username, password;
    cout << "Ingrese un nombre de usuario: ";
    cin >> username;
    cout << "Ingrese una contrasena: ";
    cin >> password;

    ofstream file(FILE_PATH, ios::app);
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

    ifstream file(FILE_PATH);
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

void CambiarNombreDeClase() {
    int index;
    string newName;

    cout << "Ingrese el numero de la clase que desea cambiar (1-8): ";
    if (!(cin >> index)) {
        cout << "Entrada invalida. Debe ser un numero." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (index < 1 || index > 8) {
        cout << "Numero de clase invalido!" << endl;
        return;
    }

    cin.ignore();
    cout << "Ingrese el nuevo nombre para la clase " << clases[index - 1] << ": ";
    getline(cin, newName);

    clases[index - 1] = newName;
    cout << "Nombre de clase actualizado correctamente." << endl;

    ofstream outFile("classes.txt");
    if (!outFile) {
        cout << "Error al abrir el archivo para guardar los cambios." << endl;
        return;
    }

    for (const auto& clase : clases) {
        outFile << clase << endl;
    }
    outFile.close();
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

void MostrarClases() {
    cout << "Lista de clases:\n";
    for (int i = 0; i < clases.size(); ++i) {
        cout << i + 1 << ") " << clases[i] << endl;
    }
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
    cout << "\nDesea volver al menu principal? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int main() {
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
            cout << "6) Cerrar sesion\n";
            cin >> opcion;

            switch (opcion) {
                case 1: Asistencia(); break;
                case 2: MostrarClases(); break;
                case 3: Calificaciones(); break;
                case 4: HoraHastaSalida(); break;
                case 5: CambiarNombreDeClase(); break;
                case 6:
                    loggedIn = false;
                    cout << "Sesion cerrada.\n";
                    break;
                default:
                    cout << "Opcion no valida" << endl;
                    break;
            }
        }

        if (loggedIn) {
            opc = SwitchReset();
        } else {
            opc = false;
        }

    } while (opc);

    return 0;
}
