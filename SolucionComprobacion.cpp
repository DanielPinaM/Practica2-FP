#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Los integrantes del grupo somos:
//Enrique Miguel Torrijos Gabriel				1ºG
//Daniel Piña Miguelsanz						1ºG

const int MAX_PROD = 25;
const int PROD_NULO = 0;
const int CENTINELA = -1;

typedef int tArray[MAX_PROD];

bool esPosValida(int tam, int pos)// Comprueba si la posicion existe en el tamaño del array
{
	bool resultado;
	if ((pos < tam) && (pos >= 0))
		resultado = true;
	else
		resultado = false;
	return resultado;
}//bool esPosValida

bool estaVacia(const tArray fila, int pos)// Comprueba si la posicion en el array esta vacia
{
	bool resultado;
	if (fila[pos] == PROD_NULO)
		resultado = true;
	else
		resultado = false;
	return true;
}//bool estaVacia

void leerFilaFich(istream &fich, tArray fila, int &tam)
{
	int i = 0; //Esta variable sirve para saber el tamanyo de la nueva fila
	bool limite = false; //Indica si hemos leido el CENTINELA (true) o no todavia (false)
	int x;
	fich >> x;
	while ((esPosValida(MAX_PROD, i)) && (x != CENTINELA))//Leemos el archivo hasta que encontramos el CENTINELA
	{
		fila[i] = x;
		fich >> x;
		if (x == CENTINELA)
			limite = true;
		++i;
	}//while

	if (i < tam)
	{
		cout << "AVISO: El tamanyo de la fila pasa de ser " << tam << " valores a " << i << " valores.\n";
		tam = i; //hemos cambiado el tamanyo de la fila
	}// if
	if ((i > tam) && (limite == true))
	{
		cout << "AVISO: El tamanyo de la fila pasa de ser " << tam << " valores a " << i << " valores.\n";
		tam = i; //hemos cambiado el tamanyo de la fila
	}
	if (limite == false)
	{
		cout << "AVISO: el usuario ha pedido cargar una fila de mas de " << MAX_PROD << " valores, sin embargo, el programa esta pensado "
			<< "para trabajar con filas de hasta " << MAX_PROD << " valores, solo se han cargado los primeros " << MAX_PROD << ".\n";
		tam = MAX_PROD; //hemos cambiado el tamanyo de la fila, sin embargo, no podemos sobrepasar MAX_PROD
	}//if
}//void leerFilaFich

void escribirFilaFich(ostream &fich, tArray fila, int tam)
{
	int i;
	for (i = 0; i < tam; ++i)
	{
		fich << fila[i] << " ";
	}//for
	fich << CENTINELA << "\n";
}//void escribirFilaFich

void mostrarFila(const tArray fila, int tam)
{
	int i;
	cout << "|";
	for (i = 0; i < tam; ++i)// Escribir la primera fila
	{
		if (fila[i] == PROD_NULO)
		{
			cout << "  |";
		}// No escribe nada
		else if (fila[i] < 10)
		{
			cout << " " << fila[i] << "|";
		}// El valor de la posicion es un digito
		else
		{
			cout << fila[i] << "|";
		}// El valor de la posicion son 2 digitos
	}//for
	cout << "\n" << "----"; //siguiente fila
	for (i = 0; i < tam - 1; ++i)// Segunda fila
	{
		cout << "---";
	}//for
	cout << "\n" << "|"; //siguiente fila
	for (i = 0; i < tam; ++i)// Tercera Fila
	{

		if (i < 10)
		{
			cout << " " << i << "|";
		}// El valor de la posicion es un digito
		else
		{
			cout << i << "|";
		}// El valor de la posicion son 2 digitos
	}//for
	cout << "\n";
}//void mostrarFila

bool esPosibleGrua1Entre(const tArray fila, int tam, int posIni, int posSoltar)
{
	bool resultado;
	if ((!esPosValida(tam, posIni)) || (!esPosValida(tam, posSoltar)))//Comprobar si no existen las posiciones en el array
	{
		resultado = false;
	}//if
	else //Las posiciones existen en el array
	{
		if (posSoltar == PROD_NULO)//Comprueba si la posicion final esta vacia
		{
			resultado = true;
		}//if
		else
			resultado = false;
	}//else
	return resultado;
}//bool esPosibleGrua1Entre

