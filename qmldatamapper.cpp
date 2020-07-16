#include "qmldatamapper.h"
#include <QDataWidgetMapper>

struct Mapping {
    QPointer <QObject> object;
    int section;
    QByteArray propertyName;
};

/**
 * Private класс, который содержит все скрытые методы и переменные.
 * Используется концепция, которая позволяет изменять внутреннее API без воздействия на внешнее API
 * (see http://en.wikipedia.org/wiki/Opaque_pointer)
 */
class QmlDataMapperPrivate
{
public:
    QmlDataMapperPrivate()
        : m_model(0), m_currentIndex(-1)
    {
    }

    // Вспомогательный метод обновления участников по заданным сопоставления с заданными параметрами
    void updateMapping(Mapping &mapping, QObject *object, const int &section, const QByteArray &propertyName);

    // Данный метод устанавливает актуальные сопоставления данных из модели данных в элементы управления
    void update();

    // Модель данных, с которой производится работа
    QAbstractItemModel* m_model;

    // Список сопоставлений, котроые установленны
    QVector<Mapping> m_mappings;

    // Текущий индекс QmlDataMapper
    int m_currentIndex;
};

void QmlDataMapperPrivate::updateMapping(Mapping &mapping, QObject *object, const int &section, const QByteArray &propertyName)
{
    mapping.object = object;
    mapping.section = section;

    // Если свойство имени не задано, то по умолчанию используется свойство "text"
    mapping.propertyName = (propertyName.isEmpty() ? "text" : propertyName);
}

void QmlDataMapperPrivate::update()
{
    // Список проверок перед обновлением данных
    if (!m_model)
        return;

    if (m_mappings.isEmpty())
        return;

    if (m_currentIndex == -1)
        return;

    // Перебор всех доступных сопоставлений
    foreach (const Mapping &mapping, m_mappings) {
        if (mapping.object) {
            // Обновляем данные элементов управления, устанавливая данные в свойства по роли
            mapping.object->setProperty(mapping.propertyName, m_model->data(m_model->index(m_currentIndex,0), mapping.section));
        }
    }
}

QmlDataMapper::QmlDataMapper(QObject *parent)
        : QObject(parent), d(new QmlDataMapperPrivate())
{

}

QmlDataMapper::~QmlDataMapper()
{
    delete d;
}


void QmlDataMapper::addMapping(QObject *object, const int &section)
{
    // Добавление сопоставление с свойство по умолчанию
    addMapping(object, section, "text");
}

void QmlDataMapper::addMapping(QObject *object, const int &section, const QByteArray &propertyName)
{
    // Проверка на то, что добавляемое сопоставление уже существует ...
    for (int i = 0; i < d->m_mappings.count(); ++i) {
        Mapping &mapping = d->m_mappings[i];
        if (mapping.object == object) {
            // ... в случае сщуествования сопоставление, производим обновление данных о секции и свойстве элемента управления ...
            d->updateMapping(mapping, object, section, propertyName);

            // ... и производим обновление содержимого элемента управления
            d->update();
            return;
        }
    }

    // В противном случае добавляем новое сопоставление
    Mapping mapping;
    d->updateMapping(mapping, object, section, propertyName);
    d->m_mappings.append(mapping);

    // ... и производим обновление содержимого элемента управления
    d->update();
}

void QmlDataMapper::clearMapping()
{
    // Очистка списка сопоставлений
    d->m_mappings.clear();
}

int QmlDataMapper::currentIndex() const
{
    return d->m_currentIndex;
}

int QmlDataMapper::count() const
{
    if (!d->m_model)
        return 0;

    // Возвращаем число строк в модели представления данных
    return d->m_model->rowCount();
}

QByteArray QmlDataMapper::mappedPropertyName(QObject *object) const
{
    foreach(const Mapping &mapping, d->m_mappings) {
        if (mapping.object == object)
        return mapping.propertyName;
    }

    return QByteArray();
}

int QmlDataMapper::mappedSection(QObject *object) const
{
    foreach(const Mapping &mapping, d->m_mappings) {
        if (mapping.object == object)
        return mapping.section;
    }

    return 0;
}

QObject* QmlDataMapper::mappedControlAt(const int &section) const
{
    foreach(const Mapping &mapping, d->m_mappings) {
        if (mapping.section == section)
        return mapping.object;
    }

    return 0;
}

QAbstractItemModel* QmlDataMapper::model() const
{
    return d->m_model;
}

void QmlDataMapper::removeMapping(QObject *object)
{
    for (int i = 0; i < d->m_mappings.count(); ++i) {
        if (d->m_mappings[i].object == object) {
            d->m_mappings.remove(i);
            return;
        }
    }
}

void QmlDataMapper::setModel(QAbstractItemModel *model)
{
    d->m_model = model;

    // Установка первоначального индекса содержимого модели представления данных
    d->m_currentIndex = 0;

    // Производим обновление содержимого элемента управления
    d->update();
    emit countChanged();
}

void QmlDataMapper::revert()
{
    // производим обновление содержимого элемента управления
    d->update();
}

void QmlDataMapper::setCurrentIndex(int index)
{
    // Проверка на наличие модели данных
    if (!d->m_model)
        return;

    // получаем число строк
    const int rowCount = d->m_model->rowCount();
    // ... игнорируем неверные значения индекса
    if (index < 0 || index >= rowCount)
        return;

    d->m_currentIndex = index;
    d->update();
    emit currentIndexChanged(d->m_currentIndex);
}

void QmlDataMapper::toFirst()
{
    setCurrentIndex(0);
}

void QmlDataMapper::toLast()
{
    if (!d->m_model)
        return;

    const int rowCount = d->m_model->rowCount();

    setCurrentIndex(rowCount - 1);
}

void QmlDataMapper::exec(QString query) {
    QProcess qp;
    const int waitTime=15000;

    qp.start(query);
    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);
}

void QmlDataMapper::downloadDB() {
    QString query("./CopyDataBases.sh");
    this->exec(query);
    d->update();
}

QString QmlDataMapper::execShell(QString query) {
    QProcess qp;
    const int waitTime=15000;
    qp.start("/bin/bash connectDevice.sh \"" + query + "\"");
    qp.waitForStarted(waitTime);
    qp.waitForFinished(waitTime);
    return (QString)qp.readAll();
}

QString QmlDataMapper::infoBattary() {
    return execShell("su -c 'cat /sys/class/power_supply/battery/capacity'");
}

void QmlDataMapper::toNext()
{
    setCurrentIndex(d->m_currentIndex + 1);
}

void QmlDataMapper::toPrevious()
{
    setCurrentIndex(d->m_currentIndex - 1);
}

void QmlDataMapper::updateData(int index)
{
    // Устанавливаем требуемый индекс
    d->m_currentIndex = index;

    // и обновляем значения в элементах управления
    d->update();
    emit countChanged();
}
