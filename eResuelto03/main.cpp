#include <QCoreApplication>
#include <QDebug>
#include <thread>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <mutex>

std::mutex vectLock;
std::vector<unsigned int> primeVect;

// Función de procesamiento secuencial para encontrar primos sin hilos
void FindPrimesWithoutThreads(unsigned int start, unsigned int end, std::vector<unsigned int>& vect) {
    for (unsigned int x = start; x <= end; x += 2) {
        bool isPrime = true;
        for (unsigned int y = 2; y * y <= x; y++) {  // Optimización: y * y <= x
            if (x % y == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            vect.push_back(x);
        }
    }
}

// Función de procesamiento paralelo para encontrar primos con hilos
void FindPrimes(unsigned int start, unsigned int end) {
    for (unsigned int x = start; x <= end; x += 2) {
        bool isPrime = true;
        for (unsigned int y = 2; y * y <= x; y++) {
            if (x % y == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            std::lock_guard<std::mutex> lock(vectLock);
            primeVect.push_back(x);
        }
    }
}

void FindPrimesWithThreads(unsigned int start, unsigned int end, unsigned int numThreads) {
    std::vector<std::thread> threadVect;
    unsigned int threadSpread = end / numThreads;
    unsigned int newEnd = start + threadSpread - 1;

    for (unsigned int x = 0; x < numThreads; x++) {
        threadVect.emplace_back(FindPrimes, start, newEnd);
        start += threadSpread;
        newEnd += threadSpread;
    }

    for (auto& t : threadVect) {
        t.join();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // SIN HILOS
    int startTime = clock();

    std::vector<unsigned int> primeVect1;
    FindPrimesWithoutThreads(1, 1000000, primeVect1);

    int endTime = clock();
    qDebug() << "Execution Time :" << (endTime - startTime) / double(CLOCKS_PER_SEC) << " // sin hilos";

    // CON HILOS
    startTime = clock();

    FindPrimesWithThreads(1, 1000000, 8);

    endTime = clock();
    qDebug() << "Execution Time :" << (endTime - startTime) / double(CLOCKS_PER_SEC) << " // con hilos";

    return a.exec();
}
