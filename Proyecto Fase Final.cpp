
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Articulo {
    int Codigo;
    char Nombre[50];
    int Precio;
    int Cantidad;
};

struct Cliente {
    int Cedula;
    char NombreApellido[50];
    char Direccion[100];
    char Telefono[15];
    int  frecuencia;
    double montoTotal;
};

struct Vendedor {
    int Cedula;
    char NombreApellido[50];
    char FechaIngreso[15]; 
    float PorcentajeComision;
};

struct Nodo {
    Articulo articulo;
    Nodo* siguiente;
};

struct NodoCliente {
    Cliente cliente;
    NodoCliente* siguiente;
};

struct NodoVendedor {
    Vendedor vendedor;
    NodoVendedor* siguiente;
};

void agregarDatos(Nodo*& lista, const Articulo& nuevoArticulo) {
    Nodo* nuevoNodo = new Nodo{ nuevoArticulo, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
}

void agregarCliente(NodoCliente*& lista, const Cliente& nuevoCliente) {
    NodoCliente* nuevoNodo = new NodoCliente{ nuevoCliente, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
}

void agregarVendedor(NodoVendedor*& lista, const Vendedor& nuevoVendedor) {
    NodoVendedor* nuevoNodo = new NodoVendedor{ nuevoVendedor, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
}

void mostrarRegistrosdeArticulos(Nodo* lista) {
    Nodo* actual = lista;
    while (actual != nullptr) {
        cout << "Codigoo: " << actual->articulo.Codigo << ", Nombre: " << actual->articulo.Nombre << ", Precio: " << actual->articulo.Precio << ", Cantidad: " << actual->articulo.Cantidad << endl;
        actual = actual->siguiente;
    }
}
void mostrarArticulosEnTabla(Nodo* listaArticulos) {
    cout << left << setw(15) << "Codigo" << setw(15) << "Nombre" << setw(20) << "Precio" << setw(15) << "Cantidad" << endl;

    for (Nodo* nodo = listaArticulos; nodo != nullptr; nodo = nodo->siguiente) {
        Articulo& articulo = nodo->articulo;
        cout << left << setw(10) << articulo.Codigo << setw(20) << articulo.Nombre << setw(22) << fixed << setprecision(5) << articulo.Precio << setw(10) << articulo.Cantidad << endl;
    }
}

void mostrarRegistrosdeClientes(NodoCliente* lista) {
    NodoCliente* actual = lista;    
    while (actual != nullptr) {
        cout << "Cedula: " << actual->cliente.Cedula << ", Nombre: " << actual->cliente.NombreApellido << ", Direccion: " << actual->cliente.Direccion << ", Telefono: " << actual->cliente.Telefono <<", Frecuencia de Compra: " << actual->cliente.frecuencia << endl;;
        actual = actual->siguiente;
    }
}
void mostrarClientesEnTabla(NodoCliente* listaClientes) {
    cout << left << setw(15) << "Cedula" << setfill(' ') << setw(50) << "Nombre y Apellido" << setfill(' ') << setw(100) << "Direccion" << setfill(' ') << setw(15) << "Teléfono" << setfill(' ') << setw(10) << "Frecuencia" << endl;
    for (NodoCliente* nodo = listaClientes; nodo != nullptr; nodo = nodo->siguiente) {
    Cliente& cliente = nodo->cliente;
    cout << left << setw(15) << cliente.Cedula << setfill(' ') << setw(50) << cliente.NombreApellido << setfill(' ') << setw(100) << cliente.Direccion << setfill(' ') << setw(15) << cliente.Telefono << setfill(' ') << setw(10) << cliente.frecuencia << endl;
    }
}
void mostrarRegistrosdeVendedores(NodoVendedor* lista) {
    NodoVendedor* actual = lista;
    while (actual != nullptr) {
        cout << "Cedula: " << actual->vendedor.Cedula << ", Nombre: " << actual->vendedor.NombreApellido << ", Fecha de Ingreso: " << actual->vendedor.FechaIngreso << ", Porcentaje de Comision: " << actual->vendedor.PorcentajeComision << endl;
        actual = actual->siguiente;
    }
}

void imprimirArticulo(const Articulo& articulo) {
    cout << "Codigo: " << articulo.Codigo << endl;
    cout << "Nombre: " << articulo.Nombre << endl;
    cout << "Precio: " << articulo.Precio << "$" << endl;
    cout << "Cantidad: " << articulo.Cantidad << endl;
}

void aMinusculas(char* str) {
    std::transform(str, str + strlen(str), str, [](unsigned char c) {
        return std::tolower(c);
    });
}
void eliminarEspacios(char* str) {
    char* dst = str;
    for (char* src = str; *src; ++src) {
        if (!isspace(static_cast<unsigned char>(*src))) {
            *dst++ = *src;
        }
    }
    *dst = '\0';
}

std::string convertirFechaParaComparacion(const char* fecha) {
    std::istringstream ss(fecha);
    int dia, mes, anio;
    char barra;
    ss >> dia >> barra >> mes >> barra >> anio;
    std::ostringstream resultado;
    resultado << std::setw(2) << std::setfill('0') << dia
            << std::setw(2) << std::setfill('0') << mes
            << anio;

    return resultado.str();
}

void buscarYMostrarArticulo(Nodo* listaArticulos, const char* nombreArticulo) {
    char nombreBusqueda[50];
    strncpy(nombreBusqueda, nombreArticulo, sizeof(nombreBusqueda));
    nombreBusqueda[sizeof(nombreBusqueda) - 1] = '\0'; 
    aMinusculas(nombreBusqueda);
    eliminarEspacios(nombreBusqueda);
    bool encontrado = false;
    cout << left << setw(10) << "Codigo" << setw(20) << "Nombre" << setw(10) << "Precio" << setw(10) << "Cantidad" << endl;
    cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;
    for (Nodo* nodo = listaArticulos; nodo != nullptr; nodo = nodo->siguiente) {
        Articulo& articulo = nodo->articulo;
        char nombreArticuloSinEspacios[50];
        strncpy(nombreArticuloSinEspacios, articulo.Nombre, sizeof(nombreArticuloSinEspacios));
        nombreArticuloSinEspacios[sizeof(nombreArticuloSinEspacios) - 1] = '\0';
        aMinusculas(nombreArticuloSinEspacios);
        eliminarEspacios(nombreArticuloSinEspacios);
        char* palabra = strtok(nombreBusqueda, " ");
        while (palabra != nullptr) {
            if (strstr(nombreArticuloSinEspacios, palabra) != nullptr) {
                cout << setw(10) << articulo.Codigo << setw(20) << articulo.Nombre << setw(10) << articulo.Precio << setw(10) << articulo.Cantidad << endl;
                encontrado = true;
                break;
            }
            palabra = strtok(nullptr, " ");
        }
    }
    if (!encontrado) {
        cout << "No se encontro ningun articulo con el nombre " << nombreArticulo << endl;
    }
}

vector<Nodo*> buscarArticuloPorCantidad(Nodo* cabeza, int cantidad) {
    vector<Nodo*> articulosConCantidad;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->articulo.Cantidad == cantidad) {
            articulosConCantidad.push_back(actual);
            imprimirArticulo(actual->articulo);
        }
        actual = actual->siguiente;
    }
    if (articulosConCantidad.empty()) {
        cout << "No se encontro ningun articulo con la cantidad especificada." << endl;
    }
    return articulosConCantidad; 
}

vector<Nodo*> buscarArticuloPorPrecio(Nodo* cabeza, int precio) {
    vector<Nodo*> articulosConPrecio;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        if (actual->articulo.Precio == precio) {
            articulosConPrecio.push_back(actual);
            imprimirArticulo(actual->articulo);
        }
        actual = actual->siguiente;
    }
    if (articulosConPrecio.empty()) {
        cout << "No se encontro ningun articulo con el precio especificado." << endl;
    }

    return articulosConPrecio; 
}

