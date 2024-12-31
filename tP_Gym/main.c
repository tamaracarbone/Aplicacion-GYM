#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define USUARIOADMINISTRADOR "admi1"
#define CLAVEADMINISTRADOR "1234"
#define DIM 50
#define DIM2 200


const char ARCH_CLIENTES[]="clientes.dat";
const char ARCH_CLASES[]="clases.dat";
const char ARCH_MISCLASES[]="misClases.dat";
const char ARCH_MISRUTINAS[]="misRutinas.dat";

///ESTRUCTURAS//////////////////
///cliente
typedef struct
{
    int idCliente;
    char nombre[DIM];
    char apellido[DIM];
    char userName[DIM];
    char password[DIM];
    char mail[DIM];
    char genero;
    char cuota[DIM];
} stCliente;

///administrador
typedef struct
{
    char userName[DIM];
    char password[DIM];
} stAdministrador;

///Producto
typedef struct
{
    int idProducto;
    char nombre[DIM];
    char descripcion[DIM];
    float precio;
} stProducto;

///CompraTienda
typedef struct
{
    int idProducto;
    int idCliente;
    int cantidad;
    float total;
} stCompra;

/// Clases
typedef struct
{
    char clase[DIM];
    char profesor[DIM];
    char dia [DIM];
    char hora[DIM];
} stClases;

/// Rutinas
typedef struct
{
    char dia[DIM];
    char desarollo[DIM2];
} stRutinas;

///Sugerencias
typedef struct
{
    char desarrollo[DIM2];
    int idCliente;
    char nombre[DIM];
    char apellido[DIM];
    char userName[DIM];
} stSugerencias;

void dibujarCuadro(int x1,int y1,int x2,int y2);///Funcion cuadro
void gotoxy (int x, int y);///Funcion gotoxy
int buscaUltimoIdCliente(char archivo []);/// Funcion comienzo de busqueda
void cargaCliente(char archivo[]);/// Carga de un unico usuario
void logeoCliente(char nombreArchivo[], char rutaTodasClases[], char rutaMisClases[]); /// Logeo Cliente
int encontrarCliente (char archivo [], char nombre []);   ///Verificar existencia usuario
int VerificarUsuarioClave(char nombreArchivo[], stCliente C);  ///Verificacion usuario contraseña
int buscaIdApartirUsuario (char usuario[], char ruta[]);    ///busca el id del cliente a partir del usuario
int VerificarUsuarioClaveAdministrador(stAdministrador A);    ///Verificacion usuario contraseña administrador
void logeoAdministrador(char rutaClientes[], char rutaClases[]);   ///Logeo Administrador
void muestraUnCliente(stCliente c); ///muestra un cliente
void cargaArchivoDeClases (char ruta[]);/// carga clases
void mostrarArchivoClases(char ruta[]);/// muestra clases
int ValidacionClaseRepetida (char rutaMisClases[], char nombreClase[]);   ///validacion clase repetida
int ValidacionClaseExistente (char rutaMisClases[], char nombreClase[]);   ///Validacion existencia clase
void cargaArchivoDeRutinas (char rutaRutinas[]); ///Carga Archivo Rutinas
void mostrarArchivoRutinas(char rutaRutinas[]);   ///Mostrar archivo rutinas
void cargaArchivoProductos (char rutaProductos[]);  ///carga archivo productos
void mostrarArchivoProductos(char rutaProductos[]);   ///mostrar archivo productos
int compraProductoArreglo (char rutaProductos[], stCompra arregloCompra[], int idLogeado, int dim);   ///compra productos por cliente (genera un arreglo de compra)
void mostrarArregloCompras (stCompra arregloCompra[], int val); ///muestra arreglo de compras por cliente
void archivoSugerenciasYquejas (int idLogeado, char rutaSugerencias[], char rutaClientes[]);    ///archivo sugerencias y quejas
void menuClienteLogeado(char ruta [], char rutaMisClases[], char rutaTodasClases[], int idLogeado); ///menu cliente
void muestraUnClienteApartirId (int idLogeado, char rutaClientes[]);   ///muestra un cliente a partir del id pasado por parametro
void mostrarArchivoSugerenciasQuejas(char rutaSugerencias[]);    ///muestra archivo sugerencias quejas
void menuAdministrador (char rutaClientes [], char rutaTodasClases[]);      ///menu administrador


