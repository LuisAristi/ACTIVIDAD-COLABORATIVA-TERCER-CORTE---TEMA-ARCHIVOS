#include "gestionAutomoviles.h"

void menuConsultaHora();
void consultarRutasPorHoraSalida();
void consultarRutasPorConductor();
void consultarRutasPorVehiculo();
void promedioViajerosPorRuta();

/*3.
Consultar rutas
3.1 Según fecha indicada (Indicar todas los viajes asignados a una hora o rango
de hora específica)
3.2 Según Conductor (Mostrar todos los viajes asignados a un
conductor, ruta, el día y hora)
3.3 Según Vehículo (Mostrar todos los viajes
asignados a un autobús, conductor, ruta, el día y hora)
3.4 Promedio de Viajeros
por ruta (mostrar el promedio de clientes que solicitaron una ruta específica)
*/

void menuConsultaHora()
{
    int opcion;
    std::cout << "1. Consultar por hora de salida\n";
    std::cout << "2. Consultar por hora de llegada\n";
    std::cout << "3. Consultar un rango de hora\n";
    opcion = ingresarNumero(opcion);
    switch (opcion)
    {
    case 1:
        consultarRutasPorHoraSalida();
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        std::cout << "ingrese una opcion valida\n";
    }
}

void consultarRutasPorHoraSalida()
{
    int contador;
    struct servicios Servicio[90];
    struct Tiempo tiempo;

    std::ifstream servicio("datosservicios.bin", std::ios::in | std::ios::binary);
    contador = 0;
    while (servicio.read(reinterpret_cast<char *>(&Servicio[contador]),
                         sizeof(servicios)))
    {
        contador++;
        if (contador >= 90)
        {
            std::cout << "Se ha alcanzado el número máximo de servicios\n";
            break;
        }
    }
    servicio.close();

    // ahora que tenemos el array de servicios, podemos hacer lo que queramos
    std::cout << "ingrese las horas de salida a buscar\n";
    ingresarTiempo(tiempo);
    for (int i = 0; i < contador; i++)
    {
        if (tiempo.hora == Servicio[i].salida.hora)
        {
            std::cout << Servicio[i].codigoDeRuta << "\n";


        }
    }
}

void consultarRutasPorConductor()
{
    struct AsignacionDeConductores conductorAsignado;
    struct Conductor conductor;
    struct servicios Servicio;
    struct ruta Ruta;
    long ID;
    std::cout << "Ingrese el ID del conductor\n";
    ID = ingresarNumero(ID);

    // buscar conductor en el archivo -----es asignacion quiero saber la ruta a la
    // que estan asignados
    getAsignacionConductores(conductorAsignado, ID);

    //debo buscar en el archivo servicio
    std::ifstream servicio("datosservicios.bin", std::ios::in | std::ios::binary);
    while (servicio.read(reinterpret_cast<char *>(&Servicio), sizeof(servicios)))
    {
        if (conductorAsignado.codigoDeServicio == Servicio.codigoDeServicio)
        {   
            compararRutaCodigo(Ruta, Servicio.codigoDeRuta);
            
            std::cout<<"ruta: "<<Ruta.nombreDeRuta<<"\n";
            std::cout<<"lugar de origen: "<< Ruta.lugarDeOrigen<<"\n";
            std::cout<<"lugar de destino"<<Ruta.lugarDestino<<"\n";

            //dias asignados
            std::cout<<"los dias asignados al conductor son\n";
            for(int i = 0; i<7; i++){
                if(Servicio.diasDeServicio.dias[i]){ dias(i);}
                std::cout<<",";
            }
            
            std::cout<<"\nhora de salida: ";
            mostrarTiempo(Servicio.salida);

            std::cout<<"\nhora de llegada: ";
            mostrarTiempo(Servicio.llegada);
        }
    }
    servicio.close();
}