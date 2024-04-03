#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

class Menu  {

    //interakcja z użytkownikiem
    //wybór komend tak, jak w projekcie z zeszłego semu z javy feedback manager (aplikacja konsolowa)
    //jeden wielki switch, wpisz numer komendy, funkcja sprawdzająca, czy użytkownik wpisał int, jak nie, to prosząca o ponowne wpisanie
    //można zajebać i przerobić kod z tamtego projektu, jak da radę

    /* 1. Przeprowadzenie testów
     * 2. Sprawdzanie poprawności algorytmów:
     *      a) wygeneruj tablicę i wypłnij liczbami losowymi (funkcja random), program powinien zapytać o rozmiar tablicy
     *      b) odczytaj tablicę z pliku -> TXTFileWorker
     * 3. Wyświetlenie ostatnio utworzonej tablicy
     * 4. Uruchomienie wybranego algorytmu na ostatnio wczytanej tablicy i wyświetlenie po sortowaniu */

};

class Algorithms  {

    //Wszystkie algorytmy są na int poza Insertion sortem
public:
    //Insertion sort (Z szablonem)
    template<typename T>
    void insertionSort(vector<T>& array) {
        for (int step = 1; step < array.size(); step++) {
            T key = array[step];
            int j = step - 1;

            while (j >= 0 && key < array[j]) {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = key;
        }
    }

    //Quick Sort
    void swapp(int &a, int &b) {
        int t = a;
        a = b;
        b = t;
    }

    int partition(vector<int>& array, int low, int high) {
        int pivot = array[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (array[j] <= pivot) {
                i++;
                swapp(array[i], array[j]);
            }
        }
        swapp(array[i + 1], array[high]);
        return (i + 1);
    }

    void quickSort(vector<int>& array, int low, int high) {
        if (low < high) {
            int pi = partition(array, low, high);
            quickSort(array, low, pi - 1);
            quickSort(array, pi + 1, high);
        }
    }

    //Heap sort
    void heapify(vector<int>& array, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && array[left] > array[largest])
            largest = left;

        if (right < n && array[right] > array[largest])
            largest = right;

        // Swap and continue heapifying if root is not largest
        if (largest != i) {
            swap(array[i], array[largest]);
            heapify(array, n, largest);
        }
    }

    void heapSort(vector<int>& array) {
        int n = array.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(array, n, i);

        for (int i = n - 1; i >= 0; i--) {
            swap(array[0], array[i]);
            heapify(array, i, 0);
        }
    }

    //Shell sort
    void shellSort(vector<int>& array) {
        int n = array.size();
        for (int interval = n / 2; interval > 0; interval /= 2) {
            for (int i = interval; i < n; i += 1) {
                int temp = array[i];
                int j;
                for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
                    array[j] = array[j - interval];
                }
                array[j] = temp;
            }
        }
    }

    //Sprawdzanie tablicy
    template<typename T>
    void checkTable(vector<T>& array) {
        bool test = true;
        for (int i = 1; i < array.size(); i++)
            if (array[i - 1] > array[i])
                test = false;
        if (!test)
            cout << "Tab has been sorted incorrectly" << endl;
        if(test)
            cout << "Wszystko gra !!!!!!!" << endl;
    }

    /*Drukowanie
    void printArray(vector<int>& array) {
        for (int i = 0; i < array.size(); i++) {
            cout << array[i] << " | ";
        }
        cout << endl;
    }*/
};

class TXTFileWorker {

    /* 1. Program ma zapytać o nazwę pliku, z którego ma pobrać dane
    2. W pierwszej linijce w programie jest wielkość tablicy, potem w każdej kolejnej linijce jest jedna liczba z tej tablicy np.
    3
    56
    76
    32
    to tab[3] = [56, 76, 32]
    4. Program ma wyświetlić tablicę przed sortowaniem i po sortowaniu */

};

