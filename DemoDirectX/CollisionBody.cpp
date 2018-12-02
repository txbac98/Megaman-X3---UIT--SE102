#include "CollisionBody.h"

CollisionBody::CollisionBody( Entity * target)
{
	_target = target;

	_collisionBodyRect.top = 0;
	_collisionBodyRect.left = 0;
	_collisionBodyRect.right = abs(_target->GetBound().left - _target->GetBound().right);
	_collisionBodyRect.left = abs(_target->GetBound().top - _target->GetBound().bottom);
}

CollisionBody::CollisionBody( Entity * target, RECT bodyRect)
{
	_target = target;
	_collisionBodyRect = bodyRect;
}

CollisionBody::~CollisionBody()
{

}

void CollisionBody::checkCollision( Entity * otherObject, float dt, bool updatePosition)
{
	// Entity::SideCollisions direction;
	//float time = isCollide(otherObject, direction, dt);

	//if (time < 1.0f)
	//{
	//	if (otherObject->GetPhysicsSide() !=  Entity::SideCollisions::NONE && (direction & otherObject->GetPhysicsBodySide()) == direction)
	//	{
	//		// cập nhật tọa độ
	//		updateTargetPosition(otherObject, direction, true);
	//	}

	//	/*CollisionEventArg* e = new CollisionEventArg(otherObject);
	//	e->_sideCollision = direction;

	//	__raise onCollisionBegin(e);

	//	_listColliding[otherObject] = true;*/
	//}
	//else if (_listColliding.find(otherObject) == _listColliding.end())	// ko có trong list đã va chạm
	//{
	//	if (isColliding(_target->GetBound(), otherObject->GetBound()))
	//	{
	//		CollisionEventArg* e = new CollisionEventArg(otherObject);
	//		e->_sideCollision = this->getSide(otherObject);

	//		__raise onCollisionBegin(e);

	//		_listColliding[otherObject] = true;
	//	}
	//}
	//else	// có trong list đã va chạm
	//{
	//	float moveX, moveY;
	//	if (isColliding(otherObject, moveX, moveY, dt))		// kt va trạm lấy khoảng chồng lấp của 2 object
	//	{
	//		auto side = this->getSide(otherObject);

	//		if (otherObject->GetPhysicsBodySide() ==  Entity::SideCollisions::NONE || (side & otherObject->GetPhysicsBodySide()) != side)
	//			return;

	//		// cập nhật tọa độ
	//		if (updatePosition)
	//			updateTargetPosition(otherObject, side, false, D3DXVECTOR2(moveX, moveY));
	//	}
	//	else // nếu ko va chạm nữa là kết thúc va chạm
	//	{
	//		CollisionEventArg* e = new CollisionEventArg(otherObject);
	//		e->_sideCollision =  Entity::SideCollisions::NONE;

	//		__raise onCollisionEnd(e);
	//		_listColliding.erase(otherObject);
	//	}
	//}

}

bool CollisionBody::checkCollision( Entity * otherObject,  Entity::SideCollisions & direction, float dt, bool updatePosition)
{
	float time = isCollide(otherObject, direction, dt);

	if (time < 1.0f)
	{
		/*if (otherObject->GetPhysicsBodySide() !=  Entity::SideCollisions::NONE && (direction & otherObject->GetPhysicsBodySide()) == direction)
		{
			updateTargetPosition(otherObject, direction, true);
		}*/

		return true;
	}
	//else
	//{
	//	float moveX, moveY;
	//	if (isColliding(otherObject, moveX, moveY, dt))
	//	{
	//		//auto side = this->getSide(otherObject);
	//		//direction = side;

	//		//if (otherObject->GetPhysicsBodySide() ==  Entity::SideCollisions::NONE || (side & otherObject->GetPhysicsBodySide()) != side)
	//		//	return true;

	//		//// cập nhật tọa độ
	//		//if (updatePosition)
	//		//	updateTargetPosition(otherObject, direction, false, D3DXVECTOR2(moveX, moveY));

	//		return true;
	//	}
	//}

	direction =  Entity::SideCollisions::NotKnow;

	return false;
}

