#ifndef _TASKSTACK_HPP
#define _TASKSTACK_HPP

#include <queue>
#include <string>

enum class TaskStatus : uint8_t
{
    INQUEUE = 0, RUNNING, 

};


struct Task 
{
    std::string item;
    std::function 


};

class TaskStack
{
public:
    TaskStack() {}

private:
    std::queue<std::function

};


#endif // _TASKSTACK_HPP
