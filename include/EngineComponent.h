#ifndef ENGINECOMPONENT_H
#define ENGINECOMPONENT_H

class EngineObject;

class EngineComponent
{
    public:
        virtual void update() {}

        inline EngineObject* get_parent() { return m_parent; }
        inline void set_parent(EngineObject* p_parent) { m_parent = p_parent; }

        virtual ~EngineComponent();
    protected:
    private:
        EngineObject* m_parent;
};

#endif // ENGINECOMPONENT_H
