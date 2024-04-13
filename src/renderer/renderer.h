#pragma once

#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

class renderer{
public:
    void Clear() const;
    void Draw(const vertexArray& va, const indexBuffer& ib, const shader& sh);
};