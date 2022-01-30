#pragma once
#include "../../IRepository/IRepository.h"
#include "Entities/Entities.h"

class ColorLinesScoreFileRepository: public IRepository<void, std::optional<UserScore>>
{
private:
    std::optional<UserScore> _score;

public:
    ColorLinesScoreFileRepository();
    ~ColorLinesScoreFileRepository();

    virtual std::optional<UserScore> getValue() override;
    virtual void setValue(const std::optional<UserScore>& value) override;
};

