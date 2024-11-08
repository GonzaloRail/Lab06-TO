#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <vector>
#include <memory>

using namespace std;

// Nodo de la lista enlazada simple
struct Node {
    int value;
    shared_ptr<Node> next;
    Node(int val) : value(val), next(nullptr) {}
};

// Clase Lista Enlazada con operaciones de insertar, eliminar, buscar y modificar
class LinkedList {
private:
    shared_ptr<Node> head;
    mutex mtx;  // Mutex para controlar las secciones críticas

public:
    LinkedList() : head(nullptr) {}

    // Inserta un nuevo nodo en la lista
    void insert(int val) {
        lock_guard<mutex> lock(mtx);
        auto newNode = make_shared<Node>(val);
        newNode->next = head;
        head = newNode;
        cout << "Insertando: " << val << endl;
    }

    // Elimina un nodo con un valor específico de la lista
    void remove(int val) {
        lock_guard<mutex> lock(mtx);
        auto current = head;
        shared_ptr<Node> prev = nullptr;
        while (current) {
            if (current->value == val) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                cout << "Eliminando: " << val << endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "No se elimino: " << val << endl;
    }

    // Busca un nodo con un valor específico en la lista
    bool search(int val) {
        lock_guard<mutex> lock(mtx);
        auto current = head;
        while (current) {
            if (current->value == val) {
                cout << "Buscado: " << val << " - Encontrado" << endl;
                return true;
            }
            current = current->next;
        }
        cout << "Buscado: " << val << " - No encontrado" << endl;
        return false;
    }

    // Modifica un nodo, sumando un valor adicional si lo encuentra
    void modify(int val, int increment) {
        lock_guard<mutex> lock(mtx);
        auto current = head;
        while (current) {
            if (current->value == val) {
                int newVal = current->value + increment;
                cout << "Modificando " << val << " a " << newVal << endl;
                current->value = newVal;
                return;
            }
            current = current->next;
        }
        cout << "No se encontro: " << val << " para modificar" << endl;
    }
};

// Función para generar números aleatorios
int generateRandomNumber(int min, int max) {
    static thread_local mt19937 generator{random_device{}()};
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

// Funciones para los Threads
void threadInsert(LinkedList &list) {
    for (int i = 0; i < 10; ++i) {
        int value = generateRandomNumber(1, 100);
        list.insert(value);
    }
}

void threadRemove(LinkedList &list) {
    for (int i = 0; i < 10; ++i) {
        int value = generateRandomNumber(1, 100);
        list.remove(value);
    }
}

void threadSearch(LinkedList &list) {
    for (int i = 0; i < 10; ++i) {
        int value = generateRandomNumber(1, 100);
        list.search(value);
    }
}

void threadModify(LinkedList &list) {
    for (int i = 0; i < 10; ++i) {
        int value = generateRandomNumber(1, 100);
        int increment = generateRandomNumber(1, 10);
        list.modify(value, increment);
    }
}

int main() {
    LinkedList list;

    // Crear y lanzar los Threads
    thread t1(threadInsert, ref(list));
    thread t2(threadRemove, ref(list));
    thread t3(threadSearch, ref(list));
    thread t4(threadModify, ref(list));

    // Esperar a que terminen todos los Threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
