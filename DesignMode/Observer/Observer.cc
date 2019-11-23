#include"Observer.h"
#include"Subject.h"
#include<iostream>

void ConcreateObserver::update(Subject *pSubject)
{
    nstate=pSubject->GetState();
    std::cout << nstate << std::endl;

}




