#include "worker.h"
#include <QFile>
#include <QMap>

worker::worker(QObject *parent) :
    QObject(parent)
{
}

void worker::init(){
    q.clear();
    q.insert("&quot;","\"");
    q.insert("&amp;","&");
    q.insert("&lt;","<");
    q.insert("&gt;",">");
    q.insert("&nbsp;","");
    q.insert("&iexcl;"," ");
    q.insert("&cent;"," ");
    q.insert("&pound;"," ");
    q.insert("&curren;","¤");
    q.insert("&yen;"," ");
    q.insert("&brvbar;","¦");
    q.insert("&sect;","§");
    q.insert("&uml;"," ");
    q.insert("&copy;","©");
    q.insert("&ordf;"," ");
    q.insert("&laquo;","«");
    q.insert("&not;","¬");
    q.insert("&shy;","");
    q.insert("&reg;","®");
    q.insert("&macr;"," ");
    q.insert("&deg;","°");
    q.insert("&plusmn;","±");
    q.insert("&sup2;"," ");
    q.insert("&sup3;"," ");
    q.insert("&acute;"," ");
    q.insert("&micro;"," ");
    q.insert("&para;","¶");
    q.insert("&middot;","·");
    q.insert("&cedil;"," ");
    q.insert("&sup1;"," ");
    q.insert("&ordm;"," ");
    q.insert("&raquo;","»");
    q.insert("&frac14;"," ");
    q.insert("&frac12;"," ");
    q.insert("&frac34;"," ");
    q.insert("&iquest;"," ");
    q.insert("&Agrave;","A");
    q.insert("&Aacute;","A");
    q.insert("&Acirc;","A");
    q.insert("&Atilde;","A");
    q.insert("&Auml;","A");
    q.insert("&Aring;","A");
    q.insert("&AElig;"," ");
    q.insert("&Ccedil;","C");
    q.insert("&Egrave;","E");
    q.insert("&Eacute;","E");
    q.insert("&Ecirc;","E");
    q.insert("&Euml;","E");
    q.insert("&Igrave;","I");
    q.insert("&Iacute;","I");
    q.insert("&Icirc;","I");
    q.insert("&Iuml;","I");
    q.insert("&ETH;"," ");
    q.insert("&Ntilde;","N");
    q.insert("&Ograve;","O");
    q.insert("&Oacute;","O");
    q.insert("&Ocirc;","O");
    q.insert("&Otilde;","O");
    q.insert("&Ouml;","O");
    q.insert("&times;"," ");
    q.insert("&Oslash;","O");
    q.insert("&Ugrave;","U");
    q.insert("&Uacute;","U");
    q.insert("&Ucirc;","U");
    q.insert("&Uuml;","U");
    q.insert("&Yacute;","Y");
    q.insert("&THORN;"," ");
    q.insert("&szlig;"," ");
    q.insert("&agrave;","a");
    q.insert("&aacute;","a");
    q.insert("&acirc;","a");
    q.insert("&atilde;","a");
    q.insert("&auml;","a");
    q.insert("&aring;","a");
    q.insert("&aelig;"," ");
    q.insert("&ccedil;","c");
    q.insert("&egrave;","e");
    q.insert("&eacute;","e");
    q.insert("&ecirc;","e");
    q.insert("&euml;","e");
    q.insert("&igrave;","i");
    q.insert("&iacute;","i");
    q.insert("&icirc;","i");
    q.insert("&iuml;","i");
    q.insert("&eth;"," ");
    q.insert("&ntilde;","n");
    q.insert("&ograve;","o");
    q.insert("&oacute;","o");
    q.insert("&ocirc;","o");
    q.insert("&otilde;","o");
    q.insert("&ouml;","o");
    q.insert("&divide;"," ");
    q.insert("&oslash;","o");
    q.insert("&ugrave;","u");
    q.insert("&uacute;","u");
    q.insert("&ucirc;","u");
    q.insert("&uuml;","u");
    q.insert("&yacute;","y");
    q.insert("&thorn;"," ");
    q.insert("&yuml;","y");
    q.insert("&euro;","€");
}

