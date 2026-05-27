#ifndef BASE_SOLUTION_CREATOR_H
#define BASE_SOLUTION_CREATOR_H

#include <memory>

template <typename Solution>
class BaseSolutionCreator
{
public:
    std::shared_ptr<Solution> getSolution()
    {
        if (!_solution)
            _solution = create();

        return _solution;
    }

protected:
    virtual std::shared_ptr<Solution> create() = 0;

private:
    std::shared_ptr<Solution> _solution;
};

#endif
