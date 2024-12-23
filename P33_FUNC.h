#ifndef P33_FUNC_H
#define P33_FUNC_H

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <functional>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

extern string FILE_PATH;

void CheckAndCreateFile();
void hora();
extern vector<string> clases;
void RegistrarUsuario();
bool IniciarSesion();
void CambiarNombreDeClase();
void Asistencia();
void MostrarClases();
void Calificaciones();
void HoraHastaSalida();
bool SwitchReset();

#endif // P33_FUNC_H