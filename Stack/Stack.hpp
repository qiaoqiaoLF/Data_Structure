#ifndef CLASS_STACK
#define CLASS_STACK
template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;
    virtual elemType Top() const = 0;
    virtual void push(const elemType &x) = 0;
    virtual elemType pop() = 0;
    virtual ~stack() {}
};

#endif