class Test  {
    /* 1. Badanie czasów sortowania tablic w funkcji ich rozmiaru
     *
     * a) dla 7 rozmiarów tablic dobranych rosnąco i tak, aby wyniki pomiarów były w ms i więcej
     *      np. 10 000, 20 000, 30 000 ... 70 000
     *      po 100 pomiarów dla za każdym razem nowo wygenerowanej losowej tablicy
     *      zmierzyć czasy sortowania dla poszczególnych algorytmów, pomijając czas generacji danych
     *      dane powinny być generowane losowo
     *      wyniki należy uśrednić i na ich podstawie zrobić wykresy np. w pythonie
     *      
     * trzeba to będzie rozdzielić wszystko sensowanie na funkcje, żeby nie duplikować kodu
     * 
     * 
     * 
     * 2. Przypadki szczególne
     * To samo, co na górze, ale dla tablic:
     * a) posortowanych rosnąco
     * b) posortowanych malejąco
     * c) tablic posortowanych częściowo 
     *  - 33% posortowania
     *  - 66% posortowania
*/
public:
    template<typename T>
    static void generateRandomArray(vector<T>& array, int size) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1.0, 10000.0);

        for (int i = 0; i < size; ++i) {
            array.push_back(dis(gen));
        }
    }

    template<typename T>
    static double measure(vector<T>& array, double& totalTime, int algorithmNumber) {
        Algorithms algorithms;
        auto start = chrono::high_resolution_clock::now(); // Początek pomiaru czasu
        switch (algorithmNumber) {
            case 1: {
                vector<int> intArray(array.size());
                transform(array.begin(), array.end(), intArray.begin(), [](float val) { return static_cast<int>(val); });
                algorithms.quickSort(intArray, 0, intArray.size() - 1);
                break;
            }
            case 2:
                //algorithms.heapSort(static_cast<vector<int>&>(array));
                break;
            case 3:
                //algorithms.shellSort(static_cast<vector<int>&>(array));
                break;
            case 4:
                algorithms.insertionSort(array);
                break;
            default:
                cout << "Podano niepoprawny numer!";
                break;
        }
        //algorithms.shellSort(array);
        auto end = chrono::high_resolution_clock::now(); // Koniec pomiaru czasu

        chrono::duration<double, milli> elapsed = end - start; // Obliczenie czasu trwania w milisekundach
        double time = elapsed.count(); // Czas sortowania w milisekundach
        totalTime += time; // Dodanie czasu do sumy
        return time;
    }

    template<typename T>
    void generatingAndTiming (vector<T>& array, int iterations, double& totalTime, int size, int alghoritm){
        Test test;
        Algorithms algorithms;
        for (int i = 0; i < iterations; ++i) {
            test.printArray(array);
            double time = Test::measure(array, totalTime, alghoritm); // Pomiar czasu sortowania
            test.printArray(array);
            algorithms.checkTable(array);
            array.clear();
            test.generateRandomArray(array, size);
            cout << "Iteracja " << i+1 << ": Czas sortowania: " << time << " ms" << endl << endl;
        }

        cout << "Suma czasów sortowania: " << totalTime << " ms" << endl;
    }

    template<typename T>
    void printArray(vector<T>& array){
        for(auto i = array.begin(); i != array.end(); ++i)
            cout << *i << " | ";
        cout <<endl;
    }

    template<typename T>
    void wywolanieFunkcji(vector<T>& array, double totalTime, int size, int algorithmNumber){
        Test test;
        vector<T> temp;

        test.generateRandomArray(array, size);
        test.printArray(array);
        cout << endl;
        temp = array;

        test.generatingAndTiming(temp, 10, totalTime, size, algorithmNumber);
        test.printArray(array);
    }

};

int main() {
    int size, algorithmNumber;
    double totalTime = 0;
    cout << "Podaj ile chcesz miec liczb do posortowania: ";
    cin >> size;
    cout << "Podaj algorytm do przetestowania (1-5): ";
    cin >> algorithmNumber;
    // 1 - quickSort, 2 - heapSort, 3 - shellSort, 4 - InsertionSort


    Test test;

    vector<float> array;
    test.wywolanieFunkcji(array, totalTime, size, algorithmNumber);
    /*vector<int> temp;

    test.generateRandomArray(array, size);
    test.printArray(array);
    cout << endl;
    temp = array;

    /* Algorithms algorithms;
    algorithms.shellSort(array);
    algorithms.printArray(array);//

    test.generatingAndTiming(temp, 10, totalTime, size, algorithmNumber);
    test.printArray(array);*/



    return 0;
}