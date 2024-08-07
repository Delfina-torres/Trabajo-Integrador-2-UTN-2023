#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "estructuras.h"

/*	
	Usuario: usuarIO 
	Contraseña: Usuario1
*/

Usuarios user;
Profesionales pro;
void registrarUsuarios(FILE *archRec);
bool verificarUsuario(char user[10]);
bool verificarContrasenia(char contrasenia[40]);
bool login();
void listarProfesionales(FILE *archPro);
void registrarProfesional(FILE *archPro);
void listarTurnos(FILE *archPro);
void ranking(FILE *archPro);
FILE *archUser, *archPro, *archTur;

main(){
	system("TITLE ADMINISTRACION");
	system("COLOR 0E");
	int op;
	archUser = fopen("usuarios.dat","ab");
	archPro = fopen("profesionales.dat","ab");
	if(login()){
		do{
			system("CLS");
	        printf("\t\t\t Modulo Administracion \n");
	        printf("\t\t\t========================= \n");
	        printf("\t\t\t 1) Registrar Profesional \n");
	        printf("\t\t\t 2) Registrar Usuario \n");
	        printf("\t\t\t 3) Atenciones por Profesional \n");
			printf("\t\t\t 4) Ranking de Profesionales por Atenciones \n");
			printf("\t\t\t 5) Listar profesionales \n");
			printf("\t\t\t 6) Cerrar la aplicacion \n");
	    	printf("\t\t\t Ingrese una opcion: ");		
			scanf("%d",&op);
			switch(op){
				case 1:
					system("CLS");
					archPro = fopen("profesionales.dat","ab");
					registrarProfesional(archPro);
					fclose(archPro);
					system("pause");
					break;
				case 2:
					system("CLS");
					archUser = fopen("usuarios.dat","ab");
					registrarUsuarios(archUser);
					fclose(archUser);
					system("pause");
					break;
				case 3:
					system("CLS");
					archTur = fopen("turnos.dat","rb");
					listarTurnos(archTur);
					fclose(archTur);
					system("pause");
					break;
					
				case 4:
					system("CLS");
					archTur = fopen("turnos.dat","rb");
					ranking(archTur);
					fclose(archTur);
					system("pause");
					break;
				case 5:
					listarProfesionales(archPro);
					fclose(archTur);
					system("pause");
					break;
				case 6:
					break;
				
				default:
					printf("Opcion incorrecta...");
			}
		}while(op!=5);
	}else{
		printf("Usuario o contrasenia incorrecto. ");
	}
}

bool login(){
	FILE *arch = fopen("usuarios.dat", "rb");
	char usuario[10], contrasenia[40];
	bool coincidencia = false;
    if (arch == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
    	printf("Usuario: ");
    	gets(usuario);
    	printf("Contrasenia: ");
    	gets(contrasenia);
    	while (fread(&user, sizeof(user), 1, arch) == 1) {
	        if(strcmp(usuario,user.Usuario)==0&&strcmp(contrasenia,user.Contrasenia)==0){
	        	coincidencia = true;
	        	printf("COINCIDE\n");
			}
    	}
    }
    return coincidencia;
    fclose(arch);
}

void registrarProfesional(FILE *archPro){
	Profesionales pro;
	pro.baja=0;
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(pro.ApeNom);
	_flushall();
	printf("ID Profesional: ");
	scanf("%d",&pro.IdProfesional);
	_flushall();
	printf("DNI: ");
	gets(pro.DNI);
	_flushall();
	printf("Tel: ");
	gets(pro.Telefono);
	_flushall();
	fwrite(&pro,sizeof(pro),1,archPro);
}

void registrarUsuarios(FILE *archUser){
	char u[10],contrasenia[40];
	_flushall();
	user.baja =0;
	do{
		printf("Ingrese usuario: ");
		gets(u);
	}while(verificarUsuario(u)==false);
	strcpy(user.Usuario,u);
	_flushall();
	do{
		printf("Ingrese Contrasenia: ");
		gets(contrasenia);
	}while(verificarContrasenia(contrasenia)==false);
	strcpy(user.Contrasenia,contrasenia);
	_flushall();
	printf("Ingrese Apellido y Nombre: ");
	gets(user.ApeNom);
	_flushall();
	fwrite(&user,sizeof(user),1,archUser);
}

