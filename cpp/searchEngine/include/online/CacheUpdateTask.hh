#ifndef __CACHEUPDATETASK_HH__
#define __CACHEUPDATETASK_HH__

#include "TimerTask.hh"

class CacheUpdateTask : public TimerTask
{
public:
    virtual void process() override;
};

#endif