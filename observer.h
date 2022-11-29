#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Subject;

class Observer {
public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
};

#endif
