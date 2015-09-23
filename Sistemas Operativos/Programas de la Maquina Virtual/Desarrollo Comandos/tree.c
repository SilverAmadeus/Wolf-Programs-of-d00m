/**
$ tree [opciones] nombre_directorio
[opciones]:
-f mostrar los ficheros que hay dentro de un directorio a�adiendo:
	(d) directorio
	(o) fichero ordinario
	(b)	fichero especial modo bloque
	(c)	fichero especial modo car�cter
	(p) tuber�a con nombre
	(x) fichero ejecutable
Retorno: 0 si se ejecuta correctamente, -1 si se produce alg�n error.
**/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#define EQ(str1, str2) (strcmp ((str1), (str2)) == 0)

struct opciones
{
	unsigned mostrar_ficheros:1;
};

enum boolean {NO, SI};

/***
	main: se encarga de analizar los argumentos de la l�nea de �rdenes y de invocar
	a la funci�n tree.
***/

main (int argc, char *argv [])
{
	struct opciones opciones = {NO};
	int i, j;

/* An�lisis de los argumentos de la l�nea de �rdenes. */
if (argc < 2) {
	fprintf (stderr, "Forma de uso: %s [-f] directorio\n", argv [0]);
}
for (i = 1; i < argc; i++)
	if (argv[i] [0] == '-')
		for (j = 1; argv [i] [j] != '\0'; j++)
		switch (argv [i] [j]) {
		case 'f':
			opciones.mostrar_ficheros = SI;
			break;
	default:
		fprintf (stderr, "Opci�n [-%c] desconocida\n",
				argv [i] [j]);
	}

/* An�lisis de la estructura en �rbol de directorios para cada uno de los
argumentos que aparecen en la l�nea de �rdenes y que no son opciones de tree. */
for (i = 1; i < argc; i++)
	if (argv [i] [0] != '-')
		tree (argv [i], opciones);
}

/***
tree: recibe la ruta de un directorio y se encarga de analizarla. Si en el directorio
hay subdirectorios, la funci�n se llama de forma recursiva para analizar ese
subdirectorio. Seg�n las opciones que est�n activas, la funci�n desplegar� por
pantalla un tipo de informaci�n u otro.
***/

tree (char *path, struct opciones opciones)
{
	DIR *dirp;
	struct dirent *dp;
	static nivel = 0;
	struct stat buf;
	int ok, i;
	char fichero [256], tipo_fichero;

/* Apertura del directorio. */
if ((dirp = opendir (path)) == NULL) {
	perror (path);
	return;
}

/* Leemos, una por una, las entradas del directorio. */
while ((dp = readdir (dirp)) != NULL) {
	/* Saltamos las entradas referidas al directorio actual (.) y al
	directorio padre (..) */
	if (EQ (dp->d_name, ".") || EQ (dp->d_name, ".."))
		continue;
	/* Formamos la ruta correpondiente al fichero de la entrada de directorio que
	estamos procesando. */
	sprintf (fichero, "%s/%s", path, dp->d_name);
	/* Lectura del nodo�i del fichero. */
	ok = stat (fichero, &buf);
	/* Si el fichero es un subdirectorio, llamamos nuevamente a tree. */
	if (ok != -1 && (buf.st_mode & S_IFMT) == S_IFDIR) {
		for (i = 0; i < nivel; i++)
			printf ("\t");
		printf ("%s %s\n", dp->d_name,
			opciones.mostrar_ficheros ? "(d)": "");
		++nivel;
		tree (fichero, opciones);
		--nivel;
}
/* Si el fichero no es un directorio y est� activa la opci�n mostrar_ficheros
(-f), presentamos por pantalla el nombre del fichero y su tipo. */
else if (ok != -1 && opciones.mostrar_ficheros == SI) {
	for (i = 0; i <= nivel; i++)
		printf ("\t");
switch (buf.st_mode & S_IFMT) {
case S_IFREG:
	if (buf.st_mode & 0111)
		tipo_fichero = 'x';
	else
		tipo_fichero = 'o';
	break;
case S_IFCHR:
	tipo_fichero = 'c';
	break;
case S_IFBLK:
	tipo_fichero = 'b';
	break;
default:
	tipo_fichero = '?';
}

		printf("(%c) %s\n", tipo_fichero, dp->d_name);
		}
	}
	closedir(dirp);
}
