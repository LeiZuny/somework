
#include <iostream>
#include <map>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <functional>


class Observer;
class Clock
{
private:
    /* data */
    static int time;
    static std::map<Observer*,  std::function<void(int)>> ObserveList;

public:
    static void SetTimer()
    {
        struct itimerval itv; 
        itv.it_value.tv_sec = 5;
        itv.it_value.tv_usec = 0;
        itv.it_interval.tv_sec = 5;
        itv.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &itv, NULL);
        signal(SIGALRM, Clock::notify);
    }

    static void attach(Observer* observer, std::function<void(int)> func)
    {
        ObserveList.insert(std::make_pair(observer, func));
    }

    static void  notify(int signal)
    {
        time += 5;
        for(auto it = ObserveList.begin(); it != ObserveList.end(); it++)
        {
            it->second(time);
        }

        if(time == 60)
        {
            exit(0);
        }
    }

    
};

int Clock::time = 0;
std::map<Observer*, std::function<void(int)>> Clock::ObserveList;


class Observer
{
public:
    virtual void  activition(int time) = 0;

};


class Teacher :public Observer
{
public:
    void activition (int time)
    {
        if(time % 15 == 0)
        {
            std::cout << "ÉÏ¿Î" << std::endl;
        }
    }
};

class Student : public Observer {
public:
	void activition(int time) {
        if (time % 30 == 0) {
            std::cout << "ÐÝÏ¢" << std::endl;
        }
    }
};

class Lesson : public Observer {
public:
	void activition(int time) override{
        if (time % 60 == 0) {
            std::cout << "ÏÂ¿Î" << std::endl;
        }
    }
};


int main()
{
    Teacher teacher;
    Observer* Pteacher = &teacher;

    Student student;
    Observer* Pstudent = &student;

    Lesson lesson;
    Observer* Plesson = &lesson;

    Clock::attach(Pteacher, std::bind(&Observer::activition, teacher, std::placeholders::_1));
    Clock::attach(Pstudent, std::bind(&Observer::activition, student, std::placeholders::_1));
    Clock::attach(Plesson, std::bind(&Observer::activition, lesson, std::placeholders::_1));

    Clock::SetTimer();
    
    while(1);
    return 0;

}