bool grua1Elemento(tArray fila, int tam, int posIni, int posSoltar)
{
	bool resultado;
	if (esPosibleGrua1Entre(fila, tam, posIni, posSoltar))//Si se puede usar la grua
	{
		fila[posSoltar] = fila[posIni];
		fila[posIni] = 0;
		cout << "La grua ha podido hacer su trabajo.\n";
		resultado = true;
	}//if
	else
	{
		cout << "La grua no puede trabajar en estas condiciones.\n";
		resultado = false;
	}//else
	return resultado;
}//bool grua1Elemento

bool sonPosicionesPosiblesGrua(int tam, int posIni, int posFin, int posSoltar) {
	bool resultado;
	if (posIni > posFin) //Nos aseguramos de que el extremo izquierdo sea menor que el derecho
		resultado = false;
	else
	{
		int posSoltarFin = posSoltar + (posFin - posIni);

		if ((posSoltarFin < tam) && (esPosValida(tam, posIni))				//Comprobamos que todos los extremos
			&& (esPosValida(tam, posFin)) && (esPosValida(tam, posSoltar)))	//estan en la fila
			resultado = true;
		else
			resultado = false;
	}//else
	return resultado;
}//bool sonPosicionesPosiblesGrua

bool esPosibleGrua(const tArray fila, int tam, int posIni, int posFin, int posSoltar) {

	bool comprobar[MAX_PROD]; //Nos informa de que una posicion es valida o no para recibir una carga
	bool resultado = true;
	int posSoltarFin, posComprobarSoltar;
	if (sonPosicionesPosiblesGrua(tam, posIni, posFin, posSoltar)) {
		posSoltarFin = posSoltar + (posFin - posIni);
		for (posComprobarSoltar = posSoltar; posComprobarSoltar <= posSoltarFin; ++posComprobarSoltar) {
			if (posComprobarSoltar >= posIni && posComprobarSoltar <= posFin)
				comprobar[posComprobarSoltar] = true;
			else if (fila[posComprobarSoltar] != PROD_NULO)
				comprobar[posComprobarSoltar] = false;
			else
				comprobar[posComprobarSoltar] = true;
		}//for

		while (posComprobarSoltar <= posSoltarFin && resultado == true)
			if (comprobar[posComprobarSoltar])
				resultado = true;
			else
				resultado = false;
	}//if
	else {
		resultado = false;
	}//else
	return resultado;
}//bool esPosibleGrua

bool grua(tArray fila, int tam, int posIni, int posFin, int posSoltar, int &mov) {

	tArray arrayAux;
	int posIniAux = posIni;
	bool resultado;

	if (esPosibleGrua(fila, tam, posIni, posFin, posSoltar)) {
		for (posIniAux; posIniAux <= posFin; ++posIniAux) {		//Se copia cada valor de fila en un array auxiliar
			arrayAux[posIniAux] = fila[posIniAux];
			++mov;
		}//for
		posIniAux = posIni;
		for (posIniAux; posIniAux <= posFin; ++posIniAux)		//Se vacian las posiciones copiadas de la fila
			fila[posIniAux] = PROD_NULO;
		for (posIni; posIni <= posFin; ++posIni) {				//Se colocan las pos de fila guardas en fila apartir de posSoltar
			fila[posSoltar] = arrayAux[posIni];
			++posSoltar;
		}//for
		resultado = true;
	}//else
	else
		resultado = false;

	return resultado;
}//bool grua

int posHuecoLibreDerecha(const tArray fila, int tam, int posIni)//No la utiliza posHuecoLibreDir
{
	int i = posIni;
	while ((i < tam) && (fila[i] != PROD_NULO))
		++i;
	if (i == tam)//Si recorre todo el array, su valor es tam, cuando debe ser la ultima posicion
		--i;
	return i;
}//int posHuecoLibreDerecha