void imprimirInformacionCliente(const Cliente& cliente) {
    cout << "Informacion del Cliente:" << endl;
    cout << "Cedula: " << cliente.Cedula << endl;
    cout << "Nombre y Apellido: " << cliente.NombreApellido << endl;
    cout << "Direccion: " << cliente.Direccion << endl;
    cout << "Telefono: " << cliente.Telefono << endl;
    cout << "Frecuencia: " << cliente.frecuencia << endl;
}

void buscarClientePorCedula(NodoCliente* listaClientes, int cedula) {
    for (NodoCliente* nodo = listaClientes; nodo != nullptr; nodo = nodo->siguiente) {
        if (nodo->cliente.Cedula == cedula) {
            imprimirInformacionCliente(nodo->cliente);
            return;
        }
    }
    cout << "No se encontro ningún cliente con la cedula proporcionada." << endl;
}

void buscarClientePorNombreApellido(NodoCliente* listaClientes, const char* nombreApellido) {
    char nombreApellidoMinusculas[50];
    strcpy(nombreApellidoMinusculas, nombreApellido);
    aMinusculas(nombreApellidoMinusculas);
    eliminarEspacios(nombreApellidoMinusculas);
    for (NodoCliente* nodo = listaClientes; nodo != nullptr; nodo = nodo->siguiente) {
        char nombreApellidoClienteMinusculas[50];
        strcpy(nombreApellidoClienteMinusculas, nodo->cliente.NombreApellido);
        aMinusculas(nombreApellidoClienteMinusculas);
        eliminarEspacios(nombreApellidoClienteMinusculas);
        if (strcmp(nombreApellidoClienteMinusculas, nombreApellidoMinusculas) == 0) {
            imprimirInformacionCliente(nodo->cliente);
            return;
        }
    }
    cout << "No se encontro ningun cliente con el nombre y apellido proporcionados." << endl;
}

