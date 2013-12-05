/************************************************************************************************************/
//
//
/************************************************************************************************************/

// TEST XINPUT CON SPRITE ALIEN
/*
#include "Windows.h"
#include "xinput.h"

#pragma comment(lib, "XInput9_1_0.lib" )

// Var usadas en el test de XINPUT
double posx = screen.GetWidth() / 2;
double posy = screen.GetHeight() / 2;
*/

/*
// INTERFAZ DE USUARIO - TEST XINPUT ( Controlador de XBox )

// En el bucle principal

XINPUT_STATE state;
ZeroMemory( &state, sizeof( XINPUT_STATE ) );
XInputGetState( 0, &state );
XINPUT_VIBRATION vibration;

if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_A )
{
	Beep( 5000, 100 );
}
if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_B )
{
	ZeroMemory( &vibration, sizeof( XINPUT_VIBRATION ) );
	vibration.wLeftMotorSpeed = 30000;
	vibration.wRightMotorSpeed = 30000;
	XInputSetState( 0, &vibration );
}
if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_Y )
{
	ZeroMemory( &vibration, sizeof( XINPUT_VIBRATION ) );
	XInputSetState( 0, &vibration );
}
float xPad = ( float ) state.Gamepad.sThumbLX / 32768;
float yPad = ( float ) state.Gamepad.sThumbLY / 32768;

posx += ( double ) xPad * 15;
posy += ( double ) yPad * 15 * -1;

renderer.SetBlendMode( sptAlien->GetBlendMode() );
sptAlien->Update( screen.ElapsedTime() );
sptAlien->Render();

sptAlien->SetPosition( posx, posy );
*/

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

#include "string.h"
#include <map>

// Códigos de GLFW que representan los distintos tipos de inputs posibles
#define GLFW_KEY_UNKNOWN      -1
#define GLFW_KEY_SPACE        32
#define GLFW_KEY_SPECIAL      256
#define GLFW_KEY_ESC          (GLFW_KEY_SPECIAL+1)
#define GLFW_KEY_F1           (GLFW_KEY_SPECIAL+2)
#define GLFW_KEY_F2           (GLFW_KEY_SPECIAL+3)
#define GLFW_KEY_F3           (GLFW_KEY_SPECIAL+4)
#define GLFW_KEY_F4           (GLFW_KEY_SPECIAL+5)
#define GLFW_KEY_F5           (GLFW_KEY_SPECIAL+6)
#define GLFW_KEY_F6           (GLFW_KEY_SPECIAL+7)
#define GLFW_KEY_F7           (GLFW_KEY_SPECIAL+8)
#define GLFW_KEY_F8           (GLFW_KEY_SPECIAL+9)
#define GLFW_KEY_F9           (GLFW_KEY_SPECIAL+10)
#define GLFW_KEY_F10          (GLFW_KEY_SPECIAL+11)
#define GLFW_KEY_F11          (GLFW_KEY_SPECIAL+12)
#define GLFW_KEY_F12          (GLFW_KEY_SPECIAL+13)
#define GLFW_KEY_F13          (GLFW_KEY_SPECIAL+14)
#define GLFW_KEY_F14          (GLFW_KEY_SPECIAL+15)
#define GLFW_KEY_F15          (GLFW_KEY_SPECIAL+16)
#define GLFW_KEY_F16          (GLFW_KEY_SPECIAL+17)
#define GLFW_KEY_F17          (GLFW_KEY_SPECIAL+18)
#define GLFW_KEY_F18          (GLFW_KEY_SPECIAL+19)
#define GLFW_KEY_F19          (GLFW_KEY_SPECIAL+20)
#define GLFW_KEY_F20          (GLFW_KEY_SPECIAL+21)
#define GLFW_KEY_F21          (GLFW_KEY_SPECIAL+22)
#define GLFW_KEY_F22          (GLFW_KEY_SPECIAL+23)
#define GLFW_KEY_F23          (GLFW_KEY_SPECIAL+24)
#define GLFW_KEY_F24          (GLFW_KEY_SPECIAL+25)
#define GLFW_KEY_F25          (GLFW_KEY_SPECIAL+26)
#define GLFW_KEY_UP           (GLFW_KEY_SPECIAL+27)
#define GLFW_KEY_DOWN         (GLFW_KEY_SPECIAL+28)
#define GLFW_KEY_LEFT         (GLFW_KEY_SPECIAL+29)
#define GLFW_KEY_RIGHT        (GLFW_KEY_SPECIAL+30)
#define GLFW_KEY_LSHIFT       (GLFW_KEY_SPECIAL+31)
#define GLFW_KEY_RSHIFT       (GLFW_KEY_SPECIAL+32)
#define GLFW_KEY_LCTRL        (GLFW_KEY_SPECIAL+33)
#define GLFW_KEY_RCTRL        (GLFW_KEY_SPECIAL+34)
#define GLFW_KEY_LALT         (GLFW_KEY_SPECIAL+35)
#define GLFW_KEY_RALT         (GLFW_KEY_SPECIAL+36)
#define GLFW_KEY_TAB          (GLFW_KEY_SPECIAL+37)
#define GLFW_KEY_ENTER        (GLFW_KEY_SPECIAL+38)
#define GLFW_KEY_BACKSPACE    (GLFW_KEY_SPECIAL+39)
#define GLFW_KEY_INSERT       (GLFW_KEY_SPECIAL+40)
#define GLFW_KEY_DEL          (GLFW_KEY_SPECIAL+41)
#define GLFW_KEY_PAGEUP       (GLFW_KEY_SPECIAL+42)
#define GLFW_KEY_PAGEDOWN     (GLFW_KEY_SPECIAL+43)
#define GLFW_KEY_HOME         (GLFW_KEY_SPECIAL+44)
#define GLFW_KEY_END          (GLFW_KEY_SPECIAL+45)
#define GLFW_KEY_KP_0         (GLFW_KEY_SPECIAL+46)
#define GLFW_KEY_KP_1         (GLFW_KEY_SPECIAL+47)
#define GLFW_KEY_KP_2         (GLFW_KEY_SPECIAL+48)
#define GLFW_KEY_KP_3         (GLFW_KEY_SPECIAL+49)
#define GLFW_KEY_KP_4         (GLFW_KEY_SPECIAL+50)
#define GLFW_KEY_KP_5         (GLFW_KEY_SPECIAL+51)
#define GLFW_KEY_KP_6         (GLFW_KEY_SPECIAL+52)
#define GLFW_KEY_KP_7         (GLFW_KEY_SPECIAL+53)
#define GLFW_KEY_KP_8         (GLFW_KEY_SPECIAL+54)
#define GLFW_KEY_KP_9         (GLFW_KEY_SPECIAL+55)
#define GLFW_KEY_KP_DIVIDE    (GLFW_KEY_SPECIAL+56)
#define GLFW_KEY_KP_MULTIPLY  (GLFW_KEY_SPECIAL+57)
#define GLFW_KEY_KP_SUBTRACT  (GLFW_KEY_SPECIAL+58)
#define GLFW_KEY_KP_ADD       (GLFW_KEY_SPECIAL+59)
#define GLFW_KEY_KP_DECIMAL   (GLFW_KEY_SPECIAL+60)
#define GLFW_KEY_KP_EQUAL     (GLFW_KEY_SPECIAL+61)
#define GLFW_KEY_KP_ENTER     (GLFW_KEY_SPECIAL+62)
#define GLFW_KEY_KP_NUM_LOCK  (GLFW_KEY_SPECIAL+63)
#define GLFW_KEY_CAPS_LOCK    (GLFW_KEY_SPECIAL+64)
#define GLFW_KEY_SCROLL_LOCK  (GLFW_KEY_SPECIAL+65)
#define GLFW_KEY_PAUSE        (GLFW_KEY_SPECIAL+66)
#define GLFW_KEY_LSUPER       (GLFW_KEY_SPECIAL+67)
#define GLFW_KEY_RSUPER       (GLFW_KEY_SPECIAL+68)
#define GLFW_KEY_MENU         (GLFW_KEY_SPECIAL+69)

