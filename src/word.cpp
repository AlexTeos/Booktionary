#include "word.h"

void Word::addDefinition(const PartOfSpeach& PartOfSpeach, const Definition& definition)
{
    if (not definitions.contains(PartOfSpeach)) definitions.insert(PartOfSpeach, definition);
}

QString Word::getWord() const
{
    return word;
}
