#include<iostream>
#include<string>
#include<sys/time.h>
#include<signal.h>
#include<list>
#include<unordered_map>
#include<functional>

class Observer
{
public:
    virtual void update(int) = 0;
};


class Clock : public Observer 
{
private:
    std::string name;
public:
    Clock(std::string name1):name(name1)
    {
        std::cout << name << "is init" << std::endl;
    }

    void update(int time) override
    {
        if(time % 60 == 0 )
        {
            std::cout<<"the class is over!" << std::endl;
            exit(1);
        }
    }
};

class Teacher : public Observer
{
private:
    std::string name;
public:
    Teacher(std::string name1): name(name1)
    {
        std::cout << name << "is init" << std::endl;
    }

    void update(int time) override
    {
        if(time % 15 == 0)
        {
            std::cout << "we will have a class" << std::endl;
        }
    }
};

class Student : public Observer
{
private:
    std::string name;
public:
    Student(std::string name1):name(name1)
    {
        std::cout << name << "is init"<<std::endl;
    }

    void update(int time) override
    {
        if(time % 30 == 0)
        {
            std::cout << "we will have a rest" << std::endl;
        }
    }
};

class ClockObservered
{
private: 
    static int time;
    static std::unordered_map<Observer*, std::function<void(int)>> observerss; 
public:
    static void Setime()
    {
        struct itimerval it;
        it.it_interval.tv_sec = 5;
        it.it_interval.tv_usec = 0;
        it.it_value.tv_sec = 5;
        it.it_value.tv_usec = 0;

        setitimer(ITIMER_REAL, &it, nullptr);
        signal(SIGALRM, ClockObservered::notify);

    }

    static void attach(Observer* ob, std::function<void(int)>func)
    {

        observerss.insert(std::make_pair(ob, func));
    }

    

    static void notify(int sigal)
    {
        time +=  5;
        for(auto it = observerss.begin(); it != observerss.end(); it++)
        {
            it->second(time);
        }
    }



};

int ClockObservered::time = 0;
std::unordered_map<Observer*, std::function<void(int)>> ClockObservered::observerss;

int main()
{
    Observer* m_teacher = new Teacher("teacher");
    Observer* m_student= new Student("student");
    Observer* m_clock = new Clock("clock");

    ClockObservered clocktime;
    clocktime.attach(m_teacher, std::bind(&Observer::update, m_teacher, std::placeholders::_1));
    clocktime.attach(m_student, std::bind(&Observer::update, m_student, std::placeholders::_1));
    clocktime.attach(m_clock, std::bind(&Observer::update, m_clock, std::placeholders::_1));
    clocktime.Setime();
    while(1);

    std::cout << "over" << std::endl;
    return 0;
}