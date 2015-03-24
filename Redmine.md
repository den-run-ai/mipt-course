## Введение ##

Здесь описано, как поднимать Redmine.

Все действия производились на свежеустановленной Ubuntu 11.10, что не должно сильно отличаться от установки под Ubuntu 10.04.


# Простой способ #
Устанавливаем необходимые пакеты:
```
sudo apt-get install redmine-mysql apache2 libapache2-mod-passenger
sudo apt-get install redmine
```

Если при установке спросят какую использовать DB - выбрать SQLite. (**TODO**: или есть причины выбрать PostgreSQL?)

Проверяем работоспособность Apache-сервера, открыв в браузере `http://myserveraddress:80`<br>(Например, myserveraddress=<code>127.0.0.1</code>)<br>
<br>
Если он не работает, надо попробовать запустить его вручную:<br>
<pre><code>sudo /etc/init.d/apache2 start<br>
</code></pre>

Создаём ссылку на содержимое Redmine в <code>/var/www</code>:<br>
<pre><code>sudo ln -s /usr/share/redmine/public /var/www/redmine<br>
</code></pre>

И, наконец, конфигурируем Apache чтобы он запускал нужные скрипты - из под <code>root</code> редактируем файл <code>/etc/apache2/sites-available/default</code>, добавляя туда следующую секцию:<br>
<br>
<pre><code>&lt;VirtualHost *:80&gt;<br>
....................<br>
  &lt;Directory "/var/www/redmine"&gt;<br>
    RailsEnv production<br>
    RailsBaseURI /redmine<br>
  &lt;/Directory&gt;<br>
&lt;/VirtualHost&gt;<br>
</code></pre>

и перезапускаем его:<br>
<pre><code>sudo /etc/init.d/apache2 restart<br>
</code></pre>

Теперь Redmine должен быть доступен по адресу <code>http://myserveraddress:80/redmine</code>

Логин/пароль = admin/admin<br>
<br>
Пароль рекомендуется сразу же поменять :)<br>
<br>
<h2>Настройка e-mail уведомлений</h2>
<b>TODO</b> Обновить<br>
<br>
Кажется, вначале я использовал <a href='http://www.redmine.org/projects/redmine/wiki/HowTo_Install_Redmine_in_Ubuntu#Sendmail-Server-Configuration'>`delivery_method: :async_sendmail`</a>
а затем отредактировал <code>hostname</code> и <code>/etc/hosts</code> чтобы получить правильные <code>From:</code> адрес.<br>
Но оно не очень дружило со спам-фильтрами.<br>
<br>
Позже я перешёл на <code>async_smtp</code> с дополнительным почтовым ящиком.<br>
<br>
<b>Готово!</b>