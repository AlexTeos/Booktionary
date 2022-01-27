#include "word.h"

void Word::addDefinition(const PartOfSpeach& PartOfSpeach, const Definition& definition)
{
    if (not m_definitions.contains(PartOfSpeach)) m_definitions.insert(PartOfSpeach, definition);
}

QString Word::word() const
{
    return m_word;
}

void Word::setState(WordState::WordState newState)
{
    m_state = newState;
}

WordState::WordState Word::state() const
{
    return m_state;
}
