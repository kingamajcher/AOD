Autor: Kinga Majcher 272354

Opis technologii:
  Programy zostały napisane w języku C++. Użyte zostały standardowe biblioteki: iostream, fstream, sstream, vector, queue, tuple, stdexcept, chrono, climits, string

Opis plików:
  "Graph.cpp" - implementacja grafu, wczytywanie danych grafu z pliku, zapis wyników do pliku
  "Dijkstra.cpp" - implementacja algorytmu Dijkstry do wyznaczania najkrótszej ścieżki w grafie, main do wywoływania programu
  "Dial.cpp" - implementacja algorytmu Diala do wyznaczania najkrótszej ścieżki w grafie, main do wywoływania programu
  "RadixHeap.cpp" - implementacja algorytmu Radix Heap do wyznaczania najkrótszej ścieżki w grafie, main do wywoływania programu

Kompilacja:
  Należy użyć polecenia "make" w terminalu będąc w folderze z implementacjami algorytmów

Uruchomienie programu:
  Należy skompilować programy, a następnie użyć jednej z komend zastępując ./Algorytm nazwą odpowiedniego algorytmu (tj. ./Dijkstra, ./Dial lub ./RadixHeap):

  Jeśli chcemy wyznaczyć średni czas wyznaczania najkrótszej ścieżki z wszystkich wierzchołków podanych w pliku zrodla.ss:
    ./Algorytm -d plik_z_danymi.gr -ss zrodla.ss -oss wyniki.ss.res

  Jeśli chcemy wyznaczyć długość najkrótszej ścieżki między podanymi w pliku pary.p2p parami wierzchołków:
    ./Algorytm -d plik_z_danymi.gr -p2p pary.p2p -op2p wyniki.p2p.res
