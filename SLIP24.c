//SLIP - 24
//Q.1
#include<stdio.h>

#define INF 999

int main(){
    int n,i,j,k;
    int cost[10][10];

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("Enter cost matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&cost[i][j]);
        }
    }

    // Floyd Warshall Algorithm
    for(k=0;k<n;k++){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                if(cost[i][k] + cost[k][j] < cost[i][j]){
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
            }
        }
    }

    printf("\nShortest Path Matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d ",cost[i][j]);
        }
        printf("\n");
    }

    return 0;
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Department (
 dno INT PRIMARY KEY,
 dname VARCHAR(20),
 city VARCHAR(20)
);

CREATE TABLE Employee (
 eno INT PRIMARY KEY,
 ename VARCHAR(20),
 salary MONEY,
 dno INT REFERENCES Department(dno)
);

//INSERT VALUES 

INSERT INTO Department VALUES
(1,'HR','Pune'),
(2,'IT','Mumbai');

INSERT INTO Employee VALUES
(101,'Om',50000,1),
(102,'Amit',60000,1),
(103,'Ravi',70000,2);
//TRIGGER

CREATE OR REPLACE FUNCTION emp_insert_msg()
RETURNS trigger AS $$
BEGIN
 RAISE NOTICE 'Employee record inserted successfully';
 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_employee
AFTER INSERT ON Employee
FOR EACH ROW
EXECUTE FUNCTION emp_insert_msg();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE even_n(n INT)
AS $$
DECLARE
 i INT := 2;
 count INT := 0;
BEGIN
 WHILE count < n LOOP
  RAISE NOTICE '%', i;
  i := i + 2;
  count := count + 1;
 END LOOP;
END;
$$ LANGUAGE plpgsql;