int main()
{

    dibujarCuadro(0,0,76,24);
    gotoxy(20,2);
    system("COLOR 06");
    char usuario[DIM + 1];
    char clave [DIM + 1];
    char control='s';

    int numPerfil;
    int numLog;
    int i = 0;

    cargaArchivoDeClases(ARCH_CLASES);

    dibujarCuadro(1,1,74,3);
    gotoxy(20,0);
    do
    {
        printf("\n\n\t\tPor favor, ingrese el numero de su perfil\n");
        printf("\n\n\n");
        printf("\n\n\t===================================================\n");
        printf("\n\n\t-- 1. Perfil Cliente ------------------------------ \n");
        printf("\n\n\t-- 2. Perfil Administrador ------------------------ \n");
        printf("\n\n\t===================================================> ");
        scanf("%d", &numPerfil);
        switch(numPerfil)
        {
        case 1:
            system("cls");
            dibujarCuadro(1,1,74,3);
            gotoxy(20,2);
            printf("  ..::Perfil Cliente::..\n\n") ;
            printf("  \n\n\tBienvenido al perfil para clientes!\n\n");
            printf("  \n\n\t===================================================\n");
            printf("  \n\n\t--- 1.Nuevo usuario / Registrarse -----------------\n");
            printf("  \n\n\t--- 2.Login ---------------------------------------\n");
            printf("  \n\n\t===================================================> ");
            scanf("%d", &numLog);
            system("cls");

            switch(numLog)
            {
            case 1:
                cargaCliente(ARCH_CLIENTES);
                system("cls");
                break;

            case 2:
                logeoCliente(ARCH_CLIENTES,ARCH_CLASES,ARCH_MISCLASES);
                system("cls");
                break;

            default:
                printf("Ingreso una opcion incorrecta\n");
            }
            break;

        case 2:
            logeoAdministrador(ARCH_CLIENTES,ARCH_CLASES);
            system("cls");
            break;

        default:
            printf("Ingreso una opcion incorrecta\n");
        }
        printf("Desea continuar? s/n\n");
        fflush(stdin);
        scanf("%c",&control);
        system("cls");
    }
    while (control=='s');
    return 0;
}



///Funcion gotoxy
void gotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y= y;
    SetConsoleCursorPosition(hcon,dwPos);
}

///FUNCION CUADRO
void dibujarCuadro(int x1,int y1,int x2,int y2)
{
    int i;

    for (i=x1; i<x2; i++)
    {
        gotoxy(i,y1);
        printf("\304"); //linea horizontal superior
        gotoxy(i,y2);
        printf("\304"); //linea horizontal inferior
    }

    for (i=y1; i<y2; i++)
    {
        gotoxy(x1,i);
        printf("\263"); //linea vertical izquierda
        gotoxy(x2,i);
        printf("\263"); //linea vertical derecha
    }

    gotoxy(x1,y1);
    printf("\332");
    gotoxy(x1,y2);
    printf("\300");
    gotoxy(x2,y1);
    printf("\277");
    gotoxy(x2,y2);
    printf("\331");
}
/// ////////////////////////////////////BUSCA ULTIMO ID DEL CLIENTE
int buscaUltimoIdCliente(char archivo [])
{
    stCliente a;
    int id=0;
    FILE *pArchi=fopen(archivo,"rb");
    if(pArchi!=NULL)
    {
        fseek(pArchi,-1 * sizeof(stCliente),SEEK_END);
        if(fread(&a,sizeof(stCliente),1,pArchi)>0)
        {
            id=a.idCliente;
        }
        fclose(pArchi);
    }
    return id;
}

/// /////////////VERIFICAR EXISTENCIA DE USUARIO
int encontrarCliente (char ruta [], char nombre [])
{
    int encontrar = 0 ;
    stCliente C;
    FILE * archivo = fopen (ruta,"rb");
    if (archivo!=NULL)
    {

        while (fread (&C,sizeof (stCliente),1,archivo)> 0 && encontrar == 0 )
        {

            if (strcmp(C.userName,nombre)== 0 )
            {

                encontrar = 1;

            }

        }


    }

    fclose (archivo);
    return encontrar;
}

/// ///////////////////////////////////////////CARGA NUEVO USUARIO CLIENTE
void cargaCliente(char archivo[])
{

    int flagg = 0 ;

    FILE *archi=NULL;

    stCliente c;

    int acceso =0 ;
    int i=0;
    int flag =0 ;
    int caracteres = 0 ;
    char control;

    i=buscaUltimoIdCliente(archivo);

    archi=fopen(archivo, "ab");

    if(archi!=NULL)
    {
        dibujarCuadro(1,1,74,3);
        gotoxy(20,0);
        printf("\n\n\t\t\tVamos a crear tu usuario \n");

        c.idCliente=i+1;///id auto incremental
        printf("\n\n\n\tIngrese nombre........................: ");
        fflush(stdin);
        gets( c.nombre);
        printf("\n\tIngrese apellido......................: ");
        fflush(stdin);
        gets(c.apellido);
        do
        {
            printf("\n\tIngrese Usuario.......................: ");
            gets(c.userName);
            acceso =encontrarCliente(archivo,c.userName);
            if (acceso == 1)
            {
                printf("\nEse usuario ya existe, ingrese uno nuevo nuevamente");
                fflush (stdin);
                gets (c.userName);

            }

        }
        while(acceso == 1);

        printf("\n\tRequisitos : Mas de 4 caracteres y hasta 12\n");
        printf("\tNo se permiten caracteres especiales\n");
        printf("\tIngrese password......................: ");

        do
        {
            fflush(stdin);
            scanf("%s",&c.password);
            caracteres = strlen(c.password);
            if (caracteres>4&&caracteres <= 12)
            {
                flag = 0 ;

            }
            else
            {
                flag = 1 ;
                printf ("\nLa clave no cumple con los requisitos\nReintente nuevamente\n");
            }
        }
        while (flag==1);

        printf("\n\tIngrese email........................: ");
        do
        {

            fflush(stdin);
            scanf("%s",&c.mail);
            if (strstr (c.mail,"@") == NULL || strstr (c.mail,".com")== NULL)
            {
                printf ("\n\tEmail Invalido, intentelo nuevamente:\n");
                flagg =1 ;
            }
            else
            {
                flagg = 0 ;
            }
        }
        while (flagg == 1);


        printf("\n\tIngrese genero (m o f)...............: ");
        fflush(stdin);
        scanf("%c",&c.genero);
        while(c.genero!='m' && c.genero!='f' && c.genero!='o' )
        {
            printf("Genero erroneo. Intente nuvamente.. ((m.Masculino   f.Femenino    o.Otro)): ");
            fflush(stdin);
            scanf("%c", &c.genero);
        }
        printf("\n\tDesea abonar la cuota? s/n...........: ");
        fflush(stdin);
        scanf("%c",&control);
        if (control=='s')
        {
            strcpy(c.cuota,"cuota al dia");
        }
        else
        {
            strcpy(c.cuota,"cuota vencida");
        }
        fwrite(&c, sizeof(stCliente),1,archi);
        system("cls");
        fclose(archi);
    }

}

