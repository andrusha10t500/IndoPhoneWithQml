#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <qmldatamapper.h>
#include <database.h>
#include <model.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /// Инициализируем базу данных
    DataBase database;

    /// Объявляем и инициализируем модель представления данных
    Model *model = new Model();
    /** Поскольку Мы отнаследовались от QSqlQueryModel, то
     * для выборки данных нам необходимо выполнить SQL-запрос,
     * в котором мы выберем все необходимы поля из нужной нам таблицы
     * */
//    model->setQuery("SELECT " TABLE_DATE ", " TABLE_TIME ", " TABLE_RANDOM ", " TABLE_MESSAGE
//                   " FROM " TABLE);
//    model->setQuery("select * from SMS");

    model->setQuery("attach database 'SMS/contacts2.db' as contacts;");

    model->setQuery("select b.display_name, address, datetime(substr(date,0,length(date)-2), 'unixepoch', 'localtime') as date_, body "
                     "from sms a "
                     "left join (select a.display_name, b.normalized_number from contacts.raw_contacts a "
                     "inner join contacts.phone_lookup b on a._id = b.raw_contact_id group by 2) b on a.address=b.normalized_number "
                     "order by 3 desc;");

    // Объявляем и инициализируем объект QmlDataMapper
    QmlDataMapper *mapper = new QmlDataMapper();
    mapper->setModel(model);

    /** А это уже знакомо из уроков по сигналам и слотам в QML
     * Помещаем полученную модель в контекст QML, чтобы была возможность
     * обращаться к модели по имени "myModel"
     * */
    engine.rootContext()->setContextProperty("myModel", model);

    /* А также даём доступ к Mapper в контексте QML
     * */
    engine.rootContext()->setContextProperty("mapper", mapper);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

