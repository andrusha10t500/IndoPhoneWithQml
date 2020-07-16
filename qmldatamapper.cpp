/****************************************************************************
 ** Ниже следующий программный код является результатом доработки программного
 ** кода для платформы BlackBerry 10 из Qt Toolkit и также распростряется
 ** по ниже следующей лицензии, которая была применена к исходному програмному коду
 **
 ** EVILEG - Evgenii Legotckoi - 2015
 ** Contact: http://www.evileg.ru/kontaktnaya-informatsiya
 ** Contact: Evgenii Legotckoi (legotskoy@gmail.com)
 ** Contact: Евгений Легоцкой (legotskoy@gmail.com)
 ** All rights reserved.
 ****************************************************************************/

/****************************************************************************
 **
 ** Portions Copyright (C) 2012 Research In Motion Limited.
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Research In Motion Ltd. (http://www.rim.com/company/contact/)
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the BB10 Platform and is derived
 ** from a similar file that is part of the Qt Toolkit.
 **
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Research In Motion, nor the name of Nokia
 **     Corporation and its Subsidiary(-ies), nor the names of its
 **     contributors may be used to endorse or promote products
 **     derived from this software without specific prior written
 **     permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ****************************************************************************/

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
