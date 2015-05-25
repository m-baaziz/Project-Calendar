#include "TaskManager.h"

TasksContainer* TasksArray::tasks = new TasksContainer;
unsigned int TasksArray::nbFactories = 0;

template<>
Handler<CompositeFactory> Singleton<CompositeFactory>::handler = Handler<CompositeFactory>();
template<>
Handler<PreemptiveFactory> Singleton<PreemptiveFactory>::handler = Handler<PreemptiveFactory>();
template<>
Handler<NonPreemptiveFactory> Singleton<NonPreemptiveFactory>::handler = Handler<NonPreemptiveFactory>();

CompositeTask* CompositeFactory::isTaskIncluded (const QString& id) {
    CompositeTask* temp = 0;
    for (TypedTasksIterator it = getTypedTasksIterator(); !(it.isDone()); it.next()) {
        if (temp = it.current().isSubTaskHere(id)) return temp;
    }
    return 0;
}
