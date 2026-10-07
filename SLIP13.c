//SLIP - 13
//Q.1
#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct node{
    int vertex;
    struct node* next;
};

struct node* adj[MAX];
int indegree[MAX],outdegree[MAX];

struct node* createNode(int v){
    struct node* n=(struct node*)malloc(sizeof(struct node));
    n->vertex=v;
    n->next=NULL;
    return n;
}

void addEdge(int u,int v){
    struct node* n=createNode(v);
    n->next=adj[u];
    adj[u]=n;

    outdegree[u]++;
    indegree[v]++;
}

void display(int n){
    for(int i=0;i<n;i++){
        printf("Vertex %d: ",i);
        struct node* temp=adj[i];
        while(temp){
            printf("%d -> ",temp->vertex);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

int main(){
    int n,e,u,v,i;

    scanf("%d",&n);

    for(i=0;i<n;i++){
        adj[i]=NULL;
        indegree[i]=outdegree[i]=0;
    }

    scanf("%d",&e);

    for(i=0;i<e;i++){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
    }

    display(n);

    printf("Vertex\tIndegree\tOutdegree\tTotal\n");
    for(i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n",i,indegree[i],outdegree[i],
               indegree[i]+outdegree[i]);
    }
}

//Q.2 - DBMS
// DBMS
//CREATE TABLE 

CREATE TABLE ROUTE (
 route_no INT PRIMARY KEY,
 source CHAR(20),
 destination CHAR(20),
 no_of_stations INT
);

CREATE TABLE BUS (
 bus_no INT PRIMARY KEY,
 capacity INT NOT NULL,
 depot_name VARCHAR(20),
 route_no INT REFERENCES ROUTE(route_no)
);

CREATE TABLE DRIVER (
 driver_no INT PRIMARY KEY,
 driver_name CHAR(20),
 license_no INT UNIQUE,
 address CHAR(20),
 d_age INT,
 salary FLOAT
);

-- M-M RELATION
CREATE TABLE BUS_DRIVER (
 bus_no INT REFERENCES BUS(bus_no),
 driver_no INT REFERENCES DRIVER(driver_no),
 duty_date DATE,
 shift INT CHECK (shift IN (1,2)),
 PRIMARY KEY(bus_no, driver_no)
);

//INSERT VALUES 
INSERT INTO ROUTE VALUES
(1,'Pune','Mumbai',10),
(2,'Mumbai','Nashik',8);

INSERT INTO BUS VALUES
(101,50,'Pune',1),
(102,40,'Mumbai',2);

INSERT INTO DRIVER VALUES
(201,'Ramesh',1111,'Pune',30,20000),
(202,'Suresh',2222,'Mumbai',45,18000);

INSERT INTO BUS_DRIVER VALUES
(101,201,'2024-01-01',1),
(102,202,'2024-01-02',2);
//TRIGGER
CREATE OR REPLACE FUNCTION check_age()
RETURNS trigger AS $$
BEGIN
 IF NEW.d_age < 18 OR NEW.d_age > 50 THEN
  RAISE EXCEPTION 'Invalid Entry';
 END IF;

 RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_driver
BEFORE INSERT ON DRIVER
FOR EACH ROW
EXECUTE FUNCTION check_age();

//Q.2 - PROCEDURE DBMS 
CREATE OR REPLACE PROCEDURE odd_numbers(n INT)
AS $$
DECLARE
 i INT := 1;
BEGIN
 WHILE i <= n LOOP
  IF i % 2 != 0 THEN
   RAISE NOTICE '%', i;
  END IF;
  i := i + 1;
 END LOOP;
END;
$$ LANGUAGE plpgsql;
