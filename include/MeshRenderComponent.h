#ifndef MESHRENDERCOMPONENT_H
#define MESHRENDERCOMPONENT_H

#include "EngineComponent.h"

class RenderingEngine;
class Shader;


class MeshRenderComponent : public EngineComponent
{
    public:
        MeshRenderComponent();

        void render(RenderingEngine*, Shader*);

        virtual ~MeshRenderComponent();
    protected:
    private:
};

#endif // MESHRENDERCOMPONENT_H
