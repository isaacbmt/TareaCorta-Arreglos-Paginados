//
// Created by Isaac Benavides on 26/8/18.
//

#include <math.h>
#include "Sort.h"

void Sort::swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void Sort::quicksort(PagedArray *array, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = array[0][(left + right) / 2];

    while (i <= j) {
        while (array[0][i] < pivot)
            i++;
        while (array[0][j] > pivot)
            j--;
        if (i <= j) {


            tmp = array[0][i];
            array[0][i] = array[0][j];
            array[0][j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quicksort(array, left, j);
    if (i < right)
        quicksort(array, i, right);
}



//int Sort::particion(PagedArray *pagedArray, int menor, int mayor, int pagMenor, int pagMayor) {
//    int pivot = pagedArray[0][pagMayor][mayor];
//    int i = (menor - 1);
//
//    for (int k = pagMenor; k < 6; ++k) {
//        for (int j = menor; j < mayor; j++) {
//            if (pagedArray[0][k][j] <= pivot){
//                swap(&pagedArray[0][k][i], &pagedArray[0][pagMayor][j]);
//                i++;
//                if (i >= 256) i = 0;
//            }
//        }
//    }
//
//    swap(&pagedArray[0][pagMenor][i + 1], &pagedArray[0][pagMayor][mayor]);
//  //  cout << "i: " << i + 1 << "  ";
//    return (i + 1);
//}
//
//void Sort::quicksort(PagedArray *pagedArray, int menor, int mayor, int pagMenor, int pagMayor) {
//    if (pagMenor < pagMayor){
//        int part = particion(pagedArray, menor, mayor, pagMenor, pagMayor);
//
//        int controlSubtr = part - 1, controlPlus = part + 1;
//
////        quicksort(pagedArray, controlPlus, mayor, pagMenor, pagMenor);
////        quicksort(pagedArray, menor, controlSubtr, pagMenor, pagMenor);
//////
//        if (controlSubtr <= -1){
//     //       cout << "Entre a resta" << endl;
//            quicksort(pagedArray, menor, 255, pagMenor, pagMayor - 1);
//        }
//        else if (controlPlus >= 256) {
//      //      cout << "Entre a suma" << endl;
//            quicksort(pagedArray, 0, mayor, pagMenor + 1, pagMayor);
//        }
//        else {
//            quicksort(pagedArray, controlPlus, mayor, pagMenor, pagMayor);
//            quicksort(pagedArray, menor, controlSubtr, pagMenor, pagMayor);
//
//        }
//    }
//
////    cout << "Mayor: " << pagMayor << "  Menor: " << pagMenor << "  Particion: "  << endl;
//
//}