///VERIFICA QUE EL USUARIO Y CONTRASEÑA DEL CLIENTE COINCIDAN
int VerificarUsuarioClave(char nombreArchivo[], stCliente C)
{
    stCliente usuarioGuardado;
    FILE * archivo=fopen(nombreArchivo,"rb");
    int ingresa=0;

    if(archivo != NULL)
    {
        while (fread(&usuarioGuardado,sizeof(stCliente),1,archivo)>0 && ingresa==0)
        {
            if(strcmp(usuarioGuardado.userName,C.userName)==0 && strcmp(usuarioGuardado.password,C.password)==0)
            {
                ingresa = 1;
            }
            else
            {
                ingresa=0;
            }
        }
        if (ingresa==0)
        {
            printf("\n\tUsuario y clave son incorrectas\n\n");
            system("pause");
        }
    }
    fclose(archivo);
    return ingresa;
}

/// //////////////////////BUSCA EL ID A PARTIR DEL USUARIO
int buscaIdApartirUsuario (char usuario[], char ruta[])
{
    stCliente C;
    int flag=0;
    int IdBuscado=0;

    FILE *archivo = fopen(ruta,"rb");

    if (archivo!=NULL)
    {
        while (fread(&C,sizeof(stCliente),1,archivo)>0 && flag==0)
        {
            if (strcmp(C.userName,usuario)==0)
            {
                flag=1;
                IdBuscado=C.idCliente;
            }
            else
            {
                flag=0;
            }
        }
    }
    fclose(archivo);
    return IdBuscado;
}

///LOGEO CLIENTE
void logeoCliente(char nombreArchivo[], char rutaTodasClases[], char rutaMisClases[])
{
    char caracter;
    int intento=0;
    int ingresa1=0;
    int id;
    stCliente cliente;

    do
    {
        int i = 0;
        system("cls");
        dibujarCuadro(1,1,74,3);
        gotoxy(20,0);
        printf("\n\n\t\t\t INICIO DE SESION\n");
        printf("\n\tUSUARIO:");
        fflush(stdin);
        gets(cliente.userName);
        printf("\n\tCLAVE: ");

        while(caracter = getch())
        {
            if(caracter==13)
            {
                cliente.password[i]='\0';
                break;
            }
            else if (caracter==8)
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                if(i<DIM)
                {
                    printf("*");
                    cliente.password[i] = caracter;
                    i++;
                }
            }

        }
        printf("\n\tClave leida: %s\n",cliente.password);

        ingresa1=VerificarUsuarioClave(nombreArchivo,cliente);
        intento++;
    }
    while(intento <3 && ingresa1 == 0);

    if(ingresa1==1)
    {
        system("pause");
        system("cls");
        printf("\n\t======================\n");
        printf("\n\tBienvenido al Sistema!\n");
        printf("\n\t======================\n\n");
        system("pause");
        id=buscaIdApartirUsuario(cliente.userName,nombreArchivo);
        menuClienteLogeado(nombreArchivo,rutaMisClases,rutaTodasClases,id);
    }
    else
    {
        printf("\n\tUsted ha sobrepasado el numero maximo de intentos permitidos\n");
        system("pause");
    }
}

///VERIFICA QUE USUARIO Y CLAVE ADMINISTRADOR COINCIDAN
int VerificarUsuarioClaveAdministrador(stAdministrador A)
{
    int ingresa=0;

    if(strcmp(USUARIOADMINISTRADOR,A.userName)==0 && strcmp(CLAVEADMINISTRADOR,A.password)==0)
    {
        ingresa = 1;
    }
    else
    {
        ingresa=0;
        printf("\n\tUsuario y clave son incorrectas\n\n");
        system("pause");
    }
    return ingresa;
}

