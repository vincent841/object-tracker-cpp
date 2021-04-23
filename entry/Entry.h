#ifndef __ENTRY_H__
#define __ENTRY_H__

#define INIT_TASKMGR() \
    TaskManager* pTaskMgr = new TaskManager();

#define REGISTER_TASK(pTaskMgr, name, cls) \
    pTaskMgr->registerTask(name, new cls());


#endif // __ENTRY_H__
