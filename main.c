#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
//Loteria version 7.5

void pedirDatos();
int *generador_baraja(int *barajaa, int n);
int *generador_tableros(int *arr_);
int *impresora_tableros(int *arr_);
int *juego_automatico(int *arr_, int elemento_baraja);
int *juego_usuario(int *arr_, int elemento_baraja);
int suma_elementos(int *arr_);
int check0=0;

FILE *ap=NULL;
int cont=0, com;
char c[20];
struct jugador
{
    char nombre[20];
    int victorias, derrotas;
    int planilla[3][3];
}usuario;

int main()
{
    int check=0, check2=0, check3=0, check4=0;
    int n_b=54, *baraja, *arr_1, *arr_2, *arr_3, opc=0, elemento_barajaa=0;
    int suma1=0, suma2=0, suma3=0,suma4=0;
    FILE *ap=NULL;
    
    baraja=(int*)malloc(n_b*sizeof(int*));
    
    arr_1=(int*)malloc(9*sizeof(int*));
    arr_2=(int*)malloc(9*sizeof(int*));
    arr_3=(int*)malloc(9*sizeof(int*));
    
    baraja=generador_baraja(baraja,n_b);
    
    
    char op;
    
    printf("%cBienvenido al juego de LOOOTER%cA!", 173, 214);
    
    if(ap=fopen("Usuarios.txt", "a+")!=NULL)
        ap=fopen("Usuarios.txt","a+");
    
    do
    {
        printf("\n\n%cQuieres jugar? (S/N) ", 168);
        scanf("%s", &op);
        if(op=='N' || op=='n')
        {
            printf("\n\nGracias por su preferencia. \n\n");
            system("PAUSE");
            exit(0);
        }
    }while (op!='s' && op!='S');
    
    arr_1=generador_tableros(arr_1);
    arr_2=generador_tableros(arr_2);
    arr_3=generador_tableros(arr_3);
    
    pedirDatos();
    do
    {
        printf("\n Tablero 1\n");
        impresora_tableros(arr_1);
        printf("\n Tablero 2\n");
        impresora_tableros(arr_2);
        printf("\n Tablero 3\n");
        impresora_tableros(arr_3);
        printf("\n ");
        scanf("%d", &opc);
    } while (opc!=1&&opc!=2&&opc!=3);
    //AQUI INICIAN LAS ITERACIONES DEL JUEGO
    elemento_barajaa=0;
    do
    {
        switch (opc)
        {
            case 1:
            {
                arr_2=juego_automatico(arr_2,baraja[elemento_barajaa]);
                arr_3=juego_automatico(arr_3,baraja[elemento_barajaa]);
                arr_1=juego_usuario(arr_1,baraja[elemento_barajaa]);
                suma2=suma_elementos(arr_2);
                suma3=suma_elementos(arr_3);
                suma1=suma_elementos(arr_1);
            } break;
            case 2:
            {
                arr_1=juego_automatico(arr_1,baraja[elemento_barajaa]);
                arr_3=juego_automatico(arr_3,baraja[elemento_barajaa]);
                arr_2=juego_usuario(arr_2,baraja[elemento_barajaa]);
                suma1=suma_elementos(arr_2);
                suma3=suma_elementos(arr_3);
                
                suma4=suma_elementos(arr_1);
            } break;
            case 3:
            {
                arr_2=juego_automatico(arr_2,baraja[elemento_barajaa]);
                arr_1=juego_automatico(arr_1,baraja[elemento_barajaa]);
                arr_3=juego_usuario(arr_3,baraja[elemento_barajaa]);
                suma2=suma_elementos(arr_2);
                suma1=suma_elementos(arr_3);
                
                suma4=suma_elementos(arr_1);
            } break;
        }
        
        
        if (suma1==900)
        { //Cuando la suma de los elementos de la matriz sea 900 check será igual a 1
            check=1;
            check0=1;
        }
        if (suma2==900)
        { //Cuando la suma de los elementos de la matriz sea 900 check será igual a 1
            check2=1;
            check0=1;
        }
        if (suma3==900)
        { //Cuando la suma de los elementos de la matriz sea 900 check será igual a 1
            check3=1;
            check0=1;
        }
        if (suma4==900)
        { //Cuando la suma de los elementos de la matriz sea 900 check será igual a 1
            check4=1;
            check0=1;
        }
        
        
        printf("\n Tablero 1\n");
        impresora_tableros(arr_1);
        printf("\n Tablero 2\n");
        impresora_tableros(arr_2);
        printf("\n Tablero 3\n");
        impresora_tableros(arr_3);
        printf("\n ");
        elemento_barajaa++;
    }while(check0!=1);
				
    if (check==1) {printf("\nYOU WIN!");}
    if (check2==1) {printf("\nGano tablero 2!");}
    if (check3==1) {printf("\nGano tablero 3!");}
    if (check4==1) {printf("\nGano tablero 1!");}
    //AQUI TERMINAN LAS ITERACIONES DEL JUEGO
    getch();
    return 0;
}

