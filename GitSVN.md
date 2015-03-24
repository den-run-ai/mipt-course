**N.B. Эта страница ещё сильно не готова - скопировано as-is из одного моего старого wave'а,**<br>
не предназначенного для студентов.<br>
<br>
<h2>Создать репозиторий в локальной папке DIRECTORY</h2>
<pre><code>git svn clone --trunk=https://PROJNAME.googlecode.com/svn/trunk DIRECTORY --username=USERNAME<br>
</code></pre>
<i>Опционально: если делается <code>clone</code> большого репозитория, то имеет смысл делать <a href='http://stackoverflow.com/questions/747075/how-to-git-svn-clone-the-last-n-revisions-from-a-subversion-repository'>shallow copy</a>, например <code>-rREV:HEAD</code>. Иначе git-svn будет дооолго скачивать всю историю с SVN сервера :)</i>

<b>Совет</b>: все локальные изменения делать в бранчах, не трогая trunk.<br>
<br>
<h2>Update</h2>
<pre><code>git svn fetch &amp;&amp; git rebase trunk MYBRANCH<br>
</code></pre>

<h2>Code review</h2>
<pre><code>./upload.py --rev=trunk        # в первый раз<br>
# или<br>
./upload.py --rev=trunk -i XYZ # в последующие разы указывайте номер changelist'а XYZ<br>
</code></pre>
Примечание: на rietveld посылается фактически<br>
git diff REV # REV=trunk<br>
т.е. все ваши коммиты относительно trunk будут объединены в один патч (сравните с dcommit)<br>
<br>
<h2>Залить коммиты относительно trunk в SVN</h2>
<pre><code>git svn dcommit<br>
</code></pre>
Другими словами, dcommit делает так, что в SVN оказывается такая же история, как та,<br>
что находится в текущем локальном бранче.<br>
Если у вас локально 10 коммитов относительно того, что лежит в SVN, то dcommit сделает в SVN 10 коммитов. С теми же комментариями, что были указаны в локальных коммитах (сравните с upload.py).<br>
Чтобы залить всё одним патчем, делайте <code>git merge squash</code> и/или <code>git commit --amend</code> или читайте <a href='http://www-cs-students.stanford.edu/~blynn/gitmagic/ch05.html'>уроки истории</a> и да прибудет с вами Сила.