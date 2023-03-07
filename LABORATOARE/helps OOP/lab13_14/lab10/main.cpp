#include "UI.h"
#include "VectorDinamicTemplate.h"
#include <iostream>
//#define _CRTDBG_MAP_ALLOC
#include "Pet.h"
#include "testall.h"
#include "CosProd.h"

#include "GUIrezerva.h"
//#include <crtdbg.h>
#include<QWidget>
#include <QApplication>
using std::cout;
using std::endl;


void testAll() {
    testeEnt();
    testecmp();
    cout << "Au fost trecute testele pentru entitati." << endl;
    testeCos();
    cout<<"teste trecute pentru cosprod"<<endl;
    testerepo();
    cout << "Au fost trecute testele pentru repository." << endl;
    testeservice();
    //testAll<VectorDinamic<Pet>>();
    cout << "Au fost trecute testele pentru service." << endl<<endl<<endl;

}
/*void startApp() {
    //ProdRepo repo;
    RepoFile repo{"produse5.txt"};
    ProdValidator val;
    ProdService srv{ repo,val };
    ConsoleUI ui{ srv };

    ui.run();
}
int main() {
    //int* v=new int[10];
    testAll();
    startApp();


}*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RepoFile repo{ "C:\\Users\\Laura\\CLionProjects\\lab10\\cmake-build-debug\\produse1.txt" };
    //ProdRepo repo;
    ProdValidator val;
    ProdService srv{ repo,val };
    GUItur gui{ srv };

    gui.run();
    return a.exec();
}