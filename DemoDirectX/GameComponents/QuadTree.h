#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include <fstream>
#include "Camera.h"
#include "../GameObjects/Entity.h"
using namespace std;
class QuadTree
{
public:

    QuadTree(int level, int node, RECT bound, char *fileQuadTree);
    ~QuadTree();
    void Clear();
    void insertEntity(Entity *entity, int id);
	void Save(int node, int id);
    
    /*lay danh sach nhung Entity co kha nang xay ra va cham
    tra ve danh sach cac phan tu nam trong vung va cham */
    void getEntitiesCollideAble(std::vector<Entity*> &entitiesOut,Entity *entity); 

    void getAllEntities(std::vector<Entity*> &entitiesOut);

    int getTotalEntities();

    RECT Bound;

protected:
	ofstream fileQuadTree;
	char *nameFileQuadTree;
    QuadTree *Nodes;
    std::vector<Entity*> mListEntity; //danh sach cac phan tu co trong vung va cham (Bound)

    /*lay vi tri cua Entity 
    1: nam trong Node con goc trai tren
    2: nam trong Node con goc phai tren
    3: nam trong Node con goc trai duoi
    4: nam trong Node con goc phai duoi
    0: bi dinh > 2 node con*/
    int getIndex(RECT body);

    void split(int index); //thuc hien chia ra cac node

    bool isContain(Entity *entity);
    int mLevel; //tuong ung voi so node
	int mNode;
};