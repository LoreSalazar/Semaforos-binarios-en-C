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
	
	//---------- Creaci�n del semaforo -----------------------------
	semaforo = CreateSemaphore(NULL, 1, 1, NULL); //El primer parametro indica un termino de seguridad, el segundo que el sem�foro est� libre, el tercero el numero maximo que puede tomar, y el cuarto un nombre opcional que se le puede dar
	
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
	WaitForSingleObject(semaforo, INFINITE); //Obtenemos el sem�foro	
	int i;
	
	for(i=0; i<10; i++){
		//WaitForSingleObject(semaforo, INFINITE); //Obtenemos el sem�foro
		//Sleep(rand() % 10000); //Esperar de 0 a 2000 ms
		recurso_compartido++;
		printf("%d\n", recurso_compartido);
		//ReleaseSemaphore(semaforo, 1, NULL); //Funci�n para liberar el sem�foro. Primer parametro es el nombre del semaforo, segundo es el valor que queremos que tenga cuando se libere, tercer parametro es un puntero opcional por eso mejor poner NULL
	}
	
	ReleaseSemaphore(semaforo, 1, NULL);
	return 0;
}


DWORD WINAPI decrementarRecurso(LPVOID arg){
	WaitForSingleObject(semaforo, INFINITE); //Obtenemos el sem�foro
	int i;
	
	for(i=0; i<10; i++){
		//WaitForSingleObject(semaforo, INFINITE); //Obtenemos el sem�foro
		//Sleep(rand() % 1000); //Esperar de 0 a 2000 ms
		recurso_compartido--;
		printf("%d\n", recurso_compartido);
		//ReleaseSemaphore(semaforo, 1, NULL);
	}
	
	ReleaseSemaphore(semaforo, 1, NULL);
	return 0;
}

/*---------------------------- NOTAS -------------------------------

Existe un solo hilo porque solo tenemos un recurso compartido. Por lo que entiendo, los semafors funcionan de la siguiente manera:

Se comienaz a ejecutar la primer funci�n, el semaforo act�a como un guardia que no deja pasar al otro sem�foro por ninguna raz�n, hasta 
que este sea liberado, ahora pasa con la segunda funci�n y ocurre lo mismo.

-----------------------------------------------------------------*/