bool excavadora1Derecha(tArray fila, int tam, int posIni)//No la utiliza excavadora1Movimiento
{
	int posFinal = posHuecoLibreDerecha(fila, tam, posIni);
	int x = fila[posIni], y; // Las variables "x" "y" sirven para guardar los valores de las posiciones
	if (posFinal == tam - 1) // Esto quiere decir que no se puede hacer el movimiento
	{
		return false;
	}//if
	else
	{
		fila[posIni] = 0;
		for (posIni = ++posIni; posIni < posFinal; ++posIni)
		{
			y = fila[posIni];
			fila[posIni] = x;
			x = y;
		}//for
		fila[posFinal] = x;
		return true;
	}//else
}//bool excavadora1Derecha

int posHuecoLibreIzquierda(const tArray fila, int tam, int posIni)//No la utiliza posHuecoLibreDir
{
	while ((posIni > 0) && (fila[posIni] != PROD_NULO))
	{
		--posIni;
	}// while
	return posIni;
}// int posHuecoLibreIzquierda

bool excavadora1Izquierda(tArray fila, int tam, int posIni)//No la utiliza excavadora1Movimiento
{
	int posFinal = posHuecoLibreIzquierda(fila, tam, posIni);
	int x, y; //Las variables "x" "y" sirven para guardar los valores de las posiciones
	if (fila[posFinal] != PROD_NULO)
		return false;
	else
	{
		for (x = 0; posIni >= posFinal; --posIni)
		{
			y = fila[posIni];
			fila[posIni] = x;
			x = y;
		}//while
	}//else
}//bool excavadora1Izquierda

int posHuecoLibreDir(const tArray fila, int tam, int posIni, int direccion)
{
	while ((posIni < tam) && (posIni >= 0) && (fila[posIni] != PROD_NULO))
	{
		posIni += direccion;
	}//while

	return posIni;
}//int posHuecoLibreDir

bool excavadora1Movimiento(tArray fila, int tam, int posIni, int direccion)
{
	bool resultado;
	int posFinal = posHuecoLibreDir(fila, tam, posIni, direccion), ultimaPos = tam - 1;
	int x = fila[posFinal], y;// las variables "x" "y" sirven para guardar los valores de las posiciones
	if ((fila[posFinal] != PROD_NULO) && ((posFinal >= 0) || (posFinal < tam)))
	{
		resultado = false;
	}//if
	else
	{
		for (x = 0; posIni != posFinal; posIni += direccion) //Hacemos el movimiento de los valores por la fila
		{
			if ((posIni != 0) && (posIni != ultimaPos))//En la siguiente condicion no entran la posicion "0" ni la "--tam"
			{
				if ((esPosValida(tam, --posIni)) && (esPosValida(tam, posIni += 2)))
					//Comprobamos que existe alguna posicion inmediatamente inferior o superior para no pasarnos del array
				{
					--posIni;//En las condiciones hemos modificado el posIni, lo primero que hacemos es corregirlo
					y = fila[posIni];
					fila[posIni] = x;
					x = y;
				}//if
			}//if
			if ((posIni == 0) && (direccion == 1))// El caso "posIni = 0" que no entra en la condicion anterior
			{
				y = fila[posIni];
				fila[posIni] = x;
				x = y;
			}//if
			if ((posIni == ultimaPos) && (direccion == -1))// El caso "posIni = ultimaPos" que no entra en la condicion anterior
			{
				y = fila[posIni];
				fila[posIni] = x;
				x = y;
			}//if
		}//for
		fila[posFinal] = x; // La ultima posicion no se ve afectada por el bucle for
		resultado = true;
	}//else
	return resultado;
}//bool excavadora1Movimiento

