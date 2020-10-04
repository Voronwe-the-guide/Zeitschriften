set output_Name=ZeitschriftenDB_Application
set output_path=ReleaseBuild\%output_Name%

mkdir %output_path%
copy ReleaseBuild\Viewer\release\ZeitschriftenDBViewer.exe %output_path%
copy ReleaseBuild\Updater\release\ZeitschriftenDB_Updater.exe %output_path%
copy openssl\*.dll %output_path%
mkdir %output_path%\sqliteTools
copy sqliteTools %output_path%\sqliteTools
copy sql_makeDB.txt %output_path%
copy makeNewDB.bat %output_path%
copy 3rdPartyLicense %output_path%
copy README.md %output_path%
copy LICENSE %output_path%

cd %output_path%

c:\Qt\5.15.1\msvc2019_64\\bin\windeployqt.exe ZeitschriftenDBViewer.exe --qmldir ..\..\QML\

cd ..

set mydate=%date%
set mydate=%mydate:.=_%

set mytime=%time%
set mytime=%mytime::=_%
set mytime=%mytime:,=_%
set time=%mydate%_%mytime%

"c:\Program Files\7-Zip\7z.exe" a %output_Name%_%time%.zip %output_Name%

pause


