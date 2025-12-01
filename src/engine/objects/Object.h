#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

class Object{
    public:
        virtual void LoadInMemory() = 0;
        virtual void Draw(GLuint scaleUniId) = 0;
};

#endif