//Swept AABB
float CollisionBody::isCollide( Entity * otherSprite,  Entity::SideCollisions & direction, float dt)
{
	RECT myRect = _target->GetBound();
	RECT otherRect = otherSprite->GetBound();

	// sử dụng Broadphase rect để kt vùng tiếp theo có va chạm ko
	RECT broadphaseRect = getSweptBroadphaseRect(_target, dt);	// là bound của object được mở rộng ra thêm một phần bằng với vận tốc (dự đoán trước bound)
	if (!isColliding(broadphaseRect, otherRect))				// kiểm tra tính chồng lắp của 2 hcn
	{
		//direction =  Entity::SideCollisions::NONE;
		return 1.0f;
	}

	//SweptAABB
	// vận tốc mỗi frame
	D3DXVECTOR2 otherVeloc = D3DXVECTOR2(otherSprite->GetVx() , otherSprite->GetVy() );
	D3DXVECTOR2 myVelocity = D3DXVECTOR2(_target->GetVx() , _target->GetVy() );
	D3DXVECTOR2 velocity = myVelocity;

	if (otherVeloc != D3DXVECTOR2(0, 0))
	{
		velocity = myVelocity-otherVeloc;
	}

	// tìm khoảng cách giữa cạnh gần nhất, xa nhất 2 object dx, dy
	// dx
	if (velocity.x > 0)
	{
		_dxEntry = otherRect.left - myRect.right;
		_dxExit = (otherRect.right - myRect.left);
	}
	else
	{
		_dxEntry = (otherRect.right - myRect.left);
		_dxExit = (otherRect.left - myRect.right);
	}

	// dy
	if (velocity.y > 0)
	{
		_dyEntry = (otherRect.top - myRect.bottom);
		_dyExit = (otherRect.bottom - myRect.top);
	}
	else
	{
		_dyEntry = (otherRect.bottom - myRect.top);
		_dyExit = (otherRect.top - myRect.bottom);
	}

	// tìm thời gian va chạm 
	if (velocity.x == 0)
	{
		// chia cho 0 ra vô cực
		_txEntry = -std::numeric_limits<float>::infinity();
		_txExit = std::numeric_limits<float>::infinity();
	}

	else
	{
		_txEntry = _dxEntry / velocity.x;
		_txExit = _dxExit / velocity.x;
	}

	if (velocity.y == 0)
	{
		_tyEntry = -std::numeric_limits<float>::infinity();
		_tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_tyEntry = _dyEntry / velocity.y;
		_tyExit = _dyExit / velocity.y;
	}

	// thời gian va chạm
	// va chạm khi x và y CÙNG chạm => thời gian va chạm trễ nhất giữa x và y
	float tEntry = max(_txEntry, _tyEntry);
	// hết va chạm là 1 trong 2 x, y hết va chạm => thời gian sớm nhất để kết thúc va chạm
	float tExit = min(_txExit, _tyExit);

	// object không va chạm khi:
	// nếu thời gian bắt đầu va chạm hơn thời gian kết thúc va chạm
	// thời gian va chạm x, y nhỏ hơn 0 (chạy qua luôn, 2 thằng đang đi xa ra nhau)
	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm)

	if (tEntry > tExit || _txEntry < 0.0f && _tyEntry < 0.0f || _txEntry > 1.0f || _tyEntry > 1.0f)
	{
		// không va chạm trả về 1 đi tiếp bt
		direction =  Entity::SideCollisions::NotKnow;
		return 1.0f;
	}

	// nếu thời gian va chạm x lơn hơn y
	if (_txEntry > _tyEntry)
	{
		// xét x
		// khoảng cách gần nhất mà nhỏ hơn 0 nghĩa là thằng kia đang nằm bên trái object này => va chạm bên phải nó
		if (_dxEntry > 0.0f)
			//if(_dxExit < 0)
		{
			direction =  Entity::SideCollisions::RIGHT;
		}
		else
		{
			direction =  Entity::SideCollisions::LEFT;
		}
	}
	else
	{
		// xét y
		if (_dyEntry > 0.0f)
			//if(_dyExit < 0.0f)
		{
			direction =  Entity::SideCollisions::TOP;
		}
		else
		{
			direction =  Entity::SideCollisions::BOTTOM;
		}
	}

	return tEntry;
}

