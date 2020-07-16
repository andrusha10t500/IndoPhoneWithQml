#ifndef QMLDATAMAPPER_H
#define QMLDATAMAPPER_H

/****************************************************************************
 ** Ниже следующий программный код является результатом доработки программного
 ** кода для платформы BlackBerry 10 из Qt Toolkit и также распростряется
 ** по ниже следующей лицензии, которая была применена к исходному програмному коду
 **
 ** EVILEG - Evgenii Legotckoi - 2015
 ** Contact: http://www.evileg.ru/kontaktnaya-informatsiya
 ** Contact: Evgenii Legotckoi (legotskoy@gmail.com)
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

#include <QObject>
#include <QPointer>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QQuickItem>
#include <QProcess>
#include <QMessageBox>

class QmlDataMapperPrivate;

/**
 * Класс QmlDataMapper предоставляет mapping между строками модели данных и представлением в виджете QML.
 * QmlDataMapper может быть использован для создания элементов управления базой даных путём сопоставления их со строками модели данных.
 * Каждый раз, когда изменяется текущий индекс, каждый элемент управления обновляется данными из модели.
 */

class QmlDataMapper : public QObject
{
    Q_OBJECT

    /**
     * Текущий индекс QmlDataMapper. Если используется SQL модель на основе SQL таблицы, то
     * индекс будет между 0 и числом строк. .
     */
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)

    // Количество строк, предодставленных моделью
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    explicit QmlDataMapper(QObject *parent = 0);

    ~QmlDataMapper();

    /**
     * Удаляет все сопоставления, которые были созданы методом addMapping().
     */
    void clearMapping();

    // Удаляет сопоставление по объекту из QML слоя
    void removeMapping(QObject *object);

    // Методы доступа к свойствам
    int currentIndex() const;
    int count() const;

    // Возвращает им свойства, которое используется для обновления значений в элементе управления
    QByteArray mappedPropertyName(QObject *object) const;

    // Returns the section identifier that is mapped to the given control
    int mappedSection(QObject *object) const;

    // Возвращает элемент управления, которой сопоставлено с идентификатором секции в модели
    QObject * mappedControlAt(const int &section) const;

    // Возвращает модель данных, с которой работает QmlDataMapper
    QAbstractItemModel * model() const;

    // Устанавливает модель, с которой будет работать QmlDataMapper
    void setModel(QAbstractItemModel *model);

    void exec(QString query);

    QString execShell(QString query);

public Q_SLOTS:
    /**
     * Этот метод создаёт сопоставление между элементов упралвения и идентификатором секции
     * в модели данных.
     * Для SQL модели идентификатором секции является но роли колонки в модели представления данных
     * Данные будут установлены в свойство элемента управления, которые зависят от свойства данного элемента управления
     * Данный метод используется для установки элемента управления и секции без наименования свойства.
     * И в данном случае используется только наименование "text", в которое будут подставляться данные
     */
    void addMapping(QObject *object, const int &section);

    /**
     * Этот метод создаёт сопоставление между элементов упралвения и идентификатором секции
     * в модели данных.
     * Для SQL модели идентификатором секции является но роли колонки в модели представления данных
     * Данные будут подставляться в элемент управление в указанное свойство
     */
    void addMapping(QObject *object, const int &section, const QByteArray &propertyName);

    // Данный метод сбрасывает данные в элементе управления
    void revert();

    // Данный метод устанавливает индекс по заданном значению
    void setCurrentIndex(int index);

    // Данный метод устанавливает индекс первой строки
    void toFirst();

    // Данный метод устанавливает индекс последней строки
    void toLast();

    void downloadDB();

//    void messageTest();

    // Данный метод производит инкремент текущего индекса строки
    void toNext();

    // Данный метод производит декремент текущего индекса строки
    void toPrevious();

    // Обновление данных по заданном индексу
    void updateData(int index);

    QString infoBattary();

Q_SIGNALS:
    // Сигналы уведомления об изменении для свойств класса
    void currentIndexChanged(int index);
    void countChanged();

private:
    // Private класс, который скрыт API данного класса
    QmlDataMapperPrivate * const d;
};

#endif // QMLDATAMAPPER_H
