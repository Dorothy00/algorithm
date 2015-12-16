#include "FPTree.h"
#include <string>
#include <sstream>
#include <algorithm>

FPTree::FPTree(string filename, int minSupport)
{
    this -> file = filename;
    this -> minSupport = minSupport;
    this -> root = NewNode("$", 0);
}

FPNode* FPTree::NewNode(string data, int support)
{
    FPNode *node = new FPNode();
    FPData *fpData = new FPData();
    fpData -> data = data;
    fpData -> support = support;
    node -> fpData = fpData;
    node -> siblings = NULL;
    node -> childs = NULL;
    node -> parent = NULL;
    return node;
}

FPItem* FPTree::NewItem(string itemData, int support)
{
    FPItem *fpItem = new FPItem();
    fpItem -> itemData = itemData;
    fpItem -> support = support;
    return fpItem;
}

FPNode* FPTree::GetFPRoot()
{
    return root;
}

void FPTree::SetFPRoot(FPNode *root)
{
    this -> root = root;
}

void FPTree::GenerateFPItems()
{
    ifstream fin(file);
    string key;
    while(fin >> key)
    {
        if(fpMap.count(key) > 0)
        {
            fpMap[key]++;
        }else
        {
            fpMap[key] = 1;
        }
    }
    fin.close();
    
    // 需满足最小支持度
    for(unordered_map<string, int>::const_iterator i = fpMap.begin(); i != fpMap.end();)
    {
        if(i -> second < minSupport)
        {
            i = fpMap.erase(i);
        }else
        {
            i ++;
        }
    }
    
    for(unordered_map<string, int>::const_iterator i = fpMap.begin(); i != fpMap.end(); i++)
    {
        FPItem* fpItem = NewItem(i -> first, i -> second);
        fpItems.push_back(fpItem);
    }

    for(int i = 0; i < fpItems.size(); i++)
    {
        cout << fpItems[i] -> itemData << ": " << fpItems[i] -> support << endl;
    }
    cout << "=======\n";
    sort(fpItems.begin(), fpItems.end(),[](FPItem* l, FPItem* r){if(l -> support == r -> support)
    {
        return stoi(l -> itemData) < stoi(r -> itemData);
    }return l -> support > r -> support;});
    for(int i = 0; i < fpItems.size(); i++)
    {
        cout << fpItems[i] -> itemData << ": " << fpItems[i] -> support << endl;
    }
}


void FPTree::OutPut()
{
    GenerateFrequentItemSets(root, NULL, fpItems);
}

void FPTree::GenerateFrequentItemSets(FPNode* fpNode, ItemSet* itemSet, vector<FPItem*> fpItems)
{
    if(fpNode == NULL)
    {
        return;
    }
    // 单个路径
    if(fpNode -> childs != NULL && fpNode -> childs -> siblings == NULL)
    {
        ItemSet itemSetA;
        FPNode* child = fpNode -> childs;
        while(child != NULL)
        {
            itemSetA.item.push_back(child -> fpData -> data);
            if(itemSetA.support > child -> fpData -> support)
            {
                itemSetA.support = child -> fpData -> support;
            }
            child = child -> childs;
        }
        combination(&itemSetA, itemSet, (int)itemSetA.item.size());
    }
    else
        if(fpNode -> childs == NULL && itemSet -> item.size() >=2)
    {
        for(int i = 0; i < itemSet -> item.size(); i++)
        {
            cout << itemSet -> item[i] << " ";
        }
        cout << endl;
    }
    else
    {
        for(int i = (int)fpItems.size() - 1; i >= 0; i--)
        {
            ItemSet itemSetB;
            string data = fpItems[i] -> itemData;
            itemSetB.item.push_back(data);
            itemSetB.support = fpItems[i] -> support;
            if(itemSet != NULL)
            {
                for(int j = 0; j < itemSet -> item.size(); j++)
                {
                    itemSetB.item.push_back(itemSet -> item[j]);
                }
            }
            FPNode* root = NewNode("$", 0);
            vector<FPItem*> childFpItems;
            BuildConditionFPItems(fpItems[i], childFpItems);
            BuildConditionTree(fpItems[i], &root, childFpItems);
            GenerateFrequentItemSets(root, &itemSetB, childFpItems);
        }
    }
}


