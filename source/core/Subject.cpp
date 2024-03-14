#include "../../include/core/Subject.h"

void Subject::addObserver(Observer* observerParam) 
{
    observer = observerParam;
}

void Subject::notify(Events event) 
{
   observer->onNotify(event);
}