void buscarClientePorDireccion(NodoCliente* listaClientes, const char* direccion) {
    char direccionMinusculas[100];
    strcpy(direccionMinusculas, direccion);
    aMinusculas(direccionMinusculas);
    eliminarEspacios(direccionMinusculas);
    for (NodoCliente* nodo = listaClientes; nodo != nullptr; nodo = nodo->siguiente) {
        char direccionClienteMinusculas[100];
        strcpy(direccionClienteMinusculas, nodo->cliente.Direccion);
        aMinusculas(direccionClienteMinusculas);
        eliminarEspacios(direccionClienteMinusculas);
        if (strcmp(direccionClienteMinusculas, direccionMinusculas) == 0) {
            imprimirInformacionCliente(nodo->cliente);
            return;
        }
    }
    cout << "No se encontro ningun cliente con la direccion proporcionada." << endl;
}
void imprimirInformacionVendedor(const Vendedor& vendedor) {
    cout << "Informacion del Vendedor:" << endl;
    cout << "Cedula: " << vendedor.Cedula << endl;
    cout << "Nombre y Apellido: " << vendedor.NombreApellido << endl;
    cout << "Fecha de Ingreso: " << vendedor.FechaIngreso << endl;
    cout << "Porcentaje de Comision: " << vendedor.PorcentajeComision << endl;
}
void buscarVendedorPorCedula(NodoVendedor* listaVendedores, int cedula) {
    for (NodoVendedor* nodo = listaVendedores; nodo != nullptr; nodo = nodo->siguiente) {
        if (nodo->vendedor.Cedula == cedula) {
            imprimirInformacionVendedor(nodo->vendedor);
            return;
        }
    }
    cout << "No se encontro ningun vendedor con la cedula proporcionada." << endl;
}
void buscarVendedorPorNombreApellido(NodoVendedor* listaVendedores, const char* nombreApellido) {
    char nombreApellidoMinusculas[50];
    strcpy(nombreApellidoMinusculas, nombreApellido);
    aMinusculas(nombreApellidoMinusculas);
    eliminarEspacios(nombreApellidoMinusculas);
    for (NodoVendedor* nodo = listaVendedores; nodo != nullptr; nodo = nodo->siguiente) {
        char nombreApellidoVendedorMinusculas[50];
        strcpy(nombreApellidoVendedorMinusculas, nodo->vendedor.NombreApellido);
        aMinusculas(nombreApellidoVendedorMinusculas);
        eliminarEspacios(nombreApellidoVendedorMinusculas);
        if (strcmp(nombreApellidoVendedorMinusculas, nombreApellidoMinusculas) == 0) {
            imprimirInformacionVendedor(nodo->vendedor);
            return;
        }
    }
    cout << "No se encontro ningun vendedor con el nombre y apellido proporcionados." << endl;
}

