#! /usr/bin/python3
import os
for key in list(os.environ.keys()):
 if (key[0] == 'H' and key[1] == 'B'):
  print(os.environ[key])