void pedirDatos()
{
    
    
    
    printf("\n Ingrese su nombre de usuario: ");
    fflush(stdin);
    gets(usuario.nombre);
    ap=fopen("Usuarios.txt", "a+");
    
    if(ap==NULL)
    {
        printf("\nError, al acceder a la Base de Datos compruebe que el archivo est%c cerrado.", 130);
        getchar();
        exit(0);
    }
    
    else
        
        
        while(feof(ap)==NULL)
        {
            
            fscanf(ap,"%s", c);
            com=strcmp(usuario.nombre,c);
            
            if(com==0)
            {
                fprintf(ap, "\t0\t0\t0");
                cont++;
            }
        }
    
    
    
    if(cont==0)
    {
        printf("\nEl usuario ''%s'' no se encontr%c, pero se ha agregado a la Base de Datos.\n", usuario.nombre, 162);
        fprintf(ap, "\n");
        fprintf(ap, " %s ", usuario.nombre);
        fprintf(ap,"\t0\t0\t0");
    }
    printf("\n Bienvenido, %s, elige una de estas planillas:", usuario.nombre);
    printf("\n\n");
}

int *generador_baraja(int *barajaa, int n)
{
    int i, r, temp=0;
    srand(time(NULL));
    for(i=0;i<n;i++)
    {
        barajaa[i]=i;
    }
    
    for(i=0; i < n ; i++)
    {
        temp=barajaa[i];
        r=rand()%54;
        barajaa[i]=barajaa[r];
        barajaa[r]=temp;
    }
    
    return barajaa;
}

