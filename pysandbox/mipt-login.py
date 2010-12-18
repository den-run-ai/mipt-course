#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2010, Nikita Kazeev with special thanks to
# Timur Iskhodzhanov
# Alexander Travov
# Alex Bochkarev
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>

# Description:
# A simple script for authorization in the mipt network
# Wrote for login page present at 12 December, 2010

from urllib import urlopen
from hashlib import md5
import re
from sys import stderr
import gnomekeyring as gk
from glib import set_application_name
set_application_name("Mipt-telecom login agent")


def create_pass(login, password):
    gk.item_create_sync("login", gk.ITEM_GENERIC_SECRET,
                        "Mipt telcom account", {"username": login},
                        password, True)


def get_creditals():
    item_keys = gk.list_item_ids_sync("login")
    for key in item_keys:
        item_info = gk.item_get_info_sync("login", key)
        if (item_info.get_display_name() == "Mipt telcom account"):
            return (gk.item_get_attributes_sync("login", key)["username"],
                    item_info.get_secret())
    return None


login_page_url = "http://login.telecom.mipt.ru/"
try:
    login_page = urlopen(login_page_url)
    login_page = login_page.read()
except:
    stderr.write("Error while accessing login page.\
                  Likely to be a networking problem.\n")
    exit(-1)

try:
    found = re.search('(?<=<INPUT type=hidden name=chalangeack value=)\w*',
                      login_page)
    chalangeack = found.group(0)
except:
    stderr.write("Error while manipulating login page.\
                 Maybe its format has changed.\n")
    exit(-2)

if not gk.is_available():
    print "Error with the keyring daemon."
    exit(-100)

if not 'login' in gk.list_keyring_names_sync():
    print "Error: no 'login' keyering. Edit the sources to select\
           another keyring."
    exit(-101)

creditals = get_creditals()
if creditals == None:
    print "No login data found"
    from getpass import getpass
    login = getpass("Login: ")
    password = getpass()
    creditals = (login, password)
    save = raw_input("Type YES to save them: ")
    if save == 'YES':
        create_pass(login, password)
else:
    login = creditals[0]
    password = creditals[1]

password_hash = md5(chalangeack + password).hexdigest()

res_page = urlopen(login_page_url + "bin/login.cgi?chalangeack=" +
                chalangeack + "&login=" + login + "&password=" + password_hash)
res_page = res_page.read()

if (re.search("Авторизация прошла успешно.",
    res_page) == None):
    stderr.write("Invalid response. Authorization is almost certain \
                  incomplete. Probably invalid creditals.\n")
    exit(-3)
else:
    print "Success"
    exit(0)