QString worker::myReplaceMask(QString str){
    QRegExp rx("&#(\\d+);");
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        int charInt = QVariant(rx.cap(1)).toInt();
        QChar ch(charInt);
        QString replaceTo = str.mid(pos,rx.matchedLength());
        str = str.replace(replaceTo,QString(ch));
        pos += rx.matchedLength();
        pos -= (replaceTo.size() - 1);


    }
    return str;
}
QString worker::myReplace(QString str){
    QString keyChar = ";";
    str = myReplaceMask(str);
    if(str.indexOf(keyChar) == -1) return str;
    QRegExp rx("&([A-z]+);");
    int pos = 0;
    while ((pos = rx.indexIn(str, pos)) != -1) {
        QString replaceTo = str.mid(pos,rx.matchedLength());
        QString val = q[replaceTo];
        if(!val.isEmpty()) str = str.replace(replaceTo,val);
        pos += rx.matchedLength();
        pos -= (replaceTo.size() - val.size());
    }
    if(str.indexOf(keyChar) != -1) str = str.replace(keyChar," ");
    return str;
}

int worker::findHar(QString str){
    for (int i = 0; i < har.size(); ++i)
        if(har[i].key == str) return i;
    return -1;
}
QString worker::getStringJoinVal(){
    QString res = "";
    foreach (data dt, har) {
        res += dt.val;
    }
    return res;
}

QString worker::getStringJoinKey(){
    QString res = "";
    foreach (data dt, har) {
        res += dt.key + ";";
    }
    return res;
}

QString worker::getKey(QString str){
    QString pat = "<tr><td>([^<]*)</td><td>([^<]*)</td></tr>";
    QRegExp rx(pat);

    int pos = 0;
    //Сначала обнуляем все значения которые есть в списке
    foreach (data dt, har) {
        dt.val =";";
    }

    //далее заполняем все значения, если есть - обновляем, если нет - говорим об ошибки
    while ((pos = rx.indexIn(str, pos)) != -1) {

        QString key = rx.cap(1);
        QString val = rx.cap(2);
        int index = findHar(key.toLower().trimmed());
        if(index==-1) listError.append( "Поле не найдено!-" + key.toLower().trimmed());
        else har[index].val = val+ ";";

        pos += rx.matchedLength();
    }

    //вернуть форматированные значения
    return getStringJoinVal();
}


//заполнения характеристиками
bool worker::appendHaract(){
    string getcountString = "select distinct(BINARY trim(lower(name))),trim(lower(name)) from temp_data;";
    string har_q = "";
    if(!db->exec(getcountString)){
        listError.append("Не удалось выполнить запрос select distinct name from temp_data; - " + db->lastError);
        //emit onComplit();
        return false;
    }
    while(db->query->next()){
        har_q = myReplace(db->query->value(1).toString().toLower());
        if(fullhar.indexOf(har_q) != -1)
            har.append(data(har_q,";"));
    }

    qDebug() << "Всего характеристик " << har.size();
}
//НЕОБХОДИМО СДЕЛАТЬ СТАТИЧЕСКИМ!!!!
bool worker::append_Full_Haract(){

    string str = "select c.cat_name,name,count(*) from hars h join hars_values hv on h.id = hv.har_id "
                            " join category c on h.cat_id = c.id "
                            " where cat_name  not like 'Market.yandex.ru%' "
                            " and cat_name not like 'Wikimart.ru%' "
                " group by c.cat_name,name "
                " order by cat_name,count(*) desc;";
    int maxCountHar = 15;                                                   // максимальное количество характеристик для каждой категории

    if(!db->exec(str)){
        listError.append("Не удалось выполнить запрос из appendHaract; - " + db->lastError);
        return false;
    }
    string cat_name = "";                                                   // название текущей категории
    string har_q = "";
    int id_part = 1;
    while(db->query->next()){                                               // по каждой строке из базы данных
        string cat_name_q = db->query->value(0).toString();                 //запоминаем категорию
        if(cat_name != cat_name_q){                                         //если текущая категория в памяти не равна данной строке
            cat_name = cat_name_q;                                          //то запомнить эту новую категорию
            id_part = 1;                                                    // и начать счетчик заново
        }
        else{
            id_part++;                                                      //а иначе мы продолжаем по той же категории, и увеличиваем счетчик
        }
        if(id_part<=maxCountHar){                                           //проверяем какой сейчас счетчик, если он меньше заданного
            har_q = myReplace(db->query->value(1).toString().toLower() );   //то пытаемся занести в список характеристику


            if(fullhar.indexOf(har_q) == -1)                                        // если этой характеристики нет в списке
                fullhar.append(har_q);  //har.append(data(har_q,";"));                                // то заносим

        }
                                                                            //выходим к следующей итерации
    }
    return true;
}

