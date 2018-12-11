#include "QuadTree.h"
#include "GameGlobal.h"

QuadTree::~QuadTree()
{
}

QuadTree::QuadTree(int level, int node, RECT bound, char *fileQuadTree)
{
	//chia lam 4

	this->Bound = bound;
	this->mLevel = level;
	nameFileQuadTree = fileQuadTree;
	mNode = node;
}

void QuadTree::Clear()
{
    if (Nodes)
    {
        for (size_t i = 1; i < 5; i++)
        {
            /*if (Nodes[i])
            {
                Nodes[i]->Clear();
                delete Nodes[i];
                Nodes[i] = nullptr;
            }*/
        }

        delete[] Nodes;
    }
}

void QuadTree::insertEntity(Entity *entity, int id)
{
	if (this->mLevel < 5) {
		int index = getIndex(entity->GetBound());

		//neu node cha ton tai thi insert vao node con
		if (Nodes != NULL)
		{
			if (index != 0)
			{
				Nodes->insertEntity(entity,id);
				return;
			}
		}

		//luc nay entity nam giua 2 Bound nen se add vao node nay luon
		if (index == 0 /*|| this->mLevel==10*/)		//Add node cha và dừng đệ quy
		{
			Save(mNode, id );
			this->mListEntity.push_back(entity);
			return;
		}
		else
		{
			//node chua dc tao nen se tao va split roi moi insert
			if (Nodes == NULL)
			{
				split(index);
			}
			Nodes->insertEntity(entity,id);
		}
	}
	else {
		//Save(mNode,id);
		this->mListEntity.push_back(entity);
	}
		
}

void QuadTree::Save(int node, int id)
{
	fileQuadTree.open(nameFileQuadTree, ios::out | ios::app);	//app :ghi thêm vào
	fileQuadTree << node;
	fileQuadTree << "\t";
	fileQuadTree << this->Bound.left;
	fileQuadTree << "\t";
	fileQuadTree << this->Bound.top;
	fileQuadTree << "\t";
	fileQuadTree << this->Bound.right;
	fileQuadTree << "\t";
	fileQuadTree << this->Bound.bottom;
	fileQuadTree << "\t";
	fileQuadTree << id;
	fileQuadTree << "\n";
	fileQuadTree.close();
}

bool QuadTree::isContain(Entity *entity)
{
    RECT r = entity->GetBound();

    if (r.left >= Bound.left && r.right <= Bound.right && r.top >= Bound.top && r.bottom <= Bound.bottom)
    {
        return true;
    }

    return false;
}

void QuadTree::split(int index)
{
    //cat phan region (ranh gioi) ra thanh 4 phan bang nhau
    //Nodes = new QuadTree * [5];

    RECT bound;

    int width = (Bound.right - Bound.left) / 2;
    int height = (Bound.bottom - Bound.top) / 2;

	switch (index)
	{
	case 1:
		//phan goc trai tren
		bound.left = Bound.left;
		bound.right = Bound.left + width;
		bound.top = Bound.top;
		bound.bottom = Bound.top + height;
		mNode = mNode * 10 + 1;
		Nodes = new QuadTree(mLevel + 1, mNode, bound, nameFileQuadTree);
		break;
	case 2:
		//phan goc phai tren
		bound.left = Bound.left + width;
		bound.right = Bound.right;
		bound.top = Bound.top;
		bound.bottom = Bound.top + height;
		mNode = mNode * 10 + 2;
		Nodes = new QuadTree(mLevel + 1, mNode, bound, nameFileQuadTree);
		break;
	case 3: 
		//phan goc trai duoi
		bound.left = Bound.left;
		bound.right = Bound.left + width;
		bound.top = Bound.top + height;
		bound.bottom = Bound.bottom;
		mNode = mNode * 10 + 3;
		Nodes = new QuadTree(mLevel + 1, mNode, bound, nameFileQuadTree);
		break;
	case 4:
		//phan goc phai duoi
		bound.left = Bound.left + width;
		bound.right = Bound.right;
		bound.top = Bound.top + height;
		bound.bottom = Bound.bottom;
		mNode = mNode * 10 + 4;
		Nodes = new QuadTree(mLevel + 1, mNode, bound, nameFileQuadTree);
		break;
	default:
		break;
	}
}

int QuadTree::getTotalEntities()
{
    int total = mListEntity.size();

    if (Nodes)
    {
        /*for (size_t i = 1; i < 5; i++)
        {
            total += Nodes[i]->getTotalEntities();
        }*/
    }

    return total;
}

int QuadTree::getIndex(RECT body)
{
    /*lay vi tri cua Entity
    1: nam trong Node con goc trai tren
    2: nam trong Node con goc phai tren
    3: nam trong Node con goc trai duoi
    4: nam trong Node con goc phai duoi
    0: bi dinh > 2 node con*/

    float middleVerticle = Bound.left + (Bound.right - Bound.left) / 2.0f;
    float middleHorizontal = Bound.top + (Bound.bottom - Bound.top) / 2.0f;

    if (body.top > Bound.top &&  body.bottom < middleHorizontal)
    {
        //nam phia ben tren
        if (body.left > Bound.left && body.right < middleVerticle)
        {
            //nam phia ben trai
			if (this->mLevel!=0)		// sữa lỗi thừa số 1 lúc đầu	
            return 1;
        }
        else if (body.left > middleVerticle && body.right < Bound.right)
        {
            //nam phia ben phai
            return 2;
        }
    }
    if(body.top > middleHorizontal && body.bottom < Bound.bottom)
    {
        //nam phia ben duoi
        if (body.left > Bound.left && body.right < middleVerticle)
        {
            //nam phia ben trai
            return 3;
        }
        else if (body.left > middleVerticle && body.right < Bound.right)
        {
            //nam phia ben phai
            return 4;
        }
    }
	//mNode = mNode * 10 ;
    return 0;
}

void QuadTree::getAllEntities(std::vector<Entity*> &entitiesOut)
{
    for (auto child : mListEntity)
    {
        entitiesOut.push_back(child);
    }

    if (Nodes)
    {
        for (size_t i = 1; i < 5; i++)
        {
            Nodes->getAllEntities(entitiesOut);
        }
    }
}

//Hàm chính được gọi, đọc file quadtree
void QuadTree::getEntitiesCollideAble(std::vector<Entity*> &entitiesOut, Entity *entity)
{
    int index = this->getIndex(entity->GetBound());

    if (index !=0)
    {
        //nhung Entity o day se la nam tren 2 node con nen chung ta cung se lay de set va cham
        for (auto child : mListEntity)
        {
            entitiesOut.push_back(child);
        }

        if (Nodes != NULL)
        {
            //kiem tra va lay cac node trong node con
            Nodes->getEntitiesCollideAble(entitiesOut, entity);
        }
    }
    else
    {
        getAllEntities(entitiesOut);
    }
}