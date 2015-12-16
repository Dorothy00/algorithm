#include "FPTree.h"

int main(int argc, char **argv) {
    FPTree *tree = new FPTree("test.txt", 2);
    tree -> GenerateFPItems();
    tree -> BuildFPTree();
    cout << "\n******************\n";
   // tree -> test();
    tree -> OutPut();
    return 0;
}