void FPTree::BuildConditionTree(FPItem* fpItem, FPNode** root, vector<FPItem*>& childFpItems)
{
    vector<FPNode*> fpNodes = fpItem -> fpNodes;
    list<FPData*> path;
    for(int i = 0; i < fpNodes.size(); i++)
    {
        FPNode* fpNode = fpNodes[i];
        while(fpNode -> parent != NULL && fpNode -> parent -> fpData -> data != "$")
        {
            FPData* fpData = new FPData();
            fpData -> data = fpNode -> parent -> fpData -> data;
            fpData -> support = fpNodes[i] -> fpData -> support;
            path.push_back(fpData);
            fpNode = fpNode -> parent;
        }
        unordered_map<string, int> map = fpMap;
        path.sort([&map](FPData* l, FPData* r){if(l -> support == r -> support)
        { return map[l -> data] > map[r -> data];}
        return l -> support > r -> support;});
        for(list<FPData*>::iterator pathIt = path.begin(); pathIt != path.end();)
        {
            bool flag = false;
            for(vector<FPItem*>::iterator itemIt = childFpItems.begin(); itemIt != childFpItems.end(); itemIt++)
            {
                if((*pathIt) -> data == (*itemIt) -> itemData)
                {
                    flag = true;
                    break;
                }
            }
            if(flag)
            {
                pathIt++;
            }else
            {
                pathIt = path.erase(pathIt);
            }
        }
        InsertFPPath(*root, path,childFpItems);
        path.clear();
    }
}

void FPTree::BuildConditionFPItems(FPItem *fpItem,vector<FPItem *>& childFpItems)
{
    if(fpItem == NULL)
    {
        return;
    }
    unordered_map<string, int> childMap;
    vector<FPNode*> fpNodes = fpItem -> fpNodes;
    for(int i = 0; i < fpNodes.size(); i++)
    {
        FPNode* fpNode = fpNodes[i];
        while(fpNode -> parent != NULL && fpNode -> parent -> fpData -> data != "$")
        {
            string key = fpNode -> parent -> fpData -> data;
            if(childMap.count(key) > 0)
            {
                childMap[key] += fpNodes[i] -> fpData -> support;
            }else
            {
                childMap[key] = fpNodes[i] -> fpData -> support;
            }
            fpNode = fpNode -> parent;
        }
    }
    
    for(unordered_map<string, int>::const_iterator i = childMap.begin(); i != childMap.end();)
    {
        if(i -> second < minSupport)
        {
            i = childMap.erase(i);
        }else
        {
            i ++;
        }
    }
    
    for(unordered_map<string, int>::const_iterator i = childMap.begin(); i != childMap.end(); i++)
    {
        FPItem* fpItem = NewItem(i -> first, i -> second);
        childFpItems.push_back(fpItem);
    }
    
}

void FPTree::test()
{
    ItemSet itemsetA;
    itemsetA.item.push_back("2");

    ItemSet itemsetB;
    itemsetB.item.push_back("1");
    itemsetB.item.push_back("3");
    combination(&itemsetA, &itemsetB, 1);
}

void FPTree::printEachResult(ItemSet* itemSetA, ItemSet* itemSetB, int index, int total){
    bool flag = true;
    for(int i = 0; i < total; ++i){
        if(((index>>i)&1) == 1){
            cout << itemSetA -> item[i] << " ";
            flag = false;
        }
    }
    if(flag && itemSetB != NULL && itemSetB -> item.size() < 2)
    {
        return;
    }
    if(itemSetB != NULL)
    {
        for(int i = 0; i < itemSetB -> item.size(); i++)
        {
            cout << itemSetB -> item[i] << " ";
        }
    }

    cout << endl;
}

