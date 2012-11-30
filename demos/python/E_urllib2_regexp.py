#!/usr/bin/python
# -*- coding: utf-8 -*-

""" Скачать последние 5 цитат баш.има и распечатать на консоль. """

import re
import urllib2

def DownloadBashQuotes(num_quotes=None):
  """ Тут неплохо было бы написать пару ласковых, типа хелп.
 
    num_quotes - максимальное количество цитат или None
  """
  opener = urllib2.build_opener()
  opener.addheaders = [('User-agent', 'Mozilla/5.0')]  # Привет админам bash.im!
  response = opener.open('http://bash.im').read()
  response = response.decode('cp1251')

  regexp = re.compile(u'<a href=[^<>]*>([^<>]*)</a>*\s*</div>\s*'
                 '<div[^<>]*>([^<>]*<br>[^<>]*)</div>')
  matches = regexp.findall(response)
  if num_quotes:
    matches = matches[:num_quotes]
  quotes = ["\n".join(m) for m in matches]

  # TODO: built-in function for that?
  quotes = [re.sub('<br>', '\n', s)  for s in quotes]
  quotes = [re.sub('&quot;', '"', s) for s in quotes]
  return quotes

if __name__ == "__main__":
  quotes = DownloadBashQuotes(5)
  print "\n----------------------------------------\n".join(quotes)
  print "----------------------------------------"
  print "Total: %d quote(s)" % len(cites)
