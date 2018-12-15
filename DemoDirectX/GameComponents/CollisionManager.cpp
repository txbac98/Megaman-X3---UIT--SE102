#include "CollisionManager.h"
#include "../Constant.h"
//#include "Simon.h"

CollisionManager* CollisionManager::instance = 0;
CollisionManager* CollisionManager::getInstance()
{
	if (instance == 0)
		instance = new CollisionManager();
	return instance;
}

//RECT CollisionManager::getBroadphaseBox(Box & M)
//{
//	/*float x, y, w, h;
//	x = M.dx > 0 ? M.x : M.x + M.dx;
//	y = M.dy > 0 ? M.y : M.y + M.dy;
//	w = M.dx > 0 ? M.width + M.dx : M.width - M.dx;
//	h = M.dy > 0 ? M.height + M.dy : M.height - M.dy;
//	RECT broadphasebox(x, y, w, h);
//
//	return broadphasebox;*/
//}
RECT CollisionManager::getBroadphaseRect(Entity* object, float deltaTime)
{
	// vận tốc mỗi frame
	auto velocity = D3DXVECTOR2(object->GetVx()*deltaTime, object->GetVy()*deltaTime);
	auto myRect = object->GetBound();

	RECT rect;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.top = velocity.y > 0 ? myRect.top : myRect.top + velocity.x;
	rect.bottom = velocity.y > 0 ? myRect.bottom + velocity.y : myRect.bottom - velocity.y;
	
	rect.right = velocity.x > 0 ? myRect.right + velocity.x : myRect.right - velocity.x;

	return rect;
}
RECT CollisionManager::getCollisionRect(RECT rectM, RECT rectS)
{
	RECT result;

	//chon max Left
	result.left = rectM.left > rectS.left ? rectM.left : rectS.left;
	//chon max right
	result.right = rectM.right < rectS.right ? rectM.right : rectS.right;
	//chon min bottom
	result.bottom = rectM.bottom < rectS.bottom ? rectM.bottom : rectS.bottom;
	//chon max top
	result.top = rectM.top > rectS.top ? rectM.top : rectS.top;

	return result;
}
bool CollisionManager::AABBCheck(RECT & rectM, RECT & rectS)
{
	return (rectM.bottom >= rectS.top && rectM.top <= rectS.bottom && rectM.left <= rectS.right && rectM.right >= rectS.left);
}
Entity::SideCollisions CollisionManager::getSideCollision(Entity *M, Entity *S)
{
	RECT rect1 = M->GetBound();
	RECT rect2 = S->GetBound();

	float w = (M->GetWidth() + S->GetWidth()) / 2.0f;
	float h = (M->GetHeight() + S->GetHeight()) / 2.0f;

	float dx = M->GetPosition().x - S->GetPosition().y;
	float dy = M->GetPosition().x - S->GetPosition().y;

	if (abs(dx) <= w && abs(dy) <= h)
	{
		/* co va cham*/
		float wy = w * dy;
		float hx = h * dx;

		if (wy > hx)
		{
			if (wy > -hx)
			{
				/*va cham phia tren M*/
				return Entity::Top;
			}
			else
			{
				/*va cham phia ben phai M*/
				return Entity::Right;
			}
		}
		else if (wy > -hx)
		{
			/*va cham ben trai M*/
			return Entity::Left;
		}
		else
		{
			/*va cham phia duoi M*/
			return Entity::Bottom;
		}
	}
}
float CollisionManager::sweptAABB(Entity * M, Entity * S, Entity::SideCollisions& side,float deltaTime)
{
	side = Entity::SideCollisions::NotKnow;
	
	float dxEntry, dyEntry;
	float dxExit, dyExit;

	D3DXVECTOR2 velocityM = D3DXVECTOR2(M->GetVx()*deltaTime , M->GetVy()*deltaTime );
	D3DXVECTOR2 velocityS = D3DXVECTOR2(S->GetVx()*deltaTime , S->GetVy()*deltaTime);
	D3DXVECTOR2 velocity = velocityM-velocityS;

	RECT rectM = M->GetBound();
	RECT rectS = S->GetBound();

	if (velocity.x > 0.0f)
	{
		dxEntry = rectS.left - rectM.right;
		dxExit = rectS.right - rectM.left;
	}
	else
	{
		dxEntry = rectS.right - rectM.left;
		dxExit = rectS.left - rectM.right;
	}

	if (velocity.y > 0.0f)
	{
		dyEntry = rectS.top - rectM.bottom;
		dyExit = rectS.bottom - rectM.top;
	}
	else
	{
		dyEntry = rectS.bottom - rectM.top;
		dyExit = rectS.top - rectM.bottom;
	}

	float txEntry, tyEntry;
	float txExit, tyExit;

	if (velocity.x == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / velocity.x;
		txExit = dxExit / velocity.x;
	}

	if (velocity.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / velocity.y;
		tyExit = dyExit / velocity.y;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	//	if (entryTime > exitTime || txEntry < 0.0f && yEntry < 0.0f || txEntry > 1.0f || yEntry > 1.0f)
	if (entryTime > exitTime || txEntry > 1.0f || tyEntry > 1.0f)
	{
		side = Entity::SideCollisions::NotKnow;
		return 1.0f;
	}
	else
	{
		RECT rect = getCollisionRect(rectM, rectS);

		//Position collision rect
		float xCenter = rect.left + (rect.right - rect.left) / 2.0f;
		float yCenter = rect.top + (rect.bottom - rect.top) / 2.0f;

		D3DXVECTOR2 cCenter = D3DXVECTOR2(xCenter, yCenter);

		//Position Object M
		D3DXVECTOR2 eCenter = M->GetPosition();

		//lay vector noi tam Entity va CollisionRect
		D3DXVECTOR2 vec = cCenter - eCenter;

		//chuan hoa vector
		D3DXVec2Normalize(&vec, &vec);


		if (vec.y < 0)
		{
			//va cham phia ben tren
			//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
			if (vec.x <= 0.35f && vec.x >= -0.35f)
			{
				side= Entity::Top;
			}
			else if (vec.x > 0.35f && vec.x < 0.8f)
			{
				//goc trong khoang 35 -> 70 phia ben top - right
				side= Entity::TopRight;
			}
			else if (vec.x >= 0.8f)
			{
				side= Entity::Right;
			}
			else if (vec.x < -0.35f && vec.x >= -0.8f)
			{
				//va cham phia top - left
				side= Entity::TopLeft;
			}
			else
			{
				side= Entity::Left;
			}
		}
		else
		{
			//va cham phia ben duoi
			//lay cos cua goc neu ma nam trong khoang goc 70 -> 110 thi va cham top
			if (vec.x <= 0.35f && vec.x >= -0.35)
			{
				side= Entity::Bottom;
			}
			else if (vec.x > 0.35 && vec.x < 0.8)
			{
				//goc trong khoang 35 -> 70 phia ben top - right
				side= Entity::BottomRight;
			}
			else if (vec.x >= 0.8)
			{
				side= Entity::Right;
			}
			else if (vec.x < -0.35f && vec.x > -0.8f)
			{
				//va cham phia top - left
				side= Entity::BottomLeft;
			}
			else
			{
				side= Entity::Left;
			}
		}


		////Thời gian va chạm x lớn hơn y
		//if (txEntry > tyEntry)
		//{
		//	//Khoảng cách giữa 2 rect
		//	if (dxEntry < 0.0f)
		//	{
		//		side = Entity::SideCollisions::Left;				
		//	}
		//	else
		//	{
		//		side = Entity::SideCollisions::Right;
		//	}
		//}
		//else
		//{

		//	if (dyEntry < 0.0f)
		//	{
		//		side = Entity::SideCollisions::Bottom;
		//	}
		//	else
		//	{
		//		side = Entity::SideCollisions::Top;
		//	}
		//}

		/*if (rectM.left <= rectS.right && rectM.right >= rectS.left 
			|| rectS.left <= rectM.right && rectS.right >= rectM.left)
		{
			if (dyEntry > 0)
				side = Entity::SideCollisions::Bottom;
			else
				side = Entity::SideCollisions::Top;
		}
		if (rectM.top <= rectS.bottom && rectM.bottom >= rectS.top
			|| rectS.top <= rectM.bottom && rectS.bottom >= rectM.top)
		{
			if (dxEntry > 0)
				side = Entity::SideCollisions::Right;
			else
				side = Entity::SideCollisions::Left;
		}*/
		return entryTime;
	}
}

void CollisionManager::checkCollision(Entity * M, Entity * S, float deltaTime)
{
	/*if (!S->alive || !M->alive)
		return;*/

	RECT rectM = M->GetBound();
	RECT rectS = S->GetBound();

	/*if (AABBCheck(rectM, rectS))
	{
		M->OnAABBCheck(S);
		S->OnAABBCheck(M);
	}*/
	RECT broadPhase = getBroadphaseRect(M,deltaTime);
	if (AABBCheck(broadPhase, rectS))
	{
		//if (AABBCheck(rectM, rectS))
		//{
		//	M->OnAABBCheck(S);
		//	S->OnAABBCheck(M);

		////	M->vx += S->vx;
		////	M->vy += S->vy;

		//	//return;
		//}
		Entity::SideCollisions side;
		float sweptTime = sweptAABB(M, S, side,deltaTime);
		if (sweptTime < 1.0f)
		{
			//RECT rectIntersection = getCollisionRect(rectM, rectS);
			M->OnCollision(S, side);
			S->OnCollision(M, side);
			//preventMove(M, S);
		}
	}
}

void CollisionManager::preventMove(Entity * M, Entity * S)
{
	RECT rectM = M->GetBound();
	RECT rectS = S->GetBound();
	if (rectM.top < rectS.bottom && rectM.bottom > rectS.top && M->vx != 0)
	{
		M->isCollision = true;
		if (M->vx > 0)
			M->vx = rectS.left - rectM.right;
		else
			M->vx = rectS.right - rectM.left;
		return;
	}

	if (rectM.left < rectS.right && rectM.right > rectS.left && M->vy != 0)
	{
		M->isCollision = true;
		if (M->vy > 0)
			M->vy = rectS.top - rectM.bottom;
		else
			M->vy = rectS.bottom - rectM.top;
		return;
	}

	M->isCollisionCross = true;
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}