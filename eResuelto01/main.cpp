#include <QCoreApplication>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <mutex>

using namespace std;

void* procesoHilo(void *dato){
    struct timespec tm={1,0};

    while(1){
        qDebug() << "proceso";
        pthread_delay_np(&tm);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pthread_t proceso1;
    pthread_t proceso2;



    pthread_create(&proceso1, NULL,&procesoHilo,NULL);
    pthread_create(&proceso2, NULL,&procesoHilo,NULL);


    pthread_join(proceso1, NULL);
    pthread_join(proceso2, NULL);

    return a.exec();
}
