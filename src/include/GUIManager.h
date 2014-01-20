#include "singleton.h"
#include "message.h"
#include "Vector2.h"
#include <map>
#include "string.h"

using namespace std;

class Control;

class GUIManager : public Singleton<GUIManager>
{
public:  

	int init();
	void end();

	void update();
	void render();

	void setRootControl( Control* control );
	Control* getRootControl();

	void injectInput( const Message& message );

	Vector2 getScreenSize() const;

	Control* findControlByName( const String& name );
	void deleteControl( const String& name );

protected:

	Control*							m_rootControl;
};
