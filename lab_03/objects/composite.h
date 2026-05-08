#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "object.h"
#include "base_visitor.h"

class Composite : public Object
{
public:
    Composite() = default;
    explicit Composite(std::shared_ptr<Object> &element);
    explicit Composite(std::vector<std::shared_ptr<Object>> &vector);

    bool add(const std::shared_ptr<Object> &element) override;
    bool remove(const Iterator &iter) override;

    bool isVisible() const override;
    bool isComposite() const override;
    void accept(BaseVisitor &visitor) override;

    Iterator begin() override;
    Iterator end() override;

    std::vector<std::shared_ptr<Object>> getElements();

private:
    std::vector<std::shared_ptr<Object>> _elements;
};


#endif
