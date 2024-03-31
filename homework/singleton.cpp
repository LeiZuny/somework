#include<iostream>


class single
{
private:
    static single * instance;
    single()
    {
        std::cout << "the single is constructed"<<std::endl;
    }
    single(const single& ) = delete;
    single& operator =(const single&) = delete;
    ~single()
    {
        std::cout << "the single is destructed"<<std::endl;
    }
public:
    static single* getinstance()
    {
       if(instance == nullptr)
       {
            instance = new single();
       }
       return instance;
    }
};

single* single::instance = nullptr;
int main()
{
    single *instance1 = single::getinstance();
    single *instance2 = single::getinstance();
    return 0;

}