#ifndef DST
#define DST
template <typename elemType,typename Key>
class dynamicSearchTable
{
public:
virtual void insert(const elemType &x,const Key & k) = 0;
virtual void remove(const Key &k) = 0;
virtual elemType& find(const Key & k) const = 0;
virtual ~dynamicSearchTable(){};
};

#endif