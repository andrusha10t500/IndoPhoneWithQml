#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QSqlQueryModel>

class Model : public QSqlQueryModel
{
    Q_OBJECT
public:
    /* Перечисляем все роли, которые будут использоваться в TableView
     * Как видите, они должны лежать в памяти выше параметра Qt::UserRole
     * Связано с тем, что информация ниже этого адреса не для кастомизаций
     * */

    enum Roles {
//        DateRole
        NameContact = Qt::UserRole + 1,
        Telefone,
        Date,
        Message
    };
//    enum Roles {
//        DateRole = Qt::UserRole + 1,    // дата
//        TimeRole,                       // время
//        RandomRole,                     // псевдослучаное число
//        MessageRole                     // сообщение
//    };

    // объявляем конструктор класса
    explicit Model(QObject *parent = 0);

    // Переопределяем метод, который будет возвращать данные
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    /* хешированная таблица ролей для колонок.
     * Метод используется в дебрях базового класса QAbstractItemModel,
     * от которого наследован класс QSqlQueryModel
     * */
    QHash<int, QByteArray> roleNames() const;

signals:

public slots:
};

#endif // MODEL_H
