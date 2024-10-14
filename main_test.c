#include "tests/ship_test.h"
#include "tests/thread_test.h"
#include "tests/mutex_test.h"
#include "tests/config_test.h"
#include "tests/canal_test.h"
#include "tests/schedulers_test.h"

int main(){
    //Si quieren correr pruebas en el main, crear una función aparte en un archivo aparte en tests/ y llamarlas aquí
    //shipTest();
    //hiloTest();
    //mutexTest();
    //configTest();
    canalTest();
    //test_schedulers();
    return 0;
}

