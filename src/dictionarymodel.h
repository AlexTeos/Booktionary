#ifndef DICTIONARYMODEL_H
#define DICTIONARYMODEL_H

#include <QAbstractListModel>

#include "translator.h"
#include "word.h"

namespace DictionaryModelState
{
enum DictionaryModelState
{
    Untranslated = 0,
    Processed,
    Translated
};
}

class DictionaryModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DictionaryModelState::DictionaryModelState state READ state NOTIFY stateChanged)
    Q_PROPERTY(double translatedCount READ translatedCount NOTIFY translatedCountChanged)
public:
    explicit DictionaryModel(QObject* parent = nullptr);
    void      addWord(Word word);
    qsizetype size() const;
    void      setTranslator(Translator* translator) { m_translator = translator; }

    // Basic functionality:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    using const_iterator = QList<Word>::const_iterator;
    const_iterator begin() const { return m_dictionary.cbegin(); }
    const_iterator end() const { return m_dictionary.cend(); }
    bool           translate(Translator& translator);

    enum DictionaryRoles
    {
        WordRole = Qt::UserRole + 1,
        StateRole,
        MeaningsRole
    };

    virtual QHash<int, QByteArray> roleNames() const override;

    DictionaryModelState::DictionaryModelState state() const { return m_state; }
    double                                     translatedCount() const { return m_translatedCount; }

public slots:
    bool translate();
    void reset();

signals:
    void stateChanged();
    void translatedCountChanged();

private:
    DictionaryModelState::DictionaryModelState m_state;
    QList<Word>                                m_dictionary;
    Translator*                                m_translator;
    qsizetype                                  m_translatedCount;
};

#endif // DICTIONARYMODEL_H
