# Общая информация #
На данный момент для нашего проекта используется buildbot 0.8.4<br>
<a href='http://ubermipt.com:8080/waterfall'>http://ubermipt.com:8080/waterfall</a><br>

Любой желающий может попробовать поднять свою копию buildbot локально.<br>
<br>
Для желающих настроить собственный buildbot для своего проекта (вне mipt-course) я специально закоммитил вначале sample master.cfg, чтобы можно было легко посмотреть <a href='http://code.google.com/p/mipt-course/source/diff?spec=svn151&old=33&r=77&format=side&path=%2Fbuildbot%2Fmaster.cfg'>чем же наш master.cfg отличается от примера</a>.<br>
<br>
Документация по buildbot доступна по адресу <a href='http://buildbot.net/buildbot/docs/0.8.4/'>http://buildbot.net/buildbot/docs/0.8.4/</a>

<h1>Процедура установки buildbot на Linux Ubuntu Lucid 10.4</h1>
<h2>Краткая инструкция</h2>
<ul><li>Устанавливаем необходимые пакеты<br>
</li><li>Заводим пользователей для master и slaves (это необязательно при локальном тестировании)<br>
</li><li>Настраиваем и стартуем master<br>
</li><li>Проверяем через <a href='http://localhost:8010/waterfall'>http://localhost:8010/waterfall</a> , что он запустился<br>
</li><li>Настраиваем и стартуем slave'ы<br>
</li><li>Проверяем через <a href='http://localhost:8010/waterfall'>http://localhost:8010/waterfall</a> , что они подсоединились к мастеру<br>
</li><li>Делаем необходимые изменения в мастере, вызываем <code>make reconfig log</code>
</li><li>Для принудительного запуска билда нажимаем на странице slave'а кнопку "Force build"<br>
</li><li>(при необходимости) переходим на шаг "делаем необходимые изменения"</li></ul>

<h2>Общее для master и slaves</h2>
<pre><code>sudo -i  # Предполагается что все выполняется под root в некоторой папке<br>
<br>
apt-get install python-twisted<br>
<br>
wget http://pypi.python.org/packages/source/d/distribute/distribute-0.6.14.tar.gz#md5=ac607e05682116c06383b27a15e2db90<br>
tar xzf distribute-0.6.14.tar.gz<br>
cd distribute-0.6.14<br>
python distribute_setup.py<br>
cd ..<br>
<br>
wget http://pypi.python.org/packages/source/J/Jinja2/Jinja2-2.5.5.tar.gz#md5=83b20c1eeb31f49d8e6392efae91b7d5<br>
tar xzf Jinja2-2.5.5.tar.gz<br>
cd Jinja2-2.5.5<br>
python setup.py install<br>
cd ..<br>
</code></pre>

<h2>master-only</h2>
<pre><code># Это делается пользователем root<br>
wget http://buildbot.googlecode.com/files/buildbot-0.8.4.zip<br>
unzip buildbot-0.8.4.zip<br>
cd buildbot-0.8.4<br>
python setup.py build &amp;&amp; python setup.py install<br>
cd ..<br>
</code></pre>

<pre><code># Это уже делается пользователем buildbot-master в папке, в которой ему можно хранить файлы<br>
buildbot create-master -r .<br>
<br>
svn checkout http://mipt-course.googlecode.com/svn/buildbot .<br>
# В конце master.cfg находим строку "forceBuild = False," и меняем False на True.<br>
make start log<br>
</code></pre>

<h2>slave-only</h2>
<pre><code># Это делается пользователем root<br>
wget http://buildbot.googlecode.com/files/buildbot-slave-0.8.4.zip<br>
unzip buildbot-slave-0.8.4.zip<br>
cd buildbot-slave-0.8.4<br>
python setup.py build &amp;&amp; python setup.py install<br>
cd ..<br>
</code></pre>

<pre><code># Это уже делается пользователем buildbot-slave в папке, в которой ему можно хранить файлы<br>
buildslave create-slave . localhost:9989 &lt;имя Slave, например linux_bot&gt; &lt;пароль Slave, например bot1passwd&gt;<br>
buildslave start<br>
tail -f twistd.log<br>
</code></pre>