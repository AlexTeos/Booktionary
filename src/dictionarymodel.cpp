#include "dictionarymodel.h"

DictionaryModel::DictionaryModel(QObject* parent)
    : QAbstractListModel(parent), m_state(DictionaryModelState::Untranslated), m_translatedCount(0)
{
}

int DictionaryModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;

    return m_dictionary.size();
}

QVariant DictionaryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    switch (role)
    {
        case WordRole:
            return QVariant(m_dictionary[index.row()].word());
        case StateRole:
            return QVariant(m_dictionary[index.row()].state());
        case MeaningsRole:
            return QVariant(m_dictionary[index.row()].meanings());
    }

    return QVariant();
}

Qt::ItemFlags DictionaryModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

void DictionaryModel::addWord(Word word)
{
    const int index = m_dictionary.size();
    beginInsertRows(QModelIndex(), index, index);
    m_dictionary.push_back(word);
    endInsertRows();
}

void DictionaryModel::reset()
{
    beginResetModel();
    m_dictionary.clear();
    endResetModel();
    m_state = DictionaryModelState::Untranslated;
    emit stateChanged();
    m_translatedCount = 0;
    emit translatedCountChanged();
}

qsizetype DictionaryModel::size() const
{
    return m_dictionary.size();
}

QHash<int, QByteArray> DictionaryModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[WordRole]     = "word";
    names[StateRole]    = "translationState";
    names[MeaningsRole] = "meanings";
    return names;
}

bool DictionaryModel::translate()
{
    m_state = DictionaryModelState::Processed;
    emit stateChanged();
    // TODO: calculate count of words dynamically
    qsizetype updateCount = qMin(512, m_dictionary.size());

    int modelCounter = 0;
    for (auto iter = m_dictionary.begin(); iter != m_dictionary.end(); iter += updateCount, modelCounter += updateCount)
    {
        updateCount = qMin(m_dictionary.size() - modelCounter, updateCount);

        if (not m_translator->translateNMT(iter, updateCount))
        {
            return false;
        }

        emit dataChanged(
            index(modelCounter), index(modelCounter + updateCount - 1), QVector<int>() << StateRole << MeaningsRole);

        m_translatedCount += updateCount;
        emit translatedCountChanged();
    }

    m_state = DictionaryModelState::Translated;
    emit stateChanged();
    return true;
}
