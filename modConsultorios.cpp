#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

struct Medico
{    
     int log;
     int IdProfesional;
     int user;
     char contra [40];
};

int dibujarMenu();
bool autenticar();
void registrarHistoriaClinica(FILE *archTur);
void visualizarListaEspera(FILE *archTurn);

int main()
{
	FILE *archPac = fopen("pacientes.dat", "a+b");
	FILE *archPro = fopen("profesionales.dat", "rb");
	FILE *archTur = fopen("turnos.dat", "rb");

		bool sesion=false;
	
	bool inicio = false, borrar = false;
	int IdProfesional;
	
	int opc;
	do{
		opc = dibujarMenu();
		switch(opc){
			case 1:		system("CLS");
    			if(autenticar()){
    				sesion=true;
    				inicio=true;
    				printf("\n\n\n\n\n\nAutenticado \n");
    			}else{
    				printf("\nUsuario o contrasenia incorrecta \n");
    			}
    			system("PAUSE");
    			break;
			case 2: if(inicio == true)
						{
						  visualizarListaEspera(archTur);
					 	}
						 else printf("\nPrimerio debe Iniciar sesion!\n");
					 break;
		
			case 3:if(inicio == true)
						{
						  registrarHistoriaClinica(archPac);
					 	}
						 else printf("\nPrimerio debe Iniciar sesion!\n");
					 break;
					 }
		printf("\n");
		system("pause");
	}while(opc != 4);
	
	fclose(archPac);
	
	fclose(archPro);
	return(0);
}
int dibujarMenu(){
	system("TITLE ADMINISTRACION");
	system("COLOR 0E");
	system("cls");
	printf("\t\t\t\t Modulo Consultorios \n");
    printf("\t\t\t\t ========================= \n");
	printf("\n\t\t\t 1) Iniciar Sesion");
	printf("\n\t\t\t 2) Visualizar Listado de Espera de Turnos");
	printf("\n\t\t\t 3) Registrar Historia Clinica");
    printf("\n\t\t\t 4) Cerrar la aplicacion");
	printf("\n\n\t\t\t Ingrese la opcion deseada: ");
	int opc;
	scanf("%d", &opc);
	return opc;
}

bool autenticar(){
	Usuarios user;
	FILE *archUser = fopen("usuarios.dat", "rb");
	char usuario[10], contrasenia[40];
	bool coincidencia = false;
    if (archUser == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }else{
    	_flushall();
    	printf("Usuario: ");
    	gets(usuario);
    	_flushall();
    	printf("Contrasenia: ");
    	gets(contrasenia);
    	while (fread(&user, sizeof(user), 1, archUser) == 1) {
	        if(strcmp(usuario,user.Usuario)==0&&strcmp(contrasenia,user.Contrasenia)==0){
	        	coincidencia = true;
	        	break;
			}
    	}
    }
    fclose(archUser);
    return coincidencia;
}   

void visualizarListaEspera(FILE *archTur){
	Turnos tur;
	int pro;
	Fecha f;
	if (archTur == NULL) {
      printf("Error al abrir el archivo.\n");
  }
	printf("Ingrese ID del profesional: ");
	scanf("%d",&pro);
	printf("Ingrese Fecha de Atencion \n->Dia: ");
	scanf("%d",&f.dia);	
	printf("->Mes: ");
	scanf("%d",&f.mes);
	printf("->Anio: ");
	scanf("%d",&f.anio);
  while (fread(&tur, sizeof(tur), 1, archTur) == 1) {
  	if(tur.IdProfesional == pro 
	&& tur.FechaAtencion.anio == f.anio
	&& tur.FechaAtencion.mes == f.mes
	&& tur.FechaAtencion.dia == f.dia)
	{
	  	printf("\nProfesional: %d \n", tur.IdProfesional);
    	printf("Fecha: %d/%d/%d\n", tur.FechaAtencion.dia,tur.FechaAtencion.mes,tur.FechaAtencion.anio);
  		printf("Paciente: %s \n", tur.ApeNom);
	}
  }
}
                 
void registrarHistoriaClinica(FILE *archTur) {
	archTur = fopen("turnos.dat", "rb");
    system("cls");
    Turnos tur, tur1;
    // Solicita el DNI del paciente
    char DNI[8]; 
    printf("Ingrese el DNI del paciente: ");
    _flushall();
    gets(tur1.DNI); 
    _flushall();
    // Busca al paciente en el archivo
    
    
    while (fread(&tur, sizeof(tur), 1, archTur) == 1) {

        if (strcmp(tur1.DNI, tur.DNI) == 0) {
            // Muestra información del paciente
            printf("\n - Paciente encontrado:\n");
            printf("   Nombre: %s\n", tur.ApeNom);
            printf("   DNI: %s\n", tur.DNI);
            printf("\n - Ingrese la historia clinica:\n");
            fflush(stdin);
            fgets(tur.DetalleAtencion, sizeof(tur.DetalleAtencion), stdin);

            // Elimina el carácter de nueva línea de la cadena ingresada por fgets
            size_t len = strlen(tur.DetalleAtencion);
            if (len > 0 && tur.DetalleAtencion[len - 1] == '\n') {
                tur.DetalleAtencion[len - 1] = '\0';
            }

            // Vuelve a la posición correcta en el archivo antes de escribir
            fseek(archTur, -sizeof(Pacientes), SEEK_CUR);

            // Escf información actualizada en el archivo
            fwrite(&tur, sizeof(Pacientes), 1, archTur);

            printf("\n - Historia clinica registrada con exito.\n");
            return;
              fclose(archTur);
        }
    }

    // Si no se encontró el paciente
    printf("\n - Paciente no encontrado.\n");
      fclose(archTur);
}
