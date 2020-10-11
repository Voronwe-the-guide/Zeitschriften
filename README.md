# Zeitschriften

Ein DatenbankViewer für Zeitschriften

(c) Thorsten Stapel

This Software is licensed under GPL3


Dies ist nur ein Hobbyprojekt und weit davon entfernt. vollständig oder sonstiges zu sein.

----- Benutzung -------
Die Software muß nicht installiert werden.

Vor dem ersten Aufruf muß eine Datenbank erzeugt werden. Die geschieht mit "makeNewDB.bat". Hier wird eine leere Datenbank "neueDB.db" erzeugt. Die kann umbenannt werden und auch in einen anderen Ordner verschoben werden.

Die Software wird mit ZeitschriftenDBViewer.exe aufgerufen.
Beim ersten Aufruf muß eine Datenbank mit "LadeDB" gelesen werden - bei allen weiteren Aufrufen wird diese DB automatisch gelesen. 
Ich empfehle, die Software nach ändern der DB zu schließen und nue zu starten. Es gab da ein paar Bugs, die ich eleminiert habe, aber, ob ich alle gefunden habe ... 
Neustart ist auf jeden Fall sicherer.

Mit "Neuer Artikel" kann ein neuer Artikel angelegt werden, mit "Neue Zeitschrift" eine neue Zeitschrift und mit "Neue ausgabe" eine neue Ausgabe.
Rote Felder sind auszufüllen.
Wenn im Artikel eine Zeitschrift oder eine Ausgabe eingetragen wird, die nicht vorhanden ist, kommt beim "Speichern" ein Pop-Up. Wenn dieses Pop-up geschlossen wurde, muß man nochmal auf Speichern drücken, sonst wird der Artikel nicht gespeichert

Man kann den Artikel auf der Karte veorten, dafür einfach in die Karte klicken. 
*bug* Es scheint Probleme mit Koordinaten zu geben, die sehr nahe am Null-Meridian oder am Äquator sind (<0,1°)

Bilder für Ausgaben und Zeitschriften werden nur als Verzeichnis-Link in der DB gespeichert, die Link wird relativ zur Datenbank gespeichert

Zeitschriften-Auswahl: Man kann in der Zeitschriften-Bar eine oder mehrere Zeitschriften auswählen, die angezeigt werden sollen. "Alle" löscht diese Auswahl.

Dies erstmal in Kürze, Viel Spaß




----- Software Build ------

Der Code ist ziemlich messy,  ich sollte mal drüber nachdenken, den aufzuräumen und ordentlich zu machen

For building the Software, Qt 5.15 is needed, which can be got from here: https://www.qt.io/download

Take in account the following:
https://doc.qt.io/qt-5/windows-requirements.html

Additionally, OpenSSL is needed (I used 1.1.1g-win64-mingw.zip), which can be downloaded here: https://bintray.com/vszakats/generic/download_file?file_path=openssl-1.1.1g-win64-mingw.zip

Or here: https://kb.firedaemon.com/support/solutions/articles/4000121705 (This one is attached to the code)

Beside this, I would like you to ask to use this software only in good mood and not for purposes which could harm people, animals, magical creatures or the environment.

