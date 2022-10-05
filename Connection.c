#include<stdio.h>
#include<mysql/mysql.h>
#include<stdlib.h>
#include<time.h>

static char *host = "localhost";
static char *user = "root";
static char *pass = "Cobain1234..";
static char *dbname = "employees";
static char *unix_socket = NULL;


unsigned int port = 3306;
unsigned int flag = 0;

struct tm * timeinfo; 

struct Date
{
   int day, month, year;
};
 

struct Employee
{
   int emp_no;
   struct Date date;
   char first_name[100];
   char last_name[100];
   char gender[1];
   struct Date hire;
};
 


MYSQL * initialize_connection()
{
  
  MYSQL *conn;
  conn = mysql_init(NULL);

  if(!(mysql_real_connect(conn, host, user, pass, dbname, port, unix_socket, flag)))
  {
	printf("\nError: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
  }

  printf("\nINFO:: Connection Successfull!\n\n");
  return conn;
}

int get_max_code()
{
  MYSQL *conn = initialize_connection();
  MYSQL_RES *res;
  MYSQL_ROW row;

  int max_code;

  if(!(mysql_query(conn, "SELECT MAX(emp_no) FROM employees"))){
     
    res = mysql_store_result(conn);
    while(row = mysql_fetch_row(res))
    {
      max_code = atoi(row[0]);
    }
    
    mysql_free_result(res);
  }
  
  else max_code = -4;
  
  mysql_close(conn);
  return max_code;
}


void insert_employee()
{
  
  struct Employee emp;

  emp.hire.year = timeinfo->tm_year+1900;
  emp.hire.month = timeinfo->tm_mon+1;
  emp.hire.day = timeinfo->tm_mday;

  emp.emp_no = get_max_code() + 1;

  MYSQL *conn = initialize_connection();

  printf("\nEmployee number: %d ", emp.emp_no);

  printf("\nName: ");
  scanf("%s", &emp.first_name);
  
  printf("\nLast name: ");
  scanf("%s", &emp.last_name);

  printf("\nBirth date (dd/mm/yyyy): ");
  scanf("%d/%d/%d", &emp.date.day, &emp.date.month, &emp.date.year);

  printf("\nInsert gender (M/F): ");
  scanf("%s", &emp.gender);
  
  
  printf("\nRecord to insert:\n");
  printf("\nNumber: %d\n", emp.emp_no);
  printf("\nFirst Name: %s\n", emp.first_name);
  printf("\nLast Name: %s\n", emp.last_name);
  printf("\nGender: %s\n", emp.gender);
  printf("\nBirth date: %d/%d/%d", emp.date.day, emp.date.month, emp.date.year);
  printf("\nDate hire: %d/%d/%d", emp.hire.day, emp.hire.month, emp.hire.year);
  
  char query[255];
  sprintf( query, "INSERT INTO employees VALUES (%d,'%d%02d%02d','%s','%s','%s','%d%02d%02d')", emp.emp_no,emp.date.year,emp.date.month,emp.date.day,emp.first_name, emp.last_name, emp.gender, emp.hire.year,emp.hire.month,emp.hire.day);

mysql_query(conn, query);
printf("\nEmployee %d inserted sucessfully!", emp.emp_no);
mysql_close(conn);
 

  
 
}

void list_employees()
{
  MYSQL *conn = initialize_connection();
  MYSQL_RES *res;
  MYSQL_ROW row;  
  
  mysql_query(conn, "SELECT * FROM employees ORDER BY hire_date DESC LIMIT 20;");

  res = mysql_store_result(conn);
  int count = 0;
  printf("| %s| | %s | | %s\t|| %s\t |\n", "emp_no", "birth_date", "first_name", "last_name");
  while(row = mysql_fetch_row(res))
  {
    count++;
    printf("| %s | | %s | | %s\t|| %s\t |\n", row[0], row[1], row[2], row[3]);
  }

  printf("\nRows: %d",count);

  mysql_free_result(res);
  mysql_close(conn);
  	
}


void show_menu()
{
  int option = 0;
  
  printf("\n\n");
  printf("\n1- Insert employee");
  printf("\n2- Delete employee");
  printf("\n3- List employees");
  printf("\nOption: ");
  scanf("%d", &option);
  
  printf("\n");
  system("clear");
  switch(option)
  {
    case 1:
	insert_employee();
	break;
    case 2:
	break;
    case 3:
	list_employees();
	break;
    default:
	printf("Error! Invalid option\n");
	break;
  }
	
   printf("\n");
   show_menu();
}



int main(){

 time_t my_time;
 
 time (&my_time);
 timeinfo = localtime (&my_time);

 show_menu();
 return 1;
}