vector<NodoVendedor*> buscarVendedorPorFechaIngreso(NodoVendedor* cabeza, const char* fecha) {
    vector<NodoVendedor*> vendedoresEncontrados;
    std::string fechaConvertida = convertirFechaParaComparacion(fecha);
    NodoVendedor* actual = cabeza;
    while (actual != nullptr) {
        std::string fechaActualConvertida = convertirFechaParaComparacion(actual->vendedor.FechaIngreso);
        if (fechaActualConvertida == fechaConvertida) {
            vendedoresEncontrados.push_back(actual);
            imprimirInformacionVendedor(actual->vendedor);
        }
        actual = actual->siguiente;
    }
    if (vendedoresEncontrados.empty()) {
        cout << "No se encontró ningún vendedor con la fecha de ingreso " << fecha << endl;
    }
    return vendedoresEncontrados;
}
void modificarArticulo(Nodo*& lista, int codigo) {
    Nodo* actual = lista;
    while (actual != nullptr) {
        if (actual->articulo.Codigo == codigo) {
            cout << "Ingrese los detalles del nuevo articulo\n";
            cout << "Ingrese el nombre: ";
            cin.ignore();
            cin.getline(actual->articulo.Nombre, 50);
            cout << "Ingrese el precio: ";
            cin >> actual->articulo.Precio;
            cout << "Ingrese la cantidad disponible: ";
            cin >> actual->articulo.Cantidad;
            cout << "Articulo actualizado correctamente.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Articulo no encontrado.\n";
}

void modificarCliente(NodoCliente*& lista, int cedula) {
    NodoCliente* actual = lista;
    while (actual != nullptr) {
        if (actual->cliente.Cedula == cedula) {
            cout << "Ingrese los detalles del nuevo cliente\n";
            cout << "Ingrese el nombre y apellido: ";
            cin.ignore();
            cin.getline(actual->cliente.NombreApellido, 50);
            cout << "Ingrese la direccion: ";
            cin.getline(actual->cliente.Direccion, 100);
            cout << "Ingrese el telefono: ";
            cin.getline(actual->cliente.Telefono, 15);
            cout << "Cliente actualizado correctamente.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Cliente no encontrado.\n";
}

void modificarVendedor(NodoVendedor*& lista, int cedula) {
    NodoVendedor* actual = lista;
    while (actual != nullptr) {
        if (actual->vendedor.Cedula == cedula) {
            cout << "Ingrese los detalles del nuevo vendedor\n";
            cout << "Ingrese el nombre y apellido: ";
            cin.ignore();
            cin.getline(actual->vendedor.NombreApellido, 50);
            cout << "Ingrese la fecha de ingreso: ";
            cin.getline(actual->vendedor.FechaIngreso, 15);
            cout << "Ingrese el porcentaje de comision: ";
            cin >> actual->vendedor.PorcentajeComision;
            cout << "Vendedor actualizado correctamente.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Vendedor no encontrado.\n";
}

void eliminarArticulo(Nodo*& lista, int codigo) {
    if (lista == nullptr) {
        cout << "\n Articulo no encontrado";
    } else if (lista->articulo.Codigo == codigo) {
        Nodo* temp = lista;
        lista = lista->siguiente;
        delete temp;
        cout << "\n Articulo eliminado correctamente";
    } else {
        Nodo* actual = lista;
        while (actual->siguiente != nullptr && actual->siguiente->articulo.Codigo != codigo) {
            actual = actual->siguiente;
        }
        if (actual->siguiente == nullptr) {
            cout << "\n Articulo no encontrado";
        } else {
            Nodo* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            cout << "\n Articulo eliminado correctamente";
        }
    }
}

void eliminarCliente(NodoCliente*& lista, int cedula) {
    if (lista == nullptr) {
        cout << "\n Cliente no encontrado";
    } else if (lista->cliente.Cedula == cedula) {
        NodoCliente* temp = lista;
        lista = lista->siguiente;
        delete temp;
        cout << "\n Cliente eliminado correctamente";
    } else {
        NodoCliente* actual = lista;
        while (actual->siguiente != nullptr && actual->siguiente->cliente.Cedula != cedula) {
            actual = actual->siguiente;
        }
        if (actual->siguiente == nullptr) {
            cout << "\n Cliente no encontrado";
        } else {
            NodoCliente* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            cout << "\n Cliente eliminado correctamente";
        }
    }
}

void eliminarVendedor(NodoVendedor*& lista, int cedula) {
    if (lista == nullptr) {
        cout << "\n Vendedor no encontrado";
    } else if (lista->vendedor.Cedula == cedula) {
        NodoVendedor* temp = lista;
        lista = lista->siguiente;
        delete temp;
        cout << "\n Vendedor eliminado correctamente";
    } else {
        NodoVendedor* actual = lista;
        while (actual->siguiente != nullptr && actual->siguiente->vendedor.Cedula != cedula) {
            actual = actual->siguiente;
        }
        if (actual->siguiente == nullptr) {
            cout << "\n Vendedor no encontrado";
        } else {
            NodoVendedor* temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            cout << "\n Vendedor eliminado correctamente";
        }
    }
}

int Esnum() {
    int num;
    while (!(cin >> num)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n Por favor, ingresa un número: ";
    }
    return num;
}

bool esSoloLetras(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && !isspace(str[i])) {
            cout << "\n Ingrese un nombre correcto";
            return false;
        }
    }
    return true;
}

int obtenerCantidadArticulos() {
    int n;
    cout << "\n Ingrese la cantidad de articulos que desea registrar: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n Por favor, ingresa una cantidad válida: ";
    }
    cin.ignore();
    return n;
}

int obtenerCantidadClientes() {
    int n;
    cout << "\n Ingrese la cantidad de clientes que desea registrar: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n Por favor, ingresa una cantidad válida: ";
    }
    cin.ignore();
    return n;
}

int obtenerCantidadVendedores() {
    int n;
    cout << "\n Ingrese la cantidad de vendedores que desea registrar: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n Por favor, ingresa una cantidad válida: ";
    }
    cin.ignore();
    return n;
}

void liberarMemoria(Nodo*& lista) {
    while (lista != nullptr) {
        Nodo* temp = lista;
        lista = lista->siguiente;
        delete temp;
    }
}

void liberarMemoriaClientes(NodoCliente*& lista) {
    while (lista != nullptr) {
        NodoCliente* temp = lista;
        lista = lista->siguiente;
        delete temp;
    }
}

void liberarMemoriaVendedores(NodoVendedor*& lista) {
    while (lista != nullptr) {
        NodoVendedor* temp = lista;
        lista = lista->siguiente;
        delete temp;
    }
}

NodoCliente* listaClientes = nullptr;
NodoVendedor* listaVendedores = nullptr;

void agregarDatosArticuloUnico(Nodo*& lista, const Articulo& nuevoArticulo) {
    Nodo* nuevoNodo = new Nodo{ nuevoArticulo, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        Nodo* actual = lista;
        while (actual->siguiente != nullptr) {
            if (actual->articulo.Codigo == nuevoArticulo.Codigo) {
                delete nuevoNodo;  
                return;
            }
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

void leerArticulosDesdeArchivo(Nodo*& lista) {
    ifstream archivo("Articulos.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo de Articulos.txt" << endl;
        return;
    }
    Articulo nuevoArticulo; 
    while (archivo.ignore(numeric_limits<streamsize>::max(), ':') && archivo >> nuevoArticulo.Codigo) {
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo.getline(nuevoArticulo.Nombre, 50);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo >> nuevoArticulo.Precio;
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo >> nuevoArticulo.Cantidad;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        agregarDatosArticuloUnico(lista, nuevoArticulo);
    }
    archivo.close();
}


void agregarClienteUnico(NodoCliente*& lista, const Cliente& nuevoCliente) {
    NodoCliente* nuevoNodo = new NodoCliente{ nuevoCliente, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        NodoCliente* actual = lista;
        while (actual->siguiente != nullptr) {
            if (actual->cliente.Cedula == nuevoCliente.Cedula) {
                delete nuevoNodo;
                return;
            }
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

void leerClientesDesdeArchivo(NodoCliente*& lista) {
    ifstream archivo("Clientes.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo de Clientes.txt" << endl;
        return;
    }
    Cliente nuevoCliente;
    while (archivo.ignore(numeric_limits<streamsize>::max(), ':') && archivo >> nuevoCliente.Cedula) {
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo.getline(nuevoCliente.NombreApellido, 50);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo.getline(nuevoCliente.Direccion, 100);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo.getline(nuevoCliente.Telefono, 15);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo >> nuevoCliente.frecuencia;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        agregarClienteUnico(lista, nuevoCliente);
    }
    archivo.close();
}


void agregarVendedorUnico(NodoVendedor*& lista, const Vendedor& nuevoVendedor) {
    NodoVendedor* nuevoNodo = new NodoVendedor{ nuevoVendedor, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        NodoVendedor* actual = lista;
        while (actual->siguiente != nullptr) {
            if (actual->vendedor.Cedula == nuevoVendedor.Cedula) {
                delete nuevoNodo;  // Eliminar el nodo si ya existe un registro con la misma cédula
                return;
            }
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

void leerVendedoresDesdeArchivo(NodoVendedor*& lista) {
    ifstream archivo("Vendedores.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo de Vendedores.txt" << endl;
        return;
    }
    Vendedor nuevoVendedor;
    while (archivo.ignore(numeric_limits<streamsize>::max(), ':') && archivo >> nuevoVendedor.Cedula) {
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo.getline(nuevoVendedor.NombreApellido, 50);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo.getline(nuevoVendedor.FechaIngreso, 15);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo >> nuevoVendedor.PorcentajeComision;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        agregarVendedorUnico(lista, nuevoVendedor);
    }
    archivo.close();
}


int main() {
    Nodo* listaArticulos = nullptr;
    int opcion;
    do {
        cout << "\n ****Bienvenido Tienda RGP****";
        cout << "\n 1. Gestion de Articulos";
        cout << "\n 2. Gestion de Clientes";
        cout << "\n 3. Gestion de Vendedores";
        cout << "\n 4. Gestion de Descuentos";
        cout << "\n 5. Generar Facturas";
        cout << "\n 6. Salir";
        cout << "\n Su opcion: ";
        if (cin >> opcion) {
            switch (opcion) {
            case 1: {
                int opcionArticulos;
                do {
                    cout << "\n ****Bienvenido al apartado de Articulos****";
                    cout << "\n 1. Agregar un Articulo";
                    cout << "\n 2. Modificar un Articulo";
                    cout << "\n 3. Eliminar un Articulo";
                    cout << "\n 4. Mostrar Articulos";
                    cout << "\n 5. Buscar Articulo";
                    cout << "\n 6. Guardar Articulos";
                    cout << "\n 7. Cargar Articulos";
                    cout << "\n 8. Salir al menu anterior";
                    cout << "\n Su opcion: ";
                    if (cin >> opcionArticulos) {
                        switch (opcionArticulos) {
                        case 1: {
                            // Agregar Articulos
                            int n = obtenerCantidadArticulos();
                            for (int i = 0; i < n; i++) {
                                Articulo nuevoArticulo;
                                cout << "\n Ingrese el codigo del Articulo " << i + 1 << ": ";
                                nuevoArticulo.Codigo = Esnum();
                                cin.ignore();
                                cout << "\n Ingrese el nombre del Articulo " << i + 1 << ": ";
                                cin.getline(nuevoArticulo.Nombre, 50);
                                while (!esSoloLetras(nuevoArticulo.Nombre)) {
                                    cout << "\n Ingrese el nombre del Articulo " << i + 1 << " correctamente: ";
                                    cin.getline(nuevoArticulo.Nombre, 50);
                                }
                                cout << "\n Ingrese el precio del Articulo " << i + 1 << ": ";
                                nuevoArticulo.Precio = Esnum();
                                cout << "\n Ingrese la cantidad disponible del Articulo " << i + 1 << ": ";
                                nuevoArticulo.Cantidad = Esnum();
                                cin.ignore();
                                agregarDatos(listaArticulos, nuevoArticulo);
                                cout << "\n Articulo Agregado Correctamente";
                            }
                            break;
                        }
                        case 2: {
                            // Modificar Articulos
                            int codigo;
                            cout << "Ingrese el codigo del Articulo a modificar: ";
                            cin >> codigo;
                            modificarArticulo(listaArticulos, codigo);
                            break;
                        }
                        case 3: {
                            // Eliminar Articulos
                            int codigo;
                            cout << "Ingrese el codigo del Articulo a eliminar: ";
                            cin >> codigo;
                            eliminarArticulo(listaArticulos, codigo);
                            break;
                        }
                        case 4: {
                            // Mostrar Articulos
                            
                           system("clear");
                            
                            mostrarArticulosEnTabla(listaArticulos);
                            

                            system("sleep 5s");
                            break;
                        }
                        case 5: {
                        int opb;
                        int cantidad;
                        int precio;
                        char nombre[50];
                        do {
                            cout << "\n Escoja el campo por el cual quiere buscar";
                            cout << "\n 1. Por Nombre";
                            cout << "\n 2. Por Precio";
                            cout << "\n 3. Por Cantidad";
                            cout << "\n 4. Volver al menú anterior";
                            cout << "\n Su opcion: ";
                            cin >> opb;
                            switch (opb) {
                                case 1: {
                                    cout << "Introduce el nombre del articulo: ";
                                    cin.ignore();
                                    cin.getline(nombre, 50);
                                    buscarYMostrarArticulo(listaArticulos, nombre);
                                    break;
                                }
                                case 2: {
                                    cout << "Introduce el precio del articulo: ";
                                    cin >> precio;
                                    buscarArticuloPorPrecio(listaArticulos, precio);
                                    break;
                                }
                                case 3: {
                                    cout << "Introduce la cantidad del articulo: ";
                                    cin >> cantidad;
                                    buscarArticuloPorCantidad(listaArticulos, cantidad);
                                    break;
                                }
                                case 4: {
                                    cout << "\n Volviendo al menú anterior...\n";
                                    break;
                                }
                                default:
                                    cout << "Opcion no valida.\n";
                            }
                        } while (opb != 4);
                        break;
                        }
                        case 6: {
                            //Guardar Estructura
                        ofstream archivo("Articulos.txt");
                        Nodo* actual = listaArticulos;
                        while (actual != nullptr) {
                            archivo << "Codigo: " << actual->articulo.Codigo << "\n";
                            archivo << "Nombre: " << actual->articulo.Nombre << "\n";
                            archivo << "Precio: " << actual->articulo.Precio <<"$" "\n";
                            archivo << "Cantidad: " << actual->articulo.Cantidad << "\n";
                            archivo << "------------------------\n";
                            actual = actual->siguiente;
                        }
                        archivo.close();
                        cout <<" \n Guardado Generado Correctamente";
                        break;
                        }
                        case 7: {
                            int opcionAA;
                            cout << "\n Desea cargar los articulos desde un archivo";
                            cout << "\n 1. Si";
                            cout << "\n 2. No";
                            cout << "\n Su opcion: ";
                            cin >> opcionAA;
                            switch (opcionAA){
                            case 1:{
                                leerArticulosDesdeArchivo(listaArticulos);
                                cout << "\n Articulos Cargados Exitosamente";
                                break;
                            }
                            case 2: {
                                cout << "\n Retornando al menu anterior";
                                break;
                            }
                            default:
                                break;
                            }
                        break;
                        }
                        case 8: {
                                cout << "\n Regresando al menu principal...\n";
                        break;
                        }
                                
                        default:
                            cout << "\n Opción no válida. Inténtalo de nuevo.";
                            break;
                        }
                    } else {
                        cout << "\n Opción no válida. Inténtalo de nuevo.";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (opcionArticulos != 8);
                    break;
            }
            case 2: {
                int opcionClientes;
                do {
                    cout << "\n ****Bienvenido al apartado de Clientes****";
                    cout << "\n 1. Agregar un Cliente";
                    cout << "\n 2. Modificar un Cliente";
                    cout << "\n 3. Eliminar un Cliente";
                    cout << "\n 4. Mostrar Clientes";
                    cout << "\n 5. Buscar Cliente";
                    cout << "\n 6. Guardar Clientes";
                    cout << "\n 7. Cargar Clientes";
                    cout << "\n 8. Salir al menu anterior";
                    cout << "\n Su opcion: ";

                    if (cin >> opcionClientes) {
                        switch (opcionClientes) {
                        case 1: {
                            // Agregar Clientes
                            int n = obtenerCantidadClientes();
                            for (int i = 0; i < n; i++) {
                                Cliente nuevoCliente;
                                cout << "\n Ingrese la cedula del Cliente " << i + 1 << ": ";
                                nuevoCliente.Cedula = Esnum();
                                cin.ignore();
                                cout << "\n Ingrese el nombre y apellido del Cliente " << i + 1 << ": ";
                                cin.getline(nuevoCliente.NombreApellido, 50);
                                while (!esSoloLetras(nuevoCliente.NombreApellido)) {
                                    cout << "\n Ingrese el nombre y apellido del Cliente " << i + 1 << " correctamente: ";
                                    cin.getline(nuevoCliente.NombreApellido, 50);
                                }
                                cout << "\n Ingrese la direccion del Cliente " << i + 1 << ": ";
                                cin.getline(nuevoCliente.Direccion, 100);
                                cout << "\n Ingrese el telefono del Cliente " << i + 1 << ": ";
                                cin.getline(nuevoCliente.Telefono, 15);
                                cout << "\n Ingrese la frecuencia de compra del Cliente " << i + 1 << ": ";
                                nuevoCliente.frecuencia = Esnum();
                                agregarCliente(listaClientes,nuevoCliente);
                                cout << "\n Cliente Agregado Correctamente";
                            }
                            break;
                        }
                        case 2: {
                            // Modificar Clientes
                            int cedula;
                            cout << "Ingrese la cedula del Cliente a modificar: ";
                            cin >> cedula;
                            modificarCliente(listaClientes, cedula);
                            break;
                        }
                        case 3: {
                            // Eliminar Clientes
                            int cedula;
                            cout << "Ingrese la cedula del Cliente a eliminar: ";
                            cin >> cedula;
                            eliminarCliente(listaClientes, cedula);
                            break;
                        }
                        case 4: {
                            // Mostrar Clientes
                            system("clear");
                            mostrarRegistrosdeClientes(listaClientes);
                            system("sleep 5s");
                            break;
                        }
                        case 5: {
                        int opcionBusquedaCliente;
                        cout << "\n ****Buscar Cliente****";
                        cout << "\n 1. Por Cedula";
                        cout << "\n 2. Por Nombre y Apellido";
                        cout << "\n 3. Por Direccion";
                        cout << "\n 4. Volver al menu anterior";
                        cout << "\n Su opcion: ";
                        if (cin >> opcionBusquedaCliente) {
                            switch (opcionBusquedaCliente) {
                            case 1: {
                                int cedulaBuscar;
                                cout << "Ingrese la cedula del Cliente a buscar: ";
                                cin >> cedulaBuscar;
                                buscarClientePorCedula(listaClientes, cedulaBuscar);
                                break;
                            }
                            case 2: {
                                char nombreApellidoBuscar[50];
                                cout << "Ingrese el nombre y apellido del Cliente a buscar: ";
                                cin.ignore();
                                cin.getline(nombreApellidoBuscar, 50);
                                buscarClientePorNombreApellido(listaClientes, nombreApellidoBuscar);
                                break;
                            }
                            case 3: {
                                char direccionBuscar[100];
                                cout << "Ingrese la direccion del Cliente a buscar: ";
                                cin.ignore();
                                cin.getline(direccionBuscar, 100);
                                buscarClientePorDireccion(listaClientes, direccionBuscar);
                                break;
                            }
                            case 4: {
                                cout << "\n Volviendo al menu anterior...\n";
                                break;
                            }
                            default:
                                cout << "\n Opcion no valida. Intentalo de nuevo.";
                                break;
                            }
                        } else {
                            cout << "\n Opcion no valida. Intentalo de nuevo.";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        break;
                        }
                        case 6: {
                            //Guardar Estructura
                        ofstream archivo("Clientes.txt");
                        NodoCliente* actual = listaClientes;
                        while (actual != nullptr) {
                            archivo << "Cedula: " << actual->cliente.Cedula << "\n";
                            archivo << "Nombre: " << actual->cliente.NombreApellido << "\n";
                            archivo << "Direccion: " << actual->cliente.Direccion << "\n";
                            archivo << "Telefono: " << actual->cliente.Telefono << "\n";
                            archivo << "Frecuencia de Compra: " << actual->cliente.frecuencia << "dias""\n";
                            archivo << "------------------------\n";
                            actual = actual->siguiente;
                        }
                        archivo.close();
                        cout <<" \n Guardado Generado Correctamente";
                        break;
                        }
                        case 7:{
                            int opcionCLA;
                            cout << "\n Desea cargar los Clientes desde un archivo";
                            cout << "\n 1. Si";
                            cout << "\n 2. No";
                            cout << "\n Su opcion: ";
                            cin >> opcionCLA;
                            switch (opcionCLA){
                            case 1:{
                                leerClientesDesdeArchivo(listaClientes);
                                cout << "\n Clientes Cargados Exitosamente";
                                break;
                            }
                            case 2: {
                                cout << "\n Retornando al menu anterior";
                                break;
                            }
                            default:
                                break;
                            }
                            break;
                        }
                        case 8: {
                            cout << "\n Regresando al menu principal...\n";
                        break;
                        }
                            
                        default:
                            cout << "\n Opción no válida. Inténtalo de nuevo.";
                            break;
                        }
                    } else {
                        cout << "\n Opción no válida. Inténtalo de nuevo.";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (opcionClientes != 8);
                    break;
            }
            case 3: {
                int opcionVendedores;
                do {
                    cout << "\n ****Bienvenido al apartado de Vendedores****";
                    cout << "\n 1. Agregar un Vendedor";
                    cout << "\n 2. Modificar un Vendedor";
                    cout << "\n 3. Eliminar un Vendedor";
                    cout << "\n 4. Mostrar Vendedores";
                    cout << "\n 5. Buscar Vendedor";
                    cout << "\n 6. Guardar contenido";
                    cout << "\n 7. Cargar Vendedores";
                    cout << "\n 8. Salir al menu anterior";
                    cout << "\n Su opcion: ";

                    if (cin >> opcionVendedores) {
                        switch (opcionVendedores) {
                        case 1: {
                            // Agregar Vendedores
                            int n = obtenerCantidadVendedores();
                            for (int i = 0; i < n; i++) {
                                Vendedor nuevoVendedor;
                                cout << "\n Ingrese la cedula del Vendedor " << i + 1 << ": ";
                                nuevoVendedor.Cedula = Esnum();
                                cin.ignore();
                                cout << "\n Ingrese el nombre y apellido del Vendedor " << i + 1 << ": ";
                                cin.getline(nuevoVendedor.NombreApellido, 50);
                                while (!esSoloLetras(nuevoVendedor.NombreApellido)) {
                                    cout << "\n Ingrese el nombre y apellido del Vendedor " << i + 1 << " correctamente: ";
                                    cin.getline(nuevoVendedor.NombreApellido, 50);
                                }
                                cout << "\n Ingrese la fecha de ingreso del Vendedor " << i + 1 << ": ";
                                cin.getline(nuevoVendedor.FechaIngreso, 15);
                                cout << "\n Ingrese el porcentaje de comision del Vendedor " << i + 1 << ": ";
                                cin >> nuevoVendedor.PorcentajeComision;
                                cin.ignore();
                                agregarVendedor(listaVendedores, nuevoVendedor);
                                cout << "\n Vendedor Agregado Correctamente";
                            }
                            break;
                        }
                        case 2: {
                            // Modificar Vendedores
                            int cedula;
                            cout << "Ingrese la cedula del Vendedor a modificar: ";
                            cin >> cedula;
                            modificarVendedor(listaVendedores, cedula);
                            break;
                        }
                        case 3: {
                            // Eliminar Vendedores
                            int cedula;
                            cout << "Ingrese la cedula del Vendedor a eliminar: ";
                            cin >> cedula;
                            eliminarVendedor(listaVendedores, cedula);
                            break;
                        }
                        case 4: {
                            // Mostrar Vendedores
                            system("clear"); 
                            mostrarRegistrosdeVendedores(listaVendedores);
                            system("sleep 5s");
                            break;
                        }
                        case 5: {
                            
                            int opcionBusquedaVendedor;
                            do {
                                cout << "\n ****Buscar Vendedor****";
                                cout << "\n 1. Por Cedula de Identidad";
                                cout << "\n 2. Por Nombre y Apellido";
                                cout << "\n 3. Por Fecha de Ingreso";
                                cout << "\n 4. Volver al menu anterior";
                                cout << "\n Su opcion: ";
                                if (cin >> opcionBusquedaVendedor) {
                                    switch (opcionBusquedaVendedor) {
                                    case 1: {
                                        int cedula;
                                        cout << "Ingrese la cedula del Vendedor a buscar: ";
                                        cin >> cedula;
                                        buscarVendedorPorCedula(listaVendedores, cedula);
                                        break;
                                    }
                                    case 2: {
                                        char nombreApellido[50];
                                        cout << "Ingrese el nombre y apellido del Vendedor a buscar: ";
                                        cin.ignore();
                                        cin.getline(nombreApellido, 50);
                                        buscarVendedorPorNombreApellido(listaVendedores, nombreApellido);
                                        break;
                                    }
                                    case 3: {
                                        char fechaIngreso[15];
                                        cout << "Ingrese la fecha de ingreso del Vendedor a buscar: ";
                                        cin.ignore();
                                        cin.getline(fechaIngreso, 15);
                                        buscarVendedorPorFechaIngreso(listaVendedores, fechaIngreso);
                                        break;
                                    }
                                    case 4: {
                                        cout << "\n Volviendo al menu anterior...\n";
                                        break;
                                    }
                                    default:
                                        cout << "\n Opcion no valida. Intentalo de nuevo.";
                                        break;
                                    }
                                } else {
                                    cout << "\n Opcion no valida. Intentalo de nuevo.";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (opcionBusquedaVendedor != 4);
                            break;
                        }
                        case 6: {
                            //Guardar Estructura
                            ofstream archivo("Vendedores.txt");
                            NodoVendedor* actual = listaVendedores;
                            while (actual != nullptr) {
                            archivo << "Cedula: " << actual->vendedor.Cedula << "\n";
                            archivo << "Nombre: " << actual->vendedor.NombreApellido << "\n";
                            archivo << "Fecha de Ingreso: " << actual->vendedor.FechaIngreso<< "\n";
                            archivo << "Comision: " << actual->vendedor.PorcentajeComision <<"%" "\n";
                            archivo << "------------------------\n";
                            actual = actual->siguiente;
                        }
                        archivo.close();
                        cout <<" \n Guardado Generado Correctamente";
                        break;
                        }
                        case 7:{
                            int opcionCLA;
                            cout << "\n Desea cargar los Vendedores desde un archivo";
                            cout << "\n 1. Si";
                            cout << "\n 2. No";
                            cout << "\n Su opcion: ";
                            cin >> opcionCLA;
                            switch (opcionCLA){
                            case 1:{
                                leerVendedoresDesdeArchivo(listaVendedores);
                                cout << "\n Vendedores Cargados Exitosamente";
                                break;
                            }
                            case 2: {
                                cout << "\n Retornando al menu anterior";
                                break;
                            }
                            default:
                                break;
                            }
                            break;
                        }
                        case 8:{
                            cout << "\n Regresando al menu principal...\n";
                            break;
                        }
                        default:
                            cout << "\n Opcion no valida. Intentalo de nuevo.";
                            break;
                        }
                    } else {
                        cout << "\n Opcion no valida. Intentalo de nuevo.";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (opcionVendedores != 8);
                    break;
            case 4:{
                break;
                } 
            }
            case 5:{
                break;
                }
            
            default:
                cout << "\n Opcion no valida. Intentalo de nuevo.";
                break;
            }
                } 
            else {
            cout << "\n Opcion no valida. Intentalo de nuevo.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 6);

    // Liberar memoria antes de salir
    liberarMemoria(listaArticulos);
    liberarMemoriaClientes(listaClientes);
    liberarMemoriaVendedores(listaVendedores);

    return 0;
}
