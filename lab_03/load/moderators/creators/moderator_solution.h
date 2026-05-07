#ifndef MODERATOR_SOLUTION_H
#define MODERATOR_SOLUTION_H

template <typename Creator>
decltype(auto) createModerator()
{
    Creator creator;
    return creator.getModerator();
}

#endif
