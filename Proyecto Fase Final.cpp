#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <cstring>
using namespace std;

struct Articulo {
    int Codigo;
    char Nombre[50];
    char Descripcion[250];
    int Precio;
    int Cantidad;
};

struct Cliente {
    int Cedula;
    char NombreApellido[50];
    char Direccion[100];
    char Telefono[15];
};

struct Vendedor {
    int Cedula;
    char NombreApellido[50];
    char FechaIngreso[15]; 
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
struct Factura {
    int NumeroFactura;
    Cliente datosCliente;
    Vendedor datosVendedor;
    Articulo articulos[50]; 
    int cantidadArticulos;
    int totalCompra;
};
struct NodoFactura {
    Factura factura;
    NodoFactura* siguiente;
};

Cliente* buscarClienteFactura(NodoCliente* listaClientes, int cedula) {
    NodoCliente* actual = listaClientes;
    while (actual != nullptr) {
        if (actual->cliente.Cedula == cedula) {
            return &(actual->cliente);
        }
        actual = actual->siguiente;
    }
    return nullptr;  
}
Vendedor* buscarVendedorFactura(NodoVendedor* listaVendedores, int cedula) {
    NodoVendedor* actual = listaVendedores;
    while (actual != nullptr) {
        if (actual->vendedor.Cedula == cedula) {
            return &(actual->vendedor);
        }
        actual = actual->siguiente;
    }
    return nullptr; 
}
int calcularTotalCompra(Articulo articulos[], int cantidadArticulos) {
    int total = 0;
    for (int i = 0; i < cantidadArticulos; ++i) {
        total += articulos[i].Precio * articulos[i].Cantidad;
    }
    return total;
}

Articulo* buscarArticuloPorCodigoFactura(Nodo* listaArticulos, int codigo) {
    for (Nodo* nodo = listaArticulos; nodo != nullptr; nodo = nodo->siguiente) {
        if (nodo->articulo.Codigo == codigo) {
            return &(nodo->articulo);
        }
    }
    return nullptr;
}

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void agregarFactura(NodoFactura*& listaFacturas, const Factura& nuevaFactura) {
    NodoFactura* nuevoNodo = new NodoFactura;
    nuevoNodo->factura = nuevaFactura;
    nuevoNodo->siguiente = listaFacturas;
    listaFacturas = nuevoNodo;
}

void mostrarRegistrodeFacturas(NodoFactura* listaFacturas) {
    cout << "\n-------------------------------------- Facturas --------------------------------------" << endl;
    for (NodoFactura* nodo = listaFacturas; nodo != nullptr; nodo = nodo->siguiente) {
        const Factura& factura = nodo->factura;
        cout << setw(25) << left << "Numero de Factura:" << factura.NumeroFactura << endl;
        cout << setw(25) << left << "Datos del Cliente:" << factura.datosCliente.NombreApellido
            << " (Cedula: " << factura.datosCliente.Cedula << ")" << endl;
        cout << setw(25) << left << "Datos del Vendedor:" << factura.datosVendedor.NombreApellido
            << " (Cedula: " << factura.datosVendedor.Cedula << ")" << endl;
        cout << "\n" << setw(10) << left << "Codigo" << setw(30) << left << "Nombre"
            << setw(15) << left << "Cantidad" << setw(15) << left << "Precio"
            << setw(15) << left << "Total" << endl;
        for (int i = 0; i < factura.cantidadArticulos; ++i) {
            cout << setw(10) << left << factura.articulos[i].Codigo;
                string nombre = factura.articulos[i].Nombre;
                cout << setw(30) << left << nombre.substr(0, 29);
                cout << setw(15) << left << factura.articulos[i].Cantidad;
                cout << setw(15) << left << factura.articulos[i].Precio;
                cout << setw(15) << left << (factura.articulos[i].Precio * factura.articulos[i].Cantidad) << endl;
        }
        cout << "\n" << setw(65) << right << "Total de la compra: " << factura.totalCompra << "$" << endl;
        cout << "\n--------------------------------------------------------------------------------------";
    }
}
Cliente LlenarClienteFactura(NodoCliente* listaClientes) {
    int cedulaCliente;
    cout << "\n Ingrese la cedula del cliente: ";
    while (!(cin >> cedulaCliente) || cedulaCliente < 0) {
        cout << "\n Error ingrese una cedula valida: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
    Cliente* cliente = buscarClienteFactura(listaClientes, cedulaCliente);
    while (cliente == nullptr) {
        cout << "\n Cliente no encontrado. Intente nuevamente: ";
        while (!(cin >> cedulaCliente) || cedulaCliente < 0) {
            cout << "\n Error ingrese una cedula valida: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        cliente = buscarClienteFactura(listaClientes, cedulaCliente);
    }
    cout << "\n Cliente cargado correctamente";
    return *cliente;
}
Vendedor LlenarVendedorFactura(NodoVendedor* listaVendedores) {
    int cedulaVendedor;
    cout << "\n Ingrese la cedula del vendedor: ";
    cin >> cedulaVendedor;
    while (cin.fail()) {
        cout << "\n Error ingrese una cedula valida: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cin >> cedulaVendedor;
    }
    Vendedor* vendedor = buscarVendedorFactura(listaVendedores, cedulaVendedor);
    while (vendedor == nullptr) {
        cout << "\n Vendedor no encontrado. Intente nuevamente: ";
        cin >> cedulaVendedor;
        while (cin.fail()) {
            cout << "\n Error ingrese una cedula valida: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cin >> cedulaVendedor;
        }
        vendedor = buscarVendedorFactura(listaVendedores, cedulaVendedor);
    }
    cout << "\n Vendedor cargado correctamente";
    return *vendedor;
}
void LlenarArticulosFactura(Nodo* listaArticulos, Factura& nuevaFactura) {
    int cantidadArticulos;
    cout << "\n Ingrese la cantidad de Articulos que compro el cliente: ";
    cin >> cantidadArticulos;
    for (int i = 0; i < cantidadArticulos && i < 50; ++i) {
        int codigoArticulo;
        cout << "\n Codigo del articulo: ";
        cin >> codigoArticulo;
        if (codigoArticulo == -1) {
            break;
        }
        Articulo* articulo = buscarArticuloPorCodigoFactura(listaArticulos, codigoArticulo);
        if (articulo != nullptr) {
            cout << " \n Cantidad: ";
            int cantidad;
            cin >> cantidad;
            if (cantidad > 0 && cantidad <= articulo->Cantidad) {
                nuevaFactura.articulos[i] = *articulo;
                nuevaFactura.articulos[i].Cantidad = cantidad;
            } else {
                cout << "\n Cantidad no valida o no disponible. Intentelo nuevamente." << endl;
                --i;
            }
        } else {
            cout << "\n Articulo no encontrado." << endl;
            --i; 
        }
    }
    nuevaFactura.cantidadArticulos = min(cantidadArticulos, 50);
}

int generarNumeroFactura(const NodoFactura* listaFacturas) {
    if (listaFacturas == nullptr) {
        return 1;
    } else {
        const NodoFactura* ultimoNodo = listaFacturas;
        while (ultimoNodo->siguiente != nullptr) {
            ultimoNodo = ultimoNodo->siguiente;
        }
        return ultimoNodo->factura.NumeroFactura + 1;
    }
}
void agregarDatos(Nodo*& lista, const Articulo& nuevoArticulo) {
    Nodo* nuevoNodo = new Nodo{ nuevoArticulo, nullptr };
    if (lista == nullptr) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
}

class Diccionario {
private:
    Nodo* inicio;

    void agregarDatos(Nodo*& lista, const Articulo& nuevoArticulo) {
        Nodo* nuevoNodo = new Nodo{ nuevoArticulo, nullptr };
        if (lista == nullptr) {
            lista = nuevoNodo;
        } else {
            nuevoNodo->siguiente = lista;
            lista = nuevoNodo;
        }
    }

    void mostrarInformacion(const Articulo& articulo) const {
    system("CLS");
    const int colWidthCodigo = 10;
    const int colWidthNombre = 20;
    const int colWidthDescripcion = 60;
    const int colWidthPrecio = 10;
    const int colWidthCantidad = 10;
    cout << "Codigo: " << articulo.Codigo << endl;
    cout << "Nombre: " << articulo.Nombre << endl;
    cout << "Descripcion: " << articulo.Descripcion << endl;
    cout << "Precio: " << articulo.Precio << "$" << endl;
    cout << "Cantidad: " << articulo.Cantidad << endl;
    cout << "\n Pulse una tecla para continuar...";
    getch();
}

public:
    Diccionario() : inicio(nullptr) {}

    void agregarArticulo(const Articulo& nuevoArticulo) {
        agregarDatos(inicio, nuevoArticulo);
    }

    void mostrarArticulos() const {
        Nodo* actual = inicio;
        while (actual != nullptr) {
            mostrarInformacion(actual->articulo);
            actual = actual->siguiente;
        }
    }

    void modificarDescripcion(int codigo, const char* nuevaDescripcion) {
        Nodo* actual = inicio;
        while (actual != nullptr) {
            if (actual->articulo.Codigo == codigo) {
                strcpy(actual->articulo.Descripcion, nuevaDescripcion);
                return;
            }
            actual = actual->siguiente;
        }
    }

    void buscarPorCodigo(int codigo) const {
        Nodo* actual = inicio;
        bool encontrado = false;
        while (actual != nullptr) {
            if (actual->articulo.Codigo == codigo) {
                mostrarInformacion(actual->articulo);
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }
        if (!encontrado) {
            cout << "No se encontraron articulos con el codigo proporcionado." << endl;
        }
    }

    void buscarPorNombre(const char* nombre) const {
        Nodo* actual = inicio;
        while (actual != nullptr) {
            if (strcmp(actual->articulo.Nombre, nombre) == 0) {
                mostrarInformacion(actual->articulo);
                return;
            }
            actual = actual->siguiente;
        }
        cout << "Articulo no encontrado por nombre." << endl;
    }
};



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
    cout << left << setw(15) << "Codigo" << setw(20) << "Nombre" << setw(15) << "Precio" << setw(15) << "Cantidad" << endl;
    cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
    while (actual != nullptr) {
        Articulo& articulo = actual->articulo;
        cout << left << setw(15) << articulo.Codigo
            << setw(20) << articulo.Nombre
            << setw(15) << fixed << setprecision(2) << articulo.Precio
            << setw(15) << articulo.Cantidad
            << endl;
        actual = actual->siguiente;
    }
}

void mostrarRegistrosdeClientes(NodoCliente* lista) {
    NodoCliente* actual = lista;
    cout << setw(10) << "Cedula" << setw(20) << "Nombre" << setw(30) << "Direccion" << setw(15) << "Telefono" << setw(25)<< endl;
    cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    while (actual != nullptr) {
        cout << setw(10) << actual->cliente.Cedula
            << setw(20) << actual->cliente.NombreApellido
            << setw(30) << actual->cliente.Direccion
            << setw(15) << actual->cliente.Telefono
            << endl;
        actual = actual->siguiente;
    }
}

void mostrarRegistrosdeVendedores(NodoVendedor* lista) {
    NodoVendedor* actual = lista;
    cout << left << setw(15) << "Cedula" << setw(20) << "Nombre" << setw(20) << "Fecha Ingreso" << setw(25) << endl;
    cout << setfill('-') << setw(80) << "-" << setfill(' ') << endl;
    while (actual != nullptr) {
        Vendedor& vendedor = actual->vendedor;
        cout << left << setw(15) << vendedor.Cedula
            << setw(20) << vendedor.NombreApellido
            << setw(20) << vendedor.FechaIngreso
            << endl;
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


string convertirFechaParaComparacion(const char* fecha) {
    istringstream ss(fecha);
    int dia, mes, anio;
    char barra;
    ss >> dia >> barra >> mes >> barra >> anio;
    ostringstream resultado;
    resultado << setw(2) << setfill('0') << dia
            << setw(2) << setfill('0') << mes
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
    string fechaConvertida = convertirFechaParaComparacion(fecha);
    NodoVendedor* actual = cabeza;
    while (actual != nullptr) {
        string fechaActualConvertida = convertirFechaParaComparacion(actual->vendedor.FechaIngreso);
        if (fechaActualConvertida == fechaConvertida) {
            vendedoresEncontrados.push_back(actual);
            imprimirInformacionVendedor(actual->vendedor);
        }
        actual = actual->siguiente;
    }
    if (vendedoresEncontrados.empty()) {
        cout << "No se encontro ningun vendedor con la fecha de ingreso " << fecha << endl;
    }
    return vendedoresEncontrados;
}


void modificarArticulo(Nodo*& lista, Diccionario& diccionario, int codigo) {
    Nodo* actual = lista;
    while (actual != nullptr) {
        if (actual->articulo.Codigo == codigo) {
            cout << "Ingrese los detalles del nuevo articulo\n";
            cout << "Ingrese el nombre: ";
            cin.ignore();
            cin.getline(actual->articulo.Nombre, 50);
            cout << "Ingrese la descripcion: ";
            cin.getline(actual->articulo.Descripcion, 250);
            cout << "Ingrese el precio: ";
            cin >> actual->articulo.Precio;
            cout << "Ingrese la cantidad disponible: ";
            cin >> actual->articulo.Cantidad;
            diccionario.modificarDescripcion(codigo, actual->articulo.Descripcion);
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
        cout << "\n Por favor, ingresa un numero: ";
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
        cout << "\n Por favor, ingresa una cantidad valida: ";
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
        cout << "\n Por favor, ingresa una cantidad valida: ";
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
        cout << "\n Por favor, ingresa una cantidad valida: ";
    }
    cin.ignore();
    return n;
}
int obtenerCantidadFacturas() {
    int n;
    cout << "\n Ingrese la cantidad de facturas que desea registrar: ";
    while (!(cin >> n) || n <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n Por favor, ingresa una cantidad valida: ";
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
void liberarMemoriaFacturas(NodoFactura*& listaFacturas) {
    while (listaFacturas != nullptr) {
        NodoFactura* temp = listaFacturas;
        listaFacturas = listaFacturas->siguiente;
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

void leerArticulosDesdeArchivo(Diccionario& diccionario,Nodo*& lista) {
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
        archivo.getline(nuevoArticulo.Descripcion, 250);
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo >> nuevoArticulo.Precio;
        archivo.ignore(numeric_limits<streamsize>::max(), ':');
        archivo >> nuevoArticulo.Cantidad;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        diccionario.agregarArticulo(nuevoArticulo);
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
        agregarVendedorUnico(lista, nuevoVendedor);
    }
    archivo.close();
}

int main() {
    Diccionario diccionario;
    Nodo* listaArticulos = nullptr;
    NodoFactura* listaFacturas = nullptr;
    
    int opcion;
    do {
        cout << "\n ****Bienvenido Tienda RGP****";
        cout << "\n 1. Gestion de Articulos";
        cout << "\n 2. Gestion de Clientes";
        cout << "\n 3. Gestion de Vendedores";
        cout << "\n 4. Gestion de Facturas";
        cout << "\n 5. Salir";
        cout << "\n Su opcion: ";
        if (cin >> opcion) {
            switch (opcion) {
            case 1: {
            limpiar_pantalla();
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
                    cout << "\n 8. Buscar Descripciones";
                    cout << "\n 9. Salir al menu anterior";
                    cout << "\n Su opcion: ";
                    if (cin >> opcionArticulos) {
                        switch (opcionArticulos) {
                        case 1: {
                            // Agregar Articulos
                            limpiar_pantalla();
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
                                cout << "\n Ingrese una descripcion del producto:";
                                cin.getline(nuevoArticulo.Descripcion, 250);
                                cout << "\n Ingrese el precio del Articulo " << i + 1 << ": ";
                                nuevoArticulo.Precio = Esnum();
                                cout << "\n Ingrese la cantidad disponible del Articulo " << i + 1 << ": ";
                                nuevoArticulo.Cantidad = Esnum();
                                cin.ignore();
                                agregarDatos(listaArticulos, nuevoArticulo);
                                diccionario.agregarArticulo(nuevoArticulo);
                                cout << "\n Articulo Agregado Correctamente";
                            }
                            break;
                        }
                        case 2: {
                            // Modificar Articulos
                            limpiar_pantalla();
                            int codigo;
                            cout << "Ingrese el codigo del Articulo a modificar: ";
                            cin >> codigo;
                            modificarArticulo(listaArticulos, diccionario, codigo);
                            break;
                        }
                        case 3: {
                            // Eliminar Articulos
                            limpiar_pantalla();
                            int codigo;
                            cout << "Ingrese el codigo del Articulo a eliminar: ";
                            cin >> codigo;
                            eliminarArticulo(listaArticulos, codigo);
                            break;
                        }
                        case 4: {
                            // Mostrar Articulos
                            limpiar_pantalla();
                            mostrarRegistrosdeArticulos(listaArticulos);
                            cout << "\n Pulse una tecla para continuar...";
                            initscr();
                            getch();
                            endwin();
                            break;
                        }
                        case 5: {
                        limpiar_pantalla();

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
                                    limpiar_pantalla();
                                    cout << "\n Volviendo al menu anterior...\n";
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
                        limpiar_pantalla();
                        ofstream archivo("Articulos.txt");
                        Nodo* actual = listaArticulos;
                        while (actual != nullptr) {
                            archivo << "Codigo: " << actual->articulo.Codigo << "\n";
                            archivo << "Nombre: " << actual->articulo.Nombre << "\n";
                            archivo << "Descripcion: " << actual->articulo.Descripcion << "\n";
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
                            limpiar_pantalla();
                            int opcionAA;
                            cout << "\n Desea cargar los articulos desde un archivo";
                            cout << "\n 1. Si";
                            cout << "\n 2. No";
                            cout << "\n Su opcion: ";
                            cin >> opcionAA;
                            switch (opcionAA){
                            case 1:{
                                limpiar_pantalla();
                                leerArticulosDesdeArchivo(diccionario,listaArticulos);
                                cout << "\n Articulos Cargados Exitosamente";
                                break;
                            }
                            case 2: {
                                limpiar_pantalla();
                                cout << "\n Retornando al menu anterior";
                                break;
                            }
                            default:
                                break;
                            }
                        break;
                        }
                        case 8:{
                            limpiar_pantalla();
                            int opcionDic;
                            cout << "\n Seleccione la forma en la que quiere buscar la descripción";
                            cout << "\n 1. Codigo";
                            cout << "\n 2. Nombre";
                            cout << "\n 3. Regresar al menu anterior";
                            cout << "\n Su opcion:";
                            cin >> opcionDic;
                            switch (opcionDic) {
                                case 1: {
                                    limpiar_pantalla();
                                    int codigo;
                                    cout << "\n Ingrese el codigo del articulo: ";
                                    cin >> codigo;
                                    diccionario.buscarPorCodigo(codigo);
                                    break;
                                }
                                case 2: {
                                    limpiar_pantalla();
                                    char nombre[50];
                                    cout << "\n Ingrese el nombre del articulo: ";
                                    cin.ignore();
                                    cin.getline(nombre, 50);
                                    diccionario.buscarPorNombre(nombre);
                                    break;
                                }
                                case 3: {
                                    cout << "\n Regresando al menu anterior...\n";
                                    break;
                                }
                                default:
                                    cout << "\n Opcion no valida. Intentalo de nuevo";
                                    break;
                            }
                            break;
                        }
                        case 9:{
                                limpiar_pantalla();
                                cout << "\n Regresando al menu principal...\n";
                            break;
                        }
                                
                        default:
                            cout << "\n Opcion no valida. Intentalo de nuevo.";
                            break;
                        }
                    } else {
                        cout << "\n Opcion no válida. Intentalo de nuevo.";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (opcionArticulos != 9);
                    break;
            }
            case 2: {
                limpiar_pantalla();
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
                            limpiar_pantalla();
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
                                cin.getline(nuevoCliente.Telefono, 15);;
                                agregarCliente(listaClientes,nuevoCliente);
                                cout << "\n Cliente Agregado Correctamente";
                            }
                            break;
                        }
                        case 2: {
                            // Modificar Clientes
                            limpiar_pantalla();
                            int cedula;
                            cout << "Ingrese la cedula del Cliente a modificar: ";
                            cin >> cedula;
                            modificarCliente(listaClientes, cedula);
                            break;
                        }
                        case 3: {
                            // Eliminar Clientes
                            limpiar_pantalla();
                            int cedula;
                            cout << "Ingrese la cedula del Cliente a eliminar: ";
                            cin >> cedula;
                            eliminarCliente(listaClientes, cedula);
                            break;
                        }
                        case 4: {
                            // Mostrar Clientes
                            limpiar_pantalla();
                            mostrarRegistrosdeClientes(listaClientes);
                            cout << "\n Pulse una tecla para continuar...";
                            initscr();
                            getch();
                            endwin();
                            break;
                        }
                        case 5: {
                        limpiar_pantalla();
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
                                limpiar_pantalla();
                                int cedulaBuscar;
                                cout << "Ingrese la cedula del Cliente a buscar: ";
                                cin >> cedulaBuscar;
                                buscarClientePorCedula(listaClientes, cedulaBuscar);
                                break;
                            }
                            case 2: {
                                limpiar_pantalla();
                                char nombreApellidoBuscar[50];
                                cout << "Ingrese el nombre y apellido del Cliente a buscar: ";
                                cin.ignore();
                                cin.getline(nombreApellidoBuscar, 50);
                                buscarClientePorNombreApellido(listaClientes, nombreApellidoBuscar);
                                break;
                            }
                            case 3: {
                                limpiar_pantalla();
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
                            limpiar_pantalla();
                        ofstream archivo("Clientes.txt");
                        NodoCliente* actual = listaClientes;
                        while (actual != nullptr) {
                            archivo << "Cedula: " << actual->cliente.Cedula << "\n";
                            archivo << "Nombre: " << actual->cliente.NombreApellido << "\n";
                            archivo << "Direccion: " << actual->cliente.Direccion << "\n";
                            archivo << "Telefono: " << actual->cliente.Telefono << "\n";
                            archivo << "------------------------\n";
                            actual = actual->siguiente;
                        }
                        archivo.close();
                        cout <<" \n Guardado Generado Correctamente";
                        break;
                        }
                        case 7:{
                            limpiar_pantalla();
                            int opcionCLA;
                            cout << "\n Desea cargar los Clientes desde un archivo";
                            cout << "\n 1. Si";
                            cout << "\n 2. No";
                            cout << "\n Su opcion: ";
                            cin >> opcionCLA;
                            switch (opcionCLA){
                            case 1:{
                                limpiar_pantalla();
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
                            limpiar_pantalla();
                            cout << "\n Regresando al menu principal...\n";
                        break;
                        }
                            
                        default:
                            cout << "\n Opcion no válida. Intentalo de nuevo.";
                            break;
                        }
                    } else {
                        cout << "\n Opcion no válida. Intentalo de nuevo.";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                } while (opcionClientes != 8);
                    break;
            }
            case 3: {
                limpiar_pantalla();
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
                            limpiar_pantalla();
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
                                cin.ignore();
                                agregarVendedor(listaVendedores, nuevoVendedor);
                                cout << "\n Vendedor Agregado Correctamente";
                            }
                            break;
                        }
                        case 2: {
                            // Modificar Vendedores
                            limpiar_pantalla();
                            int cedula;
                            cout << "Ingrese la cedula del Vendedor a modificar: ";
                            cin >> cedula;
                            modificarVendedor(listaVendedores, cedula);
                            break;
                        }
                        case 3: {
                            // Eliminar Vendedores
                            limpiar_pantalla();
                            int cedula;
                            cout << "Ingrese la cedula del Vendedor a eliminar: ";
                            cin >> cedula;
                            eliminarVendedor(listaVendedores, cedula);
                            break;
                        }
                        case 4: {
                            // Mostrar Vendedores
                            limpiar_pantalla();
                            
                            mostrarRegistrosdeVendedores(listaVendedores);
                            cout << "\n Pulse una tecla para continuar...";
                            initscr();
                            getch();
                            endwin();
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
                                        limpiar_pantalla();
                                        int cedula;
                                        cout << "Ingrese la cedula del Vendedor a buscar: ";
                                        cin >> cedula;
                                        buscarVendedorPorCedula(listaVendedores, cedula);
                                        break;
                                    }
                                    case 2: {
                                        limpiar_pantalla();
                                        char nombreApellido[50];
                                        cout << "Ingrese el nombre y apellido del Vendedor a buscar: ";
                                        cin.ignore();
                                        cin.getline(nombreApellido, 50);
                                        buscarVendedorPorNombreApellido(listaVendedores, nombreApellido);
                                        break;
                                    }
                                    case 3: {
                                        limpiar_pantalla();
                                        char fechaIngreso[15];
                                        cout << "Ingrese la fecha de ingreso del Vendedor a buscar: ";
                                        cin.ignore();
                                        cin.getline(fechaIngreso, 15);
                                        buscarVendedorPorFechaIngreso(listaVendedores, fechaIngreso);
                                        break;
                                    }
                                    case 4: {
                                        limpiar_pantalla();
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
                            limpiar_pantalla();
                            ofstream archivo("Vendedores.txt");
                            NodoVendedor* actual = listaVendedores;
                            while (actual != nullptr) {
                            archivo << "Cedula: " << actual->vendedor.Cedula << "\n";
                            archivo << "Nombre: " << actual->vendedor.NombreApellido << "\n";
                            archivo << "Fecha de Ingreso: " << actual->vendedor.FechaIngreso<< "\n";
                            archivo << "------------------------\n";
                            actual = actual->siguiente;
                        }
                        archivo.close();
                        cout <<" \n Guardado Generado Correctamente";
                        break;
                        }
                        case 7:{
                            limpiar_pantalla();
                            int opcionCLA;
                            cout << "\n Desea cargar los Vendedores desde un archivo";
                            cout << "\n 1. Si";
                            cout << "\n 2. No";
                            cout << "\n Su opcion: ";
                            cin >> opcionCLA;
                            switch (opcionCLA){
                            case 1:{
                                limpiar_pantalla();
                                leerVendedoresDesdeArchivo(listaVendedores);
                                cout << "\n Vendedores Cargados Exitosamente";
                                break;
                            }
                            case 2: {
                                limpiar_pantalla();
                                cout << "\n Retornando al menu anterior";
                                break;
                            }
                            default:
                                break;
                            }
                            break;
                        }
                        case 8:{
                            limpiar_pantalla();
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
                    limpiar_pantalla();
                    int opcF;
                    do {
                        cout << "\n ****Bienvenido al apartado de Facturas****";
                        cout << "\n 1. Crear una Factura";
                        cout << "\n 2. Mostrar Facturas guardadas";
                        cout << "\n 3. Eliminar una Factura";
                        cout << "\n 4. Guardar Factura/s";
                        cout << "\n 5. Regresar al menu principal";
                        cout << "\n Su opcion:";
                        cin >> opcF;
                        switch (opcF) {
                            case 1: {
                                limpiar_pantalla();
                                int n = obtenerCantidadFacturas();
                                for (int i = 0; i < n; i++) {
                                    Factura nuevaFactura;
                                    int cedulaCliente;
                                    int cedulaVendedor;
                                    int codigoArticulo;
                                    int cantidad;
                                    int indiceArticulos = 0;
                                    nuevaFactura.cantidadArticulos = 0;
                                    nuevaFactura.totalCompra = 0;
                                    nuevaFactura.NumeroFactura = generarNumeroFactura(listaFacturas);
                                    for (int i = 0; i < 50; ++i) {
                                        nuevaFactura.articulos[i].Codigo = 0;
                                    }
                                    nuevaFactura.datosCliente = LlenarClienteFactura(listaClientes);
                                    nuevaFactura.datosVendedor = LlenarVendedorFactura(listaVendedores);
                                    LlenarArticulosFactura(listaArticulos, nuevaFactura);
                                    nuevaFactura.totalCompra = calcularTotalCompra(nuevaFactura.articulos, nuevaFactura.cantidadArticulos);
                                    agregarFactura(listaFacturas, nuevaFactura);
                                }
                                cout << "\n Factura Creada Correctamente";
                                break;
                            }
                            case 2: {
                                limpiar_pantalla();
                                mostrarRegistrodeFacturas(listaFacturas);
                                cout << "\n Pulse una tecla para continuar...";
                                initscr();
                                getch();
                                endwin();
                                break;
                            }
                            case 3: {
                                
                                break;
                            }
                            case 4:{
                                limpiar_pantalla();
                                ofstream archivoFacturas("Facturas.txt");
                                for (NodoFactura* nodo = listaFacturas; nodo != nullptr; nodo = nodo->siguiente) {
                                    const Factura& factura = nodo->factura;
                                    archivoFacturas << "\n------------------------- Facturas -------------------------\n";
                                    archivoFacturas << setw(25) << left << "Numero de Factura:" << factura.NumeroFactura << "\n";
                                    archivoFacturas << setw(25) << left << "Datos del Cliente:" << factura.datosCliente.NombreApellido
                                                    << " (Cedula: " << factura.datosCliente.Cedula << ")\n";
                                    archivoFacturas << setw(25) << left << "Datos del Vendedor:" << factura.datosVendedor.NombreApellido
                                                    << " (Cedula: " << factura.datosVendedor.Cedula << ")\n";
                                    archivoFacturas << "\n" << setw(10) << left << "Codigo" << setw(30) << left << "Nombre"
                                                    << setw(15) << left << "Cantidad" << setw(15) << left << "Precio"
                                                    << setw(15) << left << "Total\n";
                                    for (int i = 0; i < factura.cantidadArticulos; ++i) {
                                        archivoFacturas << setw(10) << left << factura.articulos[i].Codigo;
                                        string nombre = factura.articulos[i].Nombre;
                                        archivoFacturas << setw(30) << left << nombre.substr(0, 29);
                                        archivoFacturas << setw(15) << left << factura.articulos[i].Cantidad;
                                        archivoFacturas << setw(15) << left << factura.articulos[i].Precio;
                                        archivoFacturas << setw(15) << left << (factura.articulos[i].Precio * factura.articulos[i].Cantidad) << "\n";
                                    }
                                    archivoFacturas << "\n" << setw(65) << right << "Total de la compra: " << factura.totalCompra << "$\n";
                                    archivoFacturas << "\n-------------------------------------------------------------\n";
                                }
                                archivoFacturas.close();
                                cout << "\nGuardado Generado Correctamente";
                                break;
                            }
                            default:
                                break;
                        }
                    } while (opcF != 5);
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
    } while (opcion != 5);

    // Liberar memoria antes de salir
    liberarMemoria(listaArticulos);
    liberarMemoriaClientes(listaClientes);
    liberarMemoriaVendedores(listaVendedores);
    liberarMemoriaFacturas(listaFacturas);
    

    return 0;
    }