// Actions
enum eAction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	JUMP
};

class InputManager
{
public:
	// Singleton
	static InputManager & Instance();
	// Inicialición: deteccción de dispostivos, inicialización de los mismos... etc
    bool            Init();
	// Cierre
    void            End();
	// Devuelve true si el manager ha sido inicializado correctamente
	bool 			IsOk();
	// Función de actualización, actualización de estados entre frames
    void            Update();
    // Crea un botón virtual
    void            CreateVirtualButton( eAction action, int32 button );
	// Crea un eje virtual
    void            CreateVirtualAxis( const String& action, uint8 positiveAxis, uint8 negativeAxis );
    // Está el botón pulsado en este momento?
    bool            IsVirtualButtonPressed( const String& action ) const;
	// Devuelve true durante el frame que que el usuario ha comenzaco la pulsación de un botón
    bool            IsVirtualButtonDown( const String& action ) const;
	// Devuelve true durante el frame que que el usuario ha dejado de pulsar un botón
    bool            IsVirtualButtonUp( const String& action ) const;
    // Estado de ejes virtuales normalizado de -1 a +1
    float           GetVirtualAxis( String action ) const;
    // Está el la tecla pulsada en este momento?
    bool            IsKeyPressed( int32 vkCode );
	// Devuelve true durante el frame que que el usuario ha comenzado la pulsación de una tecla (***OPCIONAL***)
    bool            IsKeyDown( int32 vkCode );
	// Devuelve true durante el frame que que el usuario ha dejado de pulsar una tecla (***OPCIONAL***)
    bool            IsKeyUp( int32 vkCode );
	// Está el la el botón del ratón tecla pulsado en este momento?
    bool            IsMouseButtonPressed( uint8 button );
	// Devuelve true durante el frame que que el usuario ha comenzaco la pulsación del botón del ratón dado
    bool            GetMouseButtonDown( uint8 button );
	// Devuelve true durante el frame que que el usuario ha dejado de pulsar el botón del ratón dado
    bool            GetMouseButtonUp( uint8 button );
	// Devuelve el estado de una acción dada
	bool			GetActionState( eAction action ) const;

protected:
	InputManager() {};
	~InputManager();

private:
	static InputManager * instance;

	// Available input devices
	bool mouse;
	bool keyboard;
	bool pad;

	// Action states
	bool left;
	bool right;
	bool up;
	bool down;
	bool jump;

	bool deltaKeyState;

public:
	std::map< eAction, int32 > virtualButtons;
};

#endif