@echo off

:: Compilo código objeto
:: Enlazo cabecera con el cpp y genero los objetos
g++ -Wall -std=c++17 -I.\include -c .\src\Ticket.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\Client.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\Incidente.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\ColaCliente.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\SupportTechnical.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\ListaTickets.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\Whatsapp.cpp
g++ -Wall -std=c++17 -I.\include -c .\src\Facebook.cpp


g++ -Wall -std=c++17 -I.\include -c main.cpp 

:: Compilo el Binario y genero el exe
g++ -I.\include Ticket.o Client.o Incidente.o ColaCliente.o ListaTickets.o Whatsapp.o Facebook.o SupportTechnical.o main.o -o miPrograma.exe

:: Limpio los códigos objeto
DEL .\*.o

:: Ejecuto
miPrograma.exe
