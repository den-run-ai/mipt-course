#!/usr/bin/python
# -*- coding: utf-8 -*-

# Example of rexexps
# This code shows you latest bash.org.ru quotes
# This code is also good sample of situation, when the result is
# much more important than anything else :)

import re
import urllib2

response = urllib2.urlopen("http://bash.im").read()
response = response.decode('cp1251')

rg = re.compile(u'(утверждена[^<]*\s*</div>\s*<div>[^<]*(<br>[^<]*)*</div>)')
rg1 = re.compile('(<div>[^<]*(<br>[^<]*)*</div>)')
r = rg.findall(response)
res = []
for m in r:
    res.append( rg1.findall(m[0])[0][0][5:-6] )

# TODO: built-in function for that?
res = map(lambda s: re.sub('<br>','\n',s) ,res)
res = map(lambda s: re.sub('&quot;','"',s) ,res)
for m in res:
    print "------"
    print m

print "Total: %d quote(s)" % len(r)
