#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>
#include <typeinfo> //nos permitira determinar por el tipo de dato

using namespace std;

void MostrarTablero(vector<string> columnas){


    cout << "\n\n\n\n";
    int contador = 0;
    for(int i = 0; i < 4; i++){
        cout << "\t|---------------|---------------|---------------|---------------|" << endl;
        cout << "\t|\t" << columnas[contador] << "\t|\t" << columnas[contador+1] << "\t|\t" << columnas[contador+2] << "\t|\t" << columnas[contador+3] << "\t|"<< endl;

        if(contador == 16){
            cout << "\t|---------------|---------------|---------------|---------------|" << endl;
        }

        contador += 4;
    }

    cout << "\n\t\t" << "      [*] JUEGO DE LOS PARES" << endl;
    cout << "\t\t" << "      [>] PRESIONA -- R -- para retroceder" << endl;
}

bool verificandoTabla(vector<string>columnas, vector<string>fichas){
    int numeros = 16;
    
    for(int i = 0; i < columnas.size(); i++){
        if(columnas[i] == fichas[i]){
            numeros -= 1;
        }
    }

    if(numeros == 0){
        return false;
    }else{
        return true;
    }
}

//tenemos que modificar la parte de generar fichas....
vector<string> generando_fichas(){
    //vamos a crear simbolos aleatorioa dentro de un arreglo...
    vector<string> simbolos = {"+", "-", "/", "*"};
    vector<string> datos = {};

    int i = 0;
    while(i <= 15){
        
        
        datos.push_back(simbolos[rand()%4]);

        i++;
    }



    return datos;
}



