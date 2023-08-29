# Mysql-C
Program in C about connection between C and Mysql

# Requeriments
 sudo apt-get install gcc
 sudo apt-get install mysql-server

 sudo apt-get install libmysqlclient-dev
 sudo apt-get install default-libmysqlclient-dev


# Compilation instructions
 gcc -o output $(mysql_config --cflags) Connection.c $(mysql_config --libs)