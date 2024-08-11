#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

HANDLE semaforo; //Ser� un tipo de tipo handle
int recurso_compartido = 0;

DWORD WINAPI incrementarRecurso(LPVOID arg);
DWORD WINAPI decrementarRecurso(LPVOID arg);

int main(){
	
	HANDLE hThread1, hThread2;   //Declaraci�n de los hilos (Tipo de datos especifico de windows). Este tipo de dato se puede usar para hilos o semaforos
	DWORD dwThread1, dwThread2;  //(Tipo de datos especifico de windows). Tipo de dato double word. Este tipo de dato se puede usar para hilos o semaforos
	srand(time(NULL)); //Inicializar el tiempo del sleep
	
	//---------- A continuaci�n se crean ambos hilos ----------------
	hThread1 = CreateThread(NULL, 0, incrementarRecurso, NULL, 0, &dwThread1);
	hThread2 = CreateThread(NULL, 0, decrementarRecurso, NULL, 0, &dwThread2);
	
	//---------- Esperar a que terminen ambos hilos -----------------
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	
	//---------- Se debe cerrar ambos hilos y el semaforo como haciamos con los archivos ----------
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(semaforo);
	
	printf("Recurso compartido: %d", recurso_compartido);
	
	return 0;
}

DWORD WINAPI incrementarRecurso(LPVOID arg){	
	int i;
	
	for(i=0; i<10; i++){
		Sleep(rand() % 2000); //Esperar de 0 a 2000 ms
		recurso_compartido++;
	}
	return 0;
}


DWORD WINAPI decrementarRecurso(LPVOID arg){
	int i;
	
	for(i=0; i<10; i++){
		Sleep(rand() % 2000); //Esperar de 0 a 2000 ms
		recurso_compartido--;
	}
	return 0;
}