int *generador_tableros(int *arr_)
{
    int i, j, r;
    
    //srand48(time(NULL));
    
    for(i=0; i < 9 ; i++)
    {
        r=rand()%54;
        arr_[i]=(r/2 + 27);
    }
    
    for (i=0;i<9;i++)
    {
        for(j=1;j<(9-i);j++)
        {
            if (arr_[i]==arr_[i+j])
            {
                arr_[i+j]=rand()%27;
            }
        }
    }
    return arr_;
    free(arr_);
}
int *impresora_tableros(int *arr_)
{
    int	**tablero_, i, j, n=0;
    tablero_=(int**)malloc(3*sizeof(int*)); //Reservando memoria para la primera dimension (filas) de tipo entero
    for(i=0;i<3;i++)                         //Se reserva memoria para la segunda dimension(columnas)
        tablero_[i]=(int*)malloc(3*sizeof(int)); //Apartir de aqui tablero_ puede usarse como arreglo
    
    
    for(i=0; i<3 ; i++)
    {
        for(j=0; j<3 ;j++)
        {
            tablero_[i][j]=arr_[n];
            n++;
        }
    }
    
    for(i=0;i<3;i++)
    {	printf("\n");
        for(j=0;j<3;j++)
        {
            switch (tablero_[i][j])
            {
                case 0: printf("\t La Rana");
                    break;
                case 1: printf("\t El Gallo");
                    break;
                case 2: printf("\t El Diablito");
                    break;
                case 3: printf("\t La Dama");
                    break;
                case 4: printf("\t El Catr%cn", 161);
                    break;
                case 5: printf("\t El Paraguas");
                    break;
                case 6: printf("\t La Sirena");
                    break;
                case 7: printf("\t La Escalera");
                    break;
                case 8: printf("\t La Botella");
                    break;
                case 9: printf("\t El Barril");
                    break;
                case 10: printf("\t El %crbol", 181);
                    break;
                case 11: printf("\t El Mel%cn", 162);
                    break;
                case 12: printf("\t El Valiente");
                    break;
                case 13: printf("\t El Gorrito");
                    break;
                case 14: printf("\t La Muerte");
                    break;
                case 15: printf("\t La Pera");
                    break;
                case 16: printf("\t La Bandera");
                    break;
                case 17: printf("\t El Bandol%cn", 162);
                    break;
                case 18: printf("\t El Violoncello");
                    break;
                case 19: printf("\t La Garza");
                    break;
                case 20: printf("\t El P%cjaro", 160);
                    break;
                case 21: printf("\t La Mano");
                    break;
                case 22: printf("\t La Bota");
                    break;
                case 23: printf("\t La Luna");
                    break;
                case 24: printf("\t El Cotorro");
                    break;
                case 25: printf("\t El Borracho");
                    break;
                case 26: printf("\t El Negrito");
                    break;
                case 27: printf("\t El Coraz%cn", 162);
                    break;
                case 28: printf("\t La Sand%ca", 161);
                    break;
                case 29: printf("\t El Tambor");
                    break;
                case 30: printf("\t El Camar%cn", 162);
                    break;
                case 31: printf("\t Las Jaras");
                    break;
                case 32: printf("\t El M%csico", 163);
                    break;
                case 33: printf("\t La Ara%ca", 164);
                    break;
                case 34: printf("\t El Soldado");
                    break;
                case 35: printf("\t La Estrella");
                    break;
                case 36: printf("\t El Cazo");
                    break;
                case 37: printf("\t El Mundo");
                    break;
                case 38: printf("\t El Apache");
                    break;
                case 39: printf("\t El Nopal");
                    break;
                case 40: printf("\t El Alacr%cn", 160);
                    break;
                case 41: printf("\t La Rosa");
                    break;
                case 42: printf("\t La Calavera");
                    break;
                case 43: printf("\t La Campana");
                    break;
                case 44: printf("\t El Cantarito");
                    break;
                case 45: printf("\t El Venado");
                    break;
                case 46: printf("\t El Sol");
                    break;
                case 47: printf("\t La Corona");
                    break;
                case 48: printf("\t La Chalupa");
                    break;
                case 49: printf("\t El Pino");
                    break;
                case 50: printf("\t El Pescado");
                    break;
                case 51: printf("\t La Palma");
                    break;
                case 52: printf("\t La Maceta");
                    break;
                case 53: printf("\t El Arpa");
                    break;
                case 100: printf("\t Listo\t");
                    break;
                    
            }
        }
    }
    for(i=0;i<3;i++)
        free(tablero_[i]);
    free(tablero_);
    return 0;
}
int *juego_automatico(int *arr_, int elemento_baraja)
{
    
    int  z;
    for (z=0;z<9;z++)
    {
        if (elemento_baraja==arr_[z])
        { //Si la carta que salio esta en tu tablero lo marca como Listo
            arr_[z]=100;
            
        }
        
    }
    
    return  arr_;
    free (arr_);
}
int *juego_usuario(int *arr_, int elemento_baraja)
{
    int z;
    char respuesta;
    
    fflush(stdin);
    //printf("\n\t El numero %d", elemento_baraja);
    //
    printf("\n");
    switch ( elemento_baraja)
    {
        case 0: printf("\t La Rana");
            break;
        case 1: printf("\t El Gallo");
            break;
        case 2: printf("\t El Diablito");
            break;
        case 3: printf("\t La Dama");
            break;
        case 4: printf("\t El Catr%cn", 161);
            break;
        case 5: printf("\t El Paraguas");
            break;
        case 6: printf("\t La Sirena");
            break;
        case 7: printf("\t La Escalera");
            break;
        case 8: printf("\t La Botella");
            break;
        case 9: printf("\t El Barril");
            break;
        case 10: printf("\t El %crbol", 181);
            break;
        case 11: printf("\t El Mel%cn", 162);
            break;
        case 12: printf("\t El Valiente");
            break;
        case 13: printf("\t El Gorrito");
            break;
        case 14: printf("\t La Muerte");
            break;
        case 15: printf("\t La Pera");
            break;
        case 16: printf("\t La Bandera");
            break;
        case 17: printf("\t El Bandol%cn", 162);
            break;
        case 18: printf("\t El Violoncello");
            break;
        case 19: printf("\t La Garza");
            break;
        case 20: printf("\t El P%cjaro", 160);
            break;
        case 21: printf("\t La Mano");
            break;
        case 22: printf("\t La Bota");
            break;
        case 23: printf("\t La Luna");
            break;
        case 24: printf("\t El Cotorro");
            break;
        case 25: printf("\t El Borracho");
            break;
        case 26: printf("\t El Negrito");
            break;
        case 27: printf("\t El Coraz%cn", 162);
            break;
        case 28: printf("\t La Sand%ca", 161);
            break;
        case 29: printf("\t El Tambor");
            break;
        case 30: printf("\t El Camar%cn", 162);
            break;
        case 31: printf("\t Las Jaras");
            break;
        case 32: printf("\t El M%csico", 163);
            break;
        case 33: printf("\t La Ara%ca", 164);
            break;
        case 34: printf("\t El Soldado");
            break;
        case 35: printf("\t La Estrella");
            break;
        case 36: printf("\t El Cazo");
            break;
        case 37: printf("\t El Mundo");
            break;
        case 38: printf("\t El Apache");
            break;
        case 39: printf("\t El Nopal");
            break;
        case 40: printf("\t El Alacr%cn", 160);
            break;
        case 41: printf("\t La Rosa");
            break;
        case 42: printf("\t La Calavera");
            break;
        case 43: printf("\t La Campana");
            break;
        case 44: printf("\t El Cantarito");
            break;
        case 45: printf("\t El Venado");
            break;
        case 46: printf("\t El Sol");
            break;
        case 47: printf("\t La Corona");
            break;
        case 48: printf("\t La Chalupa");
            break;
        case 49: printf("\t El Pino");
            break;
        case 50: printf("\t El Pescado");
            break;
        case 51: printf("\t La Palma");
            break;
        case 52: printf("\t La Maceta");
            break;
        case 53: printf("\t El Arpa");
            break;
            
        case 100: printf("\t Listo");
            break;
    }
    //
    printf("\n\t%cLo tienes? ", 168);
    scanf(" %c", &respuesta);
    fflush(stdin);
    if (respuesta=='s' || respuesta=='S') 
    {
        for (z=0;z<9;z++)
        {
            if (elemento_baraja==arr_[z]) 
            { //Si la carta que salio esta en tu tablero lo marca como Listo
                arr_[z]=100;
            }
        }
    }
    else
    {
        for (z=0;z<9;z++)
        {
            if (elemento_baraja==arr_[z]) 
            { //Si la carta que salio esta en tu tablero lo marca como
                printf("\n\t PERDISTE");
                check0=1;
            }
        }
			 }
    
    return arr_;
}

int suma_elementos(int *arr_)
{
    int z, suma=0;
    for (z=0;z<9;z++)
				{
                    suma=arr_[z]+suma; //Suma los elementos de la matriz
                }
				return suma;
}
