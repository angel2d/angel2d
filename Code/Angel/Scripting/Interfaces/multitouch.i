%module angel
%{
#include "../../Input/MultiTouch.h"
%}

struct Touch
{
    Vec2i StartingPoint;
    Vec2i CurrentPoint;
    float StartTime;
    float MotionStartTime;

    void* __platformTouch;
};

enum TouchInput
{
    TOUCH_START,
    TOUCH_END,
    TOUCH_MOVE
};

struct GestureData
{
    float Velocity;
    float GestureMagnitude;
};

typedef std::vector<Touch*> TouchList;

%feature("director") TouchListener;
class TouchListener
{
public:
    TouchListener();
    virtual ~TouchListener();
    
    virtual void TouchMotionEvent(Touch* movedTouch);
    virtual void TouchEndEvent(Touch* endedTouch);
    virtual void TouchStartEvent(Touch* startedTouch);
    
    static TouchList &GetTouchList();
};

%nodefaultctor Accelerometer;
class Accelerometer
{
public:
    static Accelerometer& GetInstance();
    
    const Vector3 GetData();
};
