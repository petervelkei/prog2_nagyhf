# A programozás alapjai 2. (VIIIAA03) nagy házi feladat 

## 1. rész: Specifikáció

### Készítette: Velkei Péter | SHBEKB

----

## Választott feladat:

```
Vonatjegy

Tervezze meg egy vonatjegy eladó rendszer egyszerűsített objektummodelljét, majd valósítsa azt meg! A vonatjegy a feladatban mindig jegyet és helyjegyet jelent együtt. Így egy jegyen minimum a következőket kell feltüntetni:

- vonatszám, kocsiszám, hely
- indulási állomás, indulási idő
- érkezési állomás, érkezési idő

A rendszerrel minimum a következő műveleteket kívánjuk elvégezni:

- vonatok felvétele
- jegy kiadása

A rendszer később lehet bővebb funkcionalitású (pl. késések kezelése, vonat törlése, menetrend, stb.), ezért nagyon fontos, hogy jól határozza meg az objektumokat és azok felelősségét.

Valósítsa meg a jeggyel végezhető összes értelmes műveletet operátor átdefiniálással (overload), de nem kell ragaszkodni az összes operátor átdefiniálásához! A megoldáshoz ne használjon STL tárolót!
```

----

### Feladatleírás

A feladat egy olyan program megalkotása, amely lehetővé teszi egy vasúttársaság számára az utasok adatainak nyilvántartását és a vasútakon végzett szolgáltatások nyomon követését. 

**A program képes:**

- A vonatok adatainak tárolására (lásd: Adatok tárolása), valamint lehetséges vonatokra jegy vásárlása, de lehetőség van vonatútvonalak törlésére is.
- Az adatok fájlban való tárolására.

---

### 1. Adatok tárolása

A csillaggal jelölt adatokat a programban új rekord felvételekor kötelező megadni (addig nem megy tovább a program)

(Az azonosítók követelmménye, hogy egyediek legyenek, de a fájlokban nem szükséges, hogy növekvő sorozatot alkossanak)


**Vonat**

A vonatokról a következő adatokat tároljuk:
- (*) vonat azonosítója (egész szám)
- (*) vonat neve		(string)
- (*) indulási állomás	(string)
- (*) indulási idő		(egész számok, HH:MM:SS formátumban)
- (*) érkezési állomás	(string)
- (*) érkezési idő		(egész számok, HH:MM:SS formátumban)
- (*) kocsiszám 		(egész szám)
- (*) kocsi kapacitás 	(egész szám)
- (*) távolság			(egész szám)

**Jegy**

A jegyekről a következő adatokat tároljuk:
- (*) vonat azonosítója (egész szám)
- (*) jegytípusok:
	- Teljes árú jegy 	(1) (egész szám, id: 1)
	- Diákjegy			(2) (egész szám, id: 2)
	- Nyugdíjas jegy	(3) (egész szám, id: 3)
- (*) ár (egész szám)
- (*) indulási állomás	(string)
- (*) érkezési állomás	(string)
- (*) kocsiszám	(egész szám)
- (*) helyszám 	(egész szám)

A futás során a menürendszer segítségével változhat az állapot. Ezeket a változásokat a program elmenti a kilépésnél.

---

### 2. Adatok tárolásának módja

Az adatokat külön-külön .csv (comma separated values), pontosvesszővel elválasztott fájlformátumban tároljuk.
A fájlban az adatok ékezet nélkül kerülnek tárolásra és a program is ékezet nélkül jeleníti meg majd azokat, illetve így várja a bemenetet.

2 db adatfájlt kezel a program, vonatok.csv, jegyek.csv, ami a fenti adatokat tárolja, soronként egy rekordot. A megjelölt adatok pontosvesszővel választja el. Példák:

**vonatok.csv**

```csv
939;Savaria IC;Szombathely;13;10;00;Budapest-Kelenföld;15;28;00;3;6;255

...
```

**jegyek.csv**

```csv
939;1;2500;Szombathely;Győr;2;38

...
```

----

### 3. Menü 

A program futtatása után megjelenik a menü. Itt több opció közül választhat a felhasználó a menüpontok előtti szám leírásával és utána az Enter gomb megnyomásával.

Egy adott menüpont kiválasztásával a menürendszer eltűnik a képernyőről, miután a kiválasztott funkció azonnal megjelenik a teljes képernyőt elfoglalva.

```
1. Vonat hozzáadás
2. Vonat törlés
3. Jegy vásárlás
4. kilépés

Válassz egy menüpontot: 1 *Enter*
```

#### 3.1 Vonat hozzáadása

Vonat hozzáadása itt történik a megfelelő adatok megadása után. Ha az adott útvonal már létezik, akkor a hozzáadás sikertelen lesz.

```
Vonat hozzáadása
----------------
1. Vonat azonosítója: 938
2. Vonat neve: Savaria IC
3. Indulási állomás: Budapest-Kelenföld
4. Indulási idő: 12:29:00
5. Érkezési állomás: Szombathely
6. Érkezési idő: 14:49:00
7. Kocsi kapacitás: 6
8. Távolság: 255
Vonat hozzáadása sikeres!

Nyomj entert a menübe való visszatéréshez *Enter*
```

#### 3.3.1 Vonat törlése

A felhasználó szabadon választhat, hogy melyik útvonalat szeretné eltörölni.

```
Vonatútvonal kiválasztása
-------------------------
1. Esztergom - Nyugati
2. Nyugati - Kecskemét
3. Szombathely - Kelenföld

Válassz egy menüpontot: 3 *Enter*
```

#### 3.3.2 Időpont kiválasztása

A felhasználó szabadon választhat, hogy melyik időpontban szeretné eltörölni az előző menüpontban kiválasztott útvonalat.

```
Időpont kiválasztása
--------------------
1. 12:29:00 - 14:49:00
2. 13:10:00 - 15:28:00
3. 23:42:00 - 02:00:00

Válassz egy menüpontot: 3 *Enter*
Vonatút törlése sikeres!

Nyomj entert menübe való visszatéréshez *Enter*
```

#### 3.4.1 Jegyvásárlás

A felhasználó által kiválasztható, hogy melyik útvonalon szeretne közlekedni.

```
Válassz útvonalat
-----------------
1. Esztergom - Nyugati
2. Nyugati - Kecskemét
3. Szombathely - Keleti

Válassz egy menüpontot: 3 *Enter*
```

#### 3.4.2 Indulási állomás kiválasztása

A felhasználó által kiválasztható, hogy az adott útvonalon melyik állomás legyen az indulási állomása.

```
Indulási-állomás
-----------------
1. Szombathely
2. Répcelak
3. Csorna
4. Győr
5. ...

Válassz egy menüpontot: 1 *Enter*
```

#### 3.4.3 Célállomás kiválasztása

A felhasználó által kiválasztható, hogy az adott útvonalon melyik állomás legyen a célállomása.

```
Cél-állomás
-----------------
1. Keleti
2. Kelenföld
3. Tatabánya
4. Tata
5. ...

Válassz egy menüpontot: 2 *Enter*
```

#### 3.4.4 Időpont kiválasztása

A felhasználó által kiválasztható, hogy az adott útvonalon mikor szeretne közlekedni.

```
Indulási időpont
----------------
1. 12:23:00
2. 14:49:00
3. 23:34:00
...

Válassz egy menüpontot: 2 *Enter*
```

#### 3.4.5 Foglalás eredménye

```
A rendszer a foglaltsági adatok alapján az 1. kocsi 38. ülését adta ki
automatikusan.

Nyomj entert a menübe való visszatéréshez *Enter*
```
