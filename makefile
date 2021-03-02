#Esta línea tiene como objetivo "euler.exe", ejecuta un comando de gcc para obtener el ejecutable

euler.exe: euler.o funcionesEuler.o

	gcc euler.o funcionesEuler.o -o euler.exe -lm

#Esta línea es para lograr el objetivo de "euler.o"

euler.o: euler.c

	gcc  -c euler.c

#Los demás objetivos

funcionesEuler.o: funcionesEuler.c

	gcc -c funcionesEuler.c
