#ifndef __ANIMATION__
#define __ANIMATION__

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"

using namespace std;

class Animation : public Sprite		//Kế thừa từ Sprite
{
public:
    //ham ho tro lay animation voi anh co duy nhat 1 hang
    Animation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame, bool repeat, D3DCOLOR colorKey = NULL);
	//Tạo animation từ sprite và info
	Animation(const char* filePath, const char* filePathInfo,float timePerFrame, bool loop=true);
	//Animation(Sprite* spriteSheet, float timeAnimate = 0.0f, bool loop = true);
    Animation();

    virtual void Update(float dt);

	void DrawSprite();

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void Draw(D3DXVECTOR2 translate);

    ~Animation();

	void AddFrameRect(RECT rect);
	//void AddFrameRect(float left, float top, int width, int height);
	void AddFrameRect(float left, float top, float right, float bottom);

	//void AddFrameRect(eID id, char* firstRectName, ...);
    //su dung cho ke thua
    void InitWithAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame,bool repeat, D3DCOLOR colorKey = NULL);
	//void InitWithAnimationFromText(const char* filePath, const char* fileText, bool repeat);

	void LoadSpriteInfo(const char* fileText);

	void NextFrame();

	void SetIndex(int index);

	int GetIndex();

	void Start();

	void Stop();

    int                         mRows, //so hang cua animation
                                mColumns, //so cot cua animation
								mIndex,	  //gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
                                mCurrentRow, // hang hien tai
                                mCurrentColumn, // cot hien tai
                                mFrameWidth, // chieu rong cua 1 frame 
                                mFrameHeight, // chieu dai cua 1 frame
                                mTotalFrame;  //tong so frame

	bool mCanAnimate;		 //cho phep animation
	bool mIsLoop;
	bool mEndAnimate;
	bool mIsAll;
	int mWidth, mHeight;
	int mStartFrame;
	int mEndFrame;
	int mTotalFrames;
    float                       mTimePerFrame, //thoi gian luan chuyen 1 frame
                                mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe
	Sprite* mSpriteSheet;
	vector<RECT> mFrameRectList;
	string mNameAnimation;
	RECT mCurrentRect;
    RECT                        mRect;
};

#endif
