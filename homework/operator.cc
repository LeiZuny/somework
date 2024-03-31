#include<iostream>

class complexnum
{
private:
    /* data */
    int real;
    int vir;
public:
    complexnum()
    {

    }
    complexnum(int num1, int num2):real(num1), vir(num2)
    {

    }
    friend std::ostream& operator<<(std::ostream& os, const  complexnum& c) {
        os << "(" << c.real << ", " << c.vir << "i)";
        return os;
    }

    complexnum operator+(complexnum& com1)
    {
        complexnum test;
        test.real = this->real + com1.real;
        test.vir = this->vir + com1.vir;
        return test;
    }

    complexnum operator-(complexnum& com1)
    {
        complexnum test;
        test.real = this->real - com1.real;
        test.vir = this->vir - com1.vir;
        return test;
    }

    // friend std::ostream&  operator<< (std::ostream& os, complexnum &com1)
    // {
    //     os << "(" << com1.real << "," << com1.vir <<"i)"<<std::endl;
    //     return os;
    // }


};

int main()
{
    complexnum a(10,10);
    complexnum b(100,-9);
    std::cout<<"a"<<a<<std::endl;
    std::cout<<"b"<<b<<std::endl;
    std::cout<<"a+b" << a+b <<std::endl;
    std::cout<<"a-b" << a-b <<std::endl;
    return 0;
}




