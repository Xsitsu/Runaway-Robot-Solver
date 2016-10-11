#!/usr/bin/python
import urllib2

URL = 'http://www.hacker.org/runaway/index.php'
USER = 'CantDecideOnABot'
PASS = 'password' # I removed this line to post to github

FILE = open("board.dat", "w");

data = urllib2.urlopen(URL + '?name=' + USER + '&password=' + PASS).read()

varpos = data.find('FlashVars=\"') + 11
varposend = data.find('\"', varpos)

variable_string = data[varpos:varposend]

variable_list = {}

var_read_start = variable_string.find('=')
var_count = 0

while (var_read_start != -1):
    var_read_start = var_read_start + 1
    
    var_end = variable_string.find('&', var_read_start)
    if (var_end != -1):
        variable_list[var_count] = variable_string[var_read_start:var_end]
    else:
        variable_list[var_count] = variable_string[var_read_start:]
    
    var_count = var_count + 1
    var_read_start = variable_string.find('=', var_read_start)

print "Read and saved data!"
for i in range(0, var_count):
    print >>FILE, variable_list[i]


FILE.close()
