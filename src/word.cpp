#include "word.h"

void Word::addDefinition(const PartOfSpeach& PartOfSpeach, const Definiton& definiton)
{
    if (not definitions.contains(PartOfSpeach)) definitions.insert(PartOfSpeach, definiton);
}

QString Word::getWord() const
{
    return word;
}
