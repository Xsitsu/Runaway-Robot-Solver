#!/usr/bin/python
import urllib2

URL = 'http://www.hacker.org/runaway/index.php'
USER = 'CantDecideOnABot'
PASS = 'password' # I removed this line to post to github

FILE = open("solution.dat", "r");
path = FILE.read()
resp = urllib2.urlopen(URL + '?name=' + USER + '&password=' + PASS + '&path=' + path).read()

FILE.close()
