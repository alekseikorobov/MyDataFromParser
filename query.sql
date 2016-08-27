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

select * from parser.temp_data
where har_value = 'KBM-01';

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

SET SQL_SAFE_UPDATES = 0;

select p.id,v.har_value
             		from hars_values v  join hars h on v.har_id = h.id
                 						join product p on v.prod_id=p.id and h.cat_id = p.cat_id 
                 where h.name = 'Артикул';
                 
insert into skus_temp(name) values('71121480'),('71122362'),('71095598'),('71122106');

create temporary table if not exists skus_temp(id int auto_increment primary key,name varchar(100), 
	prise varchar(100),count int,prod_id int) DEFAULT CHARACTER SET cp1251 COLLATE cp1251_general_ci;
	ALTER TABLE skus_temp ADD UNIQUE INDEX in_id (id ASC); 
	ALTER TABLE skus_temp ADD INDEX in_prod (prod_id ASC); 

update skus_temp s 
             join (select p.id,v.har_value
             		from hars_values v  join hars h on v.har_id = h.id
                 						join product p on v.prod_id=p.id and h.cat_id = p.cat_id 
                 where h.name = 'Артикул') v1 on v1.har_value = s.name
               set prod_id = v1.id;

create temporary table if not exists temp_data(id int,har_value nvarchar(500),name nvarchar(500),prod nvarchar(500),image nvarchar(255),brand nvarchar(255)) 
	DEFAULT CHARACTER SET cp1251 COLLATE cp1251_general_ci; 
	ALTER TABLE temp_data ADD INDEX in_prod_id (id ASC); 
	ALTER TABLE temp_data ADD INDEX in_name (`name` ASC); 
	truncate table temp_data; 
	insert into temp_data(id,har_value,name,prod,image,brand)  
	select p.id,v.har_value,h.name,p.name prod,p.image,p.brand from hars_values v join hars h on v.har_id = h.id    
					   join product p on v.prod_id=p.id and h.cat_id = p.cat_id 
	where p.id in (select prod_id from skus_temp);
    
select count(distinct name) from temp_data;

select t1.id,t1.prod,t1.artic,concat('1',LPAD(t1.id,5,'0')) art,t1.prise,t1.count,t1.htm,t1.brand,
  concat(t1.image,ifnull(concat(';',GROUP_CONCAT(i.name SEPARATOR ';')),'') ) as i  
from (
SELECT dt.id,dt.prod,st.name artic,st.prise,st.count,dt.image,dt.brand
#,GROUP_CONCAT(concat('<li><b>',replace(dt.name,'&#730;',''),'</b> : ',replace(replace(dt.har_value,'&nbsp;',''),';',',')) SEPARATOR  '</li>')  as xm,
,GROUP_CONCAT(concat('<tr><td>',dt.name,'</td><td>',dt.har_value,'</td>') SEPARATOR '</tr>')  as htm 
FROM (select id,har_value,name,prod,image,brand from temp_data where name <> 'Артикул' ) as dt  
				   join skus_temp st on st.prod_id = dt.id 
group by dt.id,dt.prod,st.name,st.prise,st.count,dt.image,dt.brand) t1 left join images i on t1.id = i.prod_id  
group by t1.id,t1.prod,t1.artic,t1.prise,t1.count,t1.htm,t1.image,t1.brand
order by t1.id;