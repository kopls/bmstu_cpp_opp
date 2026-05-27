#ifndef SOLUTION_DRAW_CREATOR_H
#define SOLUTION_DRAW_CREATOR_H

#include <memory>

#include "base_drawer_factory.h"
#include "base_solution_creator.h"
#include "draw_manager_creator.h"
#include "draw_visitor_creator.h"
#include "solution_draw.h"

class SolutionDrawCreator : public BaseSolutionCreator<SolutionDraw>
{
public:
    explicit SolutionDrawCreator(std::shared_ptr<BaseDrawerFactory> factory)
        : _factory(factory)
    {
    }

protected:
    std::shared_ptr<SolutionDraw> create() override
    {
        DrawManagerCreator managerCreator;
        DrawVisitorCreator visitorCreator;

        return std::make_shared<SolutionDraw>(managerCreator.getManager(),
                                              visitorCreator.getVisitor(),
                                              _factory->createDrawer());
    }

private:
    std::shared_ptr<BaseDrawerFactory> _factory;
};

#endif
