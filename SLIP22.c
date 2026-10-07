//SLIP - 22
//Q.1
#include <stdio.h>
#define MAX 10

int main(){
    int adj[MAX][MAX], n,e,i,j,v1,v2;

    printf("Enter vertices: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            adj[i][j]=0;

    printf("Enter edges: ");
    scanf("%d",&e);

    for(i=0;i<e;i++){
        scanf("%d %d",&v1,&v2);
        adj[v1][v2]=1;
        adj[v2][v1]=1;
    }

    printf("Adjacency Matrix:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%d ",adj[i][j]);
        printf("\n");
    }
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE Project (
 pno INT PRIMARY KEY,
 pname CHAR(30) NOT NULL,
 ptype CHAR(20),
 duration INT CHECK (duration > 0)
);

CREATE TABLE Employee (
 eno INT PRIMARY KEY,
 ename CHAR(20),
 qualification CHAR(15),
 joining_date DATE
);

-- M-M RELATION
CREATE TABLE Project_Employee (
 pno INT REFERENCES Project(pno),
 eno INT REFERENCES Employee(eno),
 start_date DATE,
 no_of_hours_worked INT,
 PRIMARY KEY(pno, eno)
);

//INSERT VALUES 

INSERT INTO Project VALUES
(1,'AI System','Software',12),
(2,'Web App','IT',6);

INSERT INTO Employee VALUES
(101,'Om','BSc','2022-01-01'),
(102,'Amit','MSc','2021-05-10');

INSERT INTO Project_Employee VALUES
(1,101,'2023-01-01',100),
(2,101,'2023-02-01',80),
(2,102,'2023-03-01',60);

//FUNCTION

CREATE OR REPLACE FUNCTION count_projects(emp_no INT)
RETURNS INT
AS $$
DECLARE cnt INT;
BEGIN
 SELECT COUNT(*) INTO cnt
 FROM Project_Employee
 WHERE eno = emp_no;

 RETURN cnt;
END;
$$ LANGUAGE plpgsql;