bool CollisionBody::isColliding( Entity * otherObject, float & moveX, float & moveY, float dt)
{
	moveX = moveY = 0.0f;
	auto myRect = _target->GetBound();
	auto otherRect = otherObject->GetBound();

	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// kt coi có va chạm không
	//  CÓ va chạm khi 
	//  left < 0 && right > 0 && top > 0 && bottom < 0
	//
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return false;

	// tính offset x, y để đi hết va chạm
	// lấy khoảng cách nhỏ nhất
	moveX = abs(left) < right ? left : right;
	moveY = top < abs(bottom) ? top : bottom;

	// chỉ lấy phần lấn vào nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

void CollisionBody::updateTargetPosition( Entity* otherObject,  Entity::SideCollisions direction, bool withVelocity, D3DXVECTOR2 move)
{
	if (withVelocity == true)
	{
		if (otherObject->GetPhysicsBodySide() !=  Entity::SideCollisions::NONE || (direction & otherObject->GetPhysicsBodySide()) == direction)
		{
			//auto v = _target->getVelocity();
			auto pos = _target->GetPosition();
			if (_txEntry > _tyEntry)
			{
				// xử lý cản left và right
				if (_txEntry < 1 && _txEntry > 0)
					pos.x += _dxEntry;
			}
			else
			{
				// xử lý cản top và bot
				if (_tyEntry < 1 && _tyEntry > 0)
					pos.y += _dyEntry;
			}
			_target->SetPosition(pos);
		}
	}
	else
	{
		if (move.y > 0 && (otherObject->GetPhysicsBodySide() &  Entity::SideCollisions::TOP) ==  Entity::SideCollisions::TOP && _target->GetVy() <= 0)
		{
			_target->AddPositionY( move.y);
		}
		else if (move.y < 0 && (otherObject->GetPhysicsBodySide() &  Entity::SideCollisions::BOTTOM) ==  Entity::SideCollisions::BOTTOM && _target->GetVy() >= 0)
		{
			_target->AddPositionY(  move.y);
		}

		if (move.x > 0 && (otherObject->GetPhysicsBodySide() &  Entity::SideCollisions::RIGHT) ==  Entity::SideCollisions::RIGHT && _target->GetVx() <= 0)
		{
			_target->AddPositionX( move.x);
		}
		else if (move.x < 0 && (otherObject->GetPhysicsBodySide() &  Entity::SideCollisions::LEFT) ==  Entity::SideCollisions::LEFT && _target->GetVx() >= 0)
		{
			_target->AddPositionX(  move.x);
		}
	}
}

bool CollisionBody::isColliding(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.bottom - myRect.top;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.top - myRect.bottom;

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

RECT CollisionBody::getSweptBroadphaseRect( Entity* object, float dt)
{
	// vận tốc của object
	auto velocity = D3DXVECTOR2(object->GetVx() * dt / 1000, object->GetVy() * dt / 1000);
	auto myRect = object->GetBound();

	RECT rect;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.right = velocity.y > 0 ? myRect.right + velocity.x : myRect.right;

	return rect;
}

 Entity::SideCollisions CollisionBody::getSide( Entity* otherObject)
{
	auto myRect = _target->GetBound();
	auto otherRect = otherObject->GetBound();

	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// kt va chạm
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return  Entity::SideCollisions::NONE;

	float minX;
	float minY;
	 Entity::SideCollisions sideY;
	 Entity::SideCollisions sideX;

	if (top > abs(bottom))
	{
		minY = bottom;
		sideY =  Entity::SideCollisions::BOTTOM;
	}
	else
	{
		minY = top;
		sideY =  Entity::SideCollisions::TOP;
	}


	if (abs(left) > right)
	{
		minX = right;
		sideX =  Entity::SideCollisions::RIGHT;
	}
	else
	{
		minX = left;
		sideX =  Entity::SideCollisions::LEFT;
	}


	if (abs(minX) < abs(minY))
	{
		return sideX;
	}
	else
	{
		return sideY;
	}
}

RECT CollisionBody::getCollisionRect()
{
	RECT rect;

	rect.top = _target->GetBound().top - _collisionBodyRect.top;
	rect.left = _target->GetBound().left + _collisionBodyRect.left;

	rect.bottom = rect.top - abs(_collisionBodyRect.top - _collisionBodyRect.bottom);
	rect.right = rect.left + abs(_collisionBodyRect.right - _collisionBodyRect.left);

	return rect;
}

bool CollisionBody::isColliding( Entity* otherObject)
{
	/*if (_listColliding.find(otherObject) != _listColliding.end())
		return true;
	else
		return false;*/
	return true;
}

void CollisionBody::update(float dt)
{
}