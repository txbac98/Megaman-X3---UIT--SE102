#include "Animation.h"

Animation::Animation()
{

}


Animation::Animation(const char* filePath, const char* filePathInfo, float timePerFrame, bool loop) {
	
	//Init Sprite nguyên sheet
	this->InitWithSprite(filePath);
	LoadSpriteInfo(filePathInfo);
	mTimePerFrame = timePerFrame;
	mTotalFrame = mFrameRectList.size();
	mIsLoop = loop;
	mEndAnimate = false;
	this->Start();
}

//Load ảnh 1 hàng, tự động cắt frame bằng nhau (không dùng)
Animation::Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame,bool repeat, D3DCOLOR colorKey)
{
    InitWithAnimation(filePath, totalFrame, rows, columns, timePerFrame,repeat, colorKey);
}
void Animation::InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame,bool repeat, D3DCOLOR colorKey)
{
    //GAMELOG("animation: frame: %d, row: %d, column: %d, time: %f", totalFrame, rows, columns, timePerFrame);
    this->InitWithSprite(filePath);
    mCurrentColumn = 0;
    mCurrentRow = 0;
    mTimePerFrame = timePerFrame;
    mTotalFrame = totalFrame;
    mRows = rows;
    mColumns = columns;


	//width - height luc nay la cua spritesheet
	mFrameWidth = GetWidth() / mColumns;
	mFrameHeight = GetHeight() / mRows;

    SetWidth(mFrameWidth);
    SetHeight(mFrameHeight);

	mRect.top = 0;
	mRect.left = 0;
	mRect.right = mFrameWidth;
	mRect.bottom = mFrameHeight;

    SetSourceRect(mRect);
}

Animation::~Animation()
{

}

void Animation::LoadSpriteInfo( const char* fileInfoPath) {

	FILE* file;
	file=fopen(fileInfoPath,"r");
	if (file)
	{
		
		while (!feof(file))
		{
			int width, height;
			RECT rect;			
			fscanf(file, "%d %d %d %d", &rect.left, &rect.top, &width, &height);
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;
			AddFrameRect(rect);			
		}
	}

	fclose(file);
}
void Animation::Update(float dt)
{
	if (mCanAnimate) {
		if (mTotalFrame <= 1)
			return;

		if (mCurrentTotalTime >= mTimePerFrame)
		{
			
			if (mIndex > mEndFrame)
			{
				if (mIsLoop) {
					mIndex = 0;
				}
				else {
					Stop();
				}
			}	
			//if (mFrameRectList.size() != 0) {
			SetSourceRect(mFrameRectList[mIndex]);
			SetWidth((mFrameRectList[mIndex].right - mFrameRectList[mIndex].left));
			SetHeight((mFrameRectList[mIndex].bottom - mFrameRectList[mIndex].top));
			//}	
			mCurrentTotalTime = 0;
			mIndex++;
		}
		else
		{
			mCurrentTotalTime += dt;
		}
	}
    
}


void Animation::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale,
    D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{

    Sprite::Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::Draw(D3DXVECTOR2 translate)
{
    Sprite::Draw(D3DXVECTOR3(), RECT(), D3DXVECTOR2(), translate);
}
void Animation::AddFrameRect(RECT rect)
{
	if (mFrameRectList.empty())
	{
		mCurrentRect = rect;
	}
	mFrameRectList.push_back(rect);
	mTotalFrames = mFrameRectList.size();

	mEndFrame = mTotalFrames - 1;
}
void Animation::AddFrameRect(float left, float top, float right, float bottom)
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;

	this->AddFrameRect(rect);
}
void Animation::NextFrame()
{
	this->SetIndex(mIndex + 1);
}

int Animation::GetIndex()
{
	return mIndex;
}

void Animation::SetIndex(int index)
{
	if (index == mIndex || mTotalFrames == 0)
		return;

	mIndex = index;

	if (mIndex > mEndFrame)
		mIndex = mStartFrame;

	mCurrentRect = mFrameRectList[mIndex];

	if (!mIsLoop && mIndex == mEndFrame)
	{
		this->Stop();
	}
}

void Animation::Start()
{
	mEndAnimate = false;
	mCanAnimate = true;
	mIndex = 0;
	//Set kich thuoc sprie ban dau (sprite)
	SetWidth((mFrameRectList[0].right - mFrameRectList[0].left));
	SetHeight((mFrameRectList[0].bottom - mFrameRectList[0].top));
	//Source Rect (Sprite)
	SetSourceRect(mFrameRectList[0]);
}

void Animation::Stop()
{
	mCanAnimate = false;
	mEndAnimate = true;
	mIndex = mEndFrame;
}