///LOGEO ADMINISTRADOR
void logeoAdministrador(char rutaClientes[], char rutaClases[])
{
    char caracter;
    int intento = 0;
    int ingresa1=0;
    stAdministrador a;

    do
    {
        int i = 0;
        system("cls");
        dibujarCuadro(1,1,74,3);
        gotoxy(20,0);
        printf("\n\n\t\t\t INICIO DE SESION\n");
        printf("\n\tUSUARIO:");
        fflush(stdin);
        gets(a.userName);
        printf("\n\tCLAVE: ");

        while(caracter = getch())
        {
            if(caracter==13)
            {
                a.password[i]='\0';
                break;
            }
            else if (caracter==8)
            {
                if(i>0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else
            {
                if(i<DIM)
                {
                    printf("*");
                    a.password[i] = caracter;
                    i++;
                }
            }

        }
        ingresa1=VerificarUsuarioClaveAdministrador(a);
        intento++;

    }
    while(intento <3 && ingresa1 == 0);

    if(ingresa1==1)
    {
        printf("\n");
        system("pause");
        system("cls");
        printf("\n\t======================\n");
        printf("\n\tBienvenido al Sistema!\n");
        printf("\n\t======================\n\n");
        system("pause");
        system("cls");
        menuAdministrador(rutaClientes,rutaClases);
    }
    else
    {
        printf("\n\tUsted ha sobrepasado el numero maximo de intentos permitidos\n");
        system("pause");
    }

}

/// /////////////////////////////////////// MUESTRA UN CLIENTE
void muestraUnCliente(stCliente c)
{

    printf("\n---------------------------------------------------");
    printf("\nId-----------------------------:%d",c.idCliente);
    printf("\nNombre-------------------------:%s",c.nombre);
    printf("\nApellido-----------------------:%s",c.apellido);
    printf("\nUser Name----------------------:%s",c.userName);
    printf("\nEmail--------------------------:%s",c.mail);
    if(c.genero=='m')
    {
        printf("\nGenero-------------------------:Masculino");
    }
    else if (c.genero=='f')
    {
        printf("\nGenero-------------------------:Femenino");
    }
    else
    {
        printf("\nGenero-------------------------:Otro ");
    }
    printf("\nEstado cuota-------------------:");
    if (strcmp(c.cuota,"cuota vencida")==0)
    {
        printf("\033[0;31m"); //Set the text to the color red
        printf("%s",c.cuota);
        printf("\033[0;33m"); //Resets the text to default color
    }
    else
    {
        printf("\033[0;32m"); //Set the text to the color red
        printf("%s",c.cuota);
        printf("\033[0;33m"); //Resets the text to default color
    }


}

/// ///////////////////////////////////////////////////////CARGAR DE ARCHIVO DE CLASES DISPONIBLES
void cargaArchivoDeClases (char ruta[])
{
    stClases cla;

    FILE * archivo = fopen(ruta,"wb");
    if(archivo!=NULL)
    {
        strcpy(cla.clase,"Yoga");
        strcpy(cla.profesor,"Osho");
        strcpy(cla.dia,"lunes miercoles viernes");
        strcpy(cla.hora,"10:00-12:00-16:00-19:00");
        fwrite(&cla,sizeof(stClases),1,archivo);

        strcpy(cla.clase,"Musculacion");
        strcpy(cla.profesor,"Arny");
        strcpy(cla.dia,"lunes martes miercoles jueves viernes sabado");
        strcpy(cla.hora,"08:00-10:00-12:00-15:00-18:00-20:00-22:00");
        fwrite(&cla,sizeof(stClases),1,archivo);

        strcpy(cla.clase,"Zumba");
        strcpy(cla.profesor,"Marcelinno");
        strcpy(cla.dia," martes jueves  sabado");
        strcpy(cla.hora,"9:00-11:00-20:00");
        fwrite(&cla,sizeof(stClases),1,archivo);

        strcpy(cla.clase,"Crossfit");
        strcpy(cla.profesor,"Jose Fit");
        strcpy(cla.dia,"lunes miercoles viernes sabado");
        strcpy(cla.hora,"08:00-10:00-12:00-13:00");
        fwrite(&cla,sizeof(stClases),1,archivo);

        strcpy(cla.clase,"Taekwondo");
        strcpy(cla.profesor,"Kung Lao");
        strcpy(cla.dia,"martes jueves");
        strcpy(cla.hora,"08:00-21:00");
        fwrite(&cla,sizeof(stClases),1,archivo);
    }
    fclose(archivo);
}
/// ////////////////////////////////////////////////////// MOSTRAR ARCHIVO CLASES
void mostrarArchivoClases(char ruta[])
{
    stClases cla;

    FILE * archivo = fopen(ruta,"rb");
    if(archivo!=NULL)
    {
        while (fread(&cla,sizeof(stClases),1,archivo)>0)
        {

            printf("Datos de la clase:\n");
            printf("Nombre de la clase: %s\n",cla.clase);
            printf("Nombre del profesor: %s\n",cla.profesor);
            printf("Dias: %s\n",cla.dia);
            printf("Horarios: %s\n",cla.hora);
            printf("=======================\n\n");
        }

    }
    fclose(archivo);
}

/// ///////////VALIDACION EXISTENCIA CLASE
int ValidacionClaseExistente (char rutaTodasClases[], char nombreClase[])
{
    int claseExistente=0;
    stClases C;

    FILE *archivo=fopen(rutaTodasClases,"rb");

    if (archivo!=NULL)
    {
        while (fread(&C,sizeof(stClases),1,archivo)>0 && claseExistente==0)
        {
            if (strcmpi(C.clase,nombreClase)==0)
            {
                claseExistente=1;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Hubo un error, el archivo no pudo abrirse\n");
    }
    return claseExistente;
}

/// ///////////VALIDACION INSCRIPCION CLASE
int ValidacionClaseRepetida (char rutaMisClases[], char nombreClase[])
{
    int claseRepetida=0;
    stClases C;

    FILE *archivo=fopen(rutaMisClases,"rb");

    if (archivo!=NULL)
    {
        while (fread(&C,sizeof(stClases),1,archivo)>0 && claseRepetida==0)
        {
            if (strcmpi(C.clase,nombreClase)==0)
            {
                claseRepetida=1;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Hubo un error, el archivo no pudo abrirse\n");
    }
    return claseRepetida;
}

int ValidacionInscriptoMusculacion (char rutaMisClases[])
{
    int muscu=0;
    stClases C;

    FILE *archivo=fopen(rutaMisClases,"rb");

    if (archivo!=NULL)
    {
        while (fread(&C,sizeof(stClases),1,archivo)>0 && muscu==0)
        {
            if (strcmpi(C.clase,"musculacion")==0)
            {
                muscu=1;
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("Hubo un error, el archivo no pudo abrirse\n");
    }
    return muscu;
}

/// ///////////////////////////////////////////////////////CARGAR DE ARCHIVO DE RUTINAS
void cargaArchivoDeRutinas (char rutaRutinas[])
{
    stRutinas R;

    FILE * archivo = fopen(rutaRutinas,"wb");

    if(archivo!=NULL)
    {
        strcpy(R.dia,"DIA 1");
        strcpy(R.desarollo,"Pecho: press bco plano 3x12 - Flexiones de brazos 3x12\nEspalda: Remo bajo 3x12 - Serrucho 3x12\nHombros: Vuelos laterales 3x12 - press arnold 3x12\n");
        fwrite(&R,sizeof(stRutinas),1,archivo);

        strcpy(R.dia,"DIA 2");
        strcpy(R.desarollo,"Gluteos: patada de burro 3x20 -  Hip Thrust 3x15\nCuadriceps: Sillon cuadriceps 3x15 - Sentadilla bulgara 3x12\nIsquiotibiales: Peso muerto 3x15 - Sillon isquio 3x15\n");
        fwrite(&R,sizeof(stRutinas),1,archivo);

        strcpy(R.dia,"DIA 3");
        strcpy(R.desarollo,"Biceps: Curl alternado 3x12 - Martillo 3x12\nTriceps: Fondos 3x12 - triceps polea 3x12\nAbductores: abductores polea 3x15 - Estocadas 3x15\n");
        fwrite(&R,sizeof(stRutinas),1,archivo);

        strcpy(R.dia,"DIA 4");
        strcpy(R.desarollo,"Gemelos: gemelos con barra 3x20\nAductores: Sentadilla Zumo 3x15 - Aductores maquina 3x15\nGluteos: Sentadilla barra 3x15 - patada de gluteos 3x15\n");
        fwrite(&R,sizeof(stRutinas),1,archivo);

    }
    fclose(archivo);
}

/// ////////////////////////////////////////////////////// MOSTRAR ARCHIVO RUTINAS
void mostrarArchivoRutinas(char rutaRutinas[])
{
    stRutinas R;

    FILE * archivo = fopen(rutaRutinas,"rb");

    if(archivo!=NULL)
    {
        while (fread(&R,sizeof(stRutinas),1,archivo)>0)
        {
            printf("%s\n",R.dia);
            printf("%s\n",R.desarollo);
            printf("=======================\n\n");
        }
    }
    fclose(archivo);
}

/// /////////CARGA ARCHIVO PRODUCTOS
void cargaArchivoProductos (char rutaProductos[])
{
    stProducto P;

    FILE *archivo=fopen(rutaProductos,"wb");

    if (archivo!=NULL)
    {

            P.idProducto=1;
            strcpy(P.nombre,"Remera");
            strcpy(P.descripcion,"Indumentaria deportiva");
            P.precio=2000;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=2;
            strcpy(P.nombre,"Calza");
            strcpy(P.descripcion,"Indumentaria deportiva");
            P.precio=5000;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=3;
            strcpy(P.nombre,"Top deportivo");
            strcpy(P.descripcion,"Indumentaria deportiva");
            P.precio=2500;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=4;
            strcpy(P.nombre,"Proteina Power800 1kg");
            strcpy(P.descripcion,"Suplementos");
            P.precio=5000;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=5;
            strcpy(P.nombre,"Mancuernas-10kg");
            strcpy(P.descripcion,"Equipamiento deportivo");
            P.precio=8000;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=6;
            strcpy(P.nombre,"Colchoneta Mat");
            strcpy(P.descripcion,"Indumentaria deportiva");
            P.precio=3000;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=7;
            strcpy(P.nombre,"Bandas elasticas");
            strcpy(P.descripcion,"Equipamiento deportivo");
            P.precio=1500;
            fwrite(&P,sizeof(stProducto),1,archivo);

            P.idProducto=8;
            strcpy(P.nombre,"Mochila");
            strcpy(P.descripcion,"Mochilas/bolsos");
            P.precio=6000;
            fwrite(&P,sizeof(stProducto),1,archivo);

    }
    else
    {
        printf("Error, no pudo abrirse el archivo\n");
    }
    fclose(archivo);
}

/// ///////////////MOSTRAR ARCHIVO PRODUCTOS
void mostrarArchivoProductos(char rutaProductos[])
{
    stProducto P;

    FILE*archivo=fopen(rutaProductos,"rb");

    if (archivo!=NULL)
    {
        while(fread(&P,sizeof(stProducto),1,archivo)>0)
        {
            printf("ID producto: %d\n",P.idProducto);
            printf("Nombre del producto: %s\n",P.nombre);
            printf("Descripcion del producto: %s\n",P.descripcion);
            printf("Precio del producto: %.2f\n",P.precio);
            printf("=========================================\n");
        }
    }
    else
    {
        printf("Error, no pudo abrirse el archivo\n");
    }
    fclose(archivo);
}

/// ////////////////// COMPRA PRODUCTO POR CLIENTE
int compraProductoArreglo (char rutaProductos[], stCompra arregloCompra[], int idLogeado, int dim)
{
    char control='s';
    stProducto P;

    int id;
    int i=0;
    int cant=0;
    int flag=0;
    float total=0;

    FILE *archivo=fopen(rutaProductos,"rb");

    if (archivo!=NULL)
    {
        printf("Desea comprar algun producto? s/n\n");
        fflush(stdin);
        scanf("%c",&control);
        while (control=='s' && i<dim)
        {
            flag=0;
            printf("Ingrese ID del producto que desea comprar:\n");
            scanf("%d",&id);
            fseek(archivo,0,SEEK_SET);
            while (fread(&P,sizeof(stProducto),1,archivo)>0 && flag==0)
            {
                if (P.idProducto==id)
                {
                    flag=1;
                    printf("Excelente el producto a comprar es: %s\n",P.nombre);
                }
                else
                {
                    flag=0;
                }
            }
            if(flag==1)
            {
                printf("Cuantas unidades desea comprar?\n");
                scanf("%d",&cant);
                if (cant>0 && cant<100)
                {
                    total=(float)cant*P.precio;
                    arregloCompra[i].idProducto=id;
                    arregloCompra[i].idCliente=idLogeado;
                    arregloCompra[i].cantidad=cant;
                    arregloCompra[i].total=total;
                    i++;
                }
                else
                {
                    printf("Error, la cantidad supera el stock disponible\n");
                }
            }
            else
            {
                printf("No se encontro el producto\n");
            }
            printf("Desea comprar mas productos? s/n\n");
            fflush(stdin);
            scanf("%c",&control);
        }
    }
    else
    {
        printf("Error, no pudo abrirse el archivo\n");
    }
    fclose(archivo);
    return i;
}

/// ///////////////////////////////////////MOSTRAR ARREGLO COMPRAS POR ID DE CLIENTE
void mostrarArregloCompras (stCompra arregloCompra[], int val)
{
    int i=0;

    printf("ID del Cliente: %d\n",arregloCompra[i].idCliente);
    printf("Carrito de compras:\n");
    while (i<val)
    {
        printf("ID del producto: %d\n",arregloCompra[i].idProducto);
        printf("Unidades compradas: %d\n",arregloCompra[i].cantidad);
        printf("Total a pagar: $%.2f\n",arregloCompra[i].total);
        printf("=============================\n\n");
        i++;
    }
}

/// ////////////////////////////////////////////////////SUGERENCIAS Y/O QUEJAS
void archivoSugerenciasYquejas (int idLogeado, char rutaSugerencias[], char rutaClientes[])
{
    stSugerencias S;
    stCliente C;
    int flag=0;

    FILE *archivo=fopen(rutaSugerencias,"ab");
    FILE *archivoCliente=fopen(rutaClientes,"rb");

    if (archivo!=NULL && archivoCliente!=NULL)
    {
        while(fread(&C,sizeof(stCliente),1,archivoCliente)>0 && flag==0)
        {
            if (C.idCliente==idLogeado)
            {
                flag=1;
                printf("Ingrese su sugerencia y/o queja\n");
                fflush(stdin);
                gets(S.desarrollo);
                S.idCliente=C.idCliente;
                strcpy(S.nombre,C.nombre);
                strcpy(S.apellido,C.apellido);
                strcpy(S.userName,C.userName);
                fwrite(&S,sizeof(stSugerencias),1,archivo);
            }
            else
            {
                flag=0;
            }
        }
        if (flag==0)
        {
            printf("Hubo un error, el ID introducido no existe\n");
        }
    }
    else
    {
        printf("Hubo un error, el archivo no pudo abrirse\n");
    }
    fclose(archivo);
    fclose(archivoCliente);
}

/// ////////////////////////////////////////////////////// MOSTRAR ARCHIVO SUGERENCIAS Y/O QUEJAS
void mostrarArchivoSugerenciasQuejas(char rutaSugerencias[])
{
    stSugerencias S;

    FILE*archivo=fopen(rutaSugerencias,"rb");

    if (archivo!=NULL)
    {
        printf("Las sugerencias y/o quejas disponibles son:\n");
        while(fread(&S,sizeof(stSugerencias),1,archivo)>0)
        {
            printf("%s\n\n",S.desarrollo);
            printf("Datos del cliente que escribio:\n");
            printf("ID: %d\n",S.idCliente);
            printf("Nombre: %s\n",S.nombre);
            printf("Apellido: %s\n",S.apellido);
            printf("Usuario: %s\n",S.userName);
            printf("=========================================\n");
        }
    }
    else
    {
        printf("Error, no pudo abrirse el archivo\n");
    }
    fclose(archivo);
}

/// ////////////////////////////////////////////////////// MENU CLIENTE

void menuClienteLogeado(char ruta [], char rutaMisClases[], char rutaTodasClases[], int idLogeado)
{
    char rutaRutinas[]= {"MisRutinas.dat"};
    char rutaProductos[]= {"Productos.dat"};
    char rutaSugerencias[]= {"SugerenciasQuejas.dat"};

    stCliente cliente;
    stClases cla;
    stClases Miclase;
    stCompra arregloCompras[20];

    int validos;
    int opcion=0;
    int flag =0;
    int claseFlag=0;
    int claseRepe;
    int claseExist;
    int rutinaFlag=0;

    char control='s';
    char control2='s';

    cargaArchivoDeRutinas(rutaRutinas);
    cargaArchivoProductos(rutaProductos);

    FILE * archivo =fopen(ruta, "rb");
    FILE *archivoClases=fopen(rutaTodasClases,"rb");
    FILE *archivoPersonal=fopen(rutaMisClases,"wb");

    if(archivo!=NULL && archivoPersonal!=NULL && archivoClases!=NULL)
    {
        while (fread(&cliente,sizeof(stCliente),1,archivo)>0 && flag ==0)
        {
            if(idLogeado == cliente.idCliente)
            {
                flag =1;
                do
                {
                    printf("\n\n\tElegi una opcion y escribi el numero: \n");
                    printf("\n\n\t1- Acceder a mi perfil ------------------------- \n");
                    printf("\n\n\t2- Ver clases disponibles ---------------------- \n");
                    printf("\n\n\t3- Mis clases ---------------------------------- \n");
                    printf("\n\n\t4- Mis rutinas --------------------------------- \n");
                    printf("\n\n\t5- Ver Tienda ---------------------------------- \n");
                    printf("\n\n\t6- Sugerencias y/o quejas ---------------------- \n");
                    printf("\n\n\t0- Cerrar sesion-------------------------------- \n");
                    printf("\n\n\t--------------------------------------------->  ");
                    scanf("%d", &opcion);
                    system("cls");


                    switch (opcion)
                    {
                    case 1:

                        printf("Mis datos");
                        muestraUnCliente(cliente);
                        break;

                    case 2:
                        mostrarArchivoClases(rutaTodasClases);
                        printf("Quiere inscribirse en alguna clase? s/n\n");
                        fflush(stdin);
                        scanf("%c",&control2);
                        while (control2=='s')
                        {
                            claseExist=0;
                            claseFlag=0;
                            claseRepe=0;
                            printf("Ingrese el nombre de la clase que quiere anotarse:\n");
                            fflush(stdin);
                            gets(Miclase.clase);
                            claseExist=ValidacionClaseExistente(rutaTodasClases,Miclase.clase);
                            if (claseExist==1)
                            {
                                claseRepe=ValidacionClaseRepetida(rutaMisClases,Miclase.clase);
                                if (claseRepe==1)
                                {
                                    printf("\nYa se encuentra inscripto en esa clase\n");
                                }
                                else
                                {
                                    claseRepe=0;
                                    fseek(archivoClases,0,SEEK_SET);
                                    while (fread(&cla,sizeof(stClases),1,archivoClases)>0 && claseFlag==0)
                                    {
                                        if (strcmpi(Miclase.clase,cla.clase)==0)
                                        {
                                            claseFlag=1;
                                            Miclase=cla;
                                            if (strcmp(cliente.cuota,"cuota vencida")!=0)
                                            {
                                                fwrite(&Miclase,sizeof(stClases),1,archivoPersonal);
                                                printf("Se ha inscripto satisfactoriamente a la clase: %s\n",Miclase.clase);
                                            }
                                            else
                                            {
                                                printf("Tiene la cuota vencida, no puede inscribirse a ninguna clase\n");
                                            }

                                        }
                                        else
                                        {
                                            claseFlag=0;
                                        }
                                    }
                                    if (claseFlag==0)
                                    {
                                        printf("Hubo un error en la inscripcion\n");
                                    }

                                }
                            }
                            else
                            {
                                claseExist=0;
                                printf("El nombre de la clase ingresada no existe\n");
                            }

                            printf("Desea inscribirse en otra clase? s/n\n");
                            scanf("%c",&control2);
                        }
                        fclose(archivo);
                        fclose(archivoClases);
                        fclose(archivoPersonal);
                        break;

                    case 3:
                        printf("Mis clases\n");
                        mostrarArchivoClases(rutaMisClases);
                        break;

                    case 4:
                        rutinaFlag=ValidacionInscriptoMusculacion(rutaMisClases);
                        if (rutinaFlag==1)
                        {
                            printf("Mi rutina\n");
                            mostrarArchivoRutinas(rutaRutinas);
                        }
                        else
                        {
                            rutinaFlag=0;
                            printf("No se encuentra inscripto en musculacion, no tiene acceso a ninguna rutina\n");
                        }
                        break;

                    case 5:
                        printf("Los productos disponibles en la tienda son:\n");
                        mostrarArchivoProductos(rutaProductos);
                        validos=compraProductoArreglo(rutaProductos,arregloCompras,idLogeado,20);
                        mostrarArregloCompras(arregloCompras,validos);
                        break;

                    case 6:
                        archivoSugerenciasYquejas(idLogeado,rutaSugerencias,ruta);
                        printf("Gracias por su comentario, atenderemos a la brevedad su queja\n");
                        break;

                    case 0:
                        exit(0);

                    default:
                        printf("La opcion ingresada es incorrecta\n");
                    }
                    printf("\n\n\t Deseas volver atras? s/n  ---->  ");
                    fflush(stdin);
                    scanf("%c", &control);
                    system("cls");

                }
                while(control=='s');
            }
            else
            {
                flag = 0;
            }
        }
    }
    fclose(archivo);
    fclose(archivoClases);
    fclose(archivoPersonal);
}

/// ////////////////////////////////////MUESTRA UN CLIENTE A PARTIR DEL ID
void muestraUnClienteApartirId (int idLogeado, char rutaClientes[])
{
    FILE*archivo=fopen(rutaClientes,"rb");
    stCliente C;
    int flag=0;

    if (archivo!=NULL)
    {
        while(fread(&C,sizeof(stCliente),1,archivo)>0 && flag==0)
        {
            if (idLogeado==C.idCliente)
            {
                flag=1;
                muestraUnCliente(C);
            }
            else
            {
                flag=0;
            }
        }
        if (flag==0)
        {
            printf("El ID ingresado no existe\n");
        }
    }
    else
    {
        printf("Error, el archivo no pudo abrirse\n");
    }
    fclose(archivo);
}

/// ////////////////////////////////////////////////////// MENU ADMINISTRADOR
void menuAdministrador (char rutaClientes [], char rutaTodasClases[])
{
    char rutaProductos[]= {"Productos.dat"};
    char rutaSugerencias[]= {"SugerenciasQuejas.dat"};

    char control='s';
    int opcion;
    int id;

    cargaArchivoProductos(rutaProductos);

    do
    {
        printf("\n\n\tElegi una opcion y escribi el numero: \n");
        printf("\n\n\t1- Acceder al perfil de un cliente -------------- \n");
        printf("\n\n\t2- Ver clases disponibles ----------------------- \n");
        printf("\n\n\t3- Ver Tienda ----------------------------------- \n");
        printf("\n\n\t4- Sugerencias y/o quejas ----------------------- \n");
        printf("\n\n\t0- Cerrar sesion--------------------------------- \n");
        printf("\n\n\t--------------------------------------------->  ");
        scanf("%d", &opcion);
        system("cls");

        switch (opcion)
        {
        case 1:
            printf("Ingrese el ID del cliente\n");
            scanf("%d",&id);
            muestraUnClienteApartirId(id,rutaClientes);
            break;

        case 2:
            mostrarArchivoClases(rutaTodasClases);
            break;

        case 3:
            mostrarArchivoProductos(rutaProductos);
            break;

        case 4:
            mostrarArchivoSugerenciasQuejas(rutaSugerencias);
            break;

        case 0:
            exit(0);

        default:
            printf("La opcion ingresada es incorrecta\n");
        }
        printf("\n\n\t Deseas volver atras? s/n  ---->  ");
        fflush(stdin);
        scanf("%c", &control);
        system("cls");
    }
    while (control=='s');

}
