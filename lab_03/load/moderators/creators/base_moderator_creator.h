#ifndef BASE_MODERATOR_CREATOR_H
#define BASE_MODERATOR_CREATOR_H

#include <memory>

template <typename Moderator>
class BaseModeratorCreator
{
public:
    virtual ~BaseModeratorCreator() = default;

    std::shared_ptr<Moderator> getModerator()
    {
        if (!_moderator)
            _moderator = create();

        return _moderator;
    }

protected:
    virtual std::shared_ptr<Moderator> create() = 0;

private:
    std::shared_ptr<Moderator> _moderator;
};

#endif
