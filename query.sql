SELECT count(*) FROM media_markt.product p1 join eldorado.product p2 on p1.name = p2.name;

#eldorado
#media_markt
#parser

SELECT * FROM media_markt.product;

#временная таблица
create table if not exists temp_data
(sourse nvarchar(200),id int,
har_value nvarchar(500),
prod nvarchar(500));

#заполнение артиклами и названием продуктов
insert into parser.temp_data(sourse,id,har_value,prod) 
select 'parser',p.id,v.har_value,p.name prod
	from hars_values v  join hars h on v.har_id = h.id
						join product p on v.prod_id=p.id and h.cat_id = p.cat_id 
where h.name = 'Артикул'
;

'30 116'
'1 277'
'29 986';
select  30116-29986;

#уникальных '30 146'

;
select count(distinct har_value) from parser.temp_data;
;
select count(*) from (
select har_value,count(*),GROUP_CONCAT(sourse)
from parser.temp_data
where sourse = 'eldorado'
group by har_value
having count(*)>1 ) s;



select * from (select har_value
				from parser.temp_data
					where sourse = 'eldorado') s1 left join 
			  (select har_value
				from parser.temp_data
					where sourse = 'parser') s2 on s1.har_value = s2.har_value
where s2.har_value is null;


select count(*) from (select har_value
				from parser.temp_data
					where sourse in ('eldorado','parser')) s1 join 
			  (select har_value
				from parser.temp_data
					where sourse = 'media_markt') s2 on s1.har_value = s2.har_value
                    ;