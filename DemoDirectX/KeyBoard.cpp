#include "Keyboard.h"

Keyboard* Keyboard::instance = 0;
Keyboard* Keyboard::getInstance()
{
	return instance;
}

Keyboard::Keyboard(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_di, NULL);
	m_di->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024;

	m_keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	m_keyboard->Acquire();

	for (int i = 0; i < 256; i++)
		m_keyStates[i] = 0x00;
}

void  Keyboard::Create(HINSTANCE hInstance, HWND hWnd)
{
	instance = new Keyboard(hInstance, hWnd);
}

void Keyboard::PollKeyboard()
{
	m_keyboard->Poll();

	if (FAILED(m_keyboard->GetDeviceState(sizeof(m_keyEvents), (LPVOID)&m_keyEvents)))
	{
		//keyboard device lost, try to re-acquire
		m_keyboard->Acquire();
		m_keyboard->GetDeviceState(sizeof(m_keyEvents), (LPVOID)&m_keyEvents);
	}
	else
		m_keyboard->GetDeviceState(sizeof(m_keyEvents), (LPVOID)&m_keyEvents);
}

void Keyboard::UpdateKeyboard()
{
	BYTE keys[256];
	m_keyboard->GetDeviceState(256, keys);

	for (int i = 0; i < 256; i++)
		m_keyStates[i] = keys[i];
}

void Keyboard::Release()
{
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}

	if (m_di)
	{
		m_di->Release();
		m_di = 0;
	}
}

bool Keyboard::IsKeyDown(BYTE keyCode)
{
	return (m_keyStates[keyCode] & 0x80) > 0;
}

bool Keyboard::IsKeyUp(BYTE keyCode)
{
	return !((m_keyStates[keyCode] & 0x80) > 0);
}

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

