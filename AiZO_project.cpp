#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;

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
            cout << "Blad sortowania!" << endl;
        if(test)
            cout << "Tablica została posortowana prawidlowo" << endl;
    }
};

class TXTFileWorker {

public:
    string path2File;
    //int size{};
    void getPath()    {

        string path;
        cout << "Podaj sciezke do pliku: " << endl;
        cin >> path;
        validatePath(path);
        path2File = path;

    }

    void validatePath(string path) {

        char answer;
        cout << "Czy podana sciezka jest poprawna (t/n)? -> : " + path << endl;
        cin >> answer;

        if (toupper(answer) == 'N') {
            getPath();
        } else if (toupper(answer) != 'T') {
            cout << endl;
            validatePath(path);
        }

    }

    template<typename T>
    vector<T> getTab() {

        ifstream file(path2File);
        int size;
        T num;

        if (!file.is_open()) {
            cerr << "Nie udalo sie otworzyc pliku " << path2File << endl;
            return {};
        }

        if (!(file >> size)) {
            cerr << "Nie udalo sie odczytac rozmiaru tablicy z pliku " << path2File << endl;
            file.close();
            return {};
        }

        vector<T> array(size);

        for (int i = 0; i < size; ++i) {
            if (!(file >> num)) {
                cerr << "Blad wczytywania danych z pliku " << path2File << endl;
                file.close();
                return {};
            }
            array[i] = num;
        }

        file.close();
        return array;
    }
};

class Test  {

public:
    template<typename T>
    static void generateRandomArray(vector<T>& array, int size) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1, 10000);

        for (int i = 0; i < size; ++i) {
            array.push_back(dis(gen));
        }
    }

    template<typename T>
    static double measure(vector<T>& array, double& totalTime, int algorithmNumber) {
        Algorithms algorithms;
        auto start = chrono::high_resolution_clock::now();
        switch (algorithmNumber) {
            case 1:
                if constexpr (is_same_v<T, int>)
                    algorithms.quickSort(array, 0, array.size() - 1);
                break;
            case 2:
                if constexpr (is_same_v<T, int>)
                    algorithms.heapSort(array);
                break;
            case 3:
                if constexpr (is_same_v<T, int>)
                    algorithms.shellSort(array);
                break;
            case 4:
                algorithms.insertionSort(array);
                break;
            default:
                cout << "Podano niepoprawny numer!";
                break;
        }
        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> elapsed = end - start;
        double time = elapsed.count();
        totalTime += time;
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
    void wywolanieFunkcji(vector<T>& array, double totalTime, int size, int algorithmNumber, int repeat){
        Test test;
        vector<T> temp;

        //W razie czego wywalić tego ifa bo wtedy ta tablica jest tą wczytaną z pliku txt co nie do końca jest git
        if(array.empty())
            test.generateRandomArray(array, size);

        temp = array;

        test.generatingAndTiming(temp, repeat, totalTime, size, algorithmNumber);
    }

};

class Menu  {

public:
    vector<int> array;
    vector<float> arrayFloat;
    Algorithms alg;
    TXTFileWorker txt;
    Test test;
    bool end = true;

    void menuDisplay() {
        cout << "1. Testuj " << endl;
        cout << "2. Wczytaj tablice " << endl;
        cout << "3. Wyswietl ostatnio wczytana tablice" << endl;
        cout << "4. Sortuj " << endl;
        cout << "5. Sprawdz algorytm " << endl;
        cout << "6. Zakoncz " << endl;
        getUserInput();
    }

    void getUserInput() {
        int input = 0;
        cout << "Wybierz numer operacji do wykonania: ";

        while (!(cin >> input) || input < 0 || input > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Bledne dane. Sprobuj ponownie: ";
        }

        switch (input) {
            case 1:
                AlgTest();
                break;
            case 2:
                array.clear();
                arrayFloat.clear();
                txt.getPath();
                if(typeCheck()){
                    array = txt.getTab<int>();
                    displayTab();
                }else{
                    arrayFloat = txt.getTab<float>();
                    displayTabFloat();
                }
                break;
            case 3:
                if (!array.empty()){
                    displayTab();
                } else{
                    displayTabFloat();
                }
                break;
            case 4:
                SortAlg();
                if (!array.empty()){
                    displayTab();
                } else{
                    displayTabFloat();
                }
                break;
            case 5:
                if (array.empty()){
                    alg.checkTable(arrayFloat);
                }else if (arrayFloat.empty()){
                    alg.checkTable(array);
                } else{
                    cout << "Tablica jest pusta!";
                }
                break;
            case 6:
                end = false;
                break;
        }
    }

    void displayTab() {
        if (!array.empty()) {
            for (int num : array) {
                cout << num << " ";
            }
            cout << endl;
        } else {
            cout << "Brak tablicy do wyswietlenia. " << endl;
        }
    }

    void displayTabFloat() {
        if (!arrayFloat.empty()) {
            for (float num : arrayFloat) {
                cout << num << " ";
            }
            cout << endl;
        } else {
            cout << "Brak tablicy do wyswietlenia. " << endl;
        }
    }

    void AlgTest(){
        int size, algorithmNumber, repeat, type;
        double totalTime = 0;
        cout << "Podaj ile chcesz miec liczb do posortowania: ";
        cin >> size;
        cout << "Podaj ile powtorzen chcesz wykonac: " << endl;
        cin >> repeat;
        cout << "Chcesz generowac float (0) czy int (1): ";
        cin >>type;
        if (type){
            cout << "1. Quick Sort 2. HeapSort 3. ShellSort 4. InsertionSort" << endl;
            cout << "Podaj algorytm do przetestowania (1-4): " << endl;
            cin >> algorithmNumber;
            test.wywolanieFunkcji(array, totalTime, size, algorithmNumber, repeat);
        }else{
            test.wywolanieFunkcji(arrayFloat, totalTime, size, 4, repeat);
        }

    }

    void SortAlg(){
        double totalTime = 0;
        if (!array.empty()){
            int algorithmNumber;
            cout << "1. Quick Sort 2. HeapSort 3. ShellSort 4. InsertionSort" << endl;
            cout << "Podaj algorytm do przetestowania (1-4): " << endl;
            cin >> algorithmNumber;
            double time = Test::measure(array, totalTime, algorithmNumber);
            cout << "Czas sortowania wyniosl: "<< time << " ms" << endl;
        }else{
            double time = Test::measure(arrayFloat, totalTime, 4);
            cout << "Czas sortowania wyniosl: "<< time << " ms" << endl;
        }
    }

    int typeCheck(){
        int type;
        cout << "Podaj czy chcesz wprowadzic float (0) czy int (1): " << endl;
        cin >> type;
        return type;
    }

};

int main() {

    Menu menu;
    while (menu.end)
        menu.menuDisplay();

    return 0;
}