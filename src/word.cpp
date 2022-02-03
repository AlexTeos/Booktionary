#include "word.h"

void Word::addDefinition(const PartOfSpeach& PartOfSpeach, const Definition& definition)
{
    if (not m_definitions.contains(PartOfSpeach)) m_definitions.insert(PartOfSpeach, definition);
}

QString Word::word() const
{
    return m_word;
}

QStringList Word::meanings() const
{
    QStringList out;
    out.reserve(m_definitions.size());
    QMultiMapIterator<PartOfSpeach, Definition> i(m_definitions);
    while (i.hasNext())
    {
        i.next();
        out.push_back(PartOfSpeachumToQString[i.key()] + ": " + i.value().meaning.join(", "));
    }
    return out;
}

void Word::setState(WordState::WordState newState)
{
    m_state = newState;
}

WordState::WordState Word::state() const
{
    return m_state;
}
