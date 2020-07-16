#include "model.h"

Model::Model(QObject *parent) :
    QSqlQueryModel(parent)
{
    // Конструктор будет пустой ;-)
}

// Метод для получения данных из модели
QVariant Model::data(const QModelIndex & index, int role) const {

    // Определяем номер колонки, адрес так сказать, по номеру роли
    int columnId = role - Qt::UserRole - 1;
    // Создаём индекс с помощью новоиспечённого ID колонки
    QModelIndex modelIndex = this->index(index.row(), columnId);

    /* И с помощью уже метода data() базового класса
     * вытаскиваем данные для таблицы из модели
     * */
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

// Метод для получения имен ролей через хешированную таблицу.
QHash<int, QByteArray> Model::roleNames() const {
    /* То есть сохраняем в хеш-таблицу названия ролей
     * по их номеру
     * */
//    QHash<int, QByteArray> roles;
//    roles[DateRole] = "date";
//    roles[TimeRole] = "time";
//    roles[RandomRole] = "random";
//    roles[MessageRole] = "message";
//    return roles;
    QHash<int, QByteArray> roles;
//    roles[DateRole] = "date";
    roles[NameContact] = "name";
    roles[Telefone] = "tel";
    roles[Date] = "dat";
    roles[Message] = "msg";
    return roles;
}