void FPTree::combination(ItemSet* itemSetA, ItemSet* itemSetB, int count){
    if(count == 0  && itemSetB != NULL && itemSetB -> item.size() >=2)
    {
        for(int i = 0; i < itemSetB -> item.size(); i++)
        {
            cout << itemSetB -> item[i] << " ";
        }
        return;
    }
    for(int i = 0; i < (1<<count); ++i){
        printEachResult(itemSetA, itemSetB, i, count);
    }
}

void FPTree::BuildFPTree()
{
    BuildFPPath();
    for(list<list<FPData*>>::iterator it = fpPaths.begin(); it != fpPaths.end(); it++)
    {
        InsertFPPath(root, (*it), fpItems);
    }
    cout << "\nItem========Item\n";
    for(int i = 0; i < fpItems.size(); i++)
    {
        FPItem* fpItem = fpItems[i];
        vector<FPNode*> fpNodes = fpItem -> fpNodes;
        for(int j = 0; j < fpNodes.size(); j++)
        {
            cout << fpNodes[j] -> fpData -> data << " ";
        }
        cout << "\n";
    }
}

void FPTree::InsertFPPath(FPNode* root, list<FPData*> fpDatas, vector<FPItem*>& fpItems)
{
    if(fpDatas.size() <= 0)
    {
        return;
    }
    bool flag = true;
    FPNode* child = root -> childs;
    while(child != NULL)
    {
        if(child -> fpData -> data == fpDatas.front() -> data)
        {
            flag = false;
            child -> fpData -> support ++;
            fpDatas.pop_front();
            InsertFPPath(child, fpDatas, fpItems);
            return;
        }
        child = child -> siblings;
    }
    if(flag)
    {
        FPData* firstData = fpDatas.front();
        FPNode* newChild = NewNode(firstData -> data, firstData -> support);
        newChild -> parent = root;
        for(int i = 0; i < fpItems.size(); i++)
        {
            string d = fpItems[i] -> itemData;
            string d2 = newChild -> fpData -> data;
            if(d == d2)
            {
                fpItems[i] -> fpNodes.push_back(newChild);
               // cout << "find ";
                break;
            }
        }
        if(root -> childs == NULL)
        {
            root -> childs = newChild;
        }else
        {
            FPNode** slibling = &root -> childs -> siblings;
            while(*slibling != NULL)
            {
                slibling = &(*slibling) -> siblings;
            }
            *slibling = newChild;
        }
        newChild -> parent = root;
        fpDatas.pop_front();
        
        if(fpDatas.size() > 0)
        {
            InsertFPPath(newChild, fpDatas, fpItems);
        }
    }
}

void FPTree::BuildFPPath()
{
    ifstream fin(file);
    string line;
    int i = 0;
    while(getline(fin, line))
    {
        i ++;
        list<FPData*> path;
        unordered_map<string, int> elemenetMap;
        istringstream iss(line);
        string key;
        while(iss >> key)
        {
            if(fpMap.count(key) > 0)
            {
                if(elemenetMap.count(key) > 0)
                {
                    elemenetMap[key] ++;
                }else
                {
                    elemenetMap[key] = 1;
                }
                FPData* fpData = new FPData();
                fpData -> data = key;
                fpData -> support = fpMap[key];
                path.push_back(fpData);
            }
            
        }
        path.sort([](FPData* l, FPData* r){return l -> support > r -> support;});
        cout << "line " << i << ":\n";
        for(list<FPData*>::iterator it = path.begin(); it != path.end(); it++)
        {
            (*it) -> support = elemenetMap[(*it) -> data];
            cout << (*it) -> data << ": " << (*it)->support << " ";
        }
        cout << endl;
        fpPaths.push_back(path);
    }
    fin.close();
}