bool excavadora(tArray fila, int tam, int posIni, int numDespla, int direccion, int &mov)
{
	bool resultado, movimientosAnteriores = false;//movimientosAnteriores nos indica si ha supuesto algun movimiento
	if (numDespla != 0)
	{
		--numDespla;
	}//if
	if (numDespla == 0)
	{
		if (direccion == 1)
			--posIni;
		else
			++posIni;
	}
	while ((excavadora1Movimiento(fila, tam, posIni, direccion)) && (numDespla > 0))//Recorre posiciones en la fila
	{
		if (esPosValida(tam, posIni) && numDespla >= 1)//Si se considera valida la posicion y, por lo tanto, se puede pasar a la siguiente
		{
			--numDespla;
			movimientosAnteriores = true;//Se ha realizado un movimiento correctamente
			if (direccion == 1)
			{
				++posIni;
			}//if
			else
				--posIni;
		}//if
		++mov;
	}//while

	if (numDespla == 0)
	{
		cout << "Se han podido realizar todos los desplazamientos.\n";
		resultado = true;
		if (movimientosAnteriores == true) //En el caso en el que no estuviera movimientosAnteriores, contaria una de mas
			++mov;
	}//if
	else
	{
		cout << "No se han podido realizar todos los desplazamientos.\n";
		resultado = false;
	}//else
	return resultado;
}//bool excavadora

bool ejecutarLeerFichero(tArray fila, int &tam)
{
	bool resultado;
	string nombre;
	cout << "Por favor, escriba el nombre del fichero que desea abrir (la extension no es necesaria):\n";
	cin >> nombre;
	nombre += ".txt";
	ifstream fichero;
	fichero.open(nombre);
	if (fichero.is_open()) {
		leerFilaFich(fichero, fila, tam);
		cout << "Se ha cargado con exito el fichero " << nombre << " pedido en la fila.\n"; //Ya esta sumado el .txt
		mostrarFila(fila, tam);
		resultado = true;
		fichero.close();
	} //If
	else
	{
		cout << "No se ha encontrado el fichero " << nombre << "\n";
		resultado = false;
	}
	return resultado;
}// void ejecutarLeerFichero

void ejecutarGuardarFichero(tArray fila, int tam)
{
	string nombre;
	cout << "Por favor, escriba el nombre del fichero en el que desea guardar la fila(no hace falta la extension):\n";
	cin >> nombre;
	nombre += ".txt";
	ofstream fich;
	fich.open(nombre);
	if (fich.is_open())
	{
		escribirFilaFich(fich, fila, tam);
		cout << "Se ha guardado con exito la fila en el fichero " << nombre << ".txt\n";
		fich.close();
	}//if
	else
		cout << "El fichero de texto no se ha podido abrir.\n";
}// void ejecutarGuardarFichero

void ejecutarGrua(tArray fila, int tam, int mov)
{
	int posIni, posFinal, posSoltar;
	cout << "Por favor introduzca la posicion desde la que desea empezar a levantar cargas (posIni): ";
	cin >> posIni;
	cout << "Por favor introduzca hasta que posicion desea levantar cargas (posFinal): ";
	cin >> posFinal;
	cout << "Por favor introduzca la posicion desde la que quiera empezar a dejar caer las cargas (posSoltar): ";
	cin >> posSoltar;

	grua(fila, tam, posIni, posFinal, posSoltar, mov);
	mostrarFila(fila, tam);
}// void ejecutarGrua

void ejecutarExcavadora(tArray fila, int tam, int &mov)
{
	int posIni, direccion, numDespla;
	cout << "Escoja desde que posicion desea que empiece a trabajar la excavadora:\n";
	cin >> posIni;
	while (esPosValida(tam, posIni) == false) //Comprobamos si existe la posicion
	{
		cout << "La posicion escrita no existe en la fila, por favor, escriba una posicion que exista:\n";
		cin >> posIni;
	}//while
	cout << "Escoja en que direccion quiere que trabaje la excavadora, "
		<< "IZQUIERDA ( -1 ) o DERECHA ( 1 ).\n";
	cin >> direccion;
	while ((direccion != 1) && (direccion != -1)) //Nos aseguramos de que solo entren los valores "1" y "-1"
	{
		cout << "El programa no entiende que quiere decirle, si quiere ir a la DERECHA escriba \"1\", "
			<< "en el caso de que quiera ir a la IZQUIERDA, escriba \"-1\":\n";
		cin >> direccion;
	}//while
	cout << "Decida cuantos movimientos quiere que haga la excavadora:\n";
	cin >> numDespla;
	if (numDespla == 1)
	{
		if (direccion == 1 && esPosValida(tam, posIni += 1))
			++mov;
		if (direccion == -1 && esPosValida(tam, posIni += -1))
			++mov;
	}//if
	if (excavadora(fila, tam, posIni, numDespla, direccion, mov))
		cout << "La excavadora ha podido hacer su trabajo.\n";
	else
		cout << "La excavadora ha terminado de trabajar, sin embargo, no ha podido hacer todos los desplazamientos solicitados.\n";
}// void ejecutarExcavadora

