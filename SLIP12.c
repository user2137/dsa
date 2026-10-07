//SLIP - 12
//Q.1

#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct node{
    int vertex;
    struct node* next;
};

struct node* adj[MAX];
int visited[MAX];

struct node* createNode(int v){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u,int v){
    struct node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = createNode(u);
    newNode->next = adj[v];
    adj[v] = newNode;
}

void DFS(int v){
    struct node* temp;
    visited[v]=1;
    printf("%d ",v);

    temp=adj[v];
    while(temp){
        if(!visited[temp->vertex])
            DFS(temp->vertex);
        temp=temp->next;
    }
}

int main(){
    int n,e,u,v,start,i;

    printf("Enter vertices: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        adj[i]=NULL;
        visited[i]=0;
    }

    printf("Enter edges: ");
    scanf("%d",&e);

    for(i=0;i<e;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }

    printf("Enter start: ");
    scanf("%d",&start);

    DFS(start);
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE PROJECT (
 pno INT PRIMARY KEY,
 p_name CHAR(30),
 ptype CHAR(20),
 duration INT
);

CREATE TABLE EMPLOYEE (
 eno INT PRIMARY KEY,
 e_name CHAR(20),
 qualification CHAR(15),
 joindate DATE
);

-- M-M RELATION
CREATE TABLE PROJECT_EMPLOYEE (
 pno INT REFERENCES PROJECT(pno),
 eno INT REFERENCES EMPLOYEE(eno),
 start_date DATE,
 no_of_hours_worked INT,
 PRIMARY KEY(pno, eno)
);

//INSERT VALUES 
INSERT INTO PROJECT VALUES
(1,'AI System','Software',12),
(2,'Web App','IT',6);

INSERT INTO EMPLOYEE VALUES
(101,'Om','BSc','2022-01-01'),
(102,'Amit','MSc','2021-05-10');

INSERT INTO PROJECT_EMPLOYEE VALUES
(1,101,'2023-01-01',100),
(2,102,'2023-02-01',80);

//TRIGGER
CREATE OR REPLACE FUNCTION check_duration()
RETURNS trigger AS $$
BEGIN
 IF NEW.duration <= 0 THEN
  RAISE EXCEPTION 'Duration must be greater than zero';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_project
BEFORE INSERT ON PROJECT
FOR EACH ROW
EXECUTE FUNCTION check_duration();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE count_odd(m INT, n INT)
AS $$
DECLARE
 i INT;
 cnt INT := 0;
BEGIN
 FOR i IN m..n LOOP
  IF i % 2 != 0 THEN
   cnt := cnt + 1;
  END IF;
 END LOOP;

 RAISE NOTICE 'Total odd numbers = %', cnt;
END;
$$ LANGUAGE plpgsql;
