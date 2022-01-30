#pragma once
#include "../../IRepository/IRepository.h"
#include "Entities/Entities.h"

class ColorLinesScoreSQLiteRepository: public IRepository<void, std::optional<UserScore>>
{
public:
    virtual std::optional<UserScore> getValue() override;
    virtual void setValue(const std::optional<UserScore> &value) override;
};