bool filaOrdenada(tArray fila, int tam)
{
	bool resultado = true;
	int i;
	int x = 0; //"x" es la ultima variable leida en el bucle distinta de PROD_NULO que sigue el orden de menor a mayor
	for (i = 0; esPosValida(tam, i); ++i)
	{
		if (fila[i] != PROD_NULO)
		{
			if (x > fila[i])// La fila no esta organizada de menor a mayor
				resultado = false;
			else
				x = fila[i];
		}//if
	}//for
	return resultado;
}//bool filaOrdenada

int menu()
{
	int pedido; //La opcion que pide el usuario
	cout << "Introduzca una opcion de las disponibles:\n" << "1.- Cargar fila de fichero.\n" << "2.- Guardar fila de fichero.\n"
		<< "3.- Usar grua.\n" << "4.- Usar excavadora.\n" << "0.- Salir.\n";
	cin >> pedido;
	while ((pedido > 4) || (pedido < 0))
	{
		cout << "La opcion escrita no se encuentra entre las mostradas, por favor, escriba otra opcion:\n";
		cin >> pedido;
	}//while
	return pedido;
}//menu

void ejecutarOpc(int opc, tArray fila, int &tam, int &mov)
{
	switch (opc)
	{
	case 1:
		if (ejecutarLeerFichero(fila, tam))//Si se ha conseguido leer el fichero
		{
			mov = 0;
			cout << "Se ha reiniciado el contador de movimientos.\n";
		}//if		
		break;
	case 2:
		ejecutarGuardarFichero(fila, tam);
		break;
	case 3:
		int posIni, posSoltar, posFin;
		cout << "Estado actual de la fila:\n";
		mostrarFila(fila, tam);
		cout << "Escoja la posIni: ";
		cin >> posIni;
		cout << "Escoja la posFin: ";
		cin >> posFin;
		cout << "Escoja la posSoltar: ";
		cin >> posSoltar;
		if (grua(fila, tam, posIni, posFin, posSoltar, mov))
			cout << "Se han ejecutado un total de " << mov << " movimientos distintos en la fila desde la ultima vez que "
			<< "se cargo una fila de un fichero.\n";
		else
			cout << "No se ha podido realizar nigun cambio en la grua.";
		if (filaOrdenada(fila, tam))
			cout << "Salvando las distancias entre unas posiciones y otras, la fila esta ordenada de menor a mayor.\n";
		else
			cout << "La fila no esta ordenada de menor a mayor.\n";
		mostrarFila(fila, tam);
		break;
	case 4:
		cout << "Estado actual de la fila:\n";
		mostrarFila(fila, tam);
		ejecutarExcavadora(fila, tam, mov);
		cout << "Se han ejecutado un total de " << mov << " movimientos distintos en la fila desde la ultima vez que "
			<< "se cargo una fila de un fichero.\n";
		if (filaOrdenada(fila, tam))
			cout << "Salvando las distancias entre unas posiciones y otras, la fila esta ordenada de menor a mayor.\n";
		else
			cout << "La fila no esta ordenada de menor a mayor.\n";
		mostrarFila(fila, tam);
		break;
	case 0:
		break;
	default:
		cout << "La opcion solicitada no existe.\n";
		break;
	}
}// void ejecutarOpc

int main()
{
	int tam = 0, mov = 0, posIni, direccion, i, opc = 1;
	tArray fila;
	cout << "Bienvenido usuario, le recomendamos que antes de utilizar la grua o la excavadora, cargue una fila de un "
		<< "archivo de texto con la opcion 1:\n";
	while (opc != 0)
	{
		opc = menu();
		ejecutarOpc(opc, fila, tam, mov);
	}//while
	return 0;
}//int main
