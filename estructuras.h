//Estructuras usadas en todos lo módulos de la aplicación

typedef struct{
	char Usuario[10];
	char Contrasenia[40];
	char ApeNom[60];
	int baja;
}Usuarios;

typedef struct{
	int IdProfesional;
	char ApeNom[60];
	char DNI[8];
	char Telefono[25];
	int baja;
}Profesionales;

typedef struct{
	int dia;
	int mes;
	int anio;
}Fecha;

typedef struct{
	char ApeNom[60];
	char DNI[8];
	char Localidad[60];
	Fecha FechaDeNac;
	char Telefono[10];
	char DetalleAtencion[380];
	int baja;
}Pacientes;

typedef struct{
	int IdProfesional;
	char ApeNom[60];
	Fecha FechaAtencion;
	char DNI[8];
	char DetalleAtencion[380];
	int baja;
}Turnos;
