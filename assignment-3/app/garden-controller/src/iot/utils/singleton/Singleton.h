#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template<class T>
class Singletonizable {
    private:
    static T* instance = nullptr;

    protected:
    virtual static T* create() = 0;

    public:
    static T* getInstance() {
        if (instance == nullptr) {
            instance = create();
        }
        return instance;
    }
};

#endif