string worker::getCratHaract(){
    string res = "<ul>";

    /*<ul>
            <li><b>Страна</b> : Малайзия</li>
            <li><b>Гарантия производителя</b> : 1 год</li>
            <li><b>Диагональ</b> : 32 (81.3 см)</li>
    </ul>*/
    foreach (data dt, har) {
        if(dt.val !=";"){
            res += "<li><b>"+dt.key+"</b> : "+dt.val+"</li>";
        }
    }
    res += "</ul>";
    return res;
}

void worker::Scan(){

    init();
    har.clear();
    QFile file(pathSave);
    file.remove();
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        listError.append("Не удалось создать или открыть файл");
        emit onComplit();
        return;
    }

    if(!db->exec("create temporary table if not exists skus_temp(id int auto_increment primary key,name varchar(100), "
                 "prise varchar(100),count int,prod_id int) DEFAULT CHARACTER SET cp1251 COLLATE cp1251_general_ci;"
                 " ALTER TABLE skus_temp ADD UNIQUE INDEX in_id (id ASC); "
                 " ALTER TABLE skus_temp ADD INDEX in_prod (prod_id ASC); "
                 ))
    {
        listError.append("Не удалось выполнить запрос create table skus_temp" + db->lastError);
        emit onComplit();
        return;
    }
    if(!db->exec("truncate table skus_temp;"))
    {
        listError.append("Не удалось выполнить запрос truncate table skus_temp;");
        emit onComplit();
        return;
    }
    if(!db->query->exec("SET SQL_SAFE_UPDATES = 0;")){
        listError.append("Не удалось выполнить запрос SET SQL_SAFE_UPDATES = 0;");
        emit onComplit();
        return;
    }
    foreach (string str, sl) {
        QStringList s = str.split(seporator);
        string art="",pr="",c="";
        if(s.size() > 4){
            listError.append("разделено больше 4х");
            emit onComplit();
            return;
        }
        if(s.size() == 4){
            art = s[0];
            pr = string(s[1]) +string(",") +string(s[2]);
            c = s[3];
            db->query->exec(string("insert into skus_temp(name,prise,count) values('%1','%2',%3)").arg(art,pr,c));
        }

        if(s.size() == 3){
            art = s[0];
            pr = s[1];
            c = s[2];
            db->query->exec(string("insert into skus_temp(name,prise,count) values('%1','%2',%3)").arg(art,pr,c));
        }
        if(s.size() == 2){
            art = s[0];
            pr = s[1];
            db->query->exec(string("insert into skus_temp(name,prise) values('%1','%2')").arg(art,pr));
        }
        if(s.size() == 1){
            art = s[0];
            db->query->exec(string("insert into skus_temp(name,prise) values('%1','%2')").arg(art,pr));
        }

    }

    //обновление продуктов
    string qup ="update skus_temp s "
                " join (select p.id,v.har_value"
                " 		from hars_values v  join hars h on v.har_id = h.id"
                " 						join product p on v.prod_id=p.id and h.cat_id = p.cat_id "
                " where h.name = 'Артикул') v1 on v1.har_value = s.name"
                " set prod_id = v1.id;";

    if(!db->query->exec(qup)){
        listError.append("Не удалось выполнить запрос update skus_temp s");
        emit onComplit();
        return;
    }
    string temp = "create temporary table if not exists temp_data(id int,har_value nvarchar(500),name nvarchar(500),prod nvarchar(500),image nvarchar(255),brand nvarchar(255),cat_name nvarchar(255)) "
                  " DEFAULT CHARACTER SET cp1251 COLLATE cp1251_general_ci; "
                  " ALTER TABLE temp_data ADD INDEX in_prod_id (id ASC); "
                  " ALTER TABLE temp_data ADD INDEX in_name (`name` ASC); "
                  " truncate table temp_data; "
                  " insert into temp_data(id,har_value,name,prod,image,brand,cat_name)  " //что делать если категории для товара нет??
                  " select p.id,v.har_value,h.name,p.name prod,p.image,p.brand,trim(substring(cat.cat_name,locate(':',cat.cat_name)+1)) "
                  "from hars_values v join hars h on v.har_id = h.id    "
                  " join product p on v.prod_id=p.id and h.cat_id = p.cat_id "
                  " join category cat on cat.id = p.cat_id "

                  " where p.id in (select prod_id from skus_temp);";

    if(!db->query->exec(temp)){
        listError.append("Не удалось создать временную таблицу temp_data");
        emit onComplit();
        return;
    }

    if(!append_Full_Haract()){
        emit onComplit();
        return;
    }

    if(!appendHaract()){
        emit onComplit();
        return;
    }

    if(!db->query->exec("SET global group_concat_max_len = 18446744073709551615;")){
        listError.append("Не удалось выполнить SET global group_concat_max_len =");
        emit onComplit();
        return;
    }
    string q = "select t1.id,ifnull(concat(t2.name,' (',concat('1',LPAD(t1.id,5,'0')),')'),t1.prod) prod,t1.artic,concat('1',LPAD(t1.id,5,'0')) art,t1.prise,t1.count,t1.htm,t1.brand, "
               " concat(t1.image,ifnull(concat(';',GROUP_CONCAT(i.name SEPARATOR ';')),'') ) as i ,t1.cat_name"
               " from ( "
               " SELECT dt.id,dt.prod,st.name artic,st.prise,st.count,dt.image,dt.brand,dt.cat_name "
               " ,GROUP_CONCAT(concat('<tr><td>',dt.name,'</td><td>',dt.har_value,'</td>') SEPARATOR '</tr>')  as htm  "
               " FROM (select id,har_value,name,prod,image,brand,cat_name from temp_data where name <> 'Артикул' ) as dt   "
               "                    join skus_temp st on st.prod_id = dt.id  "
               " group by dt.id,dt.prod,st.name,st.prise,st.count,dt.image,dt.brand,dt.cat_name) t1 left join images i on t1.id = i.prod_id   "
               "         left join (select name from product group by name having count(*)>1) t2 on t1.prod= t2.name "
               " group by t1.id,t1.prod,t2.name,t1.artic,t1.prise,t1.count,t1.htm,t1.image,t1.brand,t1.cat_name "
               " order by t1.id;";

    if(!db->exec(q)){
        listError.append("Не удалось выполнить запрос выборки всех данных - " + db->lastError);
        emit onComplit();
        return;
    }


    QStringList listRow;
    QString n = QString(";");
    while(db->query->next()){

        QString line;

        //t1.id 0,t1.prod 1,t1.artic 2 ,art 3 ,t1.prise 4 ,t1.count 5 ,t1.htm 6 ,t1.brand 7 , i 8 ,cat_name - 9

        line = myReplace(db->query->value(1).toString()) + n;///prod "Наименование"
        line += db->query->value(2).toString() + n;/// art "Артикула"
        QString qst = db->query->value(3).toString();
        line +=  qst + n;///artic "Наименование артикул"
        line +=  "RUB;";                                                        ///"Валюта"
        line +=  db->query->value(4).toString() + n;/// prise "Цена"
        line +=  "1;";///"Доступен для заказа")<<
        line += "0;";///"Зачеркнутая цена")<<
        line += "0;";///"Закупочная цена"
        line +=  db->query->value(5).toString() + n;/// count "В наличии"
        string polesHaracts = getKey(myReplace(db->query->value(6).toString() + QString("</tr>")));/// htm "Описание"
        //мы специально получаем все характеристики, чтобы можно было полученные данных добавить в краткое описание
        line += getCratHaract() + n;
        line += n;//Краткое описание;
        line += n;//Описание;
        line +=  n;/// "Наклейка")<<
        line +=  QString("1;");/// "Статус")<<
        line +=  db->query->value(9).toString()+ n;/// "Тип товаров")<<
        line +=  n;/// "Теги")<<
        line += n;/// "Облагается налогом")<<
        line +=  db->query->value(1).toString() + n;///prod "Заголовок")<<
        line +=  db->query->value(1).toString() + n;///prod "META Keywords")<<
        line +=  db->query->value(1).toString() + n;///prod "META Description")<<
        line +=  n;/// "Ссылка на витрину")<<
        line +=  n;/// "Дополнительные параметры" << n;
        line += polesHaracts;
        line += db->query->value(7).toString() + n;/// "Бренд"
        line += db->query->value(8).toString();/// img(;)
        line += QString("\n");

        listRow.append(line);
    }

    QTextStream out(&file);
    out.setCodec("windows-1251");
    out  <<QString("Наименование;")<<
           QString("Наименование артикула;")<<
           QString("Артикул;")<<
           QString("Валюта;")<<
           QString("Цена;")<<
           QString("Доступен для заказа;")<<
           QString("Зачеркнутая цена;")<<
           QString("Закупочная цена;")<<
           QString("В наличии;")<<
           QString("Краткое описание;")<<
           QString("Описание;")<<
           QString("Наклейка;")<<
           QString("Статус;")<<
           QString("Тип товаров;")<<
           QString("Теги;")<<
           QString("Облагается налогом;")<<
           QString("Заголовок;")<<
           QString("META Keywords;")<<
           QString("META Description;")<<
           QString("Ссылка на витрину;")<<
           QString("Дополнительные параметры;")
        << getStringJoinKey() ///все поля из характеристик
        <<QString("Бренд");

    for (int k = 0; k < 65; ++k) {
        out << QString(";Изображения");
    }
    out << QString("\n");
    foreach (QString line1, listRow) {
        out  << line1;
    }
    file.close();
    QString q1 = "select name,prise,count from skus_temp where prod_id is null;";
    if(!db->exec(q1)){
        listError.append("Не удалось выполнить запрос выборки всех данных - " + db->lastError);
        emit onComplit();
        return;
    }
    while(db->query->next()){
        listNot.append(db->query->value(0).toString() +string(seporator)+
                       db->query->value(1).toString() +string(seporator)+
                       db->query->value(2).toString()
                       );
    }

    QString q2 = "select id,min(har_value) from temp_data group by id having count(*) = 1 and min(`name`) = 'Артикул'";

    if(!db->exec(q2)){
        listError.append("Не удалось выполнить запрос выборки данных temp_data - " + db->lastError);
        emit onComplit();
        return;
    }
    while(db->query->next()){
        listNotHaract.append(db->query->value(1).toString());
    }
    emit onComplit();
}

bool worker::DeleteEmptyCat(){
    if(!db->query->exec("SET SQL_SAFE_UPDATES = 0;")){
        listError.append("Не удалось выполнить запрос SET SQL_SAFE_UPDATES = 0;");
        return false;
    }
    if(!db->query->exec("delete c from category c left join product p on c.id = p.cat_id where p.cat_id is null;")){
        listError.append("Не удалось выполнить запрос на удаление пустых категорий");
        return false;
    }

    return true;
}
