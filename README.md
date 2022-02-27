# Inhalt
_(English versions in italics)_


Dieses Repository ist Bestandteil eines Universitätsmoduls zur Programmierung in C.

_This repository is part of a university assignment for programming
in C._
* [`Aufgabenstellung / Task`](#aufgabenstellung--task)
* [`Einrichtung des Projekts / Setup`](#einrichtung-des-projekts--setup)
* [`Weitere Informationen / Additional information`](#weitere-informationen--additional-information)


## Aufgabenstellung / Task

```
Belegaufgabe 4 C

Programmieren Sie ein Programm zur Verwaltung verborgter Bücher, CDs, DVDs (Medien). Dabei sollen Name, Autor/Interpret (kann auch leer bleiben) und leihende Person (Name) verwaltet werden. Wird ein Medium zurückgegeben, ist der Datensatz zu entfernen.
Es soll sowohl nach dem Medium, alsauch nach der leihenden Person gesucht werden können.
```

_(rough translation)_
```
Assignmenttask 4 C

Write a program that manages lending media such as books, CDs and DVDs to customers. The program should keep track of the name of the medium, its author/artist (which can also be left blank) and the person (their name) currently borrowing it. If a medium is returned, the data set should be removed.
The program should be capable of finding a medium by name and the person borrowing it.
```

## Einrichtung des Projekts / Setup

Um das CLI zu starten muss lediglich der Befehl `make` 
auf Project-Root-Ebene ausgeführt werden.
Es entsteht ein kompiliertes C-Programm mit Namen `library`. Dieses muss dann lediglich mittels `./library` ausgeführt werden.

Es ist ggf. wichtig zu erwähnen, dass der Name der Datei `lib.csv` sowie dessen Inhalt nicht verändert werden sollte. 
In der Datei mit diesem Namen werden die Datensätze gespeichert.

_To run the CLI, simply run the command `make` at project root level.
This results in a compiled C-program named `library`.
To execute it, run `./library`._

_`lib.csv` should not be modified or renamed, as the programs data set depends on its contents._

## Weitere Informationen / Additional information

Aufgrund von Unaufmerksamkeit beim Lesen der Aufgabenstellung habe
ich mich in der Aufgabe getäuscht. 
Daher existieren einige weitere Branches mit einer anderen Aufgabe. 
Aufgrund der Tatsache, dass mir dies erst spät auffiel, ist meine eigentlich zu bearbeitende Aufgabe auf `main`. 
Sollte allerdings trotzdem das Interesse bestehen empfehle ich einen Blick auf die den branch `dict` zu werfen. 
Das Setup für das Projekt dort ist analog zum Hauptprojekt auf `main`.
Der Branch bearbeitet die Aufgabe 3, hat aber ebenfalls kein Webinterface/GUI.
