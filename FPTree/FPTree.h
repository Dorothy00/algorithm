#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

struct FPData
{
    string data;
    int support;
};

struct FPNode
{
    FPData *fpData;
    FPNode *parent;
    FPNode* siblings;
    FPNode* childs;
};

struct FPItem
{
    string itemData;
    int support;
    vector<FPNode*> fpNodes;
};

struct ItemSet
{
    int support;
    vector<string> item;
};


class FPTree
{
public:
    FPTree(string filename, int minSupport);
    FPNode* NewNode(string data, int support);
    FPItem* NewItem(string itemData, int support);
    FPNode* GetFPRoot();
    void SetFPRoot(FPNode* root);
    void BuildFPTree();
    void BuildFPPath();
    void InsertFPPath(FPNode* root, list<FPData*> fpDatas,vector<FPItem*>& fpItems);
    void GenerateFPItems();
    void GenerateFrequentItemSets(FPNode* fpNode, ItemSet* itemSet, vector<FPItem*> fpItems);
    void printEachResult(ItemSet* itemSetA, ItemSet* itemSetB, int index, int total);
    void combination(ItemSet* itemSetA, ItemSet* itemSetB,int count);
    void BuildConditionTree(FPItem* fpItem, FPNode** root, vector<FPItem*>& fpItems);
    void BuildConditionFPItems(FPItem* fpItem, vector<FPItem*>& fpItems);
    void OutPut();
    void test();
private:
    FPNode* root;
    vector<FPItem*> fpItems;
    unordered_map<string, int> fpMap;
    list<list<FPData*> > fpPaths;
    string file;
    int minSupport;
    
};



