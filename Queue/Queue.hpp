#ifndef CLASS_QUEUE
#define CLASS_QUEUE


template <class elemType>
class queue
{
public:
    virtual bool isEmpty() = 0;
    virtual elemType getHead() = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual ~queue(){};
};

#endif