#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include <QAbstractListModel>

#include "translator.h"
#include "word.h"

class DictionaryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DictionaryModel(QObject* parent = nullptr);
    void      addWord(Word word);
    void      reset();
    qsizetype size() const;

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    // Fetch data dynamically:
    //bool hasChildren(const QModelIndex& parent = QModelIndex()) const override;

    //bool canFetchMore(const QModelIndex& parent) const override;
    //void fetchMore(const QModelIndex& parent) override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // Editable:
    //bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    using const_iterator = QList<Word>::const_iterator;
    const_iterator begin() const { return m_dictionary.cbegin(); }
    const_iterator end() const { return m_dictionary.cend(); }
    bool           translate(Translator& translator);

    enum DictionaryRoles
    {
        WordRole = Qt::UserRole + 1
    };

    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QList<Word> m_dictionary;
};

#endif // DICTIONARYMODEL_H
