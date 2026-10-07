//SLIP - 20
//Q.1
#include <stdio.h>

int queue[20], front = -1, rear = -1;
int visited[20];

void enqueue(int v){
    if(front == -1) front = 0;
    queue[++rear] = v;
}

int dequeue(){
    return queue[front++];
}

void BFS(int adj[10][10], int n, int start){
    for(int i=0;i<n;i++)
        visited[i] = 0;

    enqueue(start);
    visited[start] = 1;

    while(front <= rear){
        int v = dequeue();
        printf("%d ", v);

        for(int i=0;i<n;i++){
            if(adj[v][i] == 1 && visited[i] == 0){
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main(){
    int n, adj[10][10], start;

    printf("Enter number of vertices: ");
    scanf("%d",&n);

    printf("Enter adjacency matrix:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&adj[i][j]);

    printf("Enter starting vertex: ");
    scanf("%d",&start);

    printf("BFS Traversal: ");
    BFS(adj,n,start);

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
(102,'Amit',70000,1),
(103,'Ravi',60000,2);
//FUNCTION COUNT EMPLOYES IN DEPT

CREATE OR REPLACE FUNCTION count_emp(did INT)
RETURNS INT AS $$
DECLARE c INT;
BEGIN
 SELECT COUNT(*) INTO c
 FROM Emp_Department
 WHERE dno = did;

 RETURN c;
END;
$$ LANGUAGE plpgsql;

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE table_num(n INT)
AS $$
DECLARE i INT := 1;
BEGIN
 WHILE i <= 10 LOOP
  RAISE NOTICE '% x % = %', n, i, n*i;
  i := i + 1;
 END LOOP;
END;
$$ LANGUAGE plpgsql;