int main()
{
   int primera_posicion = 0; int segunda_posicion = 0;
   int puntaje_jugador = 0; int puntaje_maquina = 0;
   string rol_jugador = "JUGADOR";
   auto fichas = generando_fichas();
   vector<string> columnas = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
   vector<int> posiciones = {};

   //vamos a generar la configuracion de los numeros aleatorioa, el cual seran el uso para
   //la maquina
    srand(time(0));
    bool ejecutar = true;
    while(ejecutar){
        system("clear");
        //aqui ejecutaremos ciertas funcion para el juego que ejecutaremos.
        cout << "PUNTAJE JUGADOR: " << to_string(puntaje_jugador) << "   " << "PUNTAJE MAQUINA: " << to_string(puntaje_maquina) << " " << endl;
        MostrarTablero(columnas);

        bool respuesta = verificandoTabla(columnas, fichas);
        //vamos a comparar las fichas... si son iguales se mantienen, caso contrario
        //la tabla deberia resetearse e ingresar nuevamente los numeros.
        if(respuesta){
            if(posiciones.size() != 0){
                //comenzamos analizando posiciones....
                if(fichas[posiciones[0]] != fichas[posiciones[1]]){

                    if(rol_jugador == "JUGADOR"){
                        for(int i : posiciones){
                            columnas[i] = to_string(i+1);
                        }
                        rol_jugador = "MAQUINA";
                    }
                    else if(rol_jugador == "MAQUINA"){
                        for(int i : posiciones){
                            columnas[i] = to_string(i+1);
                        }
                        rol_jugador = "JUGADOR";
                    }

                }else{
                    //cuando las fichas son iguales....
                    if(rol_jugador == "JUGADOR"){
                        puntaje_jugador += 1;
                        rol_jugador = "MAQUINA";
                    }
                    else if(rol_jugador == "MAQUINA"){
                        puntaje_maquina += 1;
                        rol_jugador = "JUGADOR";
                    }
                }
                posiciones = {};
                primera_posicion = 0; segunda_posicion = 0;
            }else{

                if(rol_jugador == "JUGADOR"){


                    cout << "\n|>> Introduce tu primer posicion: ";
                    cin >> primera_posicion;

                    cout << "\n|>> Introduce tu segunda posicion: ";
                    cin >> segunda_posicion;

                    if(primera_posicion == segunda_posicion){
                        //generaremos una alerta....
                        cout << "\n[!] Los Valores no deben ser iguales..." << endl;
                        usleep(2000000);
                    }else if(! (primera_posicion >=1 && primera_posicion <= 16) || !(segunda_posicion >=1 && segunda_posicion <= 16)){
                        cout << "\n[!] Posicion fuera de rango..." << endl;
                        usleep(2000000);
                    }else{
                        //continuaremos con el proceso...
                        posiciones.push_back(primera_posicion-1);
                        posiciones.push_back(segunda_posicion-1);

                        //lo que haremos es insertar las fichas en el cuadro o tablero...
                        columnas[primera_posicion-1] = fichas[primera_posicion-1];
                        columnas[segunda_posicion-1] = fichas[segunda_posicion-1];
                    }

                }
                else if(rol_jugador == "MAQUINA"){
                    cout << endl;
                    cout << "Turno de la maquina...." << endl;

                    //tenemos que buscar maneras para poder las respectivas validaciones.
                    while(true){
                        primera_posicion = 0+rand()%16;
                        if(columnas[primera_posicion] == "*" || columnas[primera_posicion] == "/" || columnas[primera_posicion] == "+" || columnas[primera_posicion] == "-"){
                            primera_posicion = 0+rand()%16;
                        }else{
                            while(true){
                                segunda_posicion = 0+rand()%16;
                                if(columnas[segunda_posicion] == "*" || columnas[segunda_posicion] == "/" || columnas[segunda_posicion] == "+" || columnas[segunda_posicion] == "-"){
                                    segunda_posicion = 0+rand()%16;
                                }else{
                                    //cuando nuestras posiciones son numeros....  
                                    //vamos a comparar entre los dos 
                                    if(primera_posicion == segunda_posicion){
                                        segunda_posicion = 0+rand()%16;
                                    }else{
                                        //generamos la insertacion de los datos....
                                        //continuaremos con el proceso...
                                        posiciones.push_back(primera_posicion);
                                        posiciones.push_back(segunda_posicion);
                                        //lo que haremos es insertar las fichas en el cuadro o tablero...
                                        columnas[primera_posicion] = fichas[primera_posicion];
                                        columnas[segunda_posicion] = fichas[segunda_posicion];
                                        break;   
                                    }
                                }
                            }
                            break;
                        } 

                    }

                }

            }
            usleep(2000000);
        }else{
            //Imprimimos datos informativos al jugador....
            string decision = "";

            while(true){
                system("clear");
                //aqui ejecutaremos ciertas funcion para el juego que ejecutaremos.
                cout << "PUNTAJE JUGADOR: " << to_string(puntaje_jugador) << "   " << "PUNTAJE MAQUINA: " << to_string(puntaje_maquina) << " " << endl;
                MostrarTablero(columnas);

                if(puntaje_jugador > puntaje_maquina){
                    cout << "JUGADOR GANA!!!!";
                    rol_jugador = "MAQUINA";
                }else if(puntaje_maquina > puntaje_jugador){
                    cout << "MAQUINA GANA!!!!";
                    rol_jugador = "JUGADOR";
                }else if(puntaje_jugador == puntaje_maquina){
                    cout << "EMPATES!!!!" << endl;
                    vector<string> jugadores = {"JUGADOR", "MAQINA"};
                    int escoge = rand()%2;
                    rol_jugador = jugadores[escoge];
                }

                cout << endl;

                cout << "[>>>] QUIERES JUGAR DE NUEVO [Y/N] :  ";
                cin >> decision;

                if(decision == "Y"){
                    //reestablecemos valores para que iterar nuevamente... se genere una jugada nueva.
                    puntaje_jugador = 0; puntaje_maquina = 0;
                    columnas = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
                    posiciones = {};
                    break;
                }else if(decision == "N"){
                    ejecutar = false;
                    break;
                }else{
                    cout << "INTRODUCE UNA OPCION CORRECTA...." << endl;
                    usleep(1000000);
                }
            }

        }
    }//while(true)
    return 0;
}
