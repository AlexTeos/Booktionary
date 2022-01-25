#include "dictionarymodel.h"

DictionaryModel::DictionaryModel(QObject* parent)
    : QAbstractListModel(parent), m_state(DictionaryModelState::Untranslated)
{
}

int DictionaryModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;

    return m_dictionary.size();
}

//bool DictionaryModel::hasChildren(const QModelIndex& parent) const
//{
//    // FIXME: Implement me!
//}

//bool DictionaryModel::canFetchMore(const QModelIndex& parent) const
//{
//    // FIXME: Implement me!
//    return false;
//}

//void DictionaryModel::fetchMore(const QModelIndex& parent)
//{
//    // FIXME: Implement me!
//}

QVariant DictionaryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    switch (role)
    {
        case WordRole:
            return QVariant(m_dictionary[index.row()].getWord());
    }

    return QVariant();
}

//bool DictionaryModel::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//    if (data(index, role) != value)
//    {
//        // FIXME: Implement me!
//        emit dataChanged(index, index, QVector<int>() << role);
//        return true;
//    }
//    return false;
//}

Qt::ItemFlags DictionaryModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
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
}

qsizetype DictionaryModel::size() const
{
    return m_dictionary.size();
}

QHash<int, QByteArray> DictionaryModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[WordRole] = "word";
    return names;
}

bool DictionaryModel::translate()
{
    m_state = DictionaryModelState::Processed;
    emit stateChanged();

    int i = 0;
    for (auto iter = m_dictionary.begin(); iter != m_dictionary.end(); iter++, i++)
    {
        if (not m_translator->translate(*iter))
        {
            return false;
        }
        else
        {
            qDebug() << i + 1 << "/" << m_dictionary.size();
        }
    }

    m_state = DictionaryModelState::Translated;
    emit stateChanged();
    return true;
}