bool verificarUsuario(char usuario[10]){
	FILE *arch = fopen("usuarios.dat", "rb");
	int may=0, digitos=0;
	bool verificado;
	if(strlen(usuario)>=6 && strlen(usuario)<=10){
		verificado = true;
    	for(int i=0;i<strlen(usuario);i++){
			if(usuario[i]>='A' && usuario[i]<='Z'){
				may++;
			}
			if(usuario[i]>='0' && usuario[i]<='9'){
				digitos++;
			}
		}
    	if(usuario[0]>='a'&&usuario[0]<='z'){
				verificado = true;
		}else{
			verificado = false;
			printf("Debe empezar con minusculas ");
		}
    	if(may<2){
				printf("Debe tener al menos dos Mayusculas.\n");
				verificado = false;
			}
		if(digitos>3){
			printf("No puede tener mas de 3 digitos ");
			verificado = false;
		}
		while(fread(&user, sizeof(user), 1, arch) == 1) {
	        if(strcmp(usuario,user.Usuario)==0){
	        	verificado = false;
	        	printf("Ya existe ese nombre de usuario \n");
			}
    	}
	}else{
		printf("Debe tener de 6 a 10 letras.\n");
		verificado = false;
	}
	return verificado;
}

bool verificarContrasenia(char contrasenia[40]){
	int min=0, may=0, num=0;
	char anterior;
	bool verificado = false;
	int longitud = strlen(contrasenia);
	if(longitud>=6 && longitud<=32){
			for(int i=0;i<longitud;i++){
				switch(contrasenia[i])
				{
					case 'a'...'z':
						min++;
						if(contrasenia[i] == anterior+1 || contrasenia[i] == anterior+33){
							verificado = false;
							printf("\nConsecutivos %c %c",anterior,contrasenia[i]);
						}
						break;
					case 'A'...'Z':
						may++;
						verificado = false;
						if(contrasenia[i] == anterior+1 || contrasenia[i] == anterior-31){
							printf("\nConsecutivos %c %c",anterior,contrasenia[i]);
						}
						break;
					case '0'...'9':
						num++;
						break;
					default:
						verificado = false;
						printf("\nNo se acepta. Debe ser alfanumerico. ");
				}
				anterior = contrasenia[i];
		}
		if(num>0 && min>0 && may>0){
			printf("\nContrasenia guardada.\n");
			verificado = true;
		}else{
			printf("\nNo se guardo \n");
			verificado = false;
		}
	}else{
		printf("Debe tener entre 6 y 32 caracteres\n");
		verificado = false;
	}
	return verificado;
}

void listarTurnos(FILE *archTur){
	Turnos tur;
	int pro;
	if (archTur == NULL) {
      printf("Error al abrir el archivo.\n");
  	}
	printf("Ingrese ID del profesional: ");
	scanf("%d",&pro);
	while (fread(&tur, sizeof(tur), 1, archTur) == 1){
		if(tur.IdProfesional == pro)
		{
		  	printf("\nProfesional: %d \n", tur.IdProfesional);
	    	printf("Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
	  		printf("Detalle: %s \n\n", tur.DetalleAtencion);
		}
	}
}

void ranking(FILE *archPro){
	Turnos tur;
	int v[100];
	int profesionales[100];
	if (archTur == NULL) {
      printf("Error al abrir el archivo.\n");
  	}
  	int i = 0, longitud = 0;
	while(fread(&tur, sizeof(tur), 1, archTur) == 1){	
		v[i]=tur.IdProfesional;
		i++;
		longitud++;
	}
	int maxCount = 0; // Contador máximo de apariciones
    int masFrecuente = 0; // Número más frecuente
    for (int i = 0; i < longitud; i++) {
        int count = 0; // Contador para el elemento actual
        for (int j = 0; j < longitud; j++) {
            if (v[i] == v[j]) {
                count++; // Incrementar el contador si encontramos el mismo elemento
            }
        }
        if (count > maxCount) {
            maxCount = count; // Actualizar el contador máximo y el número más frecuente
            masFrecuente = v[i];
        }
    }
    printf("El profesional que mas turnos tiene es: %d (tiene %d turnos)\n", masFrecuente, maxCount);
}

void listarProfesionales(FILE *archPro){
	Profesionales pro;
	archPro = fopen("profesionales.dat","rb");
	
	while(fread(&pro,sizeof(pro),1,archPro)==1){
		printf("%d - %s \n",pro.IdProfesional,pro.ApeNom);
	}
}
