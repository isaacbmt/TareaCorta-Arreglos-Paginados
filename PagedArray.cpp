#include "PagedArray.h"
#include <fstream>
#include <math.h>

using namespace std;

PagedArray::PagedArray() {
    page1 = new Page;
    page1->setPos(0);

    page2 = new Page;
    page2->setPos(1);

    page3 = new Page;
    page3->setPos(2);

    page4 = new Page;
    page4->setPos(3);

    page5 = new Page;
    page5->setPos(4);

    page6 = new Page;
    page6->setPos(5);
    currentPages = 0;

//    createBinaryFile(resultado);
}

void PagedArray::createBinaryFile(ifstream* input) {
    string contenido((istreambuf_iterator<char>(*input)), istreambuf_iterator<char>());;

    string numbers = contenido;
    string delimiter = ", ";

    size_t pos = 0, pos2 = 0;
    int index = 0, i = 0;

    while ((pos = contenido.find(delimiter)) != string::npos){
        contenido.erase(0, pos + delimiter.length());
        index++;
    }

    int array[index];

    while ((pos2 = numbers.find(delimiter)) != string::npos){
        array[i] = stoi(numbers.substr(0, numbers.find(delimiter)));
        numbers.erase(0, pos2 + delimiter.length());
        i++;
    }

    cout << endl;
    length = index;
    FILE *file = fopen("memoria.txt", "wb");;

    fwrite(array, sizeof(int), sizeof(array) / 4, file);
    fclose(file);
}

void PagedArray::fifo(int index) {
//    cout << "Current: " << currentPages << endl;
    if (currentPages < 6) {
        if (!find(index)) {
            currentPages++;
            useEmptyPage(index);
        }
    }
    else {
        if (!find(index)){
            writePageInFile(page1);
            orderPages(index);
        }
    }
}

void PagedArray::orderPages(int index) {
    page1->setPage(page2);
    page2->setPage(page3);
    page3->setPage(page4);
    page4->setPage(page5);
    page5->setPage(page6);
    int *tmp = readPageInFile(index);
    page6->setPage(tmp);
    page6->setIndex((int) floor(index / 256));
}

void PagedArray::writePageInFile(Page *page) {
    int *array = page->getPage();
    int pag = page->getIndex();
    fstream file;
    file.open("memoria.txt", fstream::in | fstream::out | fstream::binary);

    for (int j = 0; j < 256; ++j) {
//        int pos = 4 * (j - 256 * pag);
        int pos = 4 * ((256 * pag  + j) - 256 * pag ) + 4 * 256 * pag;
        file.seekp(pos, file.beg);
        file.write((char *) &array[j], sizeof(int));
        file.flush();
    }
}

int *(PagedArray::readPageInFile(int index)) {
    int *tmp = new int[256];
    int pag = (int) floor(index / 256);
    fstream file;
    file.open("memoria.txt", fstream::in | fstream::out | fstream::binary);
//    cout << "Buscando pag: "<< pag << endl;
    for (int j = 0; j < 256; ++j) {
        int pos = 4 * ((256 * pag  + j) - 256 * pag ) + 4 * 256 * pag;
        file.seekg(pos, file.beg);
        file.read((char *) &tmp[j], (int) sizeof(int));
        file.flush();
    }
    return tmp;
}

bool PagedArray::find(int i){
    if (page1->getIndex() == i){
        return true;
    }
    else if (page2->getIndex() == i){
        return true;
    }
    else if (page3->getIndex() == i){
        return true;
    }
    else if (page4->getIndex() == i){
        return true;
    }
    else if (page5->getIndex() == i){
        return true;
    }
    else return page6->getIndex() == i;
}

void PagedArray::useEmptyPage(int index) {
    int pag = (int) floor(index / 256);

    if (page1->getIndex() == -1){
//        cout << "Lleno pag 1 " << endl;
        int *tmp = readPageInFile(index);
        page1->setPage(tmp);
        page1->setIndex(pag);
    }
    else if (page2->getIndex() == -1){
//        cout << "Lleno pag 2 " << endl;
        int *tmp = readPageInFile(index);
        page2->setPage(tmp);
        page2->setIndex(pag);
        page5->setIndex(-1);

    }
    else if (page3->getIndex() == -1){
//        cout << "Lleno pag 3 " << endl;
        int *tmp = readPageInFile(index);
        page3->setPage(tmp);
        page3->setIndex(pag);
        page5->setIndex(-1);
    }
    else if (page4->getIndex() == -1){
//        cout << "Lleno pag 4 " << endl;
        int *tmp = readPageInFile(index);
        page4->setPage(tmp);
        page4->setIndex(pag);
        page5->setIndex(-1);
        page6->setIndex(-1);
    }
    else if (page5->getIndex() == -1){
//        cout << "Lleno pag 5 " << endl;
        int *tmp = readPageInFile(index);
        page5->setPage(tmp);
        page5->setIndex(pag);
        page6->setIndex(-1);
    }
    else if (page6->getIndex() == -1){
//        cout << "Lleno pag 6 " << endl;
        int *tmp = readPageInFile(index);
        page6->setPage(tmp);
        page6->setIndex(pag);
    }
    else{
        cout << "Error: no hay paginas vacias" << endl;
    }
}

void PagedArray::writeFile() {
    ofstream resultado("resultado.txt");

    if (resultado.is_open()){
        for (int i = 0; i < getLength(); ++i) {
            resultado << this[0][i] << ", ";
        }
        resultado.close();
    }
}

Page *PagedArray::getPageptr(int pag){
    if (page1->getIndex() == pag){
        return page1;
    }
    else if (page2->getIndex() == pag){
        return page2;
    }
    else if (page3->getIndex() == pag){
        return page3;
    }
    else if (page4->getIndex() == pag){
        return page4;
    }
    else if (page5->getIndex() == pag){
        return page5;
    }
    else if (page6->getIndex() == pag){
        return page6;
    }
    else{
        return nullptr;
    }
}

int &(PagedArray::operator [](int i)){
    int pag = (int) floor(i / 256);

    if (page1->getIndex() == pag){
        return page1->getPage()[i - 256 * pag];
    }
    else if (page2->getIndex() == pag){
        return page2->getPage()[i - 256 * pag];
    }
    else if (page3->getIndex() == pag){
        return page3->getPage()[i - 256 * pag];
    }
    else if (page4->getIndex() == pag){
        return page4->getPage()[i - 256 * pag];
    }
    else if (page5->getIndex() == pag){
        return page5->getPage()[i - 256 * pag];
    }
    else if (page6->getIndex() == pag){
        return page6->getPage()[i - 256 * pag];
    }
    else {
        fifo(i);
        return this[0][i - 256 * pag];
    }
}


int PagedArray::getLength() {
    return length;
}