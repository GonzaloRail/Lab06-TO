#include <QCoreApplication>
#include <QDebug>
#include <thread>
#include <sstream>
#include <chrono>
#include <ctime>
#include <random>

using namespace std;

// Generar un número aleatorio entre 1 y 3
int GetRandom(int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, max);
    return dist(gen);
}

void ExecuteThread(int id) {
    auto nowTime = chrono::system_clock::now();
    time_t sleepTime = chrono::system_clock::to_time_t(nowTime);

    // Obtener la zona horaria local
    tm *myLocalTime = localtime(&sleepTime);

    qDebug() << "Thread:" << id << "Sleep Time:" << std::ctime(&sleepTime);
    qDebug() << "Month:" << (myLocalTime->tm_mon + 1);
    qDebug() << "Day:" << myLocalTime->tm_mday;
    qDebug() << "Year:" << (myLocalTime->tm_year + 1900);
    qDebug() << "Hours:" << myLocalTime->tm_hour;
    qDebug() << "Minutes:" << myLocalTime->tm_min;
    qDebug() << "Seconds:" << myLocalTime->tm_sec;

    // Espera 3 segundos antes de imprimir en consola
    this_thread::sleep_for(chrono::seconds(GetRandom(3)));

    nowTime = chrono::system_clock::now();
    sleepTime = chrono::system_clock::to_time_t(nowTime);
    qDebug() << "Thread" << id << "Awake Time:" << std::ctime(&sleepTime);
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    thread th1(ExecuteThread, 1);
    th1.join();

    thread th2(ExecuteThread, 2);
    th2.join();

    return a.exec();
}
