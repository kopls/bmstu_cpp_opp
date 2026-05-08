#include <memory>

#include "composite.h"

Composite::Composite(std::shared_ptr<Object> &element)
{
    _elements.push_back(element);
}

Composite::Composite(std::vector<std::shared_ptr<Object>> &vector)
{
    _elements = vector;
}


bool Composite::add(const std::shared_ptr<Object> &element)  
{
    
    _elements.push_back(element);
    return true;
}

bool Composite::remove(const Iterator &iter)  
{
    _elements.erase(iter);
    return true;
}


bool Composite::isVisible() const  
{
    return false;
}

bool Composite::isComposite() const  
{
    return true;
}

void Composite::accept(BaseVisitor &visitor)  
{
    for (auto &elem : _elements)
        elem->accept(visitor);
}

Iterator Composite::begin()  
{
    return _elements.begin();
}

Iterator Composite::end()  
{
    return _elements.end();
}

std::vector<std::shared_ptr<Object>> Composite::getElements()
{
    return _elements;
}
