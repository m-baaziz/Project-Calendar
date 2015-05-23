#ifndef SINGLETON_H
#define SINGLETON_H
#include "Task.h"

/*!
 * \file "Singleton.h"
 * \brief Header file that describes all the classes needed to implement the Singleton Design Pattern.
 * In order to turn a simple class into a Singleton class, simply
   -have the simple class inheritate from Singleton
   -declare those two friendship relations : - friend class Singleton<SimpleClass>;
                                             - friend class Handler<SimpleClass>;
   -declare static handler instance like that :
        template<>
        Handler<SimpleClass> Singleton<SimpleClass>::handler = Handler<SimpleClass>();

 */

template<class S>
class Handler {
    S* instance;
    Handler():instance(0) {}
    ~Handler(){if (instance) delete instance;}
    template<class any>
    friend class Singleton;
};

template<class Type>
class Singleton {
    Singleton(const Singleton& s);
    Singleton& operator=(const Singleton& s);
protected:
    Singleton(){}
    virtual ~Singleton(){}
    template<class Fa>
    friend struct Handler;  //every Handler<Fa> is a friend of Singleton
    static Handler<Type> handler;
public:
    static Type& getInstance() {
            if (handler.instance==0) handler.instance = new Type;
            return *(handler.instance);
        }

    static void freeInstance() {
        if (handler.instance!=0) delete handler.instance;
        handler.instance = 0;
    }
};




#endif // SINGLETON_H
