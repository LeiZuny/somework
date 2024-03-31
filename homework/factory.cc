#include <iostream>
#include <unistd.h>
#include <map>

class Employee {
    std::string name;
public:
    Employee(const std::string& name) {
        this->name = name;
    }
    std::string getName() {
        return name;
    }
    virtual void display() = 0;
};


class Manager: public Employee
{
private:
    int salary;
public:
    Manager(std::string name): Employee(name)
    {
        salary = 5000;
    }

    void display()
    {
        std::cout << "name" << getName() << "get" << salary<<std::endl;
    }
};


class Seller: public Employee
{
private:
    int salary;
public:
    Seller(std::string name): Employee(name)
    {
        int profit;
        std::cout << "please insert the profit"<<std::endl;
        std::cin >> profit;
        salary = profit * 0.05 + 4000;
    }

    void display()
    {
        std::cout << "name" << getName() << "get" << salary<<std::endl;
    }
};


class HoursWorker: public Employee
{
private:
    int salary;
public:
    HoursWorker(std::string name): Employee(name)
    {
        int base = 150;
        int add = 0;
        
        std::cout << "please insert the work hours"<<std::endl;
        std::cin >> base;
        if(base  > 150)
        {
            add = base - 150;
            base = 150;
        }
        salary = base * 15 + 18*add;
    }

    void display()
    {
        std::cout << "name" << getName() << "get" << salary<<std::endl;
    }
};


enum EMPLOYEE_TYPE {
    MANAGER,
    SALEWORKER,
    HOURWORKER,
    INVALID
};


class Factory
{
private:
    
    static EMPLOYEE_TYPE Gettypefromstring(std::string& str)
    {
        std::map<std::string, EMPLOYEE_TYPE> typemap = {
             {"manager", MANAGER},
            {"saleWorker", SALEWORKER},
            {"hourWorker", HOURWORKER}
        };

        if(typemap.find(str) == typemap.end())
        {
            return INVALID;
        }
        return typemap[str];
    }

public:
   static Employee* InitEmployee(std::string type,  std::string name)
   {
       Employee* ptr = nullptr;
       EMPLOYEE_TYPE type1 = Gettypefromstring(type);
       switch(type1)
       {
            case MANAGER:
                ptr = new Manager(name);
                break;
            case SALEWORKER:
                ptr = new Seller(name);
                break;
            case HOURWORKER:
                ptr = new HoursWorker(name);
                break;
            case INVALID:
            default:
                std::cout << "error type" << std::endl;
                
       }
       return ptr;
   }
};


static void printHelp(const char* name) {
    std::cout << "Usage: " << name << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t-t \tEmpolyee Type: manager, saleWorker, hourWorker." << std::endl;
    std::cout << "\t-n \tWorker Name." << std::endl;
    std::cout << "\t-h \tPrint this help message." << std::endl;
}



int main(int argc, char* argv[]) {
    int8_t c;
    std::string empolyee;
    std::string name;
    while((c = getopt(argc, argv, "t:n:h")) != -1)
    {
        switch(c)
        {
            case 't':
                empolyee = optarg;
                break;
            case 'n':
                name = optarg;
                break;
            case 'h':
            default:
                printHelp(argv[0]);
                return 0;
        }   
    }
    if (empolyee.empty() || name.empty()) {
        std::cout << "Missing required parameters: EmployeeType and WorkerName" << std::endl;
        printHelp(argv[0]);
        return 0;
    }
    Factory factory;
    Employee* worker = factory.InitEmployee(empolyee, name);
    if (worker != nullptr) {
        worker->display();
        delete worker;
        worker = nullptr;
    }
    return